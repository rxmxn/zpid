#ifndef FILE_H
#define FILE_H

#include <QObject>

#include <QFile>
#include <QTextStream>

#include <QTimer>
#include <QDateTime>

#include <QTextEdit>

#define PIDpro_option 0

class File : public QFile
{
public:
    File(const QString & name);
    ~File();
    virtual void SaveParametros()=0; //para que PID herede de File y la implemente
    void SaveFile(QString cabecera_fichero);
    virtual void SaveMuestra()=0;
    void LoadFile(QTextEdit &textEdit);

protected:
    QDate date;
    QTime time;
};

#endif // FILE_H
