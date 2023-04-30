/////////////////////////////*DIRECTIVES*///////////////////////////////////////
#include "18f4550.h"
#fuses HS,NOWDT,NOBROWNOUT,NOPUT,NOLVP,PLL5,CPUDIV1
#device ADC=10 //number of bits the ADC should return
#device WRITE_EEPROM=ASYNC//DON't use write_eeprom from both ISR and outside ISR
#device HIGH_INTS=TRUE
#use delay(clock=20000000)
#use rs232(UART1,BAUD=9600,XMIT=PIN_C6,RCV=PIN_C7,ERRORS)//,DISABLE_INTS)//,TIMEOUT=100)

//Inicializando ROM 
#ROM 0x00F00000={0x7A87,0x0000, 0x1686,0x0000, 0x3081,0x0000, 0x0001, 0x01F4,\
								0x0003, 0x0000, 0x0007, 0x0003, 0x2E7C,0x7B14, 0x007C,0x0000,\
								0x0C7E,0xCDCC, 0x0258, 0x0014, 0x0006, 0x1687,0x0000,\
								0x2082,0x0000, 0x0C7E,0xCDCC, 0x0000, 0x0000, 0x0000} //inicializando 0-57 de la EEPROM 
/*
  							{Kp:LSB,MSB,    Ki:LSB,MSB,    Kd:LSB,MSB,    Tc,     rf,\
								cantM,  BR,     PWMf,   TP,     Kp_F:LSB,MSB,  Ki_F:LSB,MSB,\
								Kd_F:LSB,MSB,  univ_PD, univ_PI, Tc_F, stepPD:LSB,MSB,\
								stepPI:LSB,MSB, Kpi_F:LSB,MSB, fPWM1, ADselected, TipoAccion}
*/

//RDA es de alta prioridad								
#priority RDA,TIMER0,TIMER1

#include "myEEPROM.c" 

#include "stdlib.h" 
#include "input.c" 

//Mi libreria del controlador Fuzzy
#include "PID.c"

//para almacenar en  EEPROM: kp,ki,kd,tc,rf(0-1023)
#define address_Kp 0    //como son float ocupan 32 bits (4 bytes)
#define address_Ki 4
#define address_Kd 8
#define address_Tc 12    //2 bytes
#define address_rf 14   //rf(0-1023->14,15)
#define address_cantM 16  //1 byte
#define address_BaudRate 18  //1 byte
#define address_PWMf 20  //1 byte (frecuencia del PWM para calcular el registro PR2)
#define address_tipoProcesamiento 22 //1 byte
#define address_Kp_Fuzzy 24  //4 bytes
#define address_Ki_Fuzzy 28  //4 bytes
#define address_Kd_Fuzzy 32  //4 bytes
#define address_universoPD 36  //2 bytes
#define address_universoPI 38  //2 bytes
#define address_Tc_Fuzzy 40  //2 bytes
#define address_stepPD 42  //4 bytes
#define address_stepPI 46  //4 bytes
#define address_Kpi_Fuzzy 50  //4 bytes
#define address_fPWM1 54  //1 byte
#define address_ADselected 55  //1 byte
#define address_TipoAccion 56  //1 byte
 
#define Ry 1023  // ymax=1023; ymin=0; rango_Tx(A/D): Ry=ymax-ymin; 

#define conv_tiempo 0.0000016 //4*50n*8 

#define buffer_size 10

#define automatico 0
#define manual 1

#define supervision 0
#define control 1

#define directa 0
#define inversa 1

//COMANDOS
#define conectar '!'
#define desconectar 'Q'
//CONTROL
#define Tx 'X'
#define estado_pid 'O'
#define estado_pid_reenvio 'o'
#define end_of_Tx 'E'
//#define clc '~'
#define cambiar_modo 'M'
//FUZZY
#define estado_fuzzy 'F'
#define estado_fuzzy_reenvio 'f'
//Supervision
#define estado_supervision 'S'
#define tipo_de_modulo '*'
#define entrada_analogica 'A'
#define entrada_digital 'D'
#define ciclo_util_PWM 'P'
#define salida_digital 'T'
#define escritura_configuracion 'C'
#define lectura_configuracion 'L'
//Avisos de RESET
#define WDT '$'
#define POR '%'
#define BOR '#'
//Aviso por recepcion de caracteres no validos
#define caracter_no_valido '?'
//Reset por software
#define RESET 'R'

/////////////////////////////*GLOBAL VARIABLES*/////////////////////////////////

/*
  Significado de los coeficientes:
    g = guardar
    t = temporal
    f = flag o float
*/

//PID Profesional
typedef struct 
{
  float Kp,Kd,Ki; 
  int16 Tc;  //es de 16bits para procesos lentos
}Parametros;

typedef struct 
{
	Parametros param,paramTemp;
  signed int16 u;
	float en;
	float Integral,Integral_1;
	float Derivativo;
	float Proporcional;  
}PID;

//Fuzzy
typedef struct 
{
	float Kp,Kd,Ki,Kpi; //Kp->PD, Kpi->PI
	signed int16 universo_duPI_min,universo_duPI_max;
	signed int16 universo_uPD_min,universo_uPD_max;
	float stepPD,stepPI;
	int16 Tc;  //es de 16bits para procesos lentos (en este caso no influye en el algoritmo)
	BOOLEAN guniversoPI,guniversoPD;
	BOOLEAN gstepPI,gstepPD;
}FuzzyParametros;

typedef struct 
{
  FuzzyParametros fparam,fparamTemp;
	double u_PI,du_PI,u_PI_1,u_PD,u;  
	float error,error_1,derror;
	float e_P,de_D,e_I,de_P;  //d->variacion
}FUZZY;

#case  //Will cause the compiler to be case sensitive
PID pid;
FUZZY fuzzy;

signed int16 rf,yf,yf_1;  //son signed para procurar compatibilidad al calcular en(error nominal)
BOOLEAN modo;
int8 seleccionBR,seleccionPWMf;  //variable de seleccion del Baud Rate
BOOLEAN fuzzy_selected;
BOOLEAN pid_selected;
BOOLEAN grf,gBR,gPWMf,gTP;  //TP->tipo de procesamiento
BOOLEAN fprintPIDini,fprintFUZZYini,fprintTc,fprint;
BOOLEAN gk;
BOOLEAN gTc; //Para guardar en EEPROM
unsigned int16 tmr1,tmr0;
int16 count_timer;
BOOLEAN fPWM1;  //true->PWM1 seleccionado, false->PWM2 seleccionado
int ADselected;
BOOLEAN gPWMseleccion,gADseleccion;
int16 Tsupervision;
BOOLEAN fTipoAccion,gTipoAccion;

//Filtro promedio	
int8 cantM;  //cantidad de muestras para el filtro promedio	
int16 promM[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  //promedio de las muestras
int8 tipo_procesamiento;
BOOLEAN fcantM;   //depende del tipo de procesamiento
BOOLEAN gcantM;

//Case entrada_analogica
BOOLEAN fentrada_analogica;
int8 analog_value;

//Puerto serie
BOOLEAN fFirst_time_pid;
BOOLEAN fFirst_time_fuzzy;
char *buffer;
char bRx[buffer_size+1]={0,0,0,0,0,0,0,0,0,0,0};
char bufferRx[buffer_size+1]={0,0,0,0,0,0,0,0,0,0,0};
float fnumber;
BOOLEAN tgk,tgcantM,tgTc;
int tcantM;
int16 tu;
BOOLEAN fRx=FALSE;
char bRxSelect,bufferRxSelect;

/////////////////////////////*STATEMENTS*///////////////////////////////////////
#separate int16 ADC_Read(int8);
#separate int16 promedio(int16);
#separate void setup(void);
#separate void initialize(void);
#separate void set_PWM_period(void);
#separate void algoritmo_PID(void);
#separate void algoritmo_Fuzzy(void);
#separate void enable_timer0(BOOLEAN);
#separate void enable_timer1(BOOLEAN);
#separate void initialize_Fuzzy(void);
#separate void set_PWM(int16);
#separate int16 calc_tmr(int16);
#separate void print_enabled(void);
//Puerto serie
#separate void Tx_function(void);
#separate void estado_pid_function(void);
#separate void estado_fuzzy_function(void);
#separate void end_of_Tx_function(void);
#separate void escritura_configuracion_function(void);
#separate void entrada_digital_function(void);
#separate void ciclo_util_PWM_function(void);
#separate void salida_digital_function(void);
#separate void lectura_configuracion_function(void);
#separate void saveToEEPROM(void);
#separate void printRS232(void);
#separate void analizar_Rx(char);
#separate void guardar_bufferRx(void);

