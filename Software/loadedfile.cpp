#include "loadedfile.h"
#include "ui_loadedfile.h"

LoadedFile::LoadedFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadedFile)
{
    ui->setupUi(this);

    myA = new QAction(ui->textEdit);
    myA->setShortcut(Qt::Key_F5);  //para mostrar el shortcut
    myA->setText("Actualizar");

    myS = new QShortcut(ui->textEdit);
    myS->setKey(Qt::Key_F5);
}

LoadedFile::~LoadedFile()
{
    delete ui;
}

QTextEdit* LoadedFile::change_text()
{
    return ui->textEdit;
}

QAction* LoadedFile::event_Action()
{
    return myA;
}

QShortcut* LoadedFile::event_Shortcut()
{
    return myS;
}

void LoadedFile::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu rcMenu;   //rc de right click
    rcMenu.addAction(myA);
    rcMenu.exec(event->globalPos());
}
