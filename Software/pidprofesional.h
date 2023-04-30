#ifndef PIDPROFESIONAL_H
#define PIDPROFESIONAL_H

#include "file.h"
#include <curve.h>
#include <QLCDNumber>

#define automatico 0
#define manual 1

#define hist_array 20  //se incrementa cada 200 muestras, cada muestra cada 100ms

enum TipoProcesamiento{SinProcesamiento,FiltroPromedio,ConvUI,FiltroConv};

class PIDprofesional : public File
{            
public:
    PIDprofesional();
    PIDprofesional(float _Kp,float _Ki,float _Kd);
    void set_Kp(float _Kp){Kp=_Kp;}
    void set_Kp(float _Kp,QLCDNumber &lcd){Kp=_Kp; lcd.display(Kp);}
    void set_Kpi(float _Kpi){Kpi=_Kpi;}
    void set_Kpi(float _Kpi,QLCDNumber &lcd){Kpi=_Kpi; lcd.display(Kpi);}
    void set_Ki(float _Ki){Ki=_Ki;}
    void set_Ki(float _Ki,QLCDNumber &lcd){Ki=_Ki; lcd.display(Ki);}
    void set_Kd(float _Kd){Kd=_Kd;}
    void set_Kd(float _Kd,QLCDNumber &lcd){Kd=_Kd; lcd.display(Kd);}
    void set_Tc(float _Tc){Tc=_Tc;}
    void set_Tc(float _Tc,QLCDNumber &lcd){Tc=_Tc; lcd.display(Tc);}
    void set_F(int _F){F=_F;}
    void set_F(float _F,QLCDNumber &lcd){F=_F; lcd.display(F);}
    void set_Modo(int _Modo){Modo=_Modo;}
    void set_tipo_procesamiento(TipoProcesamiento _tipo_procesamiento);
    float get_Kp(){return Kp;}
    float get_Kpi(){return Kpi;}
    float get_Ki(){return Ki;}
    float get_Kd(){return Kd;}
    float get_Tc(){return Tc;}
    int get_F(){return F;}
    int get_Modo(){return Modo;}
    TipoProcesamiento get_tipo_procesamiento(){return tipo_procesamiento;}
    bool get_fconvUI(){return fconvUI;}
    bool get_fcantM(){return fcantM;}
    void set_rf(int _rf){rf=_rf;}
    void set_yf(int _yf){yf=_yf;}
    void set_u(int _u){u=_u;}
    void set_u(int _u,QLCDNumber &lcd){u=_u; lcd.display(u);}
    int calcular_error();
    int get_rf(){return rf;}
    int get_rf_UI(){return rf*resolucion;}
    int get_yf(){return yf;}
    int get_yf_UI(){return yf*resolucion;}
    int get_u(){return u;}
    int get_u_UI(){return u*resolucion;}
    int get_e(){return e;}
    int get_e_UI(){return e*resolucion;}    
    void initialize_curves(QwtPlot *parent);
    void initialize_curvesHist(QwtPlot *parentHist);
    double Conv_UI(int variable){return variable*resolucion;}
    void set_tref(int _tref){tref=_tref;}
    int get_tref(){return tref;}
    //Funciones para las graficas
    Curve* get_Y_curve(){return Ycurve;}
    Curve* get_U_curve(){return Ucurve;}
    Curve* get_E_curve(){return Ecurve;}
    void Graficar();
    void cambiar_escala(QwtPlot *parent);
    void inicializar_escala();
    void set_univPI(int _univPI){univPI=_univPI;}
    void set_univPD(int _univPD){univPD=_univPD;}
    void set_univPI(int _univPI,QLCDNumber &lcd){univPI=_univPI; lcd.display(univPI);}
    void set_univPD(int _univPD,QLCDNumber &lcd){univPD=_univPD; lcd.display(univPD);}
    int get_univPI(){return univPI;}
    int get_univPI_UI(){return univPI*resolucion;}
    int get_univPD(){return univPD;}
    int get_univPD_UI(){return univPD*resolucion;}
    void set_isFuzzy(bool _isFuzzy){isFuzzy=_isFuzzy;}
    bool get_isFuzzy(){return isFuzzy;}
    void set_stepPI(float _step){stepPI=_step;}
    void set_stepPI(int _step,QLCDNumber &lcd){stepPI=_step; lcd.display(stepPI);}
    float get_stepPI(){return stepPI;}
    float get_stepPI_UI(){return stepPI*resolucion;}
    void set_stepPD(float _step){stepPD=_step;}
    void set_stepPD(int _step,QLCDNumber &lcd){stepPD=_step; lcd.display(stepPD);}
    float get_stepPD(){return stepPD;}
    float get_stepPD_UI(){return stepPD*resolucion;}
    void set_Resolucion(double res){Ycurve->set_resolucion(res); Ucurve->set_resolucion(res); Ecurve->set_resolucion(res); resolucion=res;}
    double Resolucion(){return resolucion;}
    int get_desplazador(){return desplazador;}
    void set_desplazador(int desp){desplazador=desp;}
    void set_T(double _T){T=_T;}
    double get_T(){return T;}
    //Funciones para el fichero
    virtual void SaveParametros();
    virtual void SaveMuestra();
    bool get_flag_min(){return flag_min;}
    double get_tiempo(){return tiempo;}

    //Para el historial
    Curve *Ycurves[hist_array+1],*Ucurves[hist_array+1],*Ecurves[hist_array+1];
    Curve *Rcurves[hist_array+1];

private:
    int Modo;  //automatico o manual
    int F;  //F->cantidad de muestras del filtro promedio
    float Kp,Ki,Kd,Tc,Kpi;
    int univPI,univPD;
    float stepPI,stepPD;
    int rf,yf,u,e;
    int tref;
    TipoProcesamiento tipo_procesamiento;
    bool fconvUI;   //si es true las variables se multiplican por resolucion, cambia de estado en dependencia del tipo de procesamiento
    bool fcantM;    //si es false no permite enviar F
    Curve *Ycurve,*Ucurve,*Ecurve;
    bool isFuzzy;
    double resolucion;
    double T;
    bool flag_min;
    double tiempo;

    //Para el historial
    int desplazador;
};

#endif // PIDPROFESIONAL_H
