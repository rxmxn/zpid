#ifndef PUERTOSERIE_H
#define PUERTOSERIE_H

#include <QDebug>
#include <math.h>
#include <QElapsedTimer>

#include "rs232.h"

#include <pidprofesional.h>

#define buffer_size 10
#define Tx_size 10

//COMANDOS
#define conectar '!'
#define desconectar 'Q'
#define inicio_trama '<'
//CONTROL
#define Tx 'X'
#define estado_pid 'O'
#define estado_pid_reenvio 'o'
#define end_of_Tx 'E'
#define clc '~'
#define cambiar_modo 'M'
//FUZZY
#define estado_fuzzy 'F'
#define estado_fuzzy_reenvio 'f'
//SUPERVISION
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

enum Etapa{Inicio,Supervision,Control};
enum Supervision_error{_WDT,_POR,_BOR,_caracter_no_valido};

class PuertoSerie
{
public:
    PuertoSerie();
    ~PuertoSerie();
    bool Data_Received();
    void Init_conection();
    void mySendBYTE(unsigned char);
    bool Conected();
    void change_BaudRate(int selection);
    int cantidad_muestras();  //cantidad de muestras que se han recibido
    void ActualizarYU();
    float get_number(unsigned char*);
    PIDprofesional* myPID();    //para poder acceder al PID e interactuar con el
    void Parameter_changed();
    void Reference_changed();
    void enviar_Ref();
    void enviar_Param();
    bool get_YUact(){return YUact;}
    bool get_PARAMact(){return PARAMact;}
    void setOFF_YUact(){YUact=false;}
    void setOFF_PARAMact(){PARAMact=false;}
    void setON_PARAMact(){PARAMact=true;}
    Supervision_error get_error(){return sup_error;}
    void ActualizarAll();
    unsigned char* get_bufferRx(){return bufferRx;}
    void send_buffer(unsigned char buffer[],int comando,int tamano_buffer);
    Etapa get_etapa(){return etapa;}
    void set_etapa(Etapa _etapa){etapa=_etapa;}
    void set_bufferTx(unsigned char buffer[]);
    void set_icounter(int num_bytes_Tx){icounter=num_bytes_Tx;}
    int get_muestras(){return muestras;}
    bool get_Ract(){return Ract;}
    void setOFF_Ract(){Ract=false;}
    void set_CURVEact(bool ON){CURVEact=ON;}
    bool get_CURVEact(){return CURVEact;}
    void setOFF_Tcact(){Tcact=false;}
    bool get_Tcact(){return Tcact;}
    void ActualizarTc();
    void set_COM(int puerto);
    bool get_ErrorRx(){return ErrorRx;}
    void set_ErrorRx_false(){ErrorRx=false;}
    bool get_fTSupervision(){return fTSupervision;}
    void set_fTSupervision(bool _fTSup){fTSupervision=_fTSup;}
    bool get_data_sent(){return data_sent;}
    bool get_T_over(){return T_over;}
    void set_data_sent(bool flag){data_sent=flag;}
    void set_T_over(bool flag){T_over=flag;}
    void salvar_muestras_files();
    void load_yf(QTextEdit &textEdit);
    void load_e(QTextEdit &textEdit);
    void load_u(QTextEdit &textEdit);
    void load_tiempo(QTextEdit &textEdit);
    void reset_muestras();
    void comprobando_files_existentes();
    void dar_enter_por_cambio_ref();

private:
    int n;  //# of bytes received
    int BaudRate;
    unsigned char bufferRx[buffer_size+1],bufferTx[buffer_size+1];
    Etapa etapa;
    bool conectado;
    int muestras;   //cantidad de muestras que se han recibido
    unsigned char bAll[buffer_size*12+1],bYU[buffer_size*2+1],bTC[buffer_size+1];
    unsigned char bR[buffer_size+1],bKp[buffer_size+1],bKi[buffer_size+1],bKd[buffer_size+1],bKpi[buffer_size+1];
    unsigned char bF[buffer_size+1],bTc[buffer_size+1],bTP[buffer_size+1];
    unsigned char bunivPI[buffer_size+1],bunivPD[buffer_size+1];
    unsigned char bstepPI[buffer_size+1],bstepPD[buffer_size+1];
    unsigned char bY[buffer_size+1],bU[buffer_size+1];
    PIDprofesional PID;
    bool fPARAM_change;  //true cuando cambia en el MainWindows
    bool fREF_change;   //true cuando cambia en el MainWindows
    Supervision_error sup_error;
    int icounter;   //para llevar el numero de bytes Tx
    bool fErrorRx;
    int COM;

    //FLAGS para actualizar el MainWindows
    bool YUact; //act de actualizado      
    bool PARAMact;  //se actualizan cuando se recibe un nuevo valor por puerto serie
    bool Ract;
    bool CURVEact; //se actualiza en xcontrolador cuando el usuario cambia el tipo de procesamiento
    bool Tcact;
    bool ErrorRx;
    bool fTSupervision;

    //Flag para revisar error
    bool data_sent;
    bool T_over;

    QElapsedTimer timer;
    QFile *yf_file,*u_file,*e_file,*T_file;
};

#endif // PUERTOSERIE_H
