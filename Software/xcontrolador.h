#ifndef XCONTROLADOR_H
#define XCONTROLADOR_H

#include <QMainWindow>

#include <QMessageBox>
#include <QMenu>
#include <QContextMenuEvent>
#include <QTimer>

#include <grafica.h>
#include <puertoserie.h>

#include <loadedfile.h>
#include <ayuda.h>

namespace Ui {
    class xControlador;
}

enum Modo_Actual{SUPERVISION,PID,FUZZY};

class xControlador : public QMainWindow
{
    Q_OBJECT

public:
    explicit xControlador(QWidget *parent = 0);
    ~xControlador();

public slots:
    void modo_supervision();
    void modo_pid();
    void modo_fuzzy();
    void contextMenuEvent(QContextMenuEvent *event);
    void put_message(QString,QString);
    void TMR();
    void set_timer_OFF(bool OFF);
    void Actualizar_Ref();
    void LF_key_pressed();
    void enviar_Referencia();
    void parametros_Fuzzy();
    void parametros_PID();
    void historial();
    void graficar_historial();
    void stop_grafica();
    void play_grafica();
    void TMR_grafica();
    void set_timer_grafica_OFF(bool OFF);
    void cambiar_Tsupervision();

private:
    Ui::xControlador *ui;
    Grafica *Plot,*PlotHistorial;
    PuertoSerie PS;
    QTimer *timer;
    QTimer *timer_grafica;
    QwtPlotMarker *Ref;
    bool fGraficar;
    LoadedFile LF;
    //int PR2; //para calcular el valor equivalente al %DutyCycle
    //Tendria que recibir al inicio el valor del periodo del PWM
    Modo_Actual modo_actual;
    Ayuda ayuda;
    double T_Rx;
    QwtPlotMarker *min;
    QElapsedTimer timerson;
    int contador;
    QwtPlotMarker *seg1;
    QwtPlotMarker *seg5;
    QwtPlotMarker *seg10;
    QwtPlotMarker *seg20;
    QColor color_actual;

private slots:
    void on_cbTipoAccion_currentIndexChanged(int index);
    void on_btnTipoAccion_clicked();
    void on_actionFichero_tiempo_triggered();
    void on_actionFichero_e_triggered();
    void on_actionFichero_u_triggered();
    void on_actionFichero_yf_triggered();
    void on_spinTsupervision_valueChanged(int );
    void on_btnTsupervision_clicked();
    void on_actionPastel_triggered();
    void on_actionGreen_triggered();
    void on_actionCOM6_triggered();
    void on_actionCOM5_triggered();
    void on_actionCOM4_triggered();
    void on_actionCOM3_triggered();
    void on_actionCOM2_triggered();
    void on_actionCOM1_triggered();
    void on_cbSeleccionAD_currentIndexChanged(int index);
    void on_cbSeleccionPWM_currentIndexChanged(int index);
    void on_btnSeleccionAD_clicked();
    void on_btnSeleccionPWM_clicked();
    void on_btnBorrarGrafica_clicked();
    void on_btnReenvio_clicked();
    void on_checkConvUI_toggled(bool checked);
    void on_btnAtras_clicked();
    void on_checkConvUI_clicked();
    void on_actionHistorial_triggered();
    void on_actionOscuro_triggered();
    void on_actionMostaza_triggered();
    void on_actionAzul_triggered();
    void on_actionBlanco_triggered();
    void on_actionFUZZY_triggered();
    void on_spinSensor_valueChanged(int );
    void on_btnActualizar_clicked();
    void on_actionGray_triggered();
    void on_actionDefault_triggered();
    void on_actionAbrir_Fichero_triggered();
    void on_btnSlider_clicked();
    void on_verticalSlider_valueChanged(int value);
    void on_btnPlay_clicked();
    void on_btnStop_clicked();
    void on_btnZoom_clicked();
    void on_cbParametros_currentIndexChanged(int index);
    void on_comboBox_currentIndexChanged(int index);
    void on_btnFinalizar_clicked();
    void on_btnEnviar_clicked();
    void on_cbProcesamiento_currentIndexChanged(int index);
    void on_cbPWM_currentIndexChanged(int index);
    void on_cbCantM_currentIndexChanged(int index);
    void on_cbBaudRate_currentIndexChanged(int index);
    void on_btnReset_clicked();
    void on_btnCantMRx_clicked();
    void on_btnProcesamientoRx_clicked();
    void on_btnPWMRx_clicked();
    void on_btnBaudRateRx_clicked();
    void on_btnSalDig_clicked();
    void on_btnCU_clicked();
    void on_btnEntDig_clicked();
    void on_btnEntAna_clicked();
    void on_btnModulo_clicked();
    void on_action38400_triggered();
    void on_action33600_triggered();
    void on_action28800_triggered();
    void on_action19200_triggered();
    void on_action4800_triggered();
    void on_action2400_triggered();
    void on_action1200_triggered();
    void on_action9600_triggered();
    void on_actionAyuda_triggered();
    void on_actionAcerca_de_triggered();
    void on_actionSalir_triggered();
    void on_actionPID_triggered();
    void on_actionSupervision_triggered();
};

#endif // XCONTROLADOR_H
