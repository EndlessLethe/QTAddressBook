#include "dialog_call.h"
#include "ui_dialog_call.h"
#include "mainwindow.h"

Dialog_call::Dialog_call(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_call)
{
    ui->setupUi(this);


    connect(ui->call_a, SIGNAL(clicked()), this, SLOT(call()));
    connect(ui->call_b, SIGNAL(clicked()), this, SLOT(close()));


    i_linenum = 0;
    QString linenum, str;
    set <string> is_print;//set is used like map
    for (auto iter = ptr->saved.begin(); iter != ptr->saved.end(); iter++) {
        if (!is_print.count(iter->second.nm)) {//to make sure whether a man has one more pho nums
            linenum = QString::number(++i_linenum, 10);
            str = linenum + "\t"  + QString::fromStdString(iter->second.nm);;
            ui->call_plain->appendPlainText(str);
            is_print.insert(iter->second.nm);
        }
    }
}

Dialog_call::~Dialog_call()
{
    delete ui;
}

void Dialog_call::call() {
    const int stoptimelong = 500;
    QString qa = ui->call_line->text();
    string a = qa.toStdString();
    QString str, linenum;
    i_linenum = 0;
    ui->call_plain->appendPlainText("\nNum\tPhone");
    for (auto iter = ptr->saved.begin(); iter != ptr->saved.end(); iter++) {
        if (iter->second.nm == a) {
            linenum = QString::number(++i_linenum, 10);
            str = linenum + "\t" + QString::fromStdString(iter->second.pho);
            ui->call_plain->appendPlainText(str);
//            for (auto ch : iter->second.pho) {//c++11 new standard
//                str = ui->call_plain->toPlainText() + QString(ch);
//                ui->call_plain->clear();
//                ui->call_plain->appendPlainText(str);
//                Sleep(stoptimelong);
//            }
        }
    }
}
