#include "GLOBAL.c"

//Puerto serie
#INT_RDA HIGH
void serial_port()
{ 	
	static BOOLEAN fRxFirst=FALSE;
	static int posicion=0;
	char Rx;

	Rx=getc();

	if(Rx=='<')		
	{
		posicion=0;
		fRxFirst=TRUE;
	}	
	else
	{
		if(Rx==13)//ENTER
			fRx=TRUE;
		else
		{
			if(fRxFirst) {bufferRxSelect=Rx; fRxFirst=FALSE;}
			else 
			{
				bufferRx[posicion++]=Rx;
				
				if(posicion==buffer_size)
					posicion=0;
			}
		}	
	}
}

#separate
void analizar_Rx(char Rx)
{
	switch(Rx)
  {
  case conectar: putc('!'); break;
  case desconectar: 
		fFirst_time_pid=FALSE; 
		fFirst_time_fuzzy=FALSE;
		enable_timer0(FALSE); 
		enable_timer1(FALSE);
		set_pwm1_duty(0);
		set_pwm2_duty(0);
		break;
  //CONTROL
  case Tx: Tx_function(); putc('<'); break;
  case estado_pid: estado_pid_function(); break;
	case estado_fuzzy: estado_fuzzy_function(); break;
	case estado_pid_reenvio: fFirst_time_pid=FALSE; estado_pid_function(); break;
	case estado_fuzzy_reenvio: fFirst_time_fuzzy=FALSE; estado_fuzzy_function(); break;
  case end_of_Tx: end_of_Tx_function(); putc('<'); break;     
  case cambiar_modo: modo = bRx[0]; putc('<'); break; 
  //SUPERVISION
  case estado_supervision: enable_timer0(FALSE); enable_timer1(FALSE); putc('<'); break;
  case tipo_de_modulo: putc('^'); break; 
  case entrada_analogica: analog_value=bRx[0]; fentrada_analogica=TRUE; break;
  case entrada_digital: entrada_digital_function(); break;       
  case ciclo_util_PWM: ciclo_util_PWM_function(); putc('<'); break;  
  case salida_digital: salida_digital_function(); putc('<'); break; 
  case RESET: reset_cpu(); break;
  case escritura_configuracion: escritura_configuracion_function(); putc('<'); break;
  case lectura_configuracion: lectura_configuracion_function(); break; 
  default: putc(caracter_no_valido); break;
  }
}

#separate
void Tx_function()
{
     // get_string(bRx,buffer_size);
      fnumber = strtod(bRx,&buffer);
      
      switch(buffer[0])
      {
        case 'r':
          if(fnumber>1023) fnumber=1023;
          if(fnumber<0) fnumber=0;
          rf = fnumber; 
			//		fuzzy.u_PI_1=0;  
			//		pid.Integral_1 = 0;
          grf=1; 
          break;
        case 't': 
					if(pid_selected) 
						pid.paramTemp.Tc = ((int16)fnumber > 0 ? (int16)fnumber : 1); 
					else if(fuzzy_selected) 
						fuzzy.fparamTemp.Tc = (int16)fnumber;
					tgTc = TRUE; 
					break;
        case 'p': 
					if(pid_selected) pid.paramTemp.Kp = fnumber;
					else if(fuzzy_selected) fuzzy.fparamTemp.Kp = fnumber;
					tgk = TRUE;
					break;
        case 'i': 
					if(pid_selected) pid.paramTemp.Ki = fnumber; 
					else if(fuzzy_selected) fuzzy.fparamTemp.Ki = fnumber;
					tgk = TRUE;
					break;
        case 'd': 
					if(pid_selected) pid.paramTemp.Kd = fnumber;
					else if(fuzzy_selected) fuzzy.fparamTemp.Kd = fnumber;
					tgk = TRUE;
					break;
        case 'f': tcantM = fnumber; tgcantM = TRUE; break;
        case 'u': tu = fnumber; break;
				case 'I': 
					fuzzy.fparamTemp.universo_duPI_max = fnumber;
					fuzzy.fparamTemp.universo_duPI_min = fnumber * (-1);
					fuzzy.fparamTemp.guniversoPI = TRUE;
					break;
				case 'D': 
					fuzzy.fparamTemp.universo_uPD_max = fnumber;
					fuzzy.fparamTemp.universo_uPD_min = fnumber * (-1);
					fuzzy.fparamTemp.guniversoPD = TRUE;
					break;
				case 's': 
					fuzzy.fparamTemp.stepPD = fnumber; 
					fuzzy.fparamTemp.gstepPD = TRUE;
					break;
				case 'S': 
					fuzzy.fparamTemp.stepPI = fnumber; 
					fuzzy.fparamTemp.gstepPI = TRUE;
					break;
				case 'z': 
					fuzzy.fparamTemp.Kpi = fnumber;
					tgk = TRUE;
					break;
				case 'G':
					Tsupervision = fnumber;
					break;
        default: putc(caracter_no_valido); break;
      }
}

#separate
void estado_pid_function()
{
		if(fFirst_time_pid==FALSE) 
		{
			fFirst_time_pid=TRUE;
			fprintPIDini=TRUE;
			enable_timer0(FALSE);
		}
		else
			enable_timer0(TRUE);
	
		pid_selected=TRUE;
		fuzzy_selected=FALSE;
		fFirst_time_fuzzy=FALSE;
}

#separate
void estado_fuzzy_function()
{
		if(fFirst_time_fuzzy==FALSE) 
		{
			fFirst_time_fuzzy=TRUE;
			fprintFUZZYini=TRUE;
			enable_timer1(FALSE);
		}	
		else
			enable_timer1(TRUE);
				
		set_timer1(tmr1);		
		fuzzy_selected=TRUE;
		pid_selected=FALSE;
		fFirst_time_pid=FALSE;
}

#separate
void end_of_Tx_function()
{
     		if(pid_selected)
				{
					pid.param.Kp = pid.paramTemp.Kp;
					pid.param.Ki = pid.paramTemp.Ki;
					pid.param.Kd = pid.paramTemp.Kd;
					pid.param.Tc = pid.paramTemp.Tc;

					tmr0 = calc_tmr(pid.param.Tc);
					    
					if(modo==manual)
						pid.u=tu;
        }  
				else if(fuzzy_selected)
				{
					fuzzy.fparam.Kp = fuzzy.fparamTemp.Kp;
					fuzzy.fparam.Ki = fuzzy.fparamTemp.Ki;
					fuzzy.fparam.Kd = fuzzy.fparamTemp.Kd;
					fuzzy.fparam.Kpi = fuzzy.fparamTemp.Kpi;
					fuzzy.fparam.universo_duPI_max = fuzzy.fparamTemp.universo_duPI_max;
					fuzzy.fparam.universo_duPI_min = fuzzy.fparamTemp.universo_duPI_min;
					fuzzy.fparam.universo_uPD_max = fuzzy.fparamTemp.universo_uPD_max;
					fuzzy.fparam.universo_uPD_min = fuzzy.fparamTemp.universo_uPD_min;
					fuzzy.fparam.Tc = fuzzy.fparamTemp.Tc;
					fuzzy.fparam.stepPD = fuzzy.fparamTemp.stepPD;
					fuzzy.fparam.stepPI = fuzzy.fparamTemp.stepPI;
					
					tmr1 = calc_tmr(fuzzy.fparam.Tc);
					
				  initialize_Fuzzy();
								
					if(modo==manual)
						fuzzy.u=tu;
						
					fuzzy.fparam.gstepPD = fuzzy.fparamTemp.gstepPD;
					fuzzy.fparam.gstepPI = fuzzy.fparamTemp.gstepPI;
					fuzzy.fparam.guniversoPI = fuzzy.fparamTemp.guniversoPI;
					fuzzy.fparam.guniversoPD = fuzzy.fparamTemp.guniversoPD;

					fuzzy.fparamTemp.gstepPD = FALSE;
					fuzzy.fparamTemp.gstepPI = FALSE;
					fuzzy.fparamTemp.guniversoPI = FALSE;
					fuzzy.fparamTemp.guniversoPD = FALSE;
				}
					
				cantM = tcantM;
				if(cantM>16) 
					cantM=16;      

				gk = tgk;
				gcantM = tgcantM;
				tgk = FALSE;
				tgcantM = FALSE;
				gTc = tgTc;					
				tgTc = FALSE;
}

#separate
void escritura_configuracion_function()
{
				switch(bRx[0])
        {
        //case 0: solo para RS485
          case 1:  //cambiar baud rate
          //guardar en EEPROM un identificador y actualizar en setup() al reiniciar el micro
            gBR=1;  //habilita guardar el Baud Rate en memoria
            seleccionBR=bRx[1];
          break;
          case 2:  //cambiar frecuencia del PWM
          //guardar en EEPROM un identificador y actualizar en setup() al reiniciar el micro
            gPWMf=1;  //habilita guardar frecuencia del PWM en memoria            
            seleccionPWMf=bRx[1];
          break;
          case 3: //tipo de procesamiento
          //guardar en EEPROM un identificador y actualizar en setup() al reiniciar el micro
            gTP=1;  //habilita guardar el tipo de procesamiento en memoria
            tipo_procesamiento=bRx[1];  
            switch(tipo_procesamiento)
            {
              case 0: fcantM=FALSE; break;
              case 1: fcantM=TRUE; break;
              case 2: fcantM=FALSE; break;
              case 3: fcantM=TRUE; break;
            }          
          break;
          case 4: //cantidad de terminos del filtro promedio
            gcantM=TRUE;
            switch(bRx[1])
            {
              case 0: cantM=2; break;
              case 1: cantM=4; break;
              case 2: cantM=8; break;
              case 3: cantM=16; break;
            }
          break;
					case 5:
						gPWMseleccion=TRUE;
						fPWM1=bRx[1];
						break;
					case 6:
						gADseleccion=TRUE;
						ADselected=bRx[1];
						break;
					case 7:
						gTipoAccion=TRUE;
						fTipoAccion=bRx[1];
						break;
        }
}

#separate
void entrada_digital_function()
{
        switch(bRx[0])
        {
          case 0: printf("%d",input(PIN_B4)); break;
          case 1: printf("%d",input(PIN_B5)); break;
          case 2: printf("%d",input(PIN_B6)); break;
          case 3: printf("%d",input(PIN_B7)); break;
          case 4: printf("%d",input(PIN_B0)); break;
          case 5: printf("%d",input(PIN_A4)); break;
          default: break;
        }
}

#separate
void ciclo_util_PWM_function()
{
     //   get_string(bRx,buffer_size);
        fnumber = strtod(bRx,&buffer);
        switch(buffer[0])
        {
          case 'u':              
            set_pwm1_duty((int16)fnumber);
            break;
          case 'd': 
            set_pwm2_duty((int16)fnumber);
            break;
        }
}

#separate
void salida_digital_function()
{
        switch(bRx[0])
        {
          case 0: output_bit(PIN_B1,bRx[1]); break; //(pin,value)
          case 1: output_bit(PIN_B2,bRx[1]); break; //(pin,value)
          case 2: output_bit(PIN_B3,bRx[1]); break; //(pin,value)
          default: putc(caracter_no_valido); break;
        }
}

#separate
void lectura_configuracion_function()
{
        switch(bRx[0])
        {
        //case 0: solo en caso de RS485
        case 1:  //valor de velocidad de comunicacion segun la tabla
				putc(1);
				putc(seleccionBR);
          /*  
						switch(seleccionBR)
            {
              case 0: printf("9600bps\r"); break;
              case 1: printf("1200bps\r"); break;
              case 2: printf("2400bps\r"); break;
              case 3: printf("4800bps\r"); break;
              case 4: printf("19200bps\r"); break;
              case 5: printf("28800bps\r"); break;
              case 6: printf("33600bps\r"); break;
              case 7: printf("38400bps\r"); break;
              default: printf("9600bps\r"); break;
            }
					*/
            break;
        case 2: //periodo de los PWM 0 y 1
						putc(2);
						putc(seleccionPWMf);
					/*	
            switch(seleccionPWMf)
            {
              case 0: printf("1.22KHz [0.82ms]\r"); break;
              case 1: printf("2.44KHz [0.41ms]\r"); break;
              case 2: printf("4.88KHz [0.20ms]\r"); break;
              case 3: printf("7.32KHz [0.14ms]\r"); break;
              case 4: printf("9.76KHz [0.10ms]\r"); break;
              case 5: printf("12.20KHz [81.9us]\r"); break;
              case 6: printf("17.08KHz [58.5us]\r"); break;
              case 7: printf("19.53KHz [51.2us]\r"); break;
              case 8: printf("30.00KHz [33us]\r"); break;
              default: printf("30.00KHz [33us]\r"); break;
            }
					*/
            break;  
        case 3: //tipo de procesamiento
						putc(3);
						putc(tipo_procesamiento);
          /*  
						switch(tipo_procesamiento)
            {
              case 0: printf("SIN PROCESAMIENTO\r"); break;
              case 1: printf("FILTRO PROMEDIO\r"); break;
              case 2: printf("CONVERSION A u.i.\r"); break;
              case 3: printf("FILTRO Y CONVERSION\r"); break;
            }
					*/
            break;
        case 4: //printf("Cantidad de muestras: %d\r",cantM); 
					putc(4);
					putc(cantM);
					break;  //cantidad de muestras del filtro promedio
				case 5:  //SeleccionPWM
					putc(5);
					putc(fPWM1);
					break;
				case 6:  //SeleccionAD
					putc(6);
					putc(ADselected);
					break;
			  case 7:  //Tipo de accion
			  	putc(7);
			  	putc(fTipoAccion);
			  	break;
        }
}
