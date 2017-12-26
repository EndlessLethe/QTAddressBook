#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QMessageBox>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <fstream>
#include <set>
#include <windows.h>
#include <QDialog>
#include <QInputDialog>
#include <QDebug>
#include "ui_mainwindow.h"
using namespace std;

struct inf {
    string nm, pho, cls, email;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    map <string, inf> saved;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void print(string, string, string, string);
    void print(QString, QString, QString, QString);
    void find(int);
    void find(string);
    void find();
    string get_path();
    void action_read();
    void det(string);
    void action_det();
    void call();
    void action_call();
    void change(string, string, string, string);
    void action_change();
    void add(string, string, string, string);
    void action_add();
    void save(string, string, string, string);
    void re_save();
    int i_linenum = 0;

private slots:
    void accept();
    void connect_read();
};

#endif // MAINWINDOW_H
