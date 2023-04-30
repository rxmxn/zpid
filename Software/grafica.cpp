#include "grafica.h"

Grafica::Grafica(QWidget *parent):
        QwtPlot(parent)
{
    setAutoReplot(false);

    // grid
    grid = new QwtPlotGrid;
    grid->setMajPen(QPen(Qt::white, 0, Qt::DotLine));
    grid->setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));
    grid->attach(this);

    // axes
    setAxisTitle(QwtPlot::xBottom, "t[s]");

    picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,
                QwtPicker::PointSelection | QwtPicker::DragSelection,
                QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
                canvas());
    picker->setRubberBandPen(QColor(Qt::green));
    picker->setRubberBand(QwtPicker::CrossRubberBand);
    picker->setTrackerPen(QColor(Qt::white));

    setAutoReplot(true);
}

void Grafica::set_grid_color(QColor color)
{
    grid->setMajPen(QPen(color, 0, Qt::DotLine));
    grid->setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));
}

void Grafica::poner_leyenda()
{
    setAutoReplot(false);

    // legend
    legend = new QwtLegend;
    legend->setFrameStyle(QFrame::Box|QFrame::Sunken);
    legend->setStyleSheet("background-color: rgb(206, 255, 252)");
    insertLegend(legend, QwtPlot::RightLegend);

    setAutoReplot(true);
}

void Grafica::poner_panner()
{
    setAutoReplot(false);

    panner = new QwtPlotPanner(canvas());
    panner->setMouseButton(Qt::LeftButton);
    panner->setEnabled(true);

    setAutoReplot(true);
}

void Grafica::poner_zoomer()
{
    setAutoReplot(false);

    zoomer = new QwtPlotZoomer(QwtPlot::xBottom, QwtPlot::yLeft,
            canvas());
    zoomer->setRubberBand(QwtPicker::RectRubberBand);
    zoomer->setRubberBandPen(QColor(Qt::green));
    zoomer->setTrackerMode(QwtPicker::ActiveOnly);
    zoomer->setTrackerPen(QColor(Qt::white));
    zoomer->setEnabled(false);

    setAutoReplot(true);
}

void Grafica::set_legend_style_sheet(const QString &styleSheet)
{
    legend->setStyleSheet(styleSheet);
}

QwtPlotMarker* Grafica::add_marker(QwtPlotMarker *name, Qt::Alignment ubicacion_texto, QPen linea, QwtText label, bool eje_Y, int valor)
{
    name = new QwtPlotMarker();
    name->setLabelAlignment(ubicacion_texto);
    name->setLinePen(linea);
    name->setLabel(label);
    if(eje_Y)
    {
        name->setYValue(valor);
        name->setLineStyle(QwtPlotMarker::HLine);
    }
    else
    {
        name->setXValue(valor);
        name->setLineStyle(QwtPlotMarker::VLine);
    }
    name->attach(this);

    return name;
}

QwtPlotMarker* Grafica::add_marker(QwtPlotMarker *name, QwtText label, bool eje_Y, int valor)
{
    name = new QwtPlotMarker();
    name->setLabelAlignment(Qt::AlignRight | Qt::AlignBottom);
    name->setLinePen(QPen(Qt::white, 0, Qt::DashLine));
    if(eje_Y)
    {
        name->setYValue(valor);
        name->setLineStyle(QwtPlotMarker::HLine);
    }
    else
    {
        name->setXValue(valor);
        name->setLineStyle(QwtPlotMarker::VLine);
    }
    name->setLabel(label);
    name->attach(this);

    return name;
}

void Grafica::set_marker_color(QwtPlotMarker *name,QColor color)
{
    name->setLinePen(QPen(color, 0, Qt::DashLine));
}

void Grafica::set_X_value(QwtPlotMarker *name,double value)
{
    name->setXValue(value);
    name->attach(this);
}

void Grafica::set_Y_value(QwtPlotMarker *name,double value)
{
    name->setYValue(value);
    name->attach(this);
}
