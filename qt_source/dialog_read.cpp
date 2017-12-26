#include "dialog_read.h"
#include "ui_dialog_read.h"
#include "mainwindow.h"

Dialog_read::Dialog_read(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_read)
{
    ui->setupUi(this);
    MainWindow *ptr = (MainWindow*)parentWidget();
    connect(ui->read_a, SIGNAL(clicked()), ptr, SLOT(connect_read()));
    connect(ui->read_b, SIGNAL(clicked()), ptr, SLOT(connect_read()));
    connect(ui->read_c, SIGNAL(clicked()), ptr, SLOT(connect_read()));
    connect(ui->read_d, SIGNAL(clicked()), ptr, SLOT(connect_read()));
    connect(ui->read_e, SIGNAL(clicked()), this, SLOT(close()));
}

Dialog_read::~Dialog_read()
{
    delete ui;
}
