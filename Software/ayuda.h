#ifndef AYUDA_H
#define AYUDA_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QUrl>
#include <QtWebKit>
#include <QFileDialog>
#include <QDebug>

#define texto_size 8

namespace Ui {
    class Ayuda;
}

class Ayuda : public QDialog
{
    Q_OBJECT

public:
    explicit Ayuda(QWidget *parent = 0);
    ~Ayuda();
    void load_HTML(QString filename,int index);
    void mostrar_HTML(QString output,QString filename);

private:
    Ui::Ayuda *ui;
    QString texto[texto_size];
    bool flag_no_coincidencia;

private slots:
    void on_listBuscar_currentTextChanged(QString currentText);
    void on_btnBuscar_clicked();
    void on_listIndice_currentRowChanged(int index);
};

#endif // AYUDA_H
