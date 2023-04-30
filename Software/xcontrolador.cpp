#include "xcontrolador.h"
#include "ui_xcontrolador.h"

xControlador::xControlador(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::xControlador)
{
    ui->setupUi(this);

    fGraficar=false;

    qApp->setStyle("Plastique");

    connect(LF.event_Action(),SIGNAL(triggered()),this,SLOT(LF_key_pressed()));
    connect(LF.event_Shortcut(),SIGNAL(activated()),this,SLOT(LF_key_pressed()));

    Plot = new Grafica(this);
    Plot->setGeometry(325,50,600,400);
    Plot->setCanvasBackground(QColor(Qt::darkBlue));
    Plot->poner_leyenda();

    color_actual=QColor(Qt::white);

    Ref=Plot->add_marker(Ref,QwtText("Referencia"),true,0);
    seg1=Plot->add_marker(seg1,QwtText("1 segundo"),false,1);
    seg5=Plot->add_marker(seg5,QwtText("5 segundos"),false,5);
    seg10=Plot->add_marker(seg10,QwtText("10 segundos"),false,10);
    seg20=Plot->add_marker(seg20,QwtText("20 segundos"),false,20);

    PlotHistorial = new Grafica(this);
    PlotHistorial->setGeometry(20,50,600,400);
    PlotHistorial->setCanvasBackground(QColor(Qt::darkBlue));
    PlotHistorial->poner_panner();
    PlotHistorial->poner_zoomer();

    //iniciando timer para Rx
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(TMR()));
    set_timer_OFF(false);   //inicializando el timer

    timer_grafica = new QTimer(this);
    connect(timer_grafica,SIGNAL(timeout()),this,SLOT(TMR_grafica()));
    set_timer_grafica_OFF(true);

    PS.Init_conection();

    modo_supervision();
    ui->tabWidget->setCurrentIndex(0);  //Modo lectura inicialmente

    PS.myPID()->initialize_curves(Plot);
    PS.myPID()->initialize_curvesHist(PlotHistorial);

    ui->textEdit->append("Aquí se mostrará todo lo que se reciba por el puerto serie.");

    ui->actionDefault->setEnabled(false);  //apariencia default
    ui->btnTsupervision->setEnabled(false);

    ui->lcdR->setPalette(Qt::black);
    ui->lcdtime->setPalette(Qt::black);
    ui->lcdNumber->setPalette(Qt::black);
    ui->lcdT->setPalette(Qt::black);
    ui->lcdD->setPalette(Qt::black);
    ui->lcdE->setPalette(Qt::black);
    ui->lcdF->setPalette(Qt::black);
    ui->lcdI->setPalette(Qt::black);
    ui->lcdP->setPalette(Qt::black);
    ui->lcdU->setPalette(Qt::black);
    ui->lcdY->setPalette(Qt::black);
    ui->lcdPi->setPalette(Qt::black);
    ui->lcdStepPD->setPalette(Qt::black);
    ui->lcdStepPI->setPalette(Qt::black);
    ui->lcdPD->setPalette(Qt::black);
    ui->lcdPI->setPalette(Qt::black);

    T_Rx=10;
    contador=9;
}

xControlador::~xControlador()
{
    PS.mySendBYTE(inicio_trama);
    PS.mySendBYTE(desconectar);
    PS.mySendBYTE(13);
    set_timer_OFF(true);
    delete ui;
}

void xControlador::LF_key_pressed()
{
    qDebug("key_pressed");

    PS.myPID()->LoadFile(*LF.change_text());
}

void xControlador::set_timer_OFF(bool OFF)
{
    if(OFF==true) timer->stop();
    else timer->start(100);
}

void xControlador::set_timer_grafica_OFF(bool OFF)
{
    if(OFF==true) timer_grafica->stop();
    else timer_grafica->start(PS.myPID()->get_T()*1000); //llevando a ms
}

void xControlador::modo_supervision()
{
    static bool FirstTime=true;

    ui->MyWindows->setCurrentIndex(0);
    ui->actionSupervision->setEnabled(false);
    ui->actionPID->setEnabled(true);
    ui->actionFUZZY->setEnabled(true);
    ui->btnEnviar->setEnabled(true);

    ui->menuColor_Grafica->setEnabled(false);

    modo_actual=SUPERVISION;

    if(FirstTime)
    {
        PS.set_etapa(Inicio);
        ui->menuModo->setEnabled(false);
        ui->actionPID->setEnabled(false); //para deshabilitar shortcuts
        ui->actionFUZZY->setEnabled(false);
        ui->actionHistorial->setEnabled(false);
        ui->menuCambiar_velocidad_de_comunicacion->setEnabled(true);
        ui->menuCambiar_puerto_COM->setEnabled(true);
        FirstTime=false;
    }
    else
    {
        PS.set_etapa(Supervision);
        timer->setInterval(100);
        set_timer_grafica_OFF(false);
    }

    PS.mySendBYTE(inicio_trama);
    PS.mySendBYTE(estado_supervision);
    PS.mySendBYTE(13);
    PS.set_data_sent(false);
    contador=9;

    setGeometry(200,100,560,530);
    statusBar()->showMessage(tr("Modo Supervision"));

    Plot->setVisible(false);
    PlotHistorial->setVisible(false);
}

void xControlador::modo_pid()
{
    ui->MyWindows->setCurrentIndex(1);
    ui->actionSupervision->setEnabled(true);
    ui->actionPID->setEnabled(false);
    ui->actionFUZZY->setEnabled(true);
    Plot->setTitle("PID Profesional");

    ui->menuColor_Grafica->setEnabled(true);

    set_timer_grafica_OFF(false);

    modo_actual=PID;

    ui->label_PI->setVisible(false);
    ui->label_PD->setVisible(false);
    ui->lcdPD->setVisible(false);
    ui->lcdPI->setVisible(false);
    ui->label_stepPD->setVisible(false);
    ui->label_stepPI->setVisible(false);
    ui->lcdStepPD->setVisible(false);
    ui->lcdStepPI->setVisible(false);
    ui->lcdPi->setVisible(false);
    ui->label_Kpi->setVisible(false);

    parametros_PID();

    PS.myPID()->set_isFuzzy(false);

    timer->setInterval(T_Rx);
    PS.set_etapa(Control);

    PS.mySendBYTE(inicio_trama);
    PS.mySendBYTE(estado_pid);
    PS.mySendBYTE(13);
    PS.set_data_sent(false);
    contador=19;

    setGeometry(200,100,963,550);
    statusBar()->showMessage(tr("Modo Control utilizando un PID profesional. "
                                "ADVERTENCIA: Si no se recivieron correctamente"
                                " los parámetros presionar el botón 'Pedir reenvío'."));

    Plot->setGeometry(325,50,600,400);
    Plot->setVisible(true);

    PlotHistorial->setVisible(false);
}

void xControlador::modo_fuzzy()
{
    ui->MyWindows->setCurrentIndex(1);
    ui->actionSupervision->setEnabled(true);
    ui->actionPID->setEnabled(true);
    ui->actionFUZZY->setEnabled(false);
    Plot->setTitle("PID fuzzy");

    ui->menuColor_Grafica->setEnabled(true);

    set_timer_grafica_OFF(false);

    modo_actual=FUZZY;

    ui->label_PI->setVisible(true);
    ui->label_PD->setVisible(true);
    ui->lcdPD->setVisible(true);
    ui->lcdPI->setVisible(true);
    ui->label_stepPD->setVisible(true);
    ui->label_stepPI->setVisible(true);
    ui->lcdStepPD->setVisible(true);
    ui->lcdStepPI->setVisible(true);
    ui->lcdPi->setVisible(true);
    ui->label_Kpi->setVisible(true);

    parametros_Fuzzy();

    PS.myPID()->set_isFuzzy(true);    

    timer->setInterval(T_Rx);
    PS.set_etapa(Control);

    PS.mySendBYTE(inicio_trama);
    PS.mySendBYTE(estado_fuzzy);
    PS.mySendBYTE(13);
    PS.set_data_sent(false);
    contador=19;

    setGeometry(200,100,963,550);
    statusBar()->showMessage(tr("Modo Control utilizando un PID fuzzy. "
                                "ADVERTENCIA: Si no se recivieron correctamente"
                                " los parámetros presionar el botón 'Pedir reenvío'."));

    Plot->setGeometry(325,50,600,400);
    Plot->setVisible(true);

    PlotHistorial->setVisible(false);
}

void xControlador::historial()
{
    ui->MyWindows->setCurrentIndex(2);
    ui->actionSupervision->setEnabled(true);
    ui->actionPID->setEnabled(true);
    ui->actionFUZZY->setEnabled(true);
    ui->actionHistorial->setEnabled(false);

    ui->menuColor_Grafica->setEnabled(false);
    ui->menuModo->setEnabled(false);

    PS.mySendBYTE(estado_supervision);
    //para detener a los controladores y que no seguir Rx datos para que no
    //cambien los arreglos que se grafican

    setGeometry(200,100,750,520);
    statusBar()->showMessage(tr("Historial"));

    PlotHistorial->setVisible(true);
    Plot->setVisible(false);

    for(int value=0;value<PS.myPID()->get_desplazador();value++)
    {
        PS.myPID()->Ycurves[value]->setData(PS.myPID()->Ycurves[value]->bTiempo,
                                            PS.myPID()->Ycurves[value]->Buffer,array_size);
        PS.myPID()->Ecurves[value]->setData(PS.myPID()->Ecurves[value]->bTiempo,
                                            PS.myPID()->Ecurves[value]->Buffer,array_size);
        PS.myPID()->Ucurves[value]->setData(PS.myPID()->Ucurves[value]->bTiempo,
                                            PS.myPID()->Ucurves[value]->Buffer,array_size);
        PS.myPID()->Rcurves[value]->setData(PS.myPID()->Rcurves[value]->bTiempo,
                                            PS.myPID()->Rcurves[value]->Buffer,array_size);
    }  

    graficar_historial();
}

void xControlador::parametros_Fuzzy()
{
    ui->cbParametros->clear();

    ui->cbParametros->addItem("Kp"); //index=0
    ui->cbParametros->addItem("Ki"); //index=1
    ui->cbParametros->addItem("Kd"); //index=2
    ui->cbParametros->addItem("F"); //index=3
    ui->cbParametros->addItem("Tc"); //index=4
    ui->cbParametros->addItem("universo PI");  //index=5
    ui->cbParametros->addItem("universo PD");  //index=6
    ui->cbParametros->addItem("step PD");  //index=7
    ui->cbParametros->addItem("step PI");  //index=8
    ui->cbParametros->addItem("Kpi");  //index=9
    if(ui->cbParametros->currentIndex()==manual)
        ui->cbParametros->addItem("u (variable de control)");  //index=10
}

void xControlador::parametros_PID()
{
    ui->cbParametros->clear();

    ui->cbParametros->addItem("Kp"); //index=0
    ui->cbParametros->addItem("Ki"); //index=1
    ui->cbParametros->addItem("Kd"); //index=2
    ui->cbParametros->addItem("F"); //index=3
    ui->cbParametros->addItem("Tc"); //index=4
    if(ui->cbParametros->currentIndex()==manual)
        ui->cbParametros->addItem("u (variable de control)");  //index=5
}

void xControlador::contextMenuEvent(QContextMenuEvent *event)
{
    if(ui->MyWindows->currentIndex()!=2)
    {
        QMenu rcMenu;   //rc de right click
        rcMenu.addAction(ui->actionSupervision);
        rcMenu.addAction(ui->actionPID);
        rcMenu.addAction(ui->actionFUZZY);
        rcMenu.exec(event->globalPos());
    }
}

void xControlador::put_message(QString titulo, QString mensage)
{
    QMessageBox::about(this,titulo,mensage);
}

void xControlador::on_actionSupervision_triggered()
{
    modo_supervision();
}

void xControlador::on_actionPID_triggered()
{
    modo_pid();
}

void xControlador::on_actionSalir_triggered()
{
    close();
}

void xControlador::on_actionAcerca_de_triggered()
{
    put_message(tr("Acerca de..."),tr("Nombre del software: xControlador.\n "
                                      "Desarrollado por:\n "
                                      "    Ramón Carrasco Duboué.\n"
                                      "    Año: 2012."));
}

void xControlador::on_actionAyuda_triggered()
{
    ayuda.show();
    /*put_message(tr("Ayuda"),tr("Presione click derecho "
                               "para alternar entre los modos supervision y control."
                               "ADVERTENCIA: si se cambia el Tc en el modo Fuzzy"
                               "y este es menor que el tiempo que demoran los algoritmos"
                               "en ejecutarse, entonces la bandera de calcular el algoritmo fuzzy"
                               "estara activada todo el tiempo. Para aumentar la velocidad del "
                               "algoritmo disminuir los step, teniendo en cuenta que disminuira"
                               "la exactitud."));*/
}

void xControlador::TMR_grafica()
{
    static long int cont_min=0;
  //  ui->statusBar->showMessage(QString::number(timerson.elapsed()));
//timerson.start();

    if(fGraficar)
    {
        PS.myPID()->Graficar();
        PS.salvar_muestras_files();

        if(PS.myPID()->get_flag_min())
        {
            cont_min++;
            if(cont_min==1)
               // Plot->add_marker(min,QwtText(QString::number(cont_min)+"minuto"),false,cont_min*60);
                Plot->add_marker(min,Qt::AlignRight | Qt::AlignBottom,QPen(color_actual, 0, Qt::DashLine),QwtText(QString::number(cont_min)+"minuto"),false,cont_min*60);
            else
              //  Plot->add_marker(min,QwtText(QString::number(cont_min)+"minutos"),false,cont_min*60);
                Plot->add_marker(min,Qt::AlignRight | Qt::AlignBottom,QPen(color_actual, 0, Qt::DashLine),QwtText(QString::number(cont_min)+"minutos"),false,cont_min*60);
        }
    }

    if(PS.get_data_sent() && contador==0)
    {
        PS.set_T_over(true);
        //contador=9;
    }
    else
        contador--;

//ui->statusBar->showMessage(QString::number(timerson.elapsed()));
}

void xControlador::TMR()
{
    static bool conected=false,first_time=true,fErrorFirstTime=false;

    if(PS.Data_Received())
    {
        if(!conected)
        {
            if(PS.Conected())
            {
                conected=true;
                ui->MyWindows->setEnabled(true);
                ui->menuModo->setEnabled(true);
                ui->actionPID->setEnabled(true);
                ui->actionFUZZY->setEnabled(true);
                ui->actionHistorial->setEnabled(true);
                ui->menuCambiar_velocidad_de_comunicacion->setEnabled(false);
                ui->menuCambiar_puerto_COM->setEnabled(false);
            }
        }
        else
        {
            switch(PS.get_etapa())
            {
            case Control:
                if(PS.get_Ract())
                {
                    Actualizar_Ref();
                    PS.setOFF_Ract();
                }

                if(PS.get_CURVEact())
                {
                    qDebug("ENTRO en CURVEact");
                //    PS.myPID()->set_Resolucion((double)ui->spinSensor->value()/1023);
                    PS.myPID()->cambiar_escala(Plot);

                    PS.set_CURVEact(false);

                    Actualizar_Ref();
                }

                if(PS.get_Tcact())
                {
                    ui->lcdT->display(PS.myPID()->get_Tc());
                    PS.setOFF_Tcact();
                }

                if(PS.get_YUact())
                {
                    if(first_time && !fErrorFirstTime)
                    {
                        fGraficar=true;
                        qDebug("fGraficar=true");
                        first_time=false;
                    }
                    //borrar cuando termine el capitulo de simulacion
                    /*    if(fGraficar)
                        {
                            PS.myPID()->Graficar();
                            PS.salvar_muestras_files();
                        }*/

                    if(PS.myPID()->get_fconvUI()==false)
                    {
                        ui->lcdY->display(PS.myPID()->get_yf());
                        ui->lcdE->display(PS.myPID()->get_e());
                        ui->lcdU->display(PS.myPID()->get_u());
                    }
                    else
                    {
                        ui->lcdY->display(PS.myPID()->get_yf_UI());
                        ui->lcdE->display(PS.myPID()->get_e_UI());
                        ui->lcdU->display(PS.myPID()->get_u_UI());
                    }
                    ui->lcdtime->display(PS.get_muestras());

                    PS.setOFF_YUact();
                }

                if(PS.get_PARAMact())
                {
                    ui->lcdP->display(PS.myPID()->get_Kp());
                    ui->lcdI->display(PS.myPID()->get_Ki());
                    ui->lcdD->display(PS.myPID()->get_Kd());

                    if(PS.myPID()->get_Tc()>0 && PS.myPID()->get_Tc()<10)  //cuidandome de errores de Rx
                        ui->lcdT->display(PS.myPID()->get_Tc());
                    else
                    {
                        stop_grafica();
                        put_message(tr("ERROR"),tr("Error en la Rx de datos. "
                                                   "Presione el botón 'Pedir reenvío' y "
                                                   "posteriormente el botón 'Continuar.'"));
                    }

                    if(PS.myPID()->get_isFuzzy())
                    {
                        if(PS.myPID()->get_fconvUI()==false)
                        {
                            ui->lcdPD->display(PS.myPID()->get_univPD());
                            ui->lcdPI->display(PS.myPID()->get_univPI());
                            ui->lcdStepPD->display(PS.myPID()->get_stepPD());
                            ui->lcdStepPI->display(PS.myPID()->get_stepPI());
                        }
                        else
                        {
                            ui->lcdPD->display(PS.myPID()->get_univPD_UI());
                            ui->lcdPI->display(PS.myPID()->get_univPI_UI());
                            ui->lcdStepPD->display(PS.myPID()->get_stepPD_UI());
                            ui->lcdStepPI->display(PS.myPID()->get_stepPI_UI());
                        }
                        ui->lcdPi->display(PS.myPID()->get_Kpi());
                    }
                    ui->lcdF->display(PS.myPID()->get_F());

                    PS.setOFF_PARAMact();
                }

                if(PS.get_fTSupervision())
                {
                    cambiar_Tsupervision();

                    PS.set_fTSupervision(false);
                }

                break;  //fin del case Control
            case Supervision:                
                ui->textEdit->append((char*)PS.get_bufferRx());
                break;
            }

            if(PS.get_ErrorRx())
            {
             //   stop_grafica();

                if(first_time)
                {
                    fErrorFirstTime=true;
                    first_time=false;
                }

                ui->statusBar->showMessage(tr("Puede haber ocurrido un error en la"
                                              "recepción o transmisión de datos,"
                                              "pedir reenvío para asegurarse"),5000);
               // put_message("Error",tr("Error de recepción, pedir reenvío"));
                PS.set_ErrorRx_false();
            }
        }
    }
}

void xControlador::on_action9600_triggered()
{
    PS.change_BaudRate(0);
}

void xControlador::on_action1200_triggered()
{
    PS.change_BaudRate(1);
}

void xControlador::on_action2400_triggered()
{
    PS.change_BaudRate(2);
}

void xControlador::on_action4800_triggered()
{
    PS.change_BaudRate(3);
}

void xControlador::on_action19200_triggered()
{
    PS.change_BaudRate(4);
}

void xControlador::on_action28800_triggered()
{
    PS.change_BaudRate(5);
}

void xControlador::on_action33600_triggered()
{
    PS.change_BaudRate(6);
}

void xControlador::on_action38400_triggered()
{
    PS.change_BaudRate(7);
}

void xControlador::on_btnModulo_clicked()
{
    PS.mySendBYTE(inicio_trama);
    PS.mySendBYTE(tipo_de_modulo);
    PS.mySendBYTE(13);
}

void xControlador::on_btnEntAna_clicked()
{
    PS.mySendBYTE(inicio_trama);
    PS.mySendBYTE(entrada_analogica);
    PS.mySendBYTE(ui->cbEntAna->currentIndex());
    PS.mySendBYTE(13);
}

void xControlador::on_btnEntDig_clicked()
{
    PS.mySendBYTE(inicio_trama);
    PS.mySendBYTE(entrada_digital);
    PS.mySendBYTE(ui->cbEntDig->currentIndex());
    PS.mySendBYTE(13);
}

void xControlador::on_btnCU_clicked()
{
    int i;
    unsigned char buffer[Tx_size];

    // %duty cycle = (value / [ 4 * (PR2 +1 ) ])*100
    // .: value = (%duty cycle / 100)*[ 4 * (PR2 +1 ) ]

    QString *array_temp=new QString();
    wchar_t array[Tx_size+1];

    *array_temp=ui->sBCU->text();
    array_temp->toWCharArray(array);

    for(i=0;i<Tx_size;i++)
    {
        if((array[i]<0x30 || array[i]>0x39)) break;
        else buffer[i]=array[i];
    }

    switch(ui->cbCU->currentIndex())
    {
    case 0: buffer[i]='u'; break;
    case 1: buffer[i]='d'; break;
    }

    buffer[i+1]=13;

    PS.send_buffer(buffer,ciclo_util_PWM,i+2);

    PS.set_data_sent(true);
    contador=9;
}

void xControlador::on_btnSalDig_clicked()
{
    PS.mySendBYTE(inicio_trama);
    PS.mySendBYTE(salida_digital);
    PS.mySendBYTE(ui->cbSalDig->currentIndex());
    PS.mySendBYTE(ui->sBSalDig->value());
    PS.mySendBYTE(13);
    PS.set_data_sent(true);
    contador=9;
}

void xControlador::on_btnBaudRateRx_clicked()
{
    PS.mySendBYTE(inicio_trama);
    PS.mySendBYTE(lectura_configuracion);
    PS.mySendBYTE(1);
    PS.mySendBYTE(13);
}

void xControlador::on_btnPWMRx_clicked()
{
    PS.mySendBYTE(inicio_trama);
    PS.mySendBYTE(lectura_configuracion);
    PS.mySendBYTE(2);
    PS.mySendBYTE(13);
}

void xControlador::on_btnProcesamientoRx_clicked()
{
    PS.mySendBYTE(inicio_trama);
    PS.mySendBYTE(lectura_configuracion);
    PS.mySendBYTE(3);
    PS.mySendBYTE(13);
}

void xControlador::on_btnCantMRx_clicked()
{
    PS.mySendBYTE(inicio_trama);
    PS.mySendBYTE(lectura_configuracion);
    PS.mySendBYTE(4);
    PS.mySendBYTE(13);
}

void xControlador::on_btnReset_clicked()
{
    PS.mySendBYTE(inicio_trama);
    PS.mySendBYTE(RESET);
    PS.mySendBYTE(13);
}

void xControlador::on_cbBaudRate_currentIndexChanged(int index)
{
    if(index!=0)
    {
        PS.mySendBYTE(inicio_trama);
        PS.mySendBYTE(escritura_configuracion);
        PS.mySendBYTE(1);
        PS.mySendBYTE(index-1);
        PS.mySendBYTE(13);
        //cambia a la velocidad de comunicacion que se usara la proxima vez
        //que se reinicie el microcontrolador
        PS.set_data_sent(true);
        contador=9;
    }
}

void xControlador::on_cbCantM_currentIndexChanged(int index)
{
    if(index!=0)
    {
        PS.mySendBYTE(inicio_trama);
        PS.mySendBYTE(escritura_configuracion);
        PS.mySendBYTE(4);
        PS.mySendBYTE(index-1);
        PS.mySendBYTE(13);
        switch(index-1)
        {
        case 0: PS.myPID()->set_F(2); break;
        case 1: PS.myPID()->set_F(4); break;
        case 2: PS.myPID()->set_F(8); break;
        case 3: PS.myPID()->set_F(16); break;
        }
        PS.set_data_sent(true);
        contador=9;
    }
}

void xControlador::on_cbPWM_currentIndexChanged(int index)
{
    if(index!=0)
    {
        PS.mySendBYTE(inicio_trama);
        PS.mySendBYTE(escritura_configuracion);
        PS.mySendBYTE(2);
        PS.mySendBYTE(index-1);
        PS.mySendBYTE(13);
        PS.set_data_sent(true);
        contador=9;
     /*
        switch(index-1)
          {
            case 0: PR2=255; break;   //1.22KHz [0.82ms]
            case 1: PR2=127; break;   //2.44KHz [0.41ms]
            case 2: PR2=63; break;  //4.88KHz [0.20ms]
            case 3: PR2=170; break;  //7.32KHz [0.14ms]
            case 4: PR2=127; break;  //9.76KHz [0.10ms]
            case 5: PR2=101; break;  //12.20KHz [81.9us]
            case 6: PR2=72; break;  //17.08KHz [58.5us]
            case 7: PR2=255; break;  //19.53KHz [51.2us]
            case 8: PR2=165; break;  //30KHz [33us]
            default: PR2=165; break;
          }
      */
    }
}

void xControlador::on_cbProcesamiento_currentIndexChanged(int index)
{
    TipoProcesamiento temp;

    if(index!=0)
    {
        switch(index-1)
        {
        case 0: ui->cbCantM->setEnabled(false); temp=SinProcesamiento; break;
        case 1: ui->cbCantM->setEnabled(true); temp=FiltroPromedio; break;
        case 2: ui->cbCantM->setEnabled(false); temp=ConvUI; break;
        case 3: ui->cbCantM->setEnabled(true); temp=FiltroConv; break;
        }

        if(PS.myPID()->get_tipo_procesamiento()!=temp)
        {
            PS.mySendBYTE(inicio_trama);
            PS.mySendBYTE(escritura_configuracion);
            PS.mySendBYTE(3);
            PS.mySendBYTE(index-1);
            PS.mySendBYTE(13);

            PS.myPID()->set_tipo_procesamiento(temp);

            PS.set_CURVEact(true);
            PS.setON_PARAMact();
        }
        PS.set_data_sent(true);
        contador=9;
    }
}

void xControlador::on_btnEnviar_clicked()
{
    int i;
    unsigned char buffer[Tx_size];

    QString *array_temp=new QString();
    wchar_t array[Tx_size+1];

    int temporal;

    if(!PS.myPID()->get_isFuzzy()) temporal = 5;
    else temporal = 10;  //u

    if( ( ui->cbParametros->currentIndex()==temporal ||
         (ui->cbParametros->currentIndex()==5 &&
          ui->edtEnviar->value()/PS.myPID()->Resolucion() < 1023 ||
          ui->cbParametros->currentIndex()==6 ) ||
         ( ui->cbParametros->currentIndex()==7 &&
         (ui->edtEnviar->value()/PS.myPID()->Resolucion() > PS.myPID()->get_univPD()/10) ) ||
         ( ui->cbParametros->currentIndex()==8 &&
         (ui->edtEnviar->value()/PS.myPID()->Resolucion() > PS.myPID()->get_univPI()/10) ) ) &&
       PS.myPID()->get_fconvUI()==true )
    {
        *array_temp = QString::number(ui->edtEnviar->value()/PS.myPID()->Resolucion());
    }
    else if(ui->cbParametros->currentIndex()==4)
    {
        float temp=ui->edtEnviar->value();

        if(temp < 0.01)
            temp=0.01;

        if(!PS.myPID()->get_isFuzzy())
        {
            if(temp > 0.1)
                temp=0.1;
        }
        else
            if(temp > 0.14)
                temp=0.14;

        *array_temp = QString::number((temp/0.01));

        PS.myPID()->set_Tc(temp,*ui->lcdT);
        cambiar_Tsupervision();
    }
    //Si esta seleccionado stepPD
    else if( ui->cbParametros->currentIndex()==7 &&
            (ui->edtEnviar->value() < PS.myPID()->get_univPD()/8) &&
            PS.myPID()->get_fconvUI()==false )
    {
        *array_temp = QString::number(PS.myPID()->get_univPD()/8);
    }
    else if( ui->cbParametros->currentIndex()==7 &&
            (ui->edtEnviar->value()/PS.myPID()->Resolucion() < PS.myPID()->get_univPD()/8) &&
            PS.myPID()->get_fconvUI()==true )
    {
        *array_temp = QString::number(PS.myPID()->get_univPD()/8);
    }
    //Si esta seleccionado stepPI
    else if( ui->cbParametros->currentIndex()==8 &&
            (ui->edtEnviar->value() < PS.myPID()->get_univPI()/8) &&
            PS.myPID()->get_fconvUI()==false )
    {
        *array_temp = QString::number(PS.myPID()->get_univPI()/8);
    }
    else if( ui->cbParametros->currentIndex()==8 &&
            (ui->edtEnviar->value()/PS.myPID()->Resolucion() < PS.myPID()->get_univPI()/8) &&
            PS.myPID()->get_fconvUI()==true )
    {
        *array_temp = QString::number(PS.myPID()->get_univPI()/8);
    }
    //Si esta seleccionado univPI o univPD
    else if( (ui->cbParametros->currentIndex()==5 || ui->cbParametros->currentIndex()==6) &&
             (ui->edtEnviar->value() > 1023) &&
             PS.myPID()->get_fconvUI()==false )
    {
        *array_temp = QString::number(1023);
    }
    else if( (ui->cbParametros->currentIndex()==5 || ui->cbParametros->currentIndex()==6) &&
             (ui->edtEnviar->value()/PS.myPID()->Resolucion() > 1023) &&
             PS.myPID()->get_fconvUI()==true )
    {
        *array_temp = QString::number(1023);
    }
    else
        *array_temp=QString::number(ui->edtEnviar->value());

    array_temp->toWCharArray(array);

    for(i=0;i<Tx_size;i++)
    {
        if(array[i]!='.' && (array[i]<0x30 || array[i]>0x39)) break;
        else buffer[i]=array[i];
    }

    switch(ui->cbParametros->currentIndex())
    {
    case 0: buffer[i]='p'; PS.myPID()->set_Kp(ui->edtEnviar->value(),*ui->lcdP); break;
    case 1: buffer[i]='i'; PS.myPID()->set_Ki(ui->edtEnviar->value(),*ui->lcdI); break;
    case 2: buffer[i]='d'; PS.myPID()->set_Kd(ui->edtEnviar->value(),*ui->lcdD); break;
    case 3: buffer[i]='f'; PS.myPID()->set_F((int)ui->edtEnviar->value(),*ui->lcdF); break;
    case 4: buffer[i]='t'; break;
    case 5:
        if(!PS.myPID()->get_isFuzzy())
        {
            buffer[i]='u';
            PS.myPID()->set_u((int)ui->edtEnviar->value(),*ui->lcdU);
            if(PS.myPID()->get_fconvUI())
                PS.myPID()->set_u(PS.myPID()->get_u()/PS.myPID()->Resolucion());
        }
        else
        {
            buffer[i]='I';
            PS.myPID()->set_univPI((int)ui->edtEnviar->value(),*ui->lcdPI);
            if(PS.myPID()->get_fconvUI())
                PS.myPID()->set_univPI(PS.myPID()->get_univPI()/PS.myPID()->Resolucion());
        }
        break;
    case 6:
        buffer[i]='D';
        PS.myPID()->set_univPD((int)ui->edtEnviar->value(),*ui->lcdPD);
        if(PS.myPID()->get_fconvUI())
            PS.myPID()->set_univPD(PS.myPID()->get_univPD()/PS.myPID()->Resolucion());
        break;
    case 7:
        buffer[i]='s';
        if(ui->edtEnviar->value() < PS.myPID()->get_univPD()/8)
            PS.myPID()->set_stepPD((float)PS.myPID()->get_univPD()/8,*ui->lcdStepPD);
        else
            PS.myPID()->set_stepPD(ui->edtEnviar->value(),*ui->lcdStepPD);

        if(PS.myPID()->get_fconvUI())
            PS.myPID()->set_stepPD(PS.myPID()->get_stepPD()/PS.myPID()->Resolucion());
        break;
    case 8:
        buffer[i]='S';
        if(ui->edtEnviar->value() < PS.myPID()->get_univPI()/8)
            PS.myPID()->set_stepPI((float)PS.myPID()->get_univPI()/8,*ui->lcdStepPI);
        else
            PS.myPID()->set_stepPI(ui->edtEnviar->value(),*ui->lcdStepPI);

        if(PS.myPID()->get_fconvUI())
            PS.myPID()->set_stepPI(PS.myPID()->get_stepPI()/PS.myPID()->Resolucion());
        break;
    case 9: buffer[i]='z'; PS.myPID()->set_Kpi(ui->edtEnviar->value(),*ui->lcdPi); break;
    case 10:
        buffer[i]='u';
        PS.myPID()->set_u((int)ui->edtEnviar->value(),*ui->lcdU);
        if(PS.myPID()->get_fconvUI())
            PS.myPID()->set_u(PS.myPID()->get_u()/PS.myPID()->Resolucion());
    }

    buffer[i+1]=13;

    PS.set_bufferTx(buffer);
    PS.set_icounter(i+2);

    PS.Parameter_changed();  //para saber que tengo algo que enviar al uC

    PS.set_data_sent(true);
    contador=49;
}

void xControlador::on_btnFinalizar_clicked()
{
    ui->edtEnviar->setValue(0);
    PS.mySendBYTE(inicio_trama);
    PS.mySendBYTE(end_of_Tx);
    PS.mySendBYTE(13);
    PS.set_data_sent(true);
    contador=29;

    PS.myPID()->SaveParametros();
    statusBar()->showMessage("Graficando");
}

void xControlador::Actualizar_Ref()
{
    if(PS.myPID()->get_fconvUI())
    {
        ui->lcdR->display(PS.myPID()->get_rf_UI());
        Plot->set_Y_value(Ref,PS.myPID()->get_rf_UI());
        Plot->setAxisScale(0,0,ui->spinSensor->value(),500);
        Plot->setAxisTitle(QwtPlot::yLeft, "amplitud[mV]");
        ui->lcdNumber->display(PS.myPID()->get_rf_UI());
        ui->verticalSlider->setMaximum(ui->spinSensor->value());
        ui->verticalSlider->setValue(PS.myPID()->get_rf_UI());
    }
    else
    {
        ui->lcdR->display(PS.myPID()->get_rf());
        Plot->set_Y_value(Ref,PS.myPID()->get_rf());
        Plot->setAxisScale(0,0,ui->spinSensor->value()/PS.myPID()->Resolucion(),100);
        Plot->setAxisTitle(QwtPlot::yLeft, "amplitud[unidades de conversor]");
        ui->lcdNumber->display(PS.myPID()->get_rf());
        ui->verticalSlider->setMaximum(ui->spinSensor->value()/PS.myPID()->Resolucion());
        ui->verticalSlider->setValue(PS.myPID()->get_rf());
    }
}

void xControlador::on_comboBox_currentIndexChanged(int index)
{
    PS.myPID()->set_Modo(index);

    PS.mySendBYTE(inicio_trama);
    PS.mySendBYTE(cambiar_modo);
    PS.mySendBYTE(index);
    PS.mySendBYTE(13);
    PS.set_data_sent(true);
    contador=9;

    if(index==manual)
        ui->cbParametros->addItem("u");
    else
    {
        if(!PS.myPID()->get_isFuzzy()) ui->cbParametros->removeItem(5);
        else ui->cbParametros->removeItem(10);
    }
}

void xControlador::on_cbParametros_currentIndexChanged(int index)
{
    if(index==3)
        ui->edtEnviar->setEnabled(PS.myPID()->get_fcantM());
    else
        ui->edtEnviar->setEnabled(true);

    if(index==4)    //Tc
        ui->lblunidad->setText("s");
    else
        ui->lblunidad->setText("u");
}

void xControlador::on_btnZoom_clicked()
{    
    if(PlotHistorial->zoomer->isEnabled()==false)
    {
        PlotHistorial->zoomer->setEnabled(true);
        PlotHistorial->panner->setEnabled(false);
        ui->btnZoom->setToolTip("Desactivar Zoom");
        ui->checkConvUI->setEnabled(false);
    }
    else
    {
        PlotHistorial->zoomer->setEnabled(false);
        PlotHistorial->panner->setEnabled(true);
        ui->btnZoom->setToolTip("Activar Zoom");
        ui->checkConvUI->setEnabled(true);
    }
}

void xControlador::stop_grafica()
{
    ui->btnPlay->setVisible(true);
    ui->btnStop->setVisible(false);
    ui->btnPlay->setEnabled(true);
    fGraficar=false;
}

void xControlador::on_btnStop_clicked()
{
    stop_grafica();
}

void xControlador::play_grafica()
{
    ui->btnPlay->setVisible(false);
    ui->btnStop->setVisible(true);
    fGraficar=true;
}

void xControlador::on_btnPlay_clicked()
{
    play_grafica();
}

void xControlador::on_verticalSlider_valueChanged(int value)
{
    ui->lcdNumber->display(value);
    if(PS.myPID()->get_fconvUI())
        PS.myPID()->set_tref(value/PS.myPID()->Resolucion());
    else
        PS.myPID()->set_tref(value);
    statusBar()->showMessage("Editando Referencia");
}

void xControlador::enviar_Referencia()
{
    int i=0;
    unsigned char buffer[Tx_size];

    QString *a = new QString();
    wchar_t array[Tx_size+1];

    *a = QString::number(PS.myPID()->get_tref());

    a->toWCharArray(array);

    //si la division da un float no importara
    //cuando en el for se encuentre con el punto decimal
    //se sale, es decir, es como si estuviera tomando el valor
    //por defecto (no por exceso)
    for(i=0;i<Tx_size;i++)
    {
        if(array[i]<0x30 || array[i]>0x39) break;
        else buffer[i]=array[i];
    }

    buffer[i]='r';
    buffer[i+1]=13;

    PS.set_bufferTx(buffer);
    PS.set_icounter(i+2);

    PS.Reference_changed();

    statusBar()->showMessage("Graficando");

    PS.set_data_sent(true);
    contador=29;
}

void xControlador::on_btnSlider_clicked()
{
    enviar_Referencia();
    //PS.reset_muestras(); //reseteo si quiero
}

void xControlador::on_actionAbrir_Fichero_triggered()
{
    LF.show();
    PS.myPID()->LoadFile(*LF.change_text());
}

void xControlador::on_actionDefault_triggered()
{
    ui->actionDefault->setEnabled(false);
    ui->actionGray->setEnabled(true);
    ui->actionGreen->setEnabled(true);
    ui->actionPastel->setEnabled(true);

    ui->MyWindows->setStyleSheet("background-color: rgb(206, 255, 252)");

    Plot->set_legend_style_sheet("background-color: rgb(206, 255, 252)");

    ui->lcdR->setPalette(Qt::black);
    ui->lcdtime->setPalette(Qt::black);
    ui->lcdNumber->setPalette(Qt::black);
    ui->lcdT->setPalette(Qt::black);
    ui->lcdD->setPalette(Qt::black);
    ui->lcdE->setPalette(Qt::black);
    ui->lcdF->setPalette(Qt::black);
    ui->lcdI->setPalette(Qt::black);
    ui->lcdP->setPalette(Qt::black);
    ui->lcdU->setPalette(Qt::black);
    ui->lcdY->setPalette(Qt::black);
    ui->lcdPi->setPalette(Qt::black);
    ui->lcdStepPD->setPalette(Qt::black);
    ui->lcdStepPI->setPalette(Qt::black);
    ui->lcdPD->setPalette(Qt::black);
    ui->lcdPI->setPalette(Qt::black);
}

void xControlador::on_actionGray_triggered()
{
    ui->actionGray->setEnabled(false);
    ui->actionDefault->setEnabled(true);
    ui->actionGreen->setEnabled(true);
    ui->actionPastel->setEnabled(true);

    ui->MyWindows->setStyleSheet("");

    Plot->set_legend_style_sheet("");

    ui->lcdR->setPalette(Qt::black);
    ui->lcdtime->setPalette(Qt::black);
    ui->lcdNumber->setPalette(Qt::black);
    ui->lcdT->setPalette(Qt::black);
    ui->lcdD->setPalette(Qt::black);
    ui->lcdE->setPalette(Qt::black);
    ui->lcdF->setPalette(Qt::black);
    ui->lcdI->setPalette(Qt::black);
    ui->lcdP->setPalette(Qt::black);
    ui->lcdU->setPalette(Qt::black);
    ui->lcdY->setPalette(Qt::black);
    ui->lcdPi->setPalette(Qt::black);
    ui->lcdStepPD->setPalette(Qt::black);
    ui->lcdStepPI->setPalette(Qt::black);
    ui->lcdPD->setPalette(Qt::black);
    ui->lcdPI->setPalette(Qt::black);
}

void xControlador::on_btnActualizar_clicked()
{
 //   PS.myPID()->set_Resolucion((double)ui->spinSensor->value()/1023);

    Actualizar_Ref();
    enviar_Referencia();

    ui->btnActualizar->setEnabled(false);
    ui->verticalSlider->setEnabled(true);
    ui->btnSlider->setEnabled(true);
}

void xControlador::on_spinSensor_valueChanged(int value)
{
    ui->btnActualizar->setEnabled(true);
    ui->verticalSlider->setEnabled(false);
    ui->btnSlider->setEnabled(false);
}

void xControlador::on_actionFUZZY_triggered()
{
    modo_fuzzy();
}

void xControlador::on_actionBlanco_triggered()
{
    color_actual=QColor(Qt::black);
    Plot->setCanvasBackground(QColor(Qt::white));
    Plot->picker->setTrackerPen(color_actual);
    Plot->set_grid_color(color_actual);
    Plot->set_marker_color(Ref,color_actual);
    Plot->set_marker_color(seg1,color_actual);
    Plot->set_marker_color(seg5,color_actual);
    Plot->set_marker_color(seg10,color_actual);
    Plot->set_marker_color(seg20,color_actual);
    ui->actionBlanco->setEnabled(false);
    ui->actionAzul->setEnabled(true);
    ui->actionMostaza->setEnabled(true);
    ui->actionOscuro->setEnabled(true);
}

void xControlador::on_actionAzul_triggered()
{
    color_actual=QColor(Qt::white);
    Plot->setCanvasBackground(QColor(Qt::darkBlue));
    Plot->picker->setTrackerPen(color_actual);
    Plot->set_grid_color(color_actual);
    Plot->set_marker_color(Ref,color_actual);
    Plot->set_marker_color(seg1,color_actual);
    Plot->set_marker_color(seg5,color_actual);
    Plot->set_marker_color(seg10,color_actual);
    Plot->set_marker_color(seg20,color_actual);
 //   PlotHistorial->setCanvasBackground(QColor(Qt::darkBlue));
    ui->actionAzul->setEnabled(false);
    ui->actionBlanco->setEnabled(true);
    ui->actionMostaza->setEnabled(true);
    ui->actionOscuro->setEnabled(true);
}

void xControlador::on_actionMostaza_triggered()
{
    color_actual=QColor(Qt::black);
    const QColor bgColor(255,255,164);
    Plot->setCanvasBackground(bgColor);
    Plot->picker->setTrackerPen(color_actual);
    Plot->set_grid_color(color_actual);
    Plot->set_marker_color(Ref,color_actual);
    Plot->set_marker_color(seg1,color_actual);
    Plot->set_marker_color(seg5,color_actual);
    Plot->set_marker_color(seg10,color_actual);
    Plot->set_marker_color(seg20,color_actual);
 //   PlotHistorial->setCanvasBackground(QColor(Qt::darkGray));
    ui->actionMostaza->setEnabled(false);
    ui->actionAzul->setEnabled(true);
    ui->actionBlanco->setEnabled(true);
    ui->actionOscuro->setEnabled(true);
}

void xControlador::on_actionOscuro_triggered()
{
    color_actual=QColor(Qt::white);
    const QColor bgColor(30,30,50);
    Plot->setCanvasBackground(bgColor);
    Plot->picker->setTrackerPen(color_actual);
    Plot->set_grid_color(color_actual);
    Plot->set_marker_color(Ref,color_actual);
    Plot->set_marker_color(seg1,color_actual);
    Plot->set_marker_color(seg5,color_actual);
    Plot->set_marker_color(seg10,color_actual);
    Plot->set_marker_color(seg20,color_actual);
 //   PlotHistorial->setCanvasBackground(bgColor);
    ui->actionOscuro->setEnabled(false);
    ui->actionAzul->setEnabled(true);
    ui->actionBlanco->setEnabled(true);
    ui->actionMostaza->setEnabled(true);

    //Pone el fondo del mismo color
 //   QPalette p = palette();
 //   p.setColor(backgroundRole(), bgColor);
 //   setPalette(p);
}

void xControlador::on_actionHistorial_triggered()
{
    historial();
}

void xControlador::graficar_historial()
{    
    if(!ui->checkConvUI->isChecked())
    {
        PlotHistorial->setAxisTitle(QwtPlot::yLeft, "amplitud[unidades de conversor]");
    }
    else
    {
        PlotHistorial->setAxisTitle(QwtPlot::yLeft, "amplitud[mV]");
    }

    for(int value=0;value<PS.myPID()->get_desplazador();value++)
    {
        //PS.myPID()->Ycurves[value]->set_resolucion(4.8875);
        PS.myPID()->Ycurves[value]->Cambiar_Escala(PlotHistorial,ui->checkConvUI->isChecked());

       // PS.myPID()->Ucurves[value]->set_resolucion(4.8875);
        PS.myPID()->Ucurves[value]->Cambiar_Escala(PlotHistorial,ui->checkConvUI->isChecked());

       // PS.myPID()->Ecurves[value]->set_resolucion(4.8875);
        PS.myPID()->Ecurves[value]->Cambiar_Escala(PlotHistorial,ui->checkConvUI->isChecked());

        //PS.myPID()->Rcurves[value]->set_resolucion(4.8875);
        PS.myPID()->Rcurves[value]->Cambiar_Escala(PlotHistorial,ui->checkConvUI->isChecked());
    }

    PlotHistorial->setAxisAutoScale(0);
}

void xControlador::on_checkConvUI_clicked()
{
    graficar_historial();
}

void xControlador::on_btnAtras_clicked()
{
    switch(modo_actual)
    {
    case SUPERVISION: modo_supervision(); break;
    case PID: modo_pid(); break;
    case FUZZY: modo_fuzzy(); break;
    }

    ui->actionHistorial->setEnabled(true);
    ui->menuModo->setEnabled(true);
}

void xControlador::on_checkConvUI_toggled(bool checked)
{
    if(checked)
    {
        ui->btnZoom->setEnabled(false);
        ui->btnAtras->setEnabled(false);
    }
    else
    {
        ui->btnZoom->setEnabled(true);
        ui->btnAtras->setEnabled(true);
    }
}

void xControlador::on_btnReenvio_clicked()
{
    PS.mySendBYTE(inicio_trama);

    if(!PS.myPID()->get_isFuzzy())
        PS.mySendBYTE(estado_pid_reenvio);
    else
        PS.mySendBYTE(estado_fuzzy_reenvio);

    PS.mySendBYTE(13);
    PS.set_data_sent(true);
    contador=49;
}

void xControlador::on_btnBorrarGrafica_clicked()
{
    for(int i=0;i<PS.myPID()->get_desplazador();i++)
    {
        for(int ii=0;ii<array_size;ii++)
        {
           //Almacenando para mostrar en el historial
           PS.myPID()->Ycurves[i]->Buffer[ii] = 0;
           PS.myPID()->Ucurves[i]->Buffer[ii] = 0;
           PS.myPID()->Ecurves[i]->Buffer[ii] = 0;
           PS.myPID()->Rcurves[i]->Buffer[ii] = 0;
       }
        PS.myPID()->Ycurves[i]->setData(PS.myPID()->Ycurves[i]->bTiempo,
                                            PS.myPID()->Ycurves[i]->Buffer,array_size);
        PS.myPID()->Ecurves[i]->setData(PS.myPID()->Ecurves[i]->bTiempo,
                                            PS.myPID()->Ecurves[i]->Buffer,array_size);
        PS.myPID()->Ucurves[i]->setData(PS.myPID()->Ucurves[i]->bTiempo,
                                            PS.myPID()->Ucurves[i]->Buffer,array_size);
        PS.myPID()->Rcurves[i]->setData(PS.myPID()->Rcurves[i]->bTiempo,
                                            PS.myPID()->Rcurves[i]->Buffer,array_size);
    }
}

void xControlador::on_btnSeleccionPWM_clicked()
{
    PS.mySendBYTE(inicio_trama);
    PS.mySendBYTE(lectura_configuracion);
    PS.mySendBYTE(5);
    PS.mySendBYTE(13);
}

void xControlador::on_btnSeleccionAD_clicked()
{
    PS.mySendBYTE(inicio_trama);
    PS.mySendBYTE(lectura_configuracion);
    PS.mySendBYTE(6);
    PS.mySendBYTE(13);
}

void xControlador::on_cbSeleccionPWM_currentIndexChanged(int index)
{
    if(index!=0)
    {
        PS.mySendBYTE(inicio_trama);
        PS.mySendBYTE(escritura_configuracion);
        PS.mySendBYTE(5);
        PS.mySendBYTE(index-1);
        PS.mySendBYTE(13);
        PS.set_data_sent(true);
        contador=9;
    }
}

void xControlador::on_cbSeleccionAD_currentIndexChanged(int index)
{
    if(index!=0)
    {
        PS.mySendBYTE(inicio_trama);
        PS.mySendBYTE(escritura_configuracion);
        PS.mySendBYTE(6);
        PS.mySendBYTE(index-1);
        PS.mySendBYTE(13);
        PS.set_data_sent(true);
        contador=9;
    }
}

void xControlador::on_actionCOM1_triggered()
{
    PS.set_COM(0);
}

void xControlador::on_actionCOM2_triggered()
{
    PS.set_COM(1);
}

void xControlador::on_actionCOM3_triggered()
{
    PS.set_COM(2);
}

void xControlador::on_actionCOM4_triggered()
{
    PS.set_COM(3);
}

void xControlador::on_actionCOM5_triggered()
{
    PS.set_COM(4);
}

void xControlador::on_actionCOM6_triggered()
{
    PS.set_COM(5);
}

void xControlador::on_actionGreen_triggered()
{
    ui->actionGray->setEnabled(true);
    ui->actionDefault->setEnabled(true);
    ui->actionGreen->setEnabled(false);
    ui->actionPastel->setEnabled(true);

    ui->MyWindows->setStyleSheet("background-color: rgb(206, 255, 183)");

    Plot->set_legend_style_sheet("background-color: rgb(206, 255, 183)");

    ui->lcdR->setPalette(Qt::black);
    ui->lcdtime->setPalette(Qt::black);
    ui->lcdNumber->setPalette(Qt::black);
    ui->lcdT->setPalette(Qt::black);
    ui->lcdD->setPalette(Qt::black);
    ui->lcdE->setPalette(Qt::black);
    ui->lcdF->setPalette(Qt::black);
    ui->lcdI->setPalette(Qt::black);
    ui->lcdP->setPalette(Qt::black);
    ui->lcdU->setPalette(Qt::black);
    ui->lcdY->setPalette(Qt::black);
    ui->lcdPi->setPalette(Qt::black);
    ui->lcdStepPD->setPalette(Qt::black);
    ui->lcdStepPI->setPalette(Qt::black);
    ui->lcdPD->setPalette(Qt::black);
    ui->lcdPI->setPalette(Qt::black);
}

void xControlador::on_actionPastel_triggered()
{
    ui->actionGray->setEnabled(true);
    ui->actionDefault->setEnabled(true);
    ui->actionGreen->setEnabled(true);
    ui->actionPastel->setEnabled(false);

    ui->MyWindows->setStyleSheet("background-color: rgb(255, 220, 196)");

    Plot->set_legend_style_sheet("background-color: rgb(255, 220, 196)");

    ui->lcdR->setPalette(Qt::black);
    ui->lcdtime->setPalette(Qt::black);
    ui->lcdNumber->setPalette(Qt::black);
    ui->lcdT->setPalette(Qt::black);
    ui->lcdD->setPalette(Qt::black);
    ui->lcdE->setPalette(Qt::black);
    ui->lcdF->setPalette(Qt::black);
    ui->lcdI->setPalette(Qt::black);
    ui->lcdP->setPalette(Qt::black);
    ui->lcdU->setPalette(Qt::black);
    ui->lcdY->setPalette(Qt::black);
    ui->lcdPi->setPalette(Qt::black);
    ui->lcdStepPD->setPalette(Qt::black);
    ui->lcdStepPI->setPalette(Qt::black);
    ui->lcdPD->setPalette(Qt::black);
    ui->lcdPI->setPalette(Qt::black);
}

void xControlador::cambiar_Tsupervision()
{
    int i;
    unsigned char buffer[Tx_size];

    QString *array_temp=new QString();
    wchar_t array[Tx_size+1];

    int temporal=ui->spinTsupervision->value();
    int temp2 = PS.myPID()->get_Tc()*1000;

    while(temporal%10!=0)
        temporal++;

    if(temp2%10!=0)
    {
        if((temp2+1)%10!=0)
        {
            if((temp2-1)%10!=0)
            {
                if((temp2+2)%10!=0)
                {
                    if((temp2-2)%10!=0)
                    {
                        ui->statusBar->showMessage("Error al cambiar el período de supervisión");
                        temp2=1;
                    }
                    else
                        temp2-=2;
                }
                else
                    temp2+=2;
            }
            else
                temp2-=1;
        }
        else
           temp2+=1;
    }

    while(temporal%temp2!=0)
    {
        temporal+=10;
    }

    ui->spinTsupervision->setValue(temporal);
   // ui->statusBar->showMessage(QString::number(temporal/10));

    *array_temp=QString::number(temporal/temp2-1);

    array_temp->toWCharArray(array);

    for(i=0;i<Tx_size;i++)
    {
        if(array[i]!='.' && (array[i]<0x30 || array[i]>0x39)) break;
        else buffer[i]=array[i];
    }

    buffer[i]='G';

    buffer[i+1]=13;

    PS.set_bufferTx(buffer);
    PS.set_icounter(i+2);

    PS.Parameter_changed();

    ui->btnTsupervision->setEnabled(false);

  //  PS.set_data_sent(false);
  //  contador=29;
}

void xControlador::on_btnTsupervision_clicked()
{
    cambiar_Tsupervision();
}

void xControlador::on_spinTsupervision_valueChanged(int x)
{
    ui->btnTsupervision->setEnabled(true);
}

void xControlador::on_actionFichero_yf_triggered()
{
    LF.show();
    PS.load_yf(*LF.change_text());
}

void xControlador::on_actionFichero_u_triggered()
{
    LF.show();
    PS.load_u(*LF.change_text());
}

void xControlador::on_actionFichero_e_triggered()
{
    LF.show();
    PS.load_e(*LF.change_text());
}

void xControlador::on_actionFichero_tiempo_triggered()
{
    LF.show();
    PS.load_tiempo(*LF.change_text());
}

void xControlador::on_btnTipoAccion_clicked()
{
    PS.mySendBYTE(inicio_trama);
    PS.mySendBYTE(lectura_configuracion);
    PS.mySendBYTE(7);
    PS.mySendBYTE(13);
}

void xControlador::on_cbTipoAccion_currentIndexChanged(int index)
{
    if(index!=0)
    {
        PS.mySendBYTE(inicio_trama);
        PS.mySendBYTE(escritura_configuracion);
        PS.mySendBYTE(7);
        PS.mySendBYTE(index-1);
        PS.mySendBYTE(13);
        PS.set_data_sent(true);
        contador=9;
    }
}
