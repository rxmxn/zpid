#include "ayuda.h"
#include "ui_ayuda.h"

Ayuda::Ayuda(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ayuda)
{
    ui->setupUi(this);
    flag_no_coincidencia=true;
}

Ayuda::~Ayuda()
{
    delete ui;
}

void Ayuda::load_HTML(QString filename,int index)
{
    QFile file;

    file.setFileName(filename);

    if (!file.open(QIODevice::ReadOnly))
    {
        filename = QFileDialog::getOpenFileName(this);
        file.setFileName(filename);
       // QMessageBox::information(this, tr("Direccion"),filename); //para ver la direccion

        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Error al abrir el fichero"),file.errorString());
            return;
        }
    }

    QTextStream out(&file);
    QString output = out.readAll();
    texto[index] = output;
}

void Ayuda::mostrar_HTML(QString output, QString filename)
{
    ui->webView->setHtml(output, QUrl::fromLocalFile(filename));
}

void Ayuda::on_listIndice_currentRowChanged(int index)
{
    QString temp;

    switch(index)
    {
    case 0: temp = "C:/ayuda/controladores.html"; break;
    case 1: temp = "C:/ayuda/herramientas.html"; break;
    case 2: temp = "C:/ayuda/menu.html"; break;
    case 3: temp = "C:/ayuda/microcontrolador.html"; break;
    case 4: temp = "C:/ayuda/control.html"; break;
    case 5: temp = "C:/ayuda/supervision.html"; break;
    case 6: temp = "C:/ayuda/tipo_procesamiento.html"; break;
    }

    load_HTML(temp,index);
    mostrar_HTML(texto[index],temp);
}

void Ayuda::on_btnBuscar_clicked()
{
    QString temp,texto_temp;

    ui->listBuscar->clear();
    flag_no_coincidencia=true;

    load_HTML("C:/ayuda/controladores.html",0);
    load_HTML("C:/ayuda/herramientas.html",1);
    load_HTML("C:/ayuda/menu.html",2);
    load_HTML("C:/ayuda/microcontrolador.html",3);
    load_HTML("C:/ayuda/control.html",4);
    load_HTML("C:/ayuda/supervision.html",5);
    load_HTML("C:/ayuda/tipo_procesamiento.html",6);

    for(int i=0 ; i < texto_size-1 ; i++)
    {
        for(int j=0; j < texto[i].size() ; j++)
        {
            texto_temp = texto[i].mid(j,ui->edtBuscar->text().size());

            if((texto_temp == ui->edtBuscar->text()) ||
               (texto_temp == ui->edtBuscar->text().toUpper()) ||
               (texto_temp == ui->edtBuscar->text().toLower()))
            {
                switch(i)
                {
                case 0: temp = "Controladores"; break;
                case 1: temp = "Herramientas"; break;
                case 2: temp = "Menú"; break;
                case 3: temp = "Microcontrolador"; break;
                case 4: temp = "Control"; break;
                case 5: temp = "Supervisión"; break;
                case 6: temp = "Tipo de procesamiento"; break;
                }

                ui->listBuscar->addItem(temp);

                flag_no_coincidencia=false;

                break;  //para salir del ciclo interno
            }
        }
    }

    if(flag_no_coincidencia)
    {
        load_HTML("C:/ayuda/no_coincidencia.html",texto_size-1);
        mostrar_HTML(texto[texto_size-1],"C:/ayuda/no_coincidencia.html");
    }
}

void Ayuda::on_listBuscar_currentTextChanged(QString currentText)
{
    QString temp;
    int index;

    if(!flag_no_coincidencia && currentText!=NULL)
    {
        if(currentText == "Controladores") index=0;
        else if(currentText == "Herramientas") index=1;
        else if(currentText == "Menú") index=2;
        else if(currentText == "Microcontrolador") index=3;
        else if(currentText == "Control") index=4;
        else if(currentText == "Supervisión") index=5;
        else if(currentText == "Tipo de procesamiento") index=6;

        switch(index)
        {
        case 0: temp = "C:/ayuda/controladores.html"; break;
        case 1: temp = "C:/ayuda/herramientas.html"; break;
        case 2: temp = "C:/ayuda/menu.html"; break;
        case 3: temp = "C:/ayuda/microcontrolador.html"; break;
        case 4: temp = "C:/ayuda/control.html"; break;
        case 5: temp = "C:/ayuda/supervision.html"; break;
        case 6: temp = "C:/ayuda/tipo_procesamiento.html"; break;
        }

        load_HTML(temp,texto_size-1);
        mostrar_HTML(texto[texto_size-1],temp);
    }
}
