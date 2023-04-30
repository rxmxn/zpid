#ifndef CURVE_H
#define CURVE_H

#include <qwt_plot.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_math.h>
#include <qwt_scale_engine.h>
#include <qwt_symbol.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_text.h>
#include <qwt_panner.h>
#include <qwt_curve_fitter.h>

#define array_size 200

//#define resolucion 4.8875  //resolucion=5000mV/1023

class Curve : public QwtPlotCurve
{
public:
    Curve(QwtPlot *parent,QString name);
    Curve(QwtPlot *parent,QString name,QPen _color);
    void set_color(QPen _color);
    void set_side(int axis);
    void Cambiar_Escala(QwtPlot *parent,bool convertir);
    void set_flag_convertido(bool convertido){flag_convertido=convertido;}

    QPen get_color(){return color;}
    bool get_flag_convertido(){return flag_convertido;}

    double Buffer[array_size+1];
    double bTiempo[array_size+1];

    void set_resolucion(double res=4.8875){resolucion=res;}
    double get_resolucion(){return resolucion;}

private:
    QPen color;    
    bool flag_convertido;
    double resolucion;
};

#endif // CURVE_H
