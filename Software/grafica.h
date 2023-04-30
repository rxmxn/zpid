#ifndef GRAFICA_H
#define GRAFICA_H

#include <curve.h>

class Grafica : public QwtPlot
{
public:
    Grafica(QWidget *parent);
    QwtPlotMarker* add_marker(QwtPlotMarker *name,Qt::Alignment ubicacion_texto,
                    QPen linea,QwtText label,bool eje_Y,int valor);
    QwtPlotMarker* add_marker(QwtPlotMarker *name,QwtText label,bool eje_Y,int valor);
    void set_Y_value(QwtPlotMarker *name,double value);    //for markers
    void set_X_value(QwtPlotMarker *name,double value);    //for markers
    void set_legend_style_sheet(const QString &styleSheet);
    void poner_leyenda();
    void poner_zoomer();
    void poner_panner();
    void set_grid_color(QColor color);
    void set_marker_color(QwtPlotMarker *name,QColor color);

    QwtPlotPicker *picker;
    QwtPlotZoomer *zoomer;
    QwtPlotPanner *panner;
    QwtLegend *legend;
    QwtPlotGrid *grid;
};

#endif // GRAFICA_H
