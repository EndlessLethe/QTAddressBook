#ifndef DIALOG_CALL_H
#define DIALOG_CALL_H

#include <QDialog>
#include <ui_dialog_call.h>
#include <mainwindow.h>
#include <QThread>
namespace Ui {
class Dialog_call;
}

class Dialog_call : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_call(QWidget *parent = 0);
    ~Dialog_call();

private:
    int i_linenum = 0;
    MainWindow *ptr = (MainWindow*)parentWidget();
    Ui::Dialog_call *ui;

private slots:
    void call();
};

#endif // DIALOG_CALL_H
