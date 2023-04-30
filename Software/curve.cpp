#include "curve.h"

Curve::Curve(QwtPlot *parent,QString name):
        QwtPlotCurve(name)
{
    setYAxis(QwtPlot::yLeft);
    setPen(QPen(Qt::black));
  /*  QwtSplineCurveFitter *curveFitter = new QwtSplineCurveFitter();
    curveFitter->setFitMode(QwtSplineCurveFitter::ParametricSpline);
    curveFitter->setSplineSize(550);
    setCurveFitter(curveFitter);
    setCurveAttribute(QwtPlotCurve::Fitted, true);*/
    this->attach(parent);

    flag_convertido=false;

    resolucion=4.8875;
}

Curve::Curve(QwtPlot *parent,QString name,QPen _color):
        QwtPlotCurve(name)
{
    setYAxis(QwtPlot::yLeft);
    setPen(_color);
    this->attach(parent);

    flag_convertido=false;

    resolucion=4.8875;
}

void Curve::set_side(int axis)
{
    setYAxis(axis);
}

void Curve::set_color(QPen _color)
{
    color=_color;
}

void Curve::Cambiar_Escala(QwtPlot *parent, bool convertir)
{
    const double res=4.8875;

    detach();

    qDebug("Entro en Cambiar escala");

    if(convertir==true)
    {
        flag_convertido=true;        
        qDebug("convertir=true");

    //    setAxisScale(0,0,5000,500);
    //    setAxisTitle(QwtPlot::yLeft, "salida[0-5000mV]");

        for(int i=0;i<array_size;i++)
            Buffer[i]=Buffer[i]*res;
    }
    else
    {
    //    setAxisScale(0,0,1100,100);
    //    setAxisTitle(QwtPlot::yLeft, "salida[0-1023]");

        qDebug("convertir=false");

        if(flag_convertido)
        {
            for(int i=0;i<array_size;i++)
                Buffer[i]=Buffer[i]/res;

            flag_convertido=false;
            qDebug("Entro en flag_convertido");
        }
    }

    setData(bTiempo,Buffer,array_size);

    attach(parent);
}
