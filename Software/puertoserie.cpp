#include "puertoserie.h"

PuertoSerie::PuertoSerie()
{
    BaudRate = 9600; //valor default
    conectado=false;
    etapa=Inicio;
    muestras=0;
    fPARAM_change=false;
    fREF_change=false;

    YUact=false;
    PARAMact=false;
    Ract=false;
    CURVEact=false;
    Tcact=false;

    T_over=false;
    data_sent=false;
    fErrorRx=false;
    ErrorRx=false;
    fTSupervision=false;

    PID.SaveFile("PID, Ramon Carrasco");

    COM=0;  //COM1

    comprobando_files_existentes();

    yf_file = new QFile("file_yf.txt");
    u_file = new QFile("file_u.txt");
    e_file = new QFile("file_e.txt");
    T_file = new QFile("file_T.txt");

    if (!yf_file->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug("ERROR al abrir el fichero");
        return;
    }
    if (!u_file->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug("ERROR al abrir el fichero");
        return;
    }
    if (!e_file->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug("ERROR al abrir el fichero");
        return;
    }
    if (!T_file->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug("ERROR al abrir el fichero");
        return;
    }
}

PuertoSerie::~PuertoSerie()
{
    CloseComport(COM);
}

void PuertoSerie::comprobando_files_existentes()
{
    if(QFile::exists("file_yf_OLD.txt"))
        QFile::remove("file_yf_OLD.txt");
    if(QFile::exists("file_u_OLD.txt"))
        QFile::remove("file_u_OLD.txt");
    if(QFile::exists("file_e_OLD.txt"))
        QFile::remove("file_e_OLD.txt");
    if(QFile::exists("file_T_OLD.txt"))
        QFile::remove("file_T_OLD.txt");

    if(QFile::exists("file_yf.txt"))
        QFile::rename("file_yf.txt","file_yf_OLD.txt");
    if(QFile::exists("file_u.txt"))
        QFile::rename("file_u.txt","file_u_OLD.txt");
    if(QFile::exists("file_e.txt"))
        QFile::rename("file_e.txt","file_e_OLD.txt");
    if(QFile::exists("file_T.txt"))
        QFile::rename("file_T.txt","file_T_OLD.txt");
}

bool PuertoSerie::Data_Received()
{
    static bool fAll=false,fYU=false,fTc=false;
    static int contX=0,counter=0;

    n = PollComport(COM,bufferRx,buffer_size);
    if(n>0)
    {
        bufferRx[n]=0;

       // qDebug((char*)bufferRx);

        switch(etapa)
        {
        case Inicio:

            for(int i=0;i<n;i++)
                if(bufferRx[i]=='!')
                {
                    conectado=true;
                    etapa=Supervision;
                    break;  //para salir del for
                }

            break; //fin del case Inicio

        case Supervision:

            switch(bufferRx[0])
            {
            case '^': strcpy((char*)bufferRx,"MPIC1-RS232"); break;
            case 1:
                switch(bufferRx[1])
                {
                case 0: strcpy((char*)bufferRx,"9600bps"); break;
                case 1: strcpy((char*)bufferRx,"1200bps"); break;
                case 2: strcpy((char*)bufferRx,"2400bps"); break;
                case 3: strcpy((char*)bufferRx,"4800bps"); break;
                case 4: strcpy((char*)bufferRx,"19200bps"); break;
                case 5: strcpy((char*)bufferRx,"28800bps"); break;
                case 6: strcpy((char*)bufferRx,"33600bps"); break;
                case 7: strcpy((char*)bufferRx,"38400bps"); break;
                default: strcpy((char*)bufferRx,"ERROR DE Rx"); break;
                }
                break;
            case 2:
                switch(bufferRx[1])
                {
                case 0: strcpy((char*)bufferRx,"1.22KHz [0.82ms]"); break;
                case 1: strcpy((char*)bufferRx,"2.44KHz [0.41ms]"); break;
                case 2: strcpy((char*)bufferRx,"4.88KHz [0.20ms]"); break;
                case 3: strcpy((char*)bufferRx,"7.32KHz [0.14ms]"); break;
                case 4: strcpy((char*)bufferRx,"9.76KHz [0.10ms]"); break;
                case 5: strcpy((char*)bufferRx,"12.20KHz [81.9us]"); break;
                case 6: strcpy((char*)bufferRx,"17.08KHz [58.5us]"); break;
                case 7: strcpy((char*)bufferRx,"19.53KHz [51.2us]"); break;
                case 8: strcpy((char*)bufferRx,"30.00KHz [33us]"); break;
                default: strcpy((char*)bufferRx,"ERROR DE Rx"); break;
                }
                break;
            case 3:
                switch(bufferRx[1])
                {
                case 0: strcpy((char*)bufferRx,"SIN PROCESAMIENTO"); break;
                case 1: strcpy((char*)bufferRx,"FILTRO PROMEDIO"); break;
                case 2: strcpy((char*)bufferRx,"CONVERSION A u.i."); break;
                case 3: strcpy((char*)bufferRx,"FILTRO Y CONVERSION"); break;
                default: strcpy((char*)bufferRx,"ERROR DE Rx"); break;
                }
                break;
            case 4:
                switch(bufferRx[1])
                {
                case 0: strcpy((char*)bufferRx,"Cantidad de muestras: 0"); break;
                case 1: strcpy((char*)bufferRx,"Cantidad de muestras: 1"); break;
                case 2: strcpy((char*)bufferRx,"Cantidad de muestras: 2"); break;
                case 3: strcpy((char*)bufferRx,"Cantidad de muestras: 3"); break;
                case 4: strcpy((char*)bufferRx,"Cantidad de muestras: 4"); break;
                case 5: strcpy((char*)bufferRx,"Cantidad de muestras: 5"); break;
                case 6: strcpy((char*)bufferRx,"Cantidad de muestras: 6"); break;
                case 7: strcpy((char*)bufferRx,"Cantidad de muestras: 7"); break;
                case 8: strcpy((char*)bufferRx,"Cantidad de muestras: 8"); break;
                case 9: strcpy((char*)bufferRx,"Cantidad de muestras: 9"); break;
                case 10: strcpy((char*)bufferRx,"Cantidad de muestras: 10"); break;
                case 11: strcpy((char*)bufferRx,"Cantidad de muestras: 11"); break;
                case 12: strcpy((char*)bufferRx,"Cantidad de muestras: 12"); break;
                case 13: strcpy((char*)bufferRx,"Cantidad de muestras: 13"); break;
                case 14: strcpy((char*)bufferRx,"Cantidad de muestras: 14"); break;
                case 15: strcpy((char*)bufferRx,"Cantidad de muestras: 15"); break;
                case 16: strcpy((char*)bufferRx,"Cantidad de muestras: 16"); break;
                default: strcpy((char*)bufferRx,"ERROR DE Rx"); break;
                }
                break;
            case 5:
                switch(bufferRx[1])
                {
                case 0: strcpy((char*)bufferRx,"PWM2 seleccionado"); break;
                case 1: strcpy((char*)bufferRx,"PWM1 seleccionado"); break;
                }
                break;
            case 6:
                switch(bufferRx[1])
                {
                case 0: strcpy((char*)bufferRx,"A/D seleccionado: 0"); break;
                case 1: strcpy((char*)bufferRx,"A/D seleccionado: 1"); break;
                case 2: strcpy((char*)bufferRx,"A/D seleccionado: 2"); break;
                case 3: strcpy((char*)bufferRx,"A/D seleccionado: 3"); break;
                case 4: strcpy((char*)bufferRx,"A/D seleccionado: 4"); break;
                case 5: strcpy((char*)bufferRx,"A/D seleccionado: 5"); break;
                }
                break;
            case 7:
                switch(bufferRx[1])
                {
                case 0: strcpy((char*)bufferRx,"Acción Directa"); break;
                case 1: strcpy((char*)bufferRx,"Acción Inversa"); break;
                }
                break;
            case WDT: sup_error=_WDT; break;
            case BOR: sup_error=_BOR; break;
            case POR: sup_error=_POR; break;
            case caracter_no_valido: sup_error=_caracter_no_valido; break;
            }

            break; //fin del case Supervision

        case Control:

            if(bufferRx[0]=='@' || bufferRx[1]=='@' || fAll==true)
            {
                fAll=true;

            //    if(counter==0)
            //        timer.start();

                qDebug("Actualizar ALL");
                qDebug((char*)bufferRx);

                for(int ii=0;ii<n;ii++,counter++)
                {
                    if(counter > 0 &&
                       bufferRx[ii]!='.' && bufferRx[ii]!=',' &&
                       (bufferRx[ii]<0x30 || bufferRx[ii]>0x39))
                    {
                        qDebug("Error Rx");
                        ErrorRx=true;
                        contX=0;
                        fAll=false;
                        counter=0;
                        break;
                    }

                    bAll[counter]=bufferRx[ii];

                    if(bAll[counter]==',') contX++;

                    int temporal;
                    if(!PID.get_isFuzzy()) temporal = 7;
                    else temporal = 12;

                    if(contX==temporal)
                    {
                        contX=0;
                        fAll=false;
                        counter=0;
                        ActualizarAll();
                        qDebug("Todo actualizado");
                        break;
                    }
                 }
             }

             if(bufferRx[0]=='|' || fTc==true)  //Tc del fuzzy
             {
                 fTc=true;

                 qDebug("fTc");

                 for(int ii=0;ii<n;ii++,counter++)
                 {
                     if(bufferRx[ii]!='|' &&
                        bufferRx[ii]!='.' && bufferRx[ii]!=',' &&
                        (bufferRx[ii]<0x30 || bufferRx[ii]>0x39))
                     {
                         qDebug("Error Rx Tc");
                         ErrorRx=true;
                         fTc=false;
                         counter=0;
                         break;
                     }

                       bTC[counter]=bufferRx[ii];

                       if(bTC[counter]==',')
                       {
                           fTc=false;
                           counter=0;
                           ActualizarTc();
                           break;  //para salir del for
                       }
                 }
             }

             if(bufferRx[0]=='*' || fYU==true)
             {
                  fYU=true;
               //   qDebug("fYU");
               //   if(counter==0)
               //       timer.start();

                  for(int ii=0;ii<n;ii++,counter++)
                  {
                      if(bufferRx[ii]!='*' && bufferRx[ii]!='Y' && bufferRx[ii]!='U' &&
                         bufferRx[ii]!='.' && bufferRx[ii]!=',' && bufferRx[ii]!=13 &&
                         (bufferRx[ii]<0x30 || bufferRx[ii]>0x39))
                      {
                          qDebug("Error Rx YU");
                          ErrorRx=true;
                          fErrorRx=true;
                      }

                        bYU[counter]=bufferRx[ii];

                        if(bYU[counter]==',') contX++;

                        if(contX==2)
                        {
                            contX=0;
                            fYU=false;
                            counter=0;
                            muestras++;
                            ActualizarYU();
                            fErrorRx=false;
                            break;
                        }
                  }
             }

            break;   //fin del case Control
        }  //fin del switch(etapa)

        if(T_over && data_sent)
        {
            ErrorRx=true;
            qDebug("ErrorRx=true");
            T_over=false;
            data_sent=false;
        }
        else if(data_sent)
             if(bufferRx[0]==inicio_trama)
                data_sent=false;

        return true;
    }
    return false;
}

void PuertoSerie::Reference_changed()
{
    fREF_change=true;
}

void PuertoSerie::Parameter_changed()
{
    fPARAM_change=true;
}

PIDprofesional* PuertoSerie::myPID()
{
  return &PID;
}

void PuertoSerie::ActualizarTc()
{
    int j;

    for(j=0;bTC[j]!=',';j++)
        bTc[j]=bTC[j+1];

    qDebug("bTC=");
    qDebug((char*)bTC);
    qDebug("bTc=");
    qDebug((char*)bTc);

    PID.set_Tc(get_number(bTc)*0.01);

    Tcact=true;
    fTSupervision=true;
}

void PuertoSerie::ActualizarYU()
{
    int j,xcounter=0,ciclos;

    if(PID.get_Modo()==automatico)
        ciclos=2;
    else
        ciclos=1;

    if(!fErrorRx)
    {
        for(int i=0;xcounter<ciclos;i++)
        {
            switch(bYU[i])
            {
                case 'Y':
                   for(j=0;bYU[i+j]!=',';j++)
                        bY[j]=bYU[i+j+1];
                    xcounter++;
                    PID.set_yf(get_number(bY));
                    break;
                case 'U':
                    for(j=0;bYU[i+j]!=',';j++)
                        bU[j]=bYU[i+j+1];
                    xcounter++;
                    PID.set_u(get_number(bU));
                    break;
            }
        }

        PID.calcular_error();
    }

    enviar_Ref();
    enviar_Param();

    PID.SaveMuestra();
    //salvar_muestras_files(); //se salvan despues de graficar en xcontrolador

    YUact=true;

  //  PID.set_Tc(timer.elapsed());
 //   Tcact=true;
}

void PuertoSerie::dar_enter_por_cambio_ref()
{
    static long int conteo=0;

    QTextStream out_yf(yf_file);
    QTextStream out_u(u_file);
    QTextStream out_e(e_file);
    QTextStream out_T(T_file);

    conteo++;

    out_yf<<"\nCambio de referencia #"<<conteo<<": "<<PID.get_rf()<<"\n";
    out_u<<"\nCambio de referencia #"<<conteo<<": "<<PID.get_rf()<<"\n";
    out_e<<"\nCambio de referencia #"<<conteo<<": "<<PID.get_rf()<<"\n";
    out_T<<"\nCambio de referencia #"<<conteo<<": "<<PID.get_rf()<<"\n";
}

void PuertoSerie::salvar_muestras_files()
{
    QTextStream out_yf(yf_file);
    QTextStream out_u(u_file);
    QTextStream out_e(e_file);
    QTextStream out_T(T_file);

    out_yf<<PID.get_yf()<<",";
    out_u<<PID.get_u()<<",";
    out_e<<PID.get_e()<<",";
    out_T<<PID.get_tiempo()<<",";
}

void PuertoSerie::reset_muestras()
{
    yf_file->reset();
    u_file->reset();
    e_file->reset();
    T_file->reset();
}

void PuertoSerie::load_yf(QTextEdit &textEdit)
{
    yf_file->seek(0);
    QTextStream in(yf_file);
    textEdit.clear();

    while (!in.atEnd())
    {
        QString line = in.readLine();
        textEdit.append(line);
    }
}

void PuertoSerie::load_e(QTextEdit &textEdit)
{
    e_file->seek(0);
    QTextStream in(e_file);
    textEdit.clear();

    while (!in.atEnd())
    {
        QString line = in.readLine();
        textEdit.append(line);
    }
}

void PuertoSerie::load_u(QTextEdit &textEdit)
{
    u_file->seek(0);
    QTextStream in(u_file);
    textEdit.clear();

    while (!in.atEnd())
    {
        QString line = in.readLine();
        textEdit.append(line);
    }
}

void PuertoSerie::load_tiempo(QTextEdit &textEdit)
{
    T_file->seek(0);
    QTextStream in(T_file);
    textEdit.clear();

    while (!in.atEnd())
    {
        QString line = in.readLine();
        textEdit.append(line);
    }
}

void PuertoSerie::ActualizarAll()
{
    int i,j,xcounter,opcion,temporal;

    if(!PID.get_isFuzzy()) temporal = 7;
    else temporal = 12;

    for(xcounter=0;xcounter<temporal;xcounter++)
    {
        switch(xcounter)
        {
        case 0:
            for(i=0,j=0;bAll[j]!=',';j++)
                bTP[j]=bAll[j+1];
            i=j+1;

            qDebug("bAll=");
            qDebug((char*)bAll);
            qDebug("bTP=");
            qDebug((char*)bTP);

            opcion = get_number(bTP);
            switch(opcion)
            {
            case 0: PID.set_tipo_procesamiento(SinProcesamiento); break;
            case 1: PID.set_tipo_procesamiento(FiltroPromedio); break;
            case 2: PID.set_tipo_procesamiento(ConvUI); break;
            case 3: PID.set_tipo_procesamiento(FiltroConv); break;
            }

            PID.inicializar_escala();

            break;
        case 1:
            for(j=0;bAll[i+j]!=',';j++)
                bR[j]=bAll[i+j];
            bR[j]=bAll[i+j];
            i+=j+1;

            PID.set_rf(get_number(bR));

            qDebug("bR=");
            qDebug((char*)bR);            

            Ract=true;

            break;
        case 2:
            for(j=0;bAll[i+j]!=',';j++)
                bKp[j]=bAll[i+j];
            bKp[j]=bAll[i+j];
            i+=j+1;

            qDebug("bKp=");
            qDebug((char*)bKp);

            PID.set_Kp(get_number(bKp));

            break;
        case 3:
            for(j=0;bAll[i+j]!=',';j++)
                bKi[j]=bAll[i+j];
            bKi[j]=bAll[i+j];
            i+=j+1;

            qDebug("bKi=");
            qDebug((char*)bKi);

            PID.set_Ki(get_number(bKi));
            break;
        case 4:
            for(j=0;bAll[i+j]!=',';j++)
                bKd[j]=bAll[i+j];
            bKd[j]=bAll[i+j];
            i+=j+1;

            qDebug("bKd=");
            qDebug((char*)bKd);

            PID.set_Kd(get_number(bKd));
            break;
        case 5:
            for(j=0;bAll[i+j]!=',';j++)
                bF[j]=bAll[i+j];
            bF[j]=bAll[i+j];
            i+=j+1;

            qDebug("bF=");
            qDebug((char*)bF);

            PID.set_F(get_number(bF));
            break;
        case 6:

                for(j=0;bAll[i+j]!=',';j++)
                    bTc[j]=bAll[i+j];
                bTc[j]=bAll[i+j];
                i+=j+1;

                qDebug("bTc=");
                qDebug((char*)bTc);

              //  if(!myPID()->get_isFuzzy())
                    //PID.set_Tc((get_number(bTc)+1)*0.01);
              //  else
                    PID.set_Tc(get_number(bTc)*0.01);                  
            break;
        case 7:
                for(j=0;bAll[i+j]!=',';j++)
                    bunivPI[j]=bAll[i+j];
                bunivPI[j]=bAll[i+j];
                i+=j+1;

                qDebug("bunivPI=");
                qDebug((char*)bunivPI);

                PID.set_univPI(get_number(bunivPI));            
            break;
        case 8:
            for(j=0;bAll[i+j]!=',';j++)
                bunivPD[j]=bAll[i+j];
            bunivPD[j]=bAll[i+j];
            i+=j+1;

            qDebug("bunivPD=");
            qDebug((char*)bunivPD);

            PID.set_univPD(get_number(bunivPD));
            break;
        case 9:
            for(j=0;bAll[i+j]!=',';j++)
                bstepPD[j]=bAll[i+j];
            bstepPD[j]=bAll[i+j];
            i+=j+1;

            qDebug("bstepPD=");
            qDebug((char*)bstepPD);

            PID.set_stepPD(get_number(bstepPD));
            break;
        case 10:
            for(j=0;bAll[i+j]!=',';j++)
                bstepPI[j]=bAll[i+j];
            bstepPI[j]=bAll[i+j];
            i+=j+1;

            qDebug("bstepPI=");
            qDebug((char*)bstepPI);

            PID.set_stepPI(get_number(bstepPI));
            break;
        case 11:
            for(j=0;bAll[i+j]!=',';j++)
                bKpi[j]=bAll[i+j];
            bKpi[j]=bAll[i+j];
            i+=j+1;

            qDebug("bKpi=");
            qDebug((char*)bKpi);

            PID.set_Kpi(get_number(bKpi));
            break;
        }
    }

    PID.SaveParametros();

    PARAMact=true;
    fTSupervision=true;

 //   PID.set_Tc(timer.elapsed());
 //   Tcact=true;
}

void PuertoSerie::enviar_Ref()
{
    if(fREF_change==true)
    {
        mySendBYTE(inicio_trama);
        mySendBYTE(Tx);

        if(SendBuf(COM,bufferTx,icounter)!=-1)
        {
            qDebug("Enviando");

            //se actualiza rf para el calculo del error
            PID.set_rf(PID.get_tref());

            Ract=true;
        }
        else
            qDebug("Error en el envio");

        fREF_change=false;

        dar_enter_por_cambio_ref();
    }
}

void PuertoSerie::enviar_Param()
{
  if(fPARAM_change==true)
  {
      mySendBYTE(inicio_trama);
      mySendBYTE(Tx);

      if(SendBuf(COM,bufferTx,icounter)!=-1)
      {
          qDebug("Enviando");
      }
      else
          qDebug("Error en el envio");

      fPARAM_change=false;
  }
}

float PuertoSerie::get_number(unsigned char buf[])
{
    float fnumber=0;
    unsigned int count_digits=0;
    int count_num=0;
    bool flag_div=false;
    unsigned int start;
    bool ferror=false;

    if(buf[0]<0x30 || buf[0]>0x39)
        ferror=true;

    for(int i=0;buf[i]!=',';i++)
    {
        if((buf[i]>=0x30 && buf[i]<=0x39) || (buf[i]=='.' && buf[i+1]!=',')) count_num++;
        else {ferror=true; break;}
    }

    if(!ferror)
    {
        for(start=0;count_num>0;start++,count_num--)
        {
            if(flag_div) count_digits++;

            if(buf[start]=='.'){count_num++; flag_div=true;}
            else fnumber+=pow(10,(count_num-1))*(buf[start]-48);  //48 es 0x30
        }

        if(flag_div) fnumber=fnumber/(pow(10,count_digits));

        return fnumber;
    }
    else
        return 0;
}

int PuertoSerie::cantidad_muestras()
{
    return muestras;
}

void PuertoSerie::change_BaudRate(int selection)
{
    CloseComport(COM);

    switch(selection)
    {
    case 0: BaudRate=9600; break;
    case 1: BaudRate=1200; break;
    case 2: BaudRate=2400; break;
    case 3: BaudRate=4800; break;
    case 4: BaudRate=19200; break;
    case 5: BaudRate=28800; break;
    case 6: BaudRate=33600; break;
    case 7: BaudRate=38400; break;
    }

    Init_conection();
}

void PuertoSerie::set_COM(int puerto)
{
    COM=puerto;
    CloseComport(COM);
    Init_conection();
}

bool PuertoSerie::Conected()
{
    return conectado;
}

void PuertoSerie::Init_conection()
{
    if(!OpenComport(COM,BaudRate))  //COM, 9600 baudios (por default)
    {
        mySendBYTE(inicio_trama);
        mySendBYTE(conectar);
        mySendBYTE(13);
        qDebug("Intento de conexion");
    }
    else
        qDebug("Desconectado");
}

void PuertoSerie::mySendBYTE(unsigned char x)
{
    if(SendByte(COM,x)==1)
      qDebug("ERROR");
}

void PuertoSerie::send_buffer(unsigned char buffer[], int comando, int tamano_buffer)
{
    mySendBYTE(inicio_trama);
    mySendBYTE(comando);

    if(SendBuf(COM,buffer,tamano_buffer)!=-1)
    {
        qDebug("Enviando");
    }
    else
        qDebug("Error en el envio");
}

void PuertoSerie::set_bufferTx(unsigned char buffer[])
{
    for(int i=0;i<Tx_size;i++)
        bufferTx[i]=buffer[i];
}
