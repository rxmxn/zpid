#include "pidprofesional.h"

PIDprofesional::PIDprofesional() :
        File("PID.txt")
{
    if(!isFuzzy) {Kp=150; Ki=57.5; Kd=5.5; Tc=0.01;}
    else {Kp=1.01; Ki=0.05; Kd=3.7; Kpi=1.01; univPI=20; univPD=100; Tc=0.06; stepPD=50; stepPI=10;}
    rf=0; F=0; Modo=automatico;
    resolucion = 4.8875;
    set_tipo_procesamiento(FiltroPromedio);
    desplazador=0;
    T=0.1;
    tiempo=0;
}

PIDprofesional::PIDprofesional(float _Kp, float _Ki, float _Kd) :
        File("PID.txt")
{
    Kp=_Kp; Ki=_Ki; Kd=_Kd; Tc=0.01; Kpi=Kp;
    univPI=20; univPD=100; stepPD=50; stepPI=10;
    rf=0; F=0; Modo=automatico;
    resolucion = 4.8875;
    set_tipo_procesamiento(FiltroPromedio);
    desplazador=0;
    T=0.1;
}

void PIDprofesional::set_tipo_procesamiento(TipoProcesamiento _tipo_procesamiento)
{
    tipo_procesamiento=_tipo_procesamiento;

    switch(tipo_procesamiento)
    {
    case SinProcesamiento: fconvUI=false;  fcantM=false;  break;
    case FiltroPromedio: fconvUI=false;  fcantM=true;  break;
    case ConvUI: fconvUI=true;  fcantM=false;  break;
    case FiltroConv: fconvUI=true;  fcantM=true;  break;
    default: fconvUI=false;  fcantM=true;  break;
    }
}

void PIDprofesional::initialize_curves(QwtPlot *parent)
{
    const QColor bgColor(200,192,0);

    Ycurve = new Curve(parent,"yf",QPen(Qt::green));

    Ucurve = new Curve(parent,"u",QPen(bgColor));

    Ecurve = new Curve(parent,"e",QPen(Qt::red));
}

void PIDprofesional::initialize_curvesHist(QwtPlot *parentHist)
{
    const QColor bgColor(200,192,0);

    for(int i=0;i<=hist_array;i++)
    {
        Ycurves[i] = new Curve(parentHist,"yf",QPen(Qt::green));
        Ucurves[i] = new Curve(parentHist,"u",QPen(bgColor));
        Ecurves[i] = new Curve(parentHist,"e",QPen(Qt::red));
        Rcurves[i] = new Curve(parentHist,"rf",QPen(Qt::white, 0, Qt::DashLine));
    }
}

int PIDprofesional::calcular_error()
{
    e=rf-yf;
    return e;
}

void PIDprofesional::Graficar()
{
    static int counter=0;
    static double tiempoHistorial=0;

  //  tiempo+=0.1;  //pid virtual
  //  tiempo+=0.12;  //fuzzy virtual
    tiempo+=T;  //forma real
    tiempoHistorial+=T;

    if((int)tiempo%60==0)
        flag_min=true;
    else
        flag_min=false;

    //Almacenando para mostrar en el historial
    Ycurves[desplazador]->bTiempo[counter]=tiempoHistorial;
    Ucurves[desplazador]->bTiempo[counter]=tiempoHistorial;
    Ecurves[desplazador]->bTiempo[counter]=tiempoHistorial;
    Rcurves[desplazador]->bTiempo[counter]=tiempoHistorial;

    Ycurves[desplazador]->Buffer[counter] = yf;
    Ucurves[desplazador]->Buffer[counter] = u;
    Ecurves[desplazador]->Buffer[counter] = e;
    Rcurves[desplazador]->Buffer[counter] = rf;

    //Guardando valores en los arreglos para graficar
    Ycurve->bTiempo[counter]=tiempo;
    Ucurve->bTiempo[counter]=tiempo;
    Ecurve->bTiempo[counter]=tiempo;

    if(fconvUI)
    {
        Ycurve->Buffer[counter] = yf*resolucion;
        Ucurve->Buffer[counter] = u*resolucion;
        Ecurve->Buffer[counter] = e*resolucion;
    }
    else
    {
        Ycurve->Buffer[counter] = yf;
        Ucurve->Buffer[counter] = u;
        Ecurve->Buffer[counter] = e;
    }

    if(counter==array_size)
    {
        counter=0;

        if(tiempoHistorial >= 999)
            tiempoHistorial=0;

        if(desplazador==hist_array)
        {
            for(int i=0;i<array_size;i++)
            {
                Ycurves[0]->bTiempo[i]=Ycurves[desplazador]->bTiempo[i];
                Ucurves[0]->bTiempo[i]=Ucurves[desplazador]->bTiempo[i];
                Ecurves[0]->bTiempo[i]=Ecurves[desplazador]->bTiempo[i];
                Rcurves[0]->bTiempo[i]=Rcurves[desplazador]->bTiempo[i];

                Ycurves[0]->Buffer[i] = Ycurves[desplazador]->Buffer[i];
                Ucurves[0]->Buffer[i] = Ucurves[desplazador]->Buffer[i];
                Ecurves[0]->Buffer[i] = Ecurves[desplazador]->Buffer[i];
                Rcurves[0]->Buffer[i] = Rcurves[desplazador]->Buffer[i];
            }
            desplazador=1;
        }
        else desplazador++;
    }
    else
    {
        Ycurve->setData(Ycurve->bTiempo,Ycurve->Buffer,counter);
        Ucurve->setData(Ucurve->bTiempo,Ucurve->Buffer,counter);
        Ecurve->setData(Ecurve->bTiempo,Ecurve->Buffer,counter);

        counter++;
    }
}

void PIDprofesional::cambiar_escala(QwtPlot *parent)
{
    Ycurve->Cambiar_Escala(parent,fconvUI);
    Ecurve->Cambiar_Escala(parent,fconvUI);
    Ucurve->Cambiar_Escala(parent,fconvUI);
}

void PIDprofesional::inicializar_escala()
{
    Ycurve->set_flag_convertido(fconvUI);
    Ecurve->set_flag_convertido(fconvUI);
    Ucurve->set_flag_convertido(fconvUI);
}

void PIDprofesional::SaveParametros()
{
    QTextStream out(this);
    out<<"...............................................................\n";

    out<<"Tc="<<Tc<<",Kp="<<Kp<<",Ki="<<Ki<<",Kd="<<Kd<<",F="<<F;
    if(isFuzzy) out<<",Kpi="<<Kpi;
    if(Modo==automatico) out<<",Automatico\n";
    else out<<",Manual\n";
    if(isFuzzy) out<<"univPI="<<univPI<<",univPD="<<univPD<<",stepPI="<<stepPI<<",stepPD="<<stepPD<<"\n";
    out<<"...............................................................\n";
    out<<"Tiempo                    U                  Y                   R                   E\n";
}

void PIDprofesional::SaveMuestra()
{
    QTextStream out(this);
    out<<time.currentTime().toString("hh.mm.ss.zzz")<<"          ";
    out<<u<<"                 "<<yf<<"                 "<<rf<<"                 "<<e<<"\n";
}
