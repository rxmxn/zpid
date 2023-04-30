#include "SerialPort.c"

/////////////////////////////*FUNCTIONS*////////////////////////////////////////

#INT_default
void default_interrupt()
{
/*
	Esta interrupcion se activa cuando se resetea el micro,
	por lo que hay que deshabilitarla.
*/
	if(interrupt_active(INT_USB))
		disable_interrupts(INT_USB); 
}

#INT_TIMER0 
void TIMER0() 
{	
  set_timer0(tmr0);
     
	algoritmo_PID();
	
	print_enabled();
}

#int_TIMER1 
void TIMER1()
{  
	int16 contms=0;
	float contms1=0,contms2=0;

	set_timer1(tmr1);  
	
	contms1=get_timer1(); 			
	algoritmo_Fuzzy();			
	contms2=get_timer1();
	
	if(contms1 > contms2)
		contms = (contms2 + 65536 - contms1) * conv_tiempo * 100;
	else
		contms = (contms2 - contms1) * conv_tiempo * 100;
				
	if((contms+2) > fuzzy.fparam.Tc) 
	{
		fuzzy.fparam.Tc=contms+2;
		fuzzy.fparamTemp.Tc=fuzzy.fparam.Tc;
		tmr1 = calc_tmr(fuzzy.fparam.Tc);
		fprintTc = TRUE;
		enable_timer1(FALSE);
	}	
	
	print_enabled();
}

#separate
void print_enabled()
{
	if(!count_timer)        
  {  
		count_timer=Tsupervision; 

		fprint = TRUE;
  }
  else count_timer--;
}

#separate
int16 ADC_Read(int8 pin)
{
  set_adc_channel(pin);
  delay_us(10);
  return read_adc();
}

#separate
int16 promedio(int16 valor)  //filto promedio para las muestras
{
  int8 i;
  int16 suma=0;
  static int8 cont=0;
   
  if(cantM!=0 && fcantM==TRUE)
  {  
    promM[cont++] = valor;
  
    for(i=0;i<cantM;i++)
      suma+=promM[i];
      
    if(cont==cantM)
      cont=0;
      
    return suma/cantM;
  }
  else
    return valor;
}

#separate
void set_PWM_period()
{
	//Resolucion maxima = 10bits
  switch(seleccionPWMf)
  {
    case 0: setup_timer_2(T2_DIV_BY_16,255,1); break;   //1.22KHz [0.82ms] Resolucion=14bits
    case 1: setup_timer_2(T2_DIV_BY_16,127,1); break;   //2.44KHz [0.41ms] Resolucion=13bits
    case 2: setup_timer_2(T2_DIV_BY_16,63,1); break;  //4.88KHz [0.20ms] Resolucion=12bits
    case 3: setup_timer_2(T2_DIV_BY_4,170,1); break;  //7.32KHz [0.14ms] Resolucion=11.42bits
    case 4: setup_timer_2(T2_DIV_BY_4,127,1); break;  //9.76KHz [0.10ms] Resolucion=11bits
    case 5: setup_timer_2(T2_DIV_BY_4,101,1); break;  //12.20KHz [81.9us] Resolucion=10.67bits
    case 6: setup_timer_2(T2_DIV_BY_4,72,1); break;  //17.08KHz [58.5us] Resolucion=10.19bits
    case 7: setup_timer_2(T2_DIV_BY_1,255,1); break;  //19.53KHz [51.2us] Resolucion=10bits
    case 8: setup_timer_2(T2_DIV_BY_1,165,1); break;  //30.12KHz [33.2us] Resolucion=9.37bits
    default: setup_timer_2(T2_DIV_BY_1,255,1); break; //19.53KHz [51.2us] Resolucion=10bits 
	//PR2=(Tpwm/(Tclk*4*T2DIV))-1=255 [Tpwm=1/19.53KHz=51.2us, Tclk=1/20MHz=50ns, T2DIV=1] 
  }
}

#separate 
void setup()
{
//PORTS
  set_tris_a(0x3F);  //0b00111111
  set_tris_b(0xF1);  //0b11110001 
  set_tris_c(0x80);  //0b10000000  
  set_tris_d(0x00); 
  set_tris_e(0x01);  //E0 -> AN5
//ADC
  setup_adc_ports(AN0_TO_AN5|VSS_VDD);
  setup_adc(ADC_CLOCK_INTERNAL); 
//Timer 0                    
  setup_timer_0(RTCC_INTERNAL | RTCC_DIV_8); //RTCC and Timer0 are the same
//  set_timer0(tmr0); //para 10ms : TMR0=65536 - overflow_time/(4*Tosc*prescaler)=59286 [en este caso overflow_time=10ms, Tosc=1/20MHz=50ns, prescaler=8]
  //como TMR0=59286 -> overflow_time=(65536-TMR0)*(4*Tosc*prescaler)=(65536-59286)*(4*50ns*8)=10ms
//  enable_interrupts(INT_TIMER0); 
//Timer 1
  setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);  //104.896 milisegundos maximo
//  set_timer1(tmr1);  //para 100ms : TMR0=65536 - overflow_time/(4*Tosc*prescaler)=3036 [en este caso overflow_time=100ms, Tosc=1/20MHz=50ns, prescaler=8]
  //como TMR1=3036 -> overflow_time=(65536-TMR1)*(4*Tosc*prescaler)=(65536-3036)*(4*50ns*8)=0.1s
//  enable_interrupts(INT_TIMER1);

//INTERRUPTS                      
  enable_interrupts(GLOBAL);  //Permite activarse las interrupciones definidas previamente
	
//UART
  enable_interrupts(INT_RDA);  //Rx via puerto serie
}

#separate
void initialize() 
{  
//Inicializando variables
  pid.Integral_1=0; yf_1=0; 
	fuzzy.u_PI_1=0; fuzzy.error_1=0; 
  fuzzy.fparam.guniversoPI=FALSE; 
	fuzzy.fparam.guniversoPD=FALSE; 
	fuzzy.fparam.gstepPD=FALSE;
	fuzzy.fparam.gstepPI=FALSE;
	
	modo=automatico;
  fuzzy_selected=FALSE;
  pid_selected=FALSE;
  grf=FALSE;gBR=FALSE;gPWMf=FALSE;gTP=FALSE;  //TP->tipo de procesamiento
  fprintPIDini=FALSE;fprintFUZZYini=FALSE;fprintTc=FALSE;fprint = FALSE; 
  gk=FALSE;
  gTc=FALSE; //Para guardar en EEPROM
  gcantM=FALSE;
  fentrada_analogica=FALSE;
  fFirst_time_pid=FALSE;
	fFirst_time_fuzzy=FALSE;
	gPWMseleccion=FALSE;
	gADseleccion=FALSE;
	gTipoAccion=FALSE;
	
	fTipoAccion = directa;
	
	Tsupervision = 1;
	
	ADselected=read_eeprom(address_ADselected);
	fPWM1=read_eeprom(address_fPWM1);  
	
//Cargando de la EEPROM
  pid.param.Kp=read_float_eeprom(address_Kp); 
  pid.param.Kd=read_float_eeprom(address_Kd); 
  pid.param.Ki=read_float_eeprom(address_Ki);
  pid.param.Tc=read_int16_eeprom(address_Tc);

	tmr0 = calc_tmr(pid.param.Tc);
	set_timer1(tmr0);
  
  rf=read_int16_eeprom(address_rf);
  cantM=read_eeprom(address_cantM);
	
	fuzzy.fparam.universo_duPI_max=read_int16_eeprom(address_universoPI);
	fuzzy.fparam.universo_duPI_min=fuzzy.fparam.universo_duPI_max * (-1);
	fuzzy.fparam.universo_uPD_max=read_int16_eeprom(address_universoPD);	
	fuzzy.fparam.universo_uPD_min=fuzzy.fparam.universo_uPD_max * (-1);	
	fuzzy.fparam.Kp=read_float_eeprom(address_Kp_Fuzzy); 
	fuzzy.fparam.Ki=read_float_eeprom(address_Ki_Fuzzy);
  fuzzy.fparam.Kd=read_float_eeprom(address_Kd_Fuzzy); 
	fuzzy.fparam.Kpi=read_float_eeprom(address_Kpi_Fuzzy); 
	fuzzy.fparam.Tc=read_int16_eeprom(address_Tc_Fuzzy); 
	fuzzy.fparam.stepPD=read_float_eeprom(address_stepPD); 
	fuzzy.fparam.stepPI=read_float_eeprom(address_stepPI);

	tmr1 = calc_tmr(fuzzy.fparam.Tc);
	set_timer1(tmr1);
	
	initialize_Fuzzy();
	
	seleccionBR=read_eeprom(address_BaudRate);
  switch(seleccionBR)
  {
    case 0: set_uart_speed(9600); break;
    case 1: set_uart_speed(1200); break;
    case 2: set_uart_speed(2400); break;
    case 3: set_uart_speed(4800); break;
    case 4: set_uart_speed(19200); break;
    case 5: set_uart_speed(28800); break;
    case 6: set_uart_speed(33600); break;
    case 7: set_uart_speed(38400); break;
    default: set_uart_speed(9600); break;
  }
	
	//Tipo de procesamiento
  tipo_procesamiento=read_eeprom(address_tipoProcesamiento);
  switch(tipo_procesamiento)
  {
    case 0: fcantM=FALSE; break;
    case 1: fcantM=TRUE; break;
    case 2: fcantM=FALSE; break;
    case 3: fcantM=TRUE; break;
    default: fcantM=TRUE; break;
  }
      
	//PWM
  seleccionPWMf=read_eeprom(address_PWMf);
  
  set_PWM_period();	//configurando Timer 2 

  setup_ccp1(CCP_PWM);	  
  setup_ccp2(CCP_PWM);
	
  set_pwm1_duty(0);
  set_pwm2_duty(0); 
		
		//Inicializando variables temporales
		pid.paramTemp.Kp = pid.param.Kp;
		pid.paramTemp.Ki = pid.param.Ki;
		pid.paramTemp.Kd = pid.param.Kd;
		pid.paramTemp.Tc = pid.param.Tc;
		tcantM = cantM;
	
		tgk = gk;
		tgTc = gTc;
		tgcantM = gcantM;
		
		fuzzy.fparamTemp.gstepPD = fuzzy.fparam.gstepPD;
		fuzzy.fparamTemp.gstepPI = fuzzy.fparam.gstepPI;
		fuzzy.fparamTemp.guniversoPI = fuzzy.fparam.guniversoPI;
		fuzzy.fparamTemp.guniversoPD = fuzzy.fparam.guniversoPD;
	
		fuzzy.fparamTemp.Kp = fuzzy.fparam.Kp;
		fuzzy.fparamTemp.Ki = fuzzy.fparam.Ki;
		fuzzy.fparamTemp.Kd = fuzzy.fparam.Kd;
		fuzzy.fparamTemp.Kpi = fuzzy.fparam.Kpi;
		fuzzy.fparamTemp.Tc = fuzzy.fparam.Tc;
		fuzzy.fparamTemp.universo_duPI_min = fuzzy.fparam.universo_duPI_min;
		fuzzy.fparamTemp.universo_duPI_max = fuzzy.fparam.universo_duPI_max;
		fuzzy.fparamTemp.universo_uPD_min = fuzzy.fparam.universo_uPD_min;
		fuzzy.fparamTemp.universo_uPD_max = fuzzy.fparam.universo_uPD_max;
		fuzzy.fparamTemp.stepPD = fuzzy.fparam.stepPD;
		fuzzy.fparamTemp.stepPI = fuzzy.fparam.stepPI;
			
//Para iniciar el Software
  putc('!');
}

#separate
int16 calc_tmr(int16 Tc)
{
	return (65536 - (float)(Tc*10)/(conv_tiempo*1000));
}

#separate 
void initialize_Fuzzy()
{
	//A mayor paso mas rapido es el algoritmo pero menos exacto
	initialize_PI_Fuzzy(fuzzy.fparam.universo_duPI_min,  //default=-20
											fuzzy.fparam.universo_duPI_max,  //default=20
											fuzzy.fparam.stepPI);  //default=10											
	initialize_PD_Fuzzy(fuzzy.fparam.universo_uPD_min,  //default=-600
											fuzzy.fparam.universo_uPD_max,  //default=600
											fuzzy.fparam.stepPD);  //default=300
												 
	//Si los valores estan en el rango permisible los parametros no cambiaran
	fuzzy.fparam.universo_duPI_min=PI_salida.min;
	fuzzy.fparam.universo_duPI_max=PI_salida.max;
	fuzzy.fparam.stepPI=PI_salida.step;	
	fuzzy.fparam.universo_uPD_min=PD_salida.min;
	fuzzy.fparam.universo_uPD_max=PD_salida.max;
	fuzzy.fparam.stepPD=PD_salida.step;
}

#separate
int16 filtro_promedio()
{
	return promedio(ADC_Read(ADselected));
}

#separate
void algoritmo_PID()
{
	yf = filtro_promedio();
	
	//Algoritmo PID PROFESIONAL
	if(fTipoAccion==directa)			//Accion Directa
  	pid.en = (float)(rf-yf)/Ry;       
  else													//Accion Inversa
  	pid.en = (float)(yf-rf)/Ry; 

  if(modo==automatico)
  { 
    pid.Integral = pid.Integral_1 + pid.param.Tc*0.01*pid.en*pid.param.Ki;  //Ki=Kp/Ti
    //controlando windup con Int
    if(pid.Integral > 1023)  pid.Integral = 1023;                                                 
     
    pid.Derivativo = pid.param.Kd*(yf-yf_1)/(pid.param.Tc*0.01*Ry);  //Kd=Kp*Td
    
    pid.Proporcional = pid.param.Kp*pid.en;
    
    pid.u = pid.Proporcional - pid.Derivativo + pid.Integral;
      
    //Updating
    yf_1=yf;
    pid.Integral_1=pid.Integral;
  }
	
  //Por precaucion se controla la variable de control en modo automatico
  //En modo manual es obligatorio controlarla
  if(pid.u > 1023) pid.u=1023;
  else if(pid.u < 0) pid.u=0;
     
  //Pasando variable de control a PWM
  set_PWM(pid.u);
}

#separate
void algoritmo_Fuzzy()
{
	float T1temp;
	int16 utemp;
	
	yf = filtro_promedio();
	
	if(fTipoAccion==directa)	//Accion Directa
		fuzzy.error = rf - yf;
	else											//Accion Inversa
		fuzzy.error = yf - rf;
	
	fuzzy.derror = fabs(fuzzy.error) - fabs(fuzzy.error_1);
      
	if(modo==automatico)
	{		
		T1temp = fuzzy.error * fuzzy.fparam.Kp;
		fuzzy.e_P = (T1temp > 1023 ? 1023 : (T1temp < -1023 ? -1023 : T1temp));
			
		T1temp = fuzzy.derror * fuzzy.fparam.Kd;
		fuzzy.de_D = (T1temp > 1023 ? 1023 : (T1temp < -1023 ? -1023 : T1temp));
      
		T1temp = fuzzy.error * fuzzy.fparam.Ki;
		fuzzy.e_I = (T1temp > 1023 ? 1023 : (T1temp < -1023 ? -1023 : T1temp));
			
		T1temp = fuzzy.derror * fuzzy.fparam.Kpi;
		fuzzy.de_P = (T1temp > 1023 ? 1023 : (T1temp < -1023 ? -1023 : T1temp));

		//Algoritmo Fuzzy
		PDInferenceEngine(fuzzy.e_P, fuzzy.de_D, &fuzzy.u_PD);
	  PIInferenceEngine(fuzzy.e_I, fuzzy.de_P, &fuzzy.du_PI);
      
		fuzzy.u_PI = fuzzy.du_PI + fuzzy.u_PI_1;
      
		fuzzy.u = fuzzy.u_PD + fuzzy.u_PI;

		//Updating
		fuzzy.error_1 = fuzzy.error;
		fuzzy.u_PI_1 = fuzzy.u_PI;
  }
		
	if(fuzzy.u<0) fuzzy.u=0;
	else if(fuzzy.u>1023) fuzzy.u=1023;
	//Pasando variable de control a PWM
	
	utemp = (int16)fuzzy.u;
	set_PWM(utemp);
}

#separate
void set_PWM(int16 pwm)
{
	if(fPWM1) set_pwm1_duty(pwm);
	else set_pwm2_duty(pwm);
}

#separate
void enable_timer0(BOOLEAN ON)
{
	if(ON)
	{
		set_timer0(tmr0);
		enable_interrupts(INT_TIMER0);
		disable_interrupts(INT_TIMER1);	
		count_timer=9;	  //1 segundo (99)
		Tsupervision=9;
	}
	else
		disable_interrupts(INT_TIMER0);
}

#separate
void enable_timer1(BOOLEAN ON)
{
	if(ON)
	{
		set_timer1(tmr1);
		enable_interrupts(INT_TIMER1);
		disable_interrupts(INT_TIMER0);	
		count_timer=2;	//+-1 segundo (9)
		Tsupervision=2;
	}
	else
		disable_interrupts(INT_TIMER1);
}

#separate 
void printRS232()
{		
		if(fprintPIDini)
		{
			putc('@'); 
			printf("%01d,%04Ld,%4.3f,%4.3f,%4.3f,%02d,%03Lu,\r",
						tipo_procesamiento,rf,
						pid.param.Kp,pid.param.Ki,pid.param.Kd,cantM,pid.param.Tc);
			fprintPIDini=FALSE;
			enable_timer0(TRUE);
			putc('<');
		}
		
		if(fprintFUZZYini)
		{
			putc('@'); 
			printf("%01d,%04Ld,%4.3f,%4.3f,%4.3f,%02d,%03Lu,%04Ld,%04Ld,%3.3f,%3.3f,%4.3f,\r",
						tipo_procesamiento,rf,
						fuzzy.fparam.Kp,fuzzy.fparam.Ki,fuzzy.fparam.Kd,cantM,fuzzy.fparam.Tc,
						fuzzy.fparam.universo_duPI_max,fuzzy.fparam.universo_uPD_max,
						fuzzy.fparam.stepPD,fuzzy.fparam.stepPI,fuzzy.fparam.Kpi);
			fprintFUZZYini=FALSE;
			enable_timer1(TRUE);
			putc('<');
		}
		
		if(fprintTc)
		{
			putc('|');
			printf("%03Lu,\r",fuzzy.fparam.Tc);			
			fprintTc = FALSE;
			gTc = TRUE;
			enable_timer1(TRUE);
			putc('<');
		}
		
		if(fprint)
		{
			fprint = FALSE;
			
			putc('*');
    
			printf("Y%04Ld,\r",yf);
          
      if(modo==automatico)
      {
				if(pid_selected) printf("U%04Ld,\r",pid.u);
				else if(fuzzy_selected) printf("U%04Ld,\r",(signed int16)fuzzy.u);
      }
		}
		
    if(fentrada_analogica)
    {
        printf("%04Ld\r",ADC_Read(analog_value));
        fentrada_analogica=FALSE;
    }
}

#separate
void saveToEEPROM()
{
    //Guardando en EEPROM        
    if(grf)
  	{
    	write_int16_eeprom(address_rf,rf);
      
    	grf=FALSE;
  	}
    
    if(gk)
    {
			if(pid_selected)
			{
				write_float_eeprom(address_Kp,pid.param.Kp);
				write_float_eeprom(address_Ki,pid.param.Ki);
				write_float_eeprom(address_Kd,pid.param.Kd);
      }
			else if(fuzzy_selected)
			{
				write_float_eeprom(address_Kp_Fuzzy,fuzzy.fparam.Kp);
				write_float_eeprom(address_Ki_Fuzzy,fuzzy.fparam.Ki);
				write_float_eeprom(address_Kd_Fuzzy,fuzzy.fparam.Kd);
				write_float_eeprom(address_Kpi_Fuzzy,fuzzy.fparam.Kpi);
			}
      gk=0;
    }
        
    if(gTc)
    {
			if(pid_selected) 
				write_int16_eeprom(address_Tc,pid.param.Tc);
      else if(fuzzy_selected) 
				write_int16_eeprom(address_Tc_Fuzzy,fuzzy.fparam.Tc);
			
      gTc=FALSE;
    }
    
    if(gcantM)
    {
      write_eeprom(address_cantM,cantM);
      
      gcantM=FALSE;
    }
    
    if(gBR)
    {
      write_eeprom(address_BaudRate,seleccionBR);
      
      gBR=FALSE;
    }
        
    if(gPWMf)
    {
      write_eeprom(address_PWMf,seleccionPWMf);
      
      gPWMf=FALSE;
	  
	  	set_PWM_period();	//configurando Timer 2
    }
     
    if(gTP)
    {
      write_eeprom(address_tipoProcesamiento,tipo_procesamiento);
       
      gTP=FALSE;
    }
       
		if(fuzzy.fparam.guniversoPI)
		{
			write_int16_eeprom(address_universoPI,fuzzy.fparam.universo_duPI_max);
			
			fuzzy.fparam.guniversoPI = FALSE;
		}
		
		if(fuzzy.fparam.guniversoPD)
		{
			write_int16_eeprom(address_universoPD,fuzzy.fparam.universo_uPD_max);
			
			fuzzy.fparam.guniversoPD = FALSE;
		}
		
		if(fuzzy.fparam.gstepPD)
		{
			write_float_eeprom(address_stepPD,fuzzy.fparam.stepPD);
			
			fuzzy.fparam.gstepPD = FALSE;
		}
		
		if(fuzzy.fparam.gstepPI)
		{
			write_float_eeprom(address_stepPI,fuzzy.fparam.stepPI);
			
			fuzzy.fparam.gstepPI = FALSE;
		}
		
		if(gPWMseleccion)
		{
			write_eeprom(address_fPWM1,fPWM1);

			gPWMseleccion = FALSE;
		}
		
		if(gADseleccion)
		{
			write_eeprom(address_ADselected,ADselected);

			gADseleccion = FALSE;
		}		
		
		if(gTipoAccion)
		{
			write_eeprom(address_TipoAccion,fTipoAccion);

			gTipoAccion = FALSE;
		}			
}

#separate
void guardar_bufferRx()
{
	int i;
	
	bRxSelect=bufferRxSelect;
	
	for(i=0;i<buffer_size;i++)
		bRx[i]=bufferRx[i];
}

void main()
{	
  setup();
  initialize();

  while(TRUE)
  {		 
		printRS232();
		saveToEEPROM();

		if(fRx)
		{
			fRx=FALSE;
			
			guardar_bufferRx();
			
  		analizar_Rx(bRxSelect);
		}
  }
}
