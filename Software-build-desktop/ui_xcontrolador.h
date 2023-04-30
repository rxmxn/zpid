/********************************************************************************
** Form generated from reading UI file 'xcontrolador.ui'
**
** Created: Wed 29. May 20:27:29 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XCONTROLADOR_H
#define UI_XCONTROLADOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QStackedWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_xControlador
{
public:
    QAction *actionSupervision;
    QAction *actionPID;
    QAction *actionSalir;
    QAction *actionAcerca_de;
    QAction *actionAyuda;
    QAction *action9600;
    QAction *action1200;
    QAction *action2400;
    QAction *action4800;
    QAction *action19200;
    QAction *action28800;
    QAction *action33600;
    QAction *action38400;
    QAction *actionAbrir_Fichero;
    QAction *actionDefault;
    QAction *actionGray;
    QAction *actionFUZZY;
    QAction *actionAzul;
    QAction *actionBlanco;
    QAction *actionMostaza;
    QAction *actionOscuro;
    QAction *actionHistorial;
    QAction *actionCOM1;
    QAction *actionCOM2;
    QAction *actionCOM3;
    QAction *actionCOM4;
    QAction *actionCOM5;
    QAction *actionCOM6;
    QAction *actionGreen;
    QAction *actionPastel;
    QAction *actionFichero_yf;
    QAction *actionFichero_u;
    QAction *actionFichero_e;
    QAction *actionFichero_tiempo;
    QWidget *centralWidget;
    QStackedWidget *MyWindows;
    QWidget *page;
    QComboBox *cbEntAna;
    QTextEdit *textEdit;
    QComboBox *cbEntDig;
    QSpinBox *sBSalDig;
    QPushButton *btnEntDig;
    QSpinBox *sBCU;
    QPushButton *btnSalDig;
    QComboBox *cbCU;
    QComboBox *cbSalDig;
    QTabWidget *tabWidget;
    QWidget *tabLectura;
    QPushButton *btnPWMRx;
    QPushButton *btnBaudRateRx;
    QPushButton *btnCantMRx;
    QPushButton *btnProcesamientoRx;
    QPushButton *btnSeleccionPWM;
    QPushButton *btnSeleccionAD;
    QPushButton *btnTipoAccion;
    QWidget *tabEscritura;
    QComboBox *cbBaudRate;
    QComboBox *cbPWM;
    QComboBox *cbProcesamiento;
    QComboBox *cbCantM;
    QComboBox *cbSeleccionPWM;
    QComboBox *cbSeleccionAD;
    QComboBox *cbTipoAccion;
    QPushButton *btnEntAna;
    QPushButton *btnCU;
    QPushButton *btnModulo;
    QPushButton *btnReset;
    QWidget *page_2;
    QToolButton *btnPlay;
    QSlider *verticalSlider;
    QLabel *label_4;
    QComboBox *comboBox;
    QLCDNumber *lcdNumber;
    QLCDNumber *lcdP;
    QLCDNumber *lcdD;
    QComboBox *cbParametros;
    QLabel *label_10;
    QLabel *label;
    QPushButton *btnEnviar;
    QLabel *label_2;
    QLabel *lblunidad;
    QPushButton *btnFinalizar;
    QLabel *label_11;
    QLCDNumber *lcdR;
    QLCDNumber *lcdU;
    QLCDNumber *lcdtime;
    QLabel *label_5;
    QLCDNumber *lcdE;
    QLabel *label_9;
    QLCDNumber *lcdY;
    QLabel *label_12;
    QLabel *label_8;
    QLabel *label_7;
    QLabel *label_6;
    QLCDNumber *lcdF;
    QPushButton *btnSlider;
    QLCDNumber *lcdT;
    QLabel *label_13;
    QLCDNumber *lcdI;
    QLabel *label_3;
    QToolButton *btnStop;
    QLCDNumber *lcdPI;
    QLCDNumber *lcdPD;
    QLabel *label_PI;
    QLabel *label_PD;
    QLabel *label_stepPD;
    QLCDNumber *lcdStepPD;
    QLCDNumber *lcdStepPI;
    QLabel *label_stepPI;
    QLabel *label_Kpi;
    QLCDNumber *lcdPi;
    QSpinBox *spinSensor;
    QLabel *label_mV;
    QPushButton *btnActualizar;
    QLabel *label_sensor;
    QPushButton *btnReenvio;
    QDoubleSpinBox *edtEnviar;
    QPushButton *btnTsupervision;
    QSpinBox *spinTsupervision;
    QLabel *label_mV_2;
    QWidget *page_3;
    QCheckBox *checkConvUI;
    QToolButton *btnZoom;
    QPushButton *btnAtras;
    QPushButton *btnBorrarGrafica;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QMenu *menuModo;
    QMenu *menuCambiar_velocidad_de_comunicacion;
    QMenu *menuCambiar_puerto_COM;
    QMenu *menuAyuda;
    QMenu *menuHerramientas;
    QMenu *menuOpciones;
    QMenu *menuCambiar_Apariencia;
    QMenu *menuColor_Grafica;
    QMenu *menuAbrir_muestra;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *xControlador)
    {
        if (xControlador->objectName().isEmpty())
            xControlador->setObjectName(QString::fromUtf8("xControlador"));
        xControlador->resize(970, 529);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(xControlador->sizePolicy().hasHeightForWidth());
        xControlador->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(11);
        xControlador->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/X.png"), QSize(), QIcon::Normal, QIcon::Off);
        xControlador->setWindowIcon(icon);
        xControlador->setAutoFillBackground(false);
        actionSupervision = new QAction(xControlador);
        actionSupervision->setObjectName(QString::fromUtf8("actionSupervision"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/supervision.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSupervision->setIcon(icon1);
        actionSupervision->setSoftKeyRole(QAction::NoSoftKey);
        actionPID = new QAction(xControlador);
        actionPID->setObjectName(QString::fromUtf8("actionPID"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/pid.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPID->setIcon(icon2);
        actionSalir = new QAction(xControlador);
        actionSalir->setObjectName(QString::fromUtf8("actionSalir"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/salir.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSalir->setIcon(icon3);
        actionAcerca_de = new QAction(xControlador);
        actionAcerca_de->setObjectName(QString::fromUtf8("actionAcerca_de"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/about.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAcerca_de->setIcon(icon4);
        actionAyuda = new QAction(xControlador);
        actionAyuda->setObjectName(QString::fromUtf8("actionAyuda"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAyuda->setIcon(icon5);
        action9600 = new QAction(xControlador);
        action9600->setObjectName(QString::fromUtf8("action9600"));
        action1200 = new QAction(xControlador);
        action1200->setObjectName(QString::fromUtf8("action1200"));
        action2400 = new QAction(xControlador);
        action2400->setObjectName(QString::fromUtf8("action2400"));
        action4800 = new QAction(xControlador);
        action4800->setObjectName(QString::fromUtf8("action4800"));
        action19200 = new QAction(xControlador);
        action19200->setObjectName(QString::fromUtf8("action19200"));
        action28800 = new QAction(xControlador);
        action28800->setObjectName(QString::fromUtf8("action28800"));
        action33600 = new QAction(xControlador);
        action33600->setObjectName(QString::fromUtf8("action33600"));
        action38400 = new QAction(xControlador);
        action38400->setObjectName(QString::fromUtf8("action38400"));
        actionAbrir_Fichero = new QAction(xControlador);
        actionAbrir_Fichero->setObjectName(QString::fromUtf8("actionAbrir_Fichero"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/fichero.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbrir_Fichero->setIcon(icon6);
        actionDefault = new QAction(xControlador);
        actionDefault->setObjectName(QString::fromUtf8("actionDefault"));
        actionGray = new QAction(xControlador);
        actionGray->setObjectName(QString::fromUtf8("actionGray"));
        actionFUZZY = new QAction(xControlador);
        actionFUZZY->setObjectName(QString::fromUtf8("actionFUZZY"));
        actionFUZZY->setEnabled(true);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/fuzzy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFUZZY->setIcon(icon7);
        actionAzul = new QAction(xControlador);
        actionAzul->setObjectName(QString::fromUtf8("actionAzul"));
        actionAzul->setEnabled(false);
        actionBlanco = new QAction(xControlador);
        actionBlanco->setObjectName(QString::fromUtf8("actionBlanco"));
        actionMostaza = new QAction(xControlador);
        actionMostaza->setObjectName(QString::fromUtf8("actionMostaza"));
        actionOscuro = new QAction(xControlador);
        actionOscuro->setObjectName(QString::fromUtf8("actionOscuro"));
        actionHistorial = new QAction(xControlador);
        actionHistorial->setObjectName(QString::fromUtf8("actionHistorial"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/historial.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHistorial->setIcon(icon8);
        actionCOM1 = new QAction(xControlador);
        actionCOM1->setObjectName(QString::fromUtf8("actionCOM1"));
        actionCOM2 = new QAction(xControlador);
        actionCOM2->setObjectName(QString::fromUtf8("actionCOM2"));
        actionCOM3 = new QAction(xControlador);
        actionCOM3->setObjectName(QString::fromUtf8("actionCOM3"));
        actionCOM4 = new QAction(xControlador);
        actionCOM4->setObjectName(QString::fromUtf8("actionCOM4"));
        actionCOM5 = new QAction(xControlador);
        actionCOM5->setObjectName(QString::fromUtf8("actionCOM5"));
        actionCOM6 = new QAction(xControlador);
        actionCOM6->setObjectName(QString::fromUtf8("actionCOM6"));
        actionGreen = new QAction(xControlador);
        actionGreen->setObjectName(QString::fromUtf8("actionGreen"));
        actionPastel = new QAction(xControlador);
        actionPastel->setObjectName(QString::fromUtf8("actionPastel"));
        actionFichero_yf = new QAction(xControlador);
        actionFichero_yf->setObjectName(QString::fromUtf8("actionFichero_yf"));
        actionFichero_u = new QAction(xControlador);
        actionFichero_u->setObjectName(QString::fromUtf8("actionFichero_u"));
        actionFichero_e = new QAction(xControlador);
        actionFichero_e->setObjectName(QString::fromUtf8("actionFichero_e"));
        actionFichero_tiempo = new QAction(xControlador);
        actionFichero_tiempo->setObjectName(QString::fromUtf8("actionFichero_tiempo"));
        centralWidget = new QWidget(xControlador);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MyWindows = new QStackedWidget(centralWidget);
        MyWindows->setObjectName(QString::fromUtf8("MyWindows"));
        MyWindows->setEnabled(false);
        MyWindows->setGeometry(QRect(0, 0, 963, 531));
        MyWindows->setStyleSheet(QString::fromUtf8("background-color: rgb(206, 255, 252);\n"
""));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        cbEntAna = new QComboBox(page);
        cbEntAna->setObjectName(QString::fromUtf8("cbEntAna"));
        cbEntAna->setGeometry(QRect(380, 50, 73, 22));
        textEdit = new QTextEdit(page);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 10, 171, 181));
        textEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        textEdit->setReadOnly(true);
        cbEntDig = new QComboBox(page);
        cbEntDig->setObjectName(QString::fromUtf8("cbEntDig"));
        cbEntDig->setGeometry(QRect(380, 80, 73, 22));
        sBSalDig = new QSpinBox(page);
        sBSalDig->setObjectName(QString::fromUtf8("sBSalDig"));
        sBSalDig->setGeometry(QRect(460, 140, 46, 22));
        sBSalDig->setMaximum(1);
        btnEntDig = new QPushButton(page);
        btnEntDig->setObjectName(QString::fromUtf8("btnEntDig"));
        btnEntDig->setGeometry(QRect(190, 80, 181, 21));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        btnEntDig->setFont(font1);
        sBCU = new QSpinBox(page);
        sBCU->setObjectName(QString::fromUtf8("sBCU"));
        sBCU->setGeometry(QRect(460, 110, 46, 22));
        sBCU->setMaximum(1023);
        btnSalDig = new QPushButton(page);
        btnSalDig->setObjectName(QString::fromUtf8("btnSalDig"));
        btnSalDig->setGeometry(QRect(190, 140, 181, 21));
        btnSalDig->setFont(font1);
        cbCU = new QComboBox(page);
        cbCU->setObjectName(QString::fromUtf8("cbCU"));
        cbCU->setGeometry(QRect(380, 110, 73, 22));
        cbSalDig = new QComboBox(page);
        cbSalDig->setObjectName(QString::fromUtf8("cbSalDig"));
        cbSalDig->setGeometry(QRect(380, 140, 73, 22));
        tabWidget = new QTabWidget(page);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 210, 531, 251));
        tabLectura = new QWidget();
        tabLectura->setObjectName(QString::fromUtf8("tabLectura"));
        btnPWMRx = new QPushButton(tabLectura);
        btnPWMRx->setObjectName(QString::fromUtf8("btnPWMRx"));
        btnPWMRx->setGeometry(QRect(130, 50, 271, 21));
        btnPWMRx->setFont(font1);
        btnBaudRateRx = new QPushButton(tabLectura);
        btnBaudRateRx->setObjectName(QString::fromUtf8("btnBaudRateRx"));
        btnBaudRateRx->setGeometry(QRect(130, 20, 271, 21));
        btnBaudRateRx->setFont(font1);
        btnCantMRx = new QPushButton(tabLectura);
        btnCantMRx->setObjectName(QString::fromUtf8("btnCantMRx"));
        btnCantMRx->setGeometry(QRect(130, 110, 271, 21));
        btnCantMRx->setFont(font1);
        btnProcesamientoRx = new QPushButton(tabLectura);
        btnProcesamientoRx->setObjectName(QString::fromUtf8("btnProcesamientoRx"));
        btnProcesamientoRx->setGeometry(QRect(130, 80, 271, 21));
        btnProcesamientoRx->setFont(font1);
        btnSeleccionPWM = new QPushButton(tabLectura);
        btnSeleccionPWM->setObjectName(QString::fromUtf8("btnSeleccionPWM"));
        btnSeleccionPWM->setGeometry(QRect(130, 140, 271, 21));
        btnSeleccionPWM->setFont(font1);
        btnSeleccionAD = new QPushButton(tabLectura);
        btnSeleccionAD->setObjectName(QString::fromUtf8("btnSeleccionAD"));
        btnSeleccionAD->setGeometry(QRect(130, 170, 271, 21));
        btnSeleccionAD->setFont(font1);
        btnTipoAccion = new QPushButton(tabLectura);
        btnTipoAccion->setObjectName(QString::fromUtf8("btnTipoAccion"));
        btnTipoAccion->setGeometry(QRect(130, 200, 271, 21));
        btnTipoAccion->setFont(font1);
        tabWidget->addTab(tabLectura, QString());
        tabEscritura = new QWidget();
        tabEscritura->setObjectName(QString::fromUtf8("tabEscritura"));
        cbBaudRate = new QComboBox(tabEscritura);
        cbBaudRate->setObjectName(QString::fromUtf8("cbBaudRate"));
        cbBaudRate->setGeometry(QRect(110, 10, 291, 22));
        cbBaudRate->setFont(font1);
        cbBaudRate->setContextMenuPolicy(Qt::DefaultContextMenu);
        cbBaudRate->setLayoutDirection(Qt::LeftToRight);
        cbPWM = new QComboBox(tabEscritura);
        cbPWM->setObjectName(QString::fromUtf8("cbPWM"));
        cbPWM->setGeometry(QRect(110, 40, 291, 22));
        cbPWM->setFont(font1);
        cbProcesamiento = new QComboBox(tabEscritura);
        cbProcesamiento->setObjectName(QString::fromUtf8("cbProcesamiento"));
        cbProcesamiento->setGeometry(QRect(110, 70, 291, 22));
        cbProcesamiento->setFont(font1);
        cbCantM = new QComboBox(tabEscritura);
        cbCantM->setObjectName(QString::fromUtf8("cbCantM"));
        cbCantM->setGeometry(QRect(110, 100, 291, 22));
        cbCantM->setFont(font1);
        cbSeleccionPWM = new QComboBox(tabEscritura);
        cbSeleccionPWM->setObjectName(QString::fromUtf8("cbSeleccionPWM"));
        cbSeleccionPWM->setGeometry(QRect(110, 130, 291, 22));
        cbSeleccionPWM->setFont(font1);
        cbSeleccionAD = new QComboBox(tabEscritura);
        cbSeleccionAD->setObjectName(QString::fromUtf8("cbSeleccionAD"));
        cbSeleccionAD->setGeometry(QRect(110, 160, 291, 22));
        cbSeleccionAD->setFont(font1);
        cbTipoAccion = new QComboBox(tabEscritura);
        cbTipoAccion->setObjectName(QString::fromUtf8("cbTipoAccion"));
        cbTipoAccion->setGeometry(QRect(110, 190, 291, 22));
        cbTipoAccion->setFont(font1);
        tabWidget->addTab(tabEscritura, QString());
        btnEntAna = new QPushButton(page);
        btnEntAna->setObjectName(QString::fromUtf8("btnEntAna"));
        btnEntAna->setGeometry(QRect(190, 50, 181, 21));
        btnEntAna->setFont(font1);
        btnCU = new QPushButton(page);
        btnCU->setObjectName(QString::fromUtf8("btnCU"));
        btnCU->setGeometry(QRect(190, 110, 181, 21));
        btnCU->setFont(font1);
        btnModulo = new QPushButton(page);
        btnModulo->setObjectName(QString::fromUtf8("btnModulo"));
        btnModulo->setGeometry(QRect(190, 20, 181, 21));
        btnModulo->setFont(font1);
        btnModulo->setAutoFillBackground(false);
        btnReset = new QPushButton(page);
        btnReset->setObjectName(QString::fromUtf8("btnReset"));
        btnReset->setGeometry(QRect(190, 170, 181, 21));
        btnReset->setFont(font1);
        MyWindows->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        btnPlay = new QToolButton(page_2);
        btnPlay->setObjectName(QString::fromUtf8("btnPlay"));
        btnPlay->setEnabled(false);
        btnPlay->setGeometry(QRect(930, 190, 21, 21));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPlay->setIcon(icon9);
        verticalSlider = new QSlider(page_2);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setGeometry(QRect(280, 60, 20, 321));
        verticalSlider->setMaximum(1023);
        verticalSlider->setOrientation(Qt::Vertical);
        label_4 = new QLabel(page_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(40, 10, 53, 16));
        label_4->setLayoutDirection(Qt::RightToLeft);
        comboBox = new QComboBox(page_2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(100, 10, 141, 22));
        comboBox->setFont(font1);
        lcdNumber = new QLCDNumber(page_2);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(260, 30, 64, 23));
        lcdNumber->setFrameShape(QFrame::Panel);
        lcdNumber->setLineWidth(1);
        lcdNumber->setSmallDecimalPoint(false);
        lcdNumber->setSegmentStyle(QLCDNumber::Filled);
        lcdP = new QLCDNumber(page_2);
        lcdP->setObjectName(QString::fromUtf8("lcdP"));
        lcdP->setGeometry(QRect(60, 250, 64, 23));
        lcdP->setFrameShape(QFrame::Panel);
        lcdD = new QLCDNumber(page_2);
        lcdD->setObjectName(QString::fromUtf8("lcdD"));
        lcdD->setGeometry(QRect(60, 280, 64, 23));
        lcdD->setFrameShape(QFrame::Panel);
        cbParametros = new QComboBox(page_2);
        cbParametros->setObjectName(QString::fromUtf8("cbParametros"));
        cbParametros->setGeometry(QRect(100, 40, 141, 22));
        cbParametros->setFont(font1);
        label_10 = new QLabel(page_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(30, 310, 20, 20));
        label_10->setLayoutDirection(Qt::RightToLeft);
        label = new QLabel(page_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 40, 81, 16));
        label->setLayoutDirection(Qt::RightToLeft);
        btnEnviar = new QPushButton(page_2);
        btnEnviar->setObjectName(QString::fromUtf8("btnEnviar"));
        btnEnviar->setEnabled(false);
        btnEnviar->setGeometry(QRect(100, 100, 141, 21));
        btnEnviar->setFont(font1);
        btnEnviar->setAutoFillBackground(false);
        btnEnviar->setAutoDefault(false);
        btnEnviar->setDefault(false);
        btnEnviar->setFlat(false);
        label_2 = new QLabel(page_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 70, 53, 16));
        label_2->setLayoutDirection(Qt::RightToLeft);
        lblunidad = new QLabel(page_2);
        lblunidad->setObjectName(QString::fromUtf8("lblunidad"));
        lblunidad->setGeometry(QRect(250, 70, 21, 20));
        btnFinalizar = new QPushButton(page_2);
        btnFinalizar->setObjectName(QString::fromUtf8("btnFinalizar"));
        btnFinalizar->setGeometry(QRect(100, 120, 141, 21));
        btnFinalizar->setFont(font1);
        label_11 = new QLabel(page_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(153, 190, 20, 20));
        label_11->setLayoutDirection(Qt::RightToLeft);
        lcdR = new QLCDNumber(page_2);
        lcdR->setObjectName(QString::fromUtf8("lcdR"));
        lcdR->setGeometry(QRect(60, 190, 64, 23));
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        font2.setKerning(false);
        font2.setStyleStrategy(QFont::PreferDefault);
        lcdR->setFont(font2);
        lcdR->setAutoFillBackground(false);
        lcdR->setFrameShape(QFrame::Panel);
        lcdR->setSmallDecimalPoint(false);
        lcdR->setSegmentStyle(QLCDNumber::Filled);
        lcdU = new QLCDNumber(page_2);
        lcdU->setObjectName(QString::fromUtf8("lcdU"));
        lcdU->setGeometry(QRect(180, 190, 64, 23));
        lcdU->setFrameShape(QFrame::Panel);
        lcdtime = new QLCDNumber(page_2);
        lcdtime->setObjectName(QString::fromUtf8("lcdtime"));
        lcdtime->setGeometry(QRect(179, 310, 64, 23));
        lcdtime->setFrameShape(QFrame::Panel);
        lcdtime->setLineWidth(1);
        lcdtime->setSmallDecimalPoint(false);
        lcdtime->setSegmentStyle(QLCDNumber::Filled);
        label_5 = new QLabel(page_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(33, 190, 20, 20));
        label_5->setLayoutDirection(Qt::RightToLeft);
        lcdE = new QLCDNumber(page_2);
        lcdE->setObjectName(QString::fromUtf8("lcdE"));
        lcdE->setGeometry(QRect(180, 220, 64, 23));
        lcdE->setFrameShape(QFrame::Panel);
        label_9 = new QLabel(page_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(149, 280, 20, 20));
        label_9->setLayoutDirection(Qt::RightToLeft);
        lcdY = new QLCDNumber(page_2);
        lcdY->setObjectName(QString::fromUtf8("lcdY"));
        lcdY->setGeometry(QRect(60, 220, 64, 23));
        lcdY->setFrameShape(QFrame::Panel);
        label_12 = new QLabel(page_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(33, 220, 20, 20));
        label_12->setLayoutDirection(Qt::RightToLeft);
        label_8 = new QLabel(page_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 280, 20, 20));
        label_8->setLayoutDirection(Qt::RightToLeft);
        label_7 = new QLabel(page_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(149, 250, 20, 20));
        label_7->setLayoutDirection(Qt::RightToLeft);
        label_6 = new QLabel(page_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 250, 20, 20));
        label_6->setLayoutDirection(Qt::RightToLeft);
        lcdF = new QLCDNumber(page_2);
        lcdF->setObjectName(QString::fromUtf8("lcdF"));
        lcdF->setGeometry(QRect(60, 310, 64, 23));
        lcdF->setFrameShape(QFrame::Panel);
        btnSlider = new QPushButton(page_2);
        btnSlider->setObjectName(QString::fromUtf8("btnSlider"));
        btnSlider->setGeometry(QRect(100, 160, 141, 21));
        btnSlider->setFont(font1);
        lcdT = new QLCDNumber(page_2);
        lcdT->setObjectName(QString::fromUtf8("lcdT"));
        lcdT->setGeometry(QRect(179, 280, 64, 23));
        lcdT->setFrameShape(QFrame::Panel);
        label_13 = new QLabel(page_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(150, 220, 20, 20));
        label_13->setLayoutDirection(Qt::RightToLeft);
        lcdI = new QLCDNumber(page_2);
        lcdI->setObjectName(QString::fromUtf8("lcdI"));
        lcdI->setGeometry(QRect(179, 250, 64, 23));
        lcdI->setFrameShape(QFrame::Panel);
        label_3 = new QLabel(page_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(250, 10, 71, 20));
        label_3->setLayoutDirection(Qt::RightToLeft);
        btnStop = new QToolButton(page_2);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setGeometry(QRect(930, 190, 21, 21));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnStop->setIcon(icon10);
        lcdPI = new QLCDNumber(page_2);
        lcdPI->setObjectName(QString::fromUtf8("lcdPI"));
        lcdPI->setGeometry(QRect(60, 340, 64, 23));
        lcdPI->setFrameShape(QFrame::Panel);
        lcdPD = new QLCDNumber(page_2);
        lcdPD->setObjectName(QString::fromUtf8("lcdPD"));
        lcdPD->setGeometry(QRect(179, 340, 64, 23));
        lcdPD->setFrameShape(QFrame::Panel);
        lcdPD->setLineWidth(1);
        lcdPD->setSmallDecimalPoint(false);
        lcdPD->setSegmentStyle(QLCDNumber::Filled);
        label_PI = new QLabel(page_2);
        label_PI->setObjectName(QString::fromUtf8("label_PI"));
        label_PI->setGeometry(QRect(19, 340, 31, 20));
        label_PI->setLayoutDirection(Qt::RightToLeft);
        label_PD = new QLabel(page_2);
        label_PD->setObjectName(QString::fromUtf8("label_PD"));
        label_PD->setGeometry(QRect(129, 340, 41, 20));
        label_PD->setLayoutDirection(Qt::RightToLeft);
        label_stepPD = new QLabel(page_2);
        label_stepPD->setObjectName(QString::fromUtf8("label_stepPD"));
        label_stepPD->setGeometry(QRect(130, 370, 41, 20));
        label_stepPD->setLayoutDirection(Qt::RightToLeft);
        lcdStepPD = new QLCDNumber(page_2);
        lcdStepPD->setObjectName(QString::fromUtf8("lcdStepPD"));
        lcdStepPD->setGeometry(QRect(180, 370, 64, 23));
        lcdStepPD->setFrameShape(QFrame::Panel);
        lcdStepPD->setLineWidth(1);
        lcdStepPD->setSmallDecimalPoint(false);
        lcdStepPD->setSegmentStyle(QLCDNumber::Filled);
        lcdStepPI = new QLCDNumber(page_2);
        lcdStepPI->setObjectName(QString::fromUtf8("lcdStepPI"));
        lcdStepPI->setGeometry(QRect(60, 370, 64, 23));
        lcdStepPI->setFrameShape(QFrame::Panel);
        lcdStepPI->setLineWidth(1);
        lcdStepPI->setSmallDecimalPoint(false);
        lcdStepPI->setSegmentStyle(QLCDNumber::Filled);
        label_stepPI = new QLabel(page_2);
        label_stepPI->setObjectName(QString::fromUtf8("label_stepPI"));
        label_stepPI->setGeometry(QRect(10, 370, 41, 20));
        label_stepPI->setLayoutDirection(Qt::RightToLeft);
        label_Kpi = new QLabel(page_2);
        label_Kpi->setObjectName(QString::fromUtf8("label_Kpi"));
        label_Kpi->setGeometry(QRect(30, 400, 20, 20));
        label_Kpi->setLayoutDirection(Qt::RightToLeft);
        lcdPi = new QLCDNumber(page_2);
        lcdPi->setObjectName(QString::fromUtf8("lcdPi"));
        lcdPi->setGeometry(QRect(60, 400, 64, 23));
        lcdPi->setFrameShape(QFrame::Panel);
        spinSensor = new QSpinBox(page_2);
        spinSensor->setObjectName(QString::fromUtf8("spinSensor"));
        spinSensor->setGeometry(QRect(480, 420, 51, 22));
        spinSensor->setMaximum(5000);
        spinSensor->setSingleStep(100);
        spinSensor->setValue(5000);
        label_mV = new QLabel(page_2);
        label_mV->setObjectName(QString::fromUtf8("label_mV"));
        label_mV->setGeometry(QRect(530, 420, 20, 20));
        label_mV->setLayoutDirection(Qt::RightToLeft);
        btnActualizar = new QPushButton(page_2);
        btnActualizar->setObjectName(QString::fromUtf8("btnActualizar"));
        btnActualizar->setEnabled(false);
        btnActualizar->setGeometry(QRect(350, 420, 121, 21));
        btnActualizar->setFont(font1);
        btnActualizar->setAutoFillBackground(false);
        btnActualizar->setAutoDefault(false);
        btnActualizar->setDefault(false);
        btnActualizar->setFlat(false);
        label_sensor = new QLabel(page_2);
        label_sensor->setObjectName(QString::fromUtf8("label_sensor"));
        label_sensor->setGeometry(QRect(410, 400, 121, 20));
        label_sensor->setLayoutDirection(Qt::RightToLeft);
        btnReenvio = new QPushButton(page_2);
        btnReenvio->setObjectName(QString::fromUtf8("btnReenvio"));
        btnReenvio->setGeometry(QRect(10, 450, 91, 23));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/reenvio.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnReenvio->setIcon(icon11);
        edtEnviar = new QDoubleSpinBox(page_2);
        edtEnviar->setObjectName(QString::fromUtf8("edtEnviar"));
        edtEnviar->setGeometry(QRect(100, 70, 141, 22));
        edtEnviar->setAutoFillBackground(false);
        edtEnviar->setDecimals(3);
        edtEnviar->setMaximum(100000);
        btnTsupervision = new QPushButton(page_2);
        btnTsupervision->setObjectName(QString::fromUtf8("btnTsupervision"));
        btnTsupervision->setGeometry(QRect(350, 440, 121, 21));
        spinTsupervision = new QSpinBox(page_2);
        spinTsupervision->setObjectName(QString::fromUtf8("spinTsupervision"));
        spinTsupervision->setGeometry(QRect(480, 440, 51, 22));
        spinTsupervision->setMinimum(100);
        spinTsupervision->setMaximum(1000);
        spinTsupervision->setSingleStep(10);
        label_mV_2 = new QLabel(page_2);
        label_mV_2->setObjectName(QString::fromUtf8("label_mV_2"));
        label_mV_2->setGeometry(QRect(530, 440, 20, 21));
        label_mV_2->setLayoutDirection(Qt::RightToLeft);
        MyWindows->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        checkConvUI = new QCheckBox(page_3);
        checkConvUI->setObjectName(QString::fromUtf8("checkConvUI"));
        checkConvUI->setGeometry(QRect(650, 20, 91, 18));
        btnZoom = new QToolButton(page_3);
        btnZoom->setObjectName(QString::fromUtf8("btnZoom"));
        btnZoom->setGeometry(QRect(650, 190, 21, 21));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/lupa.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnZoom->setIcon(icon12);
        btnAtras = new QPushButton(page_3);
        btnAtras->setObjectName(QString::fromUtf8("btnAtras"));
        btnAtras->setGeometry(QRect(650, 420, 75, 23));
        btnBorrarGrafica = new QPushButton(page_3);
        btnBorrarGrafica->setObjectName(QString::fromUtf8("btnBorrarGrafica"));
        btnBorrarGrafica->setGeometry(QRect(10, 420, 81, 23));
        MyWindows->addWidget(page_3);
        xControlador->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(xControlador);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 970, 20));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        menuModo = new QMenu(menuMenu);
        menuModo->setObjectName(QString::fromUtf8("menuModo"));
        menuModo->setFont(font);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/modo.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuModo->setIcon(icon13);
        menuCambiar_velocidad_de_comunicacion = new QMenu(menuMenu);
        menuCambiar_velocidad_de_comunicacion->setObjectName(QString::fromUtf8("menuCambiar_velocidad_de_comunicacion"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/baud.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuCambiar_velocidad_de_comunicacion->setIcon(icon14);
        menuCambiar_puerto_COM = new QMenu(menuMenu);
        menuCambiar_puerto_COM->setObjectName(QString::fromUtf8("menuCambiar_puerto_COM"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/COM.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuCambiar_puerto_COM->setIcon(icon15);
        menuAyuda = new QMenu(menuBar);
        menuAyuda->setObjectName(QString::fromUtf8("menuAyuda"));
        menuHerramientas = new QMenu(menuBar);
        menuHerramientas->setObjectName(QString::fromUtf8("menuHerramientas"));
        menuOpciones = new QMenu(menuHerramientas);
        menuOpciones->setObjectName(QString::fromUtf8("menuOpciones"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/opciones.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuOpciones->setIcon(icon16);
        menuCambiar_Apariencia = new QMenu(menuOpciones);
        menuCambiar_Apariencia->setObjectName(QString::fromUtf8("menuCambiar_Apariencia"));
        menuColor_Grafica = new QMenu(menuOpciones);
        menuColor_Grafica->setObjectName(QString::fromUtf8("menuColor_Grafica"));
        menuAbrir_muestra = new QMenu(menuHerramientas);
        menuAbrir_muestra->setObjectName(QString::fromUtf8("menuAbrir_muestra"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/loadmuestra.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuAbrir_muestra->setIcon(icon17);
        xControlador->setMenuBar(menuBar);
        mainToolBar = new QToolBar(xControlador);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        xControlador->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(xControlador);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        xControlador->setStatusBar(statusBar);

        menuBar->addAction(menuMenu->menuAction());
        menuBar->addAction(menuHerramientas->menuAction());
        menuBar->addAction(menuAyuda->menuAction());
        menuMenu->addAction(menuModo->menuAction());
        menuMenu->addAction(menuCambiar_velocidad_de_comunicacion->menuAction());
        menuMenu->addAction(menuCambiar_puerto_COM->menuAction());
        menuMenu->addAction(actionSalir);
        menuModo->addSeparator();
        menuModo->addAction(actionSupervision);
        menuModo->addAction(actionPID);
        menuModo->addAction(actionFUZZY);
        menuCambiar_velocidad_de_comunicacion->addAction(action1200);
        menuCambiar_velocidad_de_comunicacion->addAction(action2400);
        menuCambiar_velocidad_de_comunicacion->addAction(action4800);
        menuCambiar_velocidad_de_comunicacion->addAction(action9600);
        menuCambiar_velocidad_de_comunicacion->addAction(action19200);
        menuCambiar_velocidad_de_comunicacion->addAction(action28800);
        menuCambiar_velocidad_de_comunicacion->addAction(action33600);
        menuCambiar_velocidad_de_comunicacion->addAction(action38400);
        menuCambiar_puerto_COM->addAction(actionCOM1);
        menuCambiar_puerto_COM->addAction(actionCOM2);
        menuCambiar_puerto_COM->addAction(actionCOM3);
        menuCambiar_puerto_COM->addAction(actionCOM4);
        menuCambiar_puerto_COM->addAction(actionCOM5);
        menuCambiar_puerto_COM->addAction(actionCOM6);
        menuAyuda->addAction(actionAcerca_de);
        menuAyuda->addAction(actionAyuda);
        menuHerramientas->addAction(actionAbrir_Fichero);
        menuHerramientas->addAction(menuOpciones->menuAction());
        menuHerramientas->addAction(actionHistorial);
        menuHerramientas->addAction(menuAbrir_muestra->menuAction());
        menuOpciones->addAction(menuCambiar_Apariencia->menuAction());
        menuOpciones->addAction(menuColor_Grafica->menuAction());
        menuCambiar_Apariencia->addAction(actionDefault);
        menuCambiar_Apariencia->addAction(actionGray);
        menuCambiar_Apariencia->addAction(actionGreen);
        menuCambiar_Apariencia->addAction(actionPastel);
        menuColor_Grafica->addAction(actionAzul);
        menuColor_Grafica->addAction(actionBlanco);
        menuColor_Grafica->addAction(actionMostaza);
        menuColor_Grafica->addAction(actionOscuro);
        menuAbrir_muestra->addAction(actionFichero_yf);
        menuAbrir_muestra->addAction(actionFichero_u);
        menuAbrir_muestra->addAction(actionFichero_e);
        menuAbrir_muestra->addAction(actionFichero_tiempo);

        retranslateUi(xControlador);

        MyWindows->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(xControlador);
    } // setupUi

    void retranslateUi(QMainWindow *xControlador)
    {
        xControlador->setWindowTitle(QApplication::translate("xControlador", "xControlador", 0, QApplication::UnicodeUTF8));
        actionSupervision->setText(QApplication::translate("xControlador", "Supervisi\303\263n", 0, QApplication::UnicodeUTF8));
        actionSupervision->setShortcut(QApplication::translate("xControlador", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionPID->setText(QApplication::translate("xControlador", "Control PID", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPID->setToolTip(QApplication::translate("xControlador", "Control PID", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionPID->setShortcut(QApplication::translate("xControlador", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        actionSalir->setText(QApplication::translate("xControlador", "Salir", 0, QApplication::UnicodeUTF8));
        actionSalir->setShortcut(QApplication::translate("xControlador", "Ctrl+E", 0, QApplication::UnicodeUTF8));
        actionAcerca_de->setText(QApplication::translate("xControlador", "Acerca de...", 0, QApplication::UnicodeUTF8));
        actionAyuda->setText(QApplication::translate("xControlador", "Ayuda", 0, QApplication::UnicodeUTF8));
        actionAyuda->setShortcut(QApplication::translate("xControlador", "F1", 0, QApplication::UnicodeUTF8));
        action9600->setText(QApplication::translate("xControlador", "9600", 0, QApplication::UnicodeUTF8));
        action1200->setText(QApplication::translate("xControlador", "1200", 0, QApplication::UnicodeUTF8));
        action2400->setText(QApplication::translate("xControlador", "2400", 0, QApplication::UnicodeUTF8));
        action4800->setText(QApplication::translate("xControlador", "4800", 0, QApplication::UnicodeUTF8));
        action19200->setText(QApplication::translate("xControlador", "19200", 0, QApplication::UnicodeUTF8));
        action28800->setText(QApplication::translate("xControlador", "28800", 0, QApplication::UnicodeUTF8));
        action33600->setText(QApplication::translate("xControlador", "33600", 0, QApplication::UnicodeUTF8));
        action38400->setText(QApplication::translate("xControlador", "38400", 0, QApplication::UnicodeUTF8));
        actionAbrir_Fichero->setText(QApplication::translate("xControlador", "Abrir Fichero", 0, QApplication::UnicodeUTF8));
        actionAbrir_Fichero->setShortcut(QApplication::translate("xControlador", "Ctrl+A", 0, QApplication::UnicodeUTF8));
        actionDefault->setText(QApplication::translate("xControlador", "Azul", 0, QApplication::UnicodeUTF8));
        actionGray->setText(QApplication::translate("xControlador", "Gris", 0, QApplication::UnicodeUTF8));
        actionFUZZY->setText(QApplication::translate("xControlador", "Control FUZZY", 0, QApplication::UnicodeUTF8));
        actionFUZZY->setShortcut(QApplication::translate("xControlador", "Ctrl+F", 0, QApplication::UnicodeUTF8));
        actionAzul->setText(QApplication::translate("xControlador", "Azul (default)", 0, QApplication::UnicodeUTF8));
        actionBlanco->setText(QApplication::translate("xControlador", "Blanco", 0, QApplication::UnicodeUTF8));
        actionMostaza->setText(QApplication::translate("xControlador", "Mostaza", 0, QApplication::UnicodeUTF8));
        actionOscuro->setText(QApplication::translate("xControlador", "Oscuro", 0, QApplication::UnicodeUTF8));
        actionHistorial->setText(QApplication::translate("xControlador", "Historial", 0, QApplication::UnicodeUTF8));
        actionHistorial->setShortcut(QApplication::translate("xControlador", "Ctrl+H", 0, QApplication::UnicodeUTF8));
        actionCOM1->setText(QApplication::translate("xControlador", "COM1", 0, QApplication::UnicodeUTF8));
        actionCOM2->setText(QApplication::translate("xControlador", "COM2", 0, QApplication::UnicodeUTF8));
        actionCOM3->setText(QApplication::translate("xControlador", "COM3", 0, QApplication::UnicodeUTF8));
        actionCOM4->setText(QApplication::translate("xControlador", "COM4", 0, QApplication::UnicodeUTF8));
        actionCOM5->setText(QApplication::translate("xControlador", "COM5", 0, QApplication::UnicodeUTF8));
        actionCOM6->setText(QApplication::translate("xControlador", "COM6", 0, QApplication::UnicodeUTF8));
        actionGreen->setText(QApplication::translate("xControlador", "Verde", 0, QApplication::UnicodeUTF8));
        actionPastel->setText(QApplication::translate("xControlador", "Pastel", 0, QApplication::UnicodeUTF8));
        actionFichero_yf->setText(QApplication::translate("xControlador", "Fichero yf", 0, QApplication::UnicodeUTF8));
        actionFichero_u->setText(QApplication::translate("xControlador", "Fichero u", 0, QApplication::UnicodeUTF8));
        actionFichero_e->setText(QApplication::translate("xControlador", "Fichero e", 0, QApplication::UnicodeUTF8));
        actionFichero_tiempo->setText(QApplication::translate("xControlador", "Fichero tiempo", 0, QApplication::UnicodeUTF8));
        cbEntAna->clear();
        cbEntAna->insertItems(0, QStringList()
         << QApplication::translate("xControlador", "EA0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "EA1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "EA2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "EA3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "EA4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "EA5", 0, QApplication::UnicodeUTF8)
        );
        cbEntDig->clear();
        cbEntDig->insertItems(0, QStringList()
         << QApplication::translate("xControlador", "ED0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "ED1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "ED2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "ED3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "ED4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "ED5", 0, QApplication::UnicodeUTF8)
        );
        btnEntDig->setText(QApplication::translate("xControlador", "Valor de entrada digital", 0, QApplication::UnicodeUTF8));
        btnSalDig->setText(QApplication::translate("xControlador", "Modificar salida digital", 0, QApplication::UnicodeUTF8));
        cbCU->clear();
        cbCU->insertItems(0, QStringList()
         << QApplication::translate("xControlador", "pwm1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "pwm2", 0, QApplication::UnicodeUTF8)
        );
        cbSalDig->clear();
        cbSalDig->insertItems(0, QStringList()
         << QApplication::translate("xControlador", "SD0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "SD1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "SD2", 0, QApplication::UnicodeUTF8)
        );
        btnPWMRx->setText(QApplication::translate("xControlador", "Per\303\255odo de los PWM", 0, QApplication::UnicodeUTF8));
        btnBaudRateRx->setText(QApplication::translate("xControlador", "Velocidad de comunicaci\303\263n", 0, QApplication::UnicodeUTF8));
        btnCantMRx->setText(QApplication::translate("xControlador", "Cantidad de t\303\251rminos del filtro promedio", 0, QApplication::UnicodeUTF8));
        btnProcesamientoRx->setText(QApplication::translate("xControlador", "Tipo de procesamiento", 0, QApplication::UnicodeUTF8));
        btnSeleccionPWM->setText(QApplication::translate("xControlador", "Selecci\303\263n del PWM", 0, QApplication::UnicodeUTF8));
        btnSeleccionAD->setText(QApplication::translate("xControlador", "Selecci\303\263n del A/D", 0, QApplication::UnicodeUTF8));
        btnTipoAccion->setText(QApplication::translate("xControlador", "Tipo de Acci\303\263n", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabLectura), QApplication::translate("xControlador", "Lectura", 0, QApplication::UnicodeUTF8));
        cbBaudRate->clear();
        cbBaudRate->insertItems(0, QStringList()
         << QApplication::translate("xControlador", "Velocidad de comunicaci\303\263n", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "9600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "1200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "2400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "4800", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "19200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "28800", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "33600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "38400", 0, QApplication::UnicodeUTF8)
        );
        cbPWM->clear();
        cbPWM->insertItems(0, QStringList()
         << QApplication::translate("xControlador", "Per\303\255odo de los PWM", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "1.22KHz [0.82ms] Resoluci\303\263n=14bits", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "2.44KHz [0.41ms] Resoluci\303\263n=13bits", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "4.88KHz [0.20ms] Resoluci\303\263n=12bits", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "7.32KHz [0.14ms] Resoluci\303\263n=11.42bits", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "9.76KHz [0.10ms] Resoluci\303\263n=11bits", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "12.20KHz [81.9us] Resoluci\303\263n=10.67bits", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "17.08KHz [58.5us] Resoluci\303\263n=10.19bits", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "19.53KHz [51.2us] Resoluci\303\263n=10bits", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "30.12KHz [33.2us] Resoluci\303\263n=9.37bits", 0, QApplication::UnicodeUTF8)
        );
        cbProcesamiento->clear();
        cbProcesamiento->insertItems(0, QStringList()
         << QApplication::translate("xControlador", "Tipo de procesamiento", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "Sin procesamiento", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "Filtro promedio", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "Conversion a u.i.", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "Filtro y conversion", 0, QApplication::UnicodeUTF8)
        );
        cbCantM->clear();
        cbCantM->insertItems(0, QStringList()
         << QApplication::translate("xControlador", "Cantidad de t\303\251rminos del filtro promedio", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "16", 0, QApplication::UnicodeUTF8)
        );
        cbSeleccionPWM->clear();
        cbSeleccionPWM->insertItems(0, QStringList()
         << QApplication::translate("xControlador", "Selecci\303\263n del PWM", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "PWM2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "PWM1", 0, QApplication::UnicodeUTF8)
        );
        cbSeleccionAD->clear();
        cbSeleccionAD->insertItems(0, QStringList()
         << QApplication::translate("xControlador", "Selecci\303\263n del A/D", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "EA0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "EA1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "EA2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "EA3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "EA4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "EA5", 0, QApplication::UnicodeUTF8)
        );
        cbTipoAccion->clear();
        cbTipoAccion->insertItems(0, QStringList()
         << QApplication::translate("xControlador", "Tipo de Acci\303\263n", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "Acci\303\263n Directa", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "Acci\303\263n Inversa", 0, QApplication::UnicodeUTF8)
        );
        tabWidget->setTabText(tabWidget->indexOf(tabEscritura), QApplication::translate("xControlador", "Escritura", 0, QApplication::UnicodeUTF8));
        btnEntAna->setText(QApplication::translate("xControlador", "Valor de entrada anal\303\263gica", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnCU->setToolTip(QApplication::translate("xControlador", "%duty cycle = (value / [ 4 * (PR2 +1 ) ])*100", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnCU->setText(QApplication::translate("xControlador", "Modificar Ciclo \303\232til", 0, QApplication::UnicodeUTF8));
        btnModulo->setText(QApplication::translate("xControlador", "Tipo de m\303\263dulo", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnReset->setToolTip(QApplication::translate("xControlador", "Reset del microcontrolador", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnReset->setText(QApplication::translate("xControlador", "RESET", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnPlay->setToolTip(QApplication::translate("xControlador", "Reanudar", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnPlay->setText(QApplication::translate("xControlador", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        verticalSlider->setToolTip(QApplication::translate("xControlador", "Cambiar Referencia", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("xControlador", "Modo:", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("xControlador", "Autom\303\241tico", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("xControlador", "Manual", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        lcdP->setToolTip(QApplication::translate("xControlador", "Ganancia proporcional", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        lcdD->setToolTip(QApplication::translate("xControlador", "Ganancia derivativa", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_10->setText(QApplication::translate("xControlador", "F", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("xControlador", "Par\303\241metro:", 0, QApplication::UnicodeUTF8));
        btnEnviar->setText(QApplication::translate("xControlador", "Enviar", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("xControlador", "Valor:", 0, QApplication::UnicodeUTF8));
        lblunidad->setText(QApplication::translate("xControlador", "u", 0, QApplication::UnicodeUTF8));
        btnFinalizar->setText(QApplication::translate("xControlador", "Finalizar", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("xControlador", "U", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lcdR->setToolTip(QApplication::translate("xControlador", "Referencia", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        lcdU->setToolTip(QApplication::translate("xControlador", "Salida de control", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        lcdtime->setToolTip(QApplication::translate("xControlador", "Cantidad de muestras", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("xControlador", "R", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lcdE->setToolTip(QApplication::translate("xControlador", "Error", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_9->setText(QApplication::translate("xControlador", "Tc", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lcdY->setToolTip(QApplication::translate("xControlador", "Salida", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_12->setText(QApplication::translate("xControlador", "Y", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("xControlador", "Kd", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("xControlador", "Ki", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("xControlador", "Kp", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lcdF->setToolTip(QApplication::translate("xControlador", "Filtro promedio", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnSlider->setText(QApplication::translate("xControlador", "Enviar Referencia", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lcdT->setToolTip(QApplication::translate("xControlador", "Per\303\255odo de control", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_13->setText(QApplication::translate("xControlador", "E", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lcdI->setToolTip(QApplication::translate("xControlador", "Ganancia integral", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("xControlador", "Referencia:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnStop->setToolTip(QApplication::translate("xControlador", "Detener", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnStop->setText(QApplication::translate("xControlador", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lcdPI->setToolTip(QApplication::translate("xControlador", "universo PI", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        lcdPD->setToolTip(QApplication::translate("xControlador", "universo PD", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_PI->setText(QApplication::translate("xControlador", "univPI", 0, QApplication::UnicodeUTF8));
        label_PD->setText(QApplication::translate("xControlador", "univPD", 0, QApplication::UnicodeUTF8));
        label_stepPD->setText(QApplication::translate("xControlador", "step PD", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lcdStepPD->setToolTip(QApplication::translate("xControlador", "Step PD", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        lcdStepPI->setToolTip(QApplication::translate("xControlador", "Step PI", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_stepPI->setText(QApplication::translate("xControlador", "step PI", 0, QApplication::UnicodeUTF8));
        label_Kpi->setText(QApplication::translate("xControlador", "Kpi", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lcdPi->setToolTip(QApplication::translate("xControlador", "Ganancia proporcional del PI", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_mV->setText(QApplication::translate("xControlador", "mV", 0, QApplication::UnicodeUTF8));
        btnActualizar->setText(QApplication::translate("xControlador", "Actualizar", 0, QApplication::UnicodeUTF8));
        label_sensor->setText(QApplication::translate("xControlador", "Valor m\303\241ximo del sensor:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnReenvio->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        btnReenvio->setText(QApplication::translate("xControlador", "Pedir reenv\303\255o", 0, QApplication::UnicodeUTF8));
        btnTsupervision->setText(QApplication::translate("xControlador", "Per\303\255odo de supervisi\303\263n", 0, QApplication::UnicodeUTF8));
        label_mV_2->setText(QApplication::translate("xControlador", "ms", 0, QApplication::UnicodeUTF8));
        checkConvUI->setText(QApplication::translate("xControlador", "Convertir a UI", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnZoom->setToolTip(QApplication::translate("xControlador", "Activar Zoom", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnZoom->setText(QApplication::translate("xControlador", "...", 0, QApplication::UnicodeUTF8));
        btnAtras->setText(QApplication::translate("xControlador", "Atr\303\241s", 0, QApplication::UnicodeUTF8));
        btnAtras->setShortcut(QApplication::translate("xControlador", "Ctrl+Backspace", 0, QApplication::UnicodeUTF8));
        btnBorrarGrafica->setText(QApplication::translate("xControlador", "Limpiar Gr\303\241fica", 0, QApplication::UnicodeUTF8));
        menuMenu->setTitle(QApplication::translate("xControlador", "Men\303\272", 0, QApplication::UnicodeUTF8));
        menuModo->setTitle(QApplication::translate("xControlador", "Modo", 0, QApplication::UnicodeUTF8));
        menuCambiar_velocidad_de_comunicacion->setTitle(QApplication::translate("xControlador", "Cambiar velocidad de comunicaci\303\263n", 0, QApplication::UnicodeUTF8));
        menuCambiar_puerto_COM->setTitle(QApplication::translate("xControlador", "Cambiar puerto COM", 0, QApplication::UnicodeUTF8));
        menuAyuda->setTitle(QApplication::translate("xControlador", "Ayuda", 0, QApplication::UnicodeUTF8));
        menuHerramientas->setTitle(QApplication::translate("xControlador", "Herramientas", 0, QApplication::UnicodeUTF8));
        menuOpciones->setTitle(QApplication::translate("xControlador", "Opciones", 0, QApplication::UnicodeUTF8));
        menuCambiar_Apariencia->setTitle(QApplication::translate("xControlador", "Apariencia", 0, QApplication::UnicodeUTF8));
        menuColor_Grafica->setTitle(QApplication::translate("xControlador", "Color Gr\303\241fica", 0, QApplication::UnicodeUTF8));
        menuAbrir_muestra->setTitle(QApplication::translate("xControlador", "Abrir muestra", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class xControlador: public Ui_xControlador {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XCONTROLADOR_H
