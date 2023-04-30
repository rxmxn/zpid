/********************************************************************************
** Form generated from reading UI file 'loadedfile.ui'
**
** Created: Sun 12. May 14:07:46 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADEDFILE_H
#define UI_LOADEDFILE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_LoadedFile
{
public:
    QTextEdit *textEdit;

    void setupUi(QDialog *LoadedFile)
    {
        if (LoadedFile->objectName().isEmpty())
            LoadedFile->setObjectName(QString::fromUtf8("LoadedFile"));
        LoadedFile->resize(460, 461);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/fichero.png"), QSize(), QIcon::Normal, QIcon::Off);
        LoadedFile->setWindowIcon(icon);
        textEdit = new QTextEdit(LoadedFile);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(0, 0, 461, 461));
        textEdit->setContextMenuPolicy(Qt::ActionsContextMenu);
        textEdit->setReadOnly(true);
        textEdit->setOverwriteMode(false);

        retranslateUi(LoadedFile);

        QMetaObject::connectSlotsByName(LoadedFile);
    } // setupUi

    void retranslateUi(QDialog *LoadedFile)
    {
        LoadedFile->setWindowTitle(QApplication::translate("LoadedFile", "Fichero de muestras", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LoadedFile: public Ui_LoadedFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADEDFILE_H
