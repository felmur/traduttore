#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QClipboard>

#include <iostream>
using namespace std;

QProcess *p=nullptr;

char *deflang0=(char *)"Italian";
char *deflang1=(char *)"English";

QString prgname = "Traduttore";
QString version = (char *)"1.1a";
QString email = (char *)"linuxboy@fel.hopto.org";
QString location = (char *)"Salerno - Italia";
QString copyright = (char *)"(c) 2026 by Felice Murolo - All rights reserved";
QClipboard *clipboard = NULL;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QList<QByteArray> cfg;
    char l[128];

    ui->setupUi(this);

    clipboard = QGuiApplication::clipboard();

    setWindowTitle(prgname+" v"+version+" - "+copyright);
    setWindowIcon(QIcon(":/img/icon"));


    QStringList ii;
    for (int i = 0; i < ui->cblang0->count(); ++i) {
        ii << ui->cblang0->itemText(i);
    }
    ui->cblang1->addItems(ii);

    ui->cblang0->setCurrentText(deflang0);
    ui->cblang1->setCurrentText(deflang1);
    ui->tbcopy->setEnabled(false);

    QFile f(QDir::homePath()+"/.traduttore.cfg");
    if (f.open(QFile::ReadOnly)){
        f.readLine(l,127);
        cfg << l;
        f.readLine(l,127);
        cfg << l;
        f.close();
        ui->cblang0->setCurrentText(cfg[0].trimmed());
        ui->cblang1->setCurrentText(cfg[1].trimmed());
    }

}

MainWindow::~MainWindow()
{
    QFile f(QDir::homePath()+"/.traduttore.cfg");
    if (f.open(QFile::WriteOnly)){
        f.write(ui->cblang0->currentText().toLocal8Bit().data());
        f.write("\n");
        f.write(ui->cblang1->currentText().toLocal8Bit().data());
        f.write("\n");
        f.close();
    }
    delete ui;
}

void MainWindow::goclick()
{
    if (ui->telang0->toPlainText().length()){
        QStringList args;
        args << "-b" << getlangid(ui->cblang0->currentText())+":"+getlangid(ui->cblang1->currentText()) << ui->telang0->toPlainText();

        p = new QProcess();
        connect(p, SIGNAL(readyReadStandardOutput()), this, SLOT(procReadyRead()));
        connect(p, SIGNAL(readyReadStandardError()), this, SLOT(procReadyReadError()));
        p->start("trans", args);
        p->waitForFinished();
    }
}

void MainWindow::swapclick()
{
    int c0 = ui->cblang0->currentIndex();
    int c1 = ui->cblang1->currentIndex();
    ui->cblang0->setCurrentIndex(c1);
    ui->cblang1->setCurrentIndex(c0);
}

void MainWindow::procReadyRead()
{
    ui->telang1->clear();
    QByteArray data = p->readAllStandardOutput();
    ui->telang1->appendPlainText(data);
}

void MainWindow::procReadyReadError()
{
    QByteArray data = p->readAllStandardOutput();
    cout << "Error!" << endl << data.data() << endl;
}

QString MainWindow::getlangid(QString lang)
{
    if (lang == "Chinese") return "zh";
    if (lang == "Czech") return "cs";
    if (lang == "Dutch") return "nl";
    if (lang == "English") return "en";
    if (lang == "Estonian") return "et";
    if (lang == "Finnish") return "fi";
    if (lang == "French") return "fr";
    if (lang == "German") return "de";
    if (lang == "Greek") return "el";
    if (lang == "Italian") return "it";
    if (lang == "Japanese") return "ja";
    if (lang == "Korean") return "ko";
    if (lang == "Latin") return "la";
    if (lang == "Polish") return "pl";
    if (lang == "Portughese") return "pt";
    if (lang == "Russian") return "ru";
    if (lang == "Serbian") return "sr";
    if (lang == "Slovak") return "sk";
    if (lang == "Spanish") return "es";
    if (lang == "Svedish") return "sv";
    if (lang == "Turkish") return "tr";
    if (lang == "Ukrainian") return "uk";
    return "";
}

void MainWindow::copyresultsclick()
{
    if (ui->telang1->toPlainText().length()){
        clipboard->setText(ui->telang1->toPlainText());
    }
}

void MainWindow::lang1changed()
{
    if (ui->telang1->toPlainText().length()){
        ui->tbcopy->setEnabled(true);
    }
}
