#ifndef LOADEDFILE_H
#define LOADEDFILE_H

#include <QDialog>

#include <QTextEdit>
#include <QKeyEvent>
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>
#include <QShortcut>

namespace Ui {
    class LoadedFile;
}

class LoadedFile : public QDialog
{
    Q_OBJECT

public:
    explicit LoadedFile(QWidget *parent = 0);
    ~LoadedFile();

public slots:
    QTextEdit* change_text();
    QAction* event_Action();
    QShortcut* event_Shortcut();
    void contextMenuEvent(QContextMenuEvent *event);

private:
    Ui::LoadedFile *ui;
    QAction *myA;
    QShortcut *myS;
};

#endif // LOADEDFILE_H
