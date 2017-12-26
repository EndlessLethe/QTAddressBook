#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_call.h"
#include "dialog_read.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setupUi(this);
    setWindowTitle("Information Manage System");
    connect(pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(pushButton_2, SIGNAL(clicked()), this, SLOT(accept()));
    connect(pushButton_3, SIGNAL(clicked()), this, SLOT(accept()));
    connect(pushButton_4, SIGNAL(clicked()), this, SLOT(accept()));
    connect(pushButton_5, SIGNAL(clicked()), this, SLOT(accept()));
    connect(pushButton_6, SIGNAL(clicked()), this, SLOT(close()));
    string str = get_path();
    ifstream input(str,
                   ios::in);

    if (!input) {
        plainTextEdit->appendPlainText(tr("Read failed.No such file."));
    }
    else {
        string a, b, c, d;
        i_linenum = 0;
        QString str = "Num\tName\tPhone\tClass\tEmail";
        plainTextEdit->appendPlainText(str);
        while (input >> a >> b >> c >> d) {
            save(a, b, c, d);
            print(a, b, c, d);
        }
        input.close();
    }
}

MainWindow::~MainWindow()
{
    re_save();
    delete ui;
}

void MainWindow::accept() {
    QObject* lSender = sender();
    if(lSender==0)
       return ;
    if(lSender->objectName()=="pushButton") {
        action_read();
    }
    else if (lSender->objectName()=="pushButton_2") {
        action_add();
        find();
        return ;
    }
    else if (lSender->objectName()=="pushButton_3") {
        action_change();
        find();
        return ;
    }
    else if (lSender->objectName()=="pushButton_4") {
        action_det();
        find();
        return ;
    }
    else if (lSender->objectName()=="pushButton_5") {
        action_call();
        return ;
    }
    else {
        QMessageBox::warning(this, tr("waring"),
                             tr("no match"), QMessageBox::Yes);
    }
    re_save();
}

void MainWindow::find() {
    plainTextEdit->clear();
    QString str = "Num\tName\tPhone\tClass\tEmail";
    plainTextEdit->appendPlainText(str);
    i_linenum = 0;
    for (auto iter=saved.begin(); iter!=saved.end(); iter++) {
        print(iter->second.nm,iter->second.pho,
              iter->second.cls,iter->second.email);
    }
}

void MainWindow::find(int a) {
    plainTextEdit->clear();
    QString str = "Num\tName\tPhone\tClass\tEmail";
    plainTextEdit->appendPlainText(str);
    i_linenum = 0;
    stringstream ss;
    string s;
    ss << a;
    ss >> s;
    for (auto iter=saved.begin(); iter!=saved.end(); iter++) {
        if (iter->second.cls == s)
            print(iter->second.nm,iter->second.pho,
                  iter->second.cls,iter->second.email);
    }
//    plainTextEdit->appendPlainText("aaa");
}

void MainWindow::find(string a) {
    plainTextEdit->clear();
    QString str = "Num\tName\tPhone\tClass\tEmail";
    plainTextEdit->appendPlainText(str);
    i_linenum = 0;
    for (auto iter=saved.begin(); iter!=saved.end(); iter++) {
        if (iter->second.nm == a)
            print(iter->second.nm,iter->second.pho,
                  iter->second.cls,iter->second.email);
    }
}

void MainWindow::print(string a, string b, string c, string d) {
    QString qa = QString::fromStdString(a);
    QString qb = QString::fromStdString(b);
    QString qc = QString::fromStdString(c);
    QString qd = QString::fromStdString(d);
    QString linenum = QString::number(++i_linenum, 10);
    QString str = linenum + "\t"  + qa + "\t" + qb + "\t" + qc + "\t" + qd;
    plainTextEdit->appendPlainText(str);
}

void MainWindow::print(QString qa, QString qb, QString qc, QString qd) {
    QString linenum = QString::number(++i_linenum, 10);
    QString str = linenum + "\t"  + qa + "\t" + qb + "\t" + qc + "\t" + qd;
    plainTextEdit->appendPlainText(str);
}

void MainWindow::save(string a, string b, string c, string d) {
    saved[a+b].nm = a;
    saved[a+b].pho = b;
    saved[a+b].cls = c;
    saved[a+b].email = d;
}

void MainWindow::add(string a, string b, string c, string d) {
    if (saved.count(a+b)) {//a+b to make sure nm and pho are not both same
        QMessageBox::warning(this, tr("waring"),
                             tr("Data repeated"), QMessageBox::Yes);
        return;
    }
    else if (saved.size() >= 15) {
        QMessageBox::warning(this, tr("waring"),
                             tr("No more storage"), QMessageBox::Yes);
        return;
    }
    else if (a == "NULL") {
        QMessageBox::warning(this, tr("waring"),
                             tr("Invalid input"), QMessageBox::Yes);
        return;
    }
    else if (b == "NULL" && c == "NULL" && d == "NULL") {
        QMessageBox::warning(this, tr("waring"),
                             tr("Invalid input"), QMessageBox::Yes);
        return;
    }
    else {
        save(a, b, c, d);
        QMessageBox::warning(this, tr("Tip"),
                             tr("Add success"), QMessageBox::Yes);
    }
}

void MainWindow::action_read() {
    Dialog_read dialog_read(this);
    dialog_read.exec();
}

void MainWindow::connect_read() {
    QObject* lSender = sender();
    if(lSender==0)
       return ;
    if(lSender->objectName()=="read_a") {
        find();
        return;
    }
    else if(lSender->objectName()=="read_b") {
        find(1);
        return;
    }
    else if(lSender->objectName()=="read_c") {
        find(2);
        return;
    }
    else if(lSender->objectName()=="read_d") {
        find(3);
        return;
    }
}

void MainWindow::action_add() {
    QString qa = lineEdit->text();
    QString qb = lineEdit_2->text();
    QString qc = lineEdit_3->text();
    QString qd = lineEdit_4->text();
    string a = qa.toStdString();
    string b = qb.toStdString();
    string c = qc.toStdString();
    string d = qd.toStdString();
    add(a, b, c, d);
    lineEdit->setText("Null");
    lineEdit_2->setText("Null");
    lineEdit_3->setText("Null");
    lineEdit_4->setText("Null");
}

void MainWindow::change(string a, string b, string c, string d) {
    if (!saved.count(a+b)) {
        QMessageBox::warning(this, tr("waring"),
                             tr("No file exists"), QMessageBox::Yes);
    }
    else {
        save(a, b, c, d);
    }
}

void MainWindow::action_change() {
    QString qa = lineEdit->text();
    QString qb = lineEdit_2->text();
    QString qc = lineEdit_3->text();
    QString qd = lineEdit_4->text();
    string a = qa.toStdString();
    string b = qb.toStdString();
    string c = qc.toStdString();
    string d = qd.toStdString();
    change(a, b, c, d);
    lineEdit->setText("Null");
    lineEdit_2->setText("Null");
    lineEdit_3->setText("Null");
    lineEdit_4->setText("Null");
}

void MainWindow::det(string a) {
    bool is_enter = 0;
    for (auto iter = saved.begin(); iter != saved.end(); ) {
        if (iter->second.nm == a) {
            saved.erase(a + (iter++)->second.pho);
            is_enter = 1;
        }
        else iter++;
    }
    if (!is_enter) QMessageBox::warning(this, tr("waring"),
                                        tr("Delete failed.\nNo file exists"),
                                        QMessageBox::Yes);
}

void MainWindow::action_det() {
    bool isOK;
    QString text = QInputDialog::getText(NULL, "Det",
                                       "Please input the name you want to delete",
                                       QLineEdit::Normal,
                                       "",
                                       &isOK);
    if(isOK) {
       string a = text.toStdString();
       det(a);
    }
}

void MainWindow::action_call() {
    Dialog_call dialog_call(this);
    dialog_call.exec();
}

string MainWindow::get_path() {
    QFile file("test.txt");
    QFileInfo info(file);
//    plainTextEdit->appendPlainText("abs path"+info.absoluteFilePath());
    string i_path = info.absoluteFilePath().toStdString();
    string str;
    for (auto ch : i_path) {
        if (ch == '/') str += "//";
        else str += ch;
    }
    QString qstr = QString::fromStdString(str);
//    plainTextEdit->appendPlainText(qstr);
    return str;
}

void MainWindow::re_save() {
    string str = get_path();
    ofstream output(str);
    if (!output) {
        cout << "Save failed" << endl;
    }
    else {
        for (auto iter=saved.begin(); iter!=saved.end(); iter++) {
            output << iter->second.nm << " " << iter->second.pho <<
              " " << iter->second.cls << " " << iter->second.email << endl;
        }
    }
    output.close();
}
