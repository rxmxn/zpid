#include "file.h"

File::File(const QString & name)
    :QFile(name)
{
    QString old=name;
    old.insert(old.indexOf(QString(".txt")),QString("_OLD"));

    if(exists(old))
        remove(old);
    if(exists(name))
        rename(name,old);

    if (!open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug("ERROR al abrir el fichero");
        return;
    }
}

File::~File()
{
    QTextStream out(this);
    out<<"------------------------------------------------------------------\n";

    close();
}

void File::SaveFile(QString cabecera_fichero)
{
    reset();

    QTextStream out(this);
    out<<date.currentDate().toString("dd.MM.yyyy")<<", "<<cabecera_fichero<<"\n";
}

void File::LoadFile(QTextEdit &textEdit)
{
    seek(0);
    QTextStream in(this);
    textEdit.clear();

    while (!in.atEnd())
    {
        QString line = in.readLine();
        textEdit.append(line);
    }
}
