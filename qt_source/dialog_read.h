#ifndef DIALOG_READ_H
#define DIALOG_READ_H

#include <QDialog>
#include <ui_dialog_read.h>

namespace Ui {
class Dialog_read;
}

class Dialog_read : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_read(QWidget *parent = 0);

    ~Dialog_read();

private:
    Ui::Dialog_read *ui;
};

#endif // DIALOG_READ_H
