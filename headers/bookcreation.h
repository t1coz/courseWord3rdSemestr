#ifndef BOOKCREATION_H
#define BOOKCREATION_H

#include <QDialog>

namespace Ui {
class bookCreation;
}

class bookCreation : public QDialog
{
    Q_OBJECT

public:
    explicit bookCreation(QWidget *parent = nullptr);
    ~bookCreation();

private slots:

    void on_uploadBtn_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::bookCreation *ui;
};

#endif // BOOKCREATION_H
