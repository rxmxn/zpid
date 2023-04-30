/********************************************************************************
** Form generated from reading UI file 'ayuda.ui'
**
** Created: Sun 12. May 14:07:46 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AYUDA_H
#define UI_AYUDA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_Ayuda
{
public:
    QTabWidget *tabMenu;
    QWidget *tabIndice;
    QListWidget *listIndice;
    QWidget *tabBuscar;
    QPushButton *btnBuscar;
    QListWidget *listBuscar;
    QLineEdit *edtBuscar;
    QWebView *webView;
    QFrame *line_3;

    void setupUi(QDialog *Ayuda)
    {
        if (Ayuda->objectName().isEmpty())
            Ayuda->setObjectName(QString::fromUtf8("Ayuda"));
        Ayuda->resize(986, 667);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        Ayuda->setWindowIcon(icon);
        tabMenu = new QTabWidget(Ayuda);
        tabMenu->setObjectName(QString::fromUtf8("tabMenu"));
        tabMenu->setGeometry(QRect(10, 10, 181, 651));
        tabIndice = new QWidget();
        tabIndice->setObjectName(QString::fromUtf8("tabIndice"));
        listIndice = new QListWidget(tabIndice);
        new QListWidgetItem(listIndice);
        new QListWidgetItem(listIndice);
        new QListWidgetItem(listIndice);
        new QListWidgetItem(listIndice);
        new QListWidgetItem(listIndice);
        new QListWidgetItem(listIndice);
        new QListWidgetItem(listIndice);
        listIndice->setObjectName(QString::fromUtf8("listIndice"));
        listIndice->setGeometry(QRect(0, 0, 171, 621));
        tabMenu->addTab(tabIndice, QString());
        tabBuscar = new QWidget();
        tabBuscar->setObjectName(QString::fromUtf8("tabBuscar"));
        btnBuscar = new QPushButton(tabBuscar);
        btnBuscar->setObjectName(QString::fromUtf8("btnBuscar"));
        btnBuscar->setGeometry(QRect(0, 20, 171, 23));
        listBuscar = new QListWidget(tabBuscar);
        listBuscar->setObjectName(QString::fromUtf8("listBuscar"));
        listBuscar->setGeometry(QRect(0, 50, 171, 571));
        edtBuscar = new QLineEdit(tabBuscar);
        edtBuscar->setObjectName(QString::fromUtf8("edtBuscar"));
        edtBuscar->setGeometry(QRect(0, 0, 171, 20));
        tabMenu->addTab(tabBuscar, QString());
        webView = new QWebView(Ayuda);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setGeometry(QRect(200, 10, 781, 651));
        webView->setUrl(QUrl("about:blank"));
        line_3 = new QFrame(Ayuda);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(190, 10, 20, 651));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        retranslateUi(Ayuda);

        tabMenu->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Ayuda);
    } // setupUi

    void retranslateUi(QDialog *Ayuda)
    {
        Ayuda->setWindowTitle(QApplication::translate("Ayuda", "Ayuda", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = listIndice->isSortingEnabled();
        listIndice->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listIndice->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("Ayuda", "Controladores", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem1 = listIndice->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("Ayuda", "Herramientas", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem2 = listIndice->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("Ayuda", "Men\303\272", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem3 = listIndice->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("Ayuda", "Microcontrolador", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem4 = listIndice->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("Ayuda", "Modo Control", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem5 = listIndice->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("Ayuda", "Modo Supervisi\303\263n", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem6 = listIndice->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("Ayuda", "-Tipo de procesamiento", 0, QApplication::UnicodeUTF8));
        listIndice->setSortingEnabled(__sortingEnabled);

        tabMenu->setTabText(tabMenu->indexOf(tabIndice), QApplication::translate("Ayuda", "Indice", 0, QApplication::UnicodeUTF8));
        btnBuscar->setText(QApplication::translate("Ayuda", "Realizar b\303\272squeda", 0, QApplication::UnicodeUTF8));
        btnBuscar->setShortcut(QApplication::translate("Ayuda", "Return", 0, QApplication::UnicodeUTF8));
        tabMenu->setTabText(tabMenu->indexOf(tabBuscar), QApplication::translate("Ayuda", "Buscar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Ayuda: public Ui_Ayuda {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AYUDA_H
