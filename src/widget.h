#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QString>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    enum Actions {NONE,ADD, SUB, TIM, DIV, POWN, SQRN};
    ~Widget();

private slots:
    void buttonClicked();
    void on_buttonA_clicked();
    void on_buttonM_clicked();
    void on_buttonT_clicked();
    void on_buttonD_clicked();
    void on_buttonEq_clicked();
    void on_buttonClear_clicked();
    void on_buttonDot_clicked();
    void on_buttonSign_clicked();
    void on_buttonDel_clicked();
    void on_buttonInv_clicked();
    void on_buttonSqr_clicked();
    void on_buttonPow_clicked();
    void on_buttonInvers_clicked();
    void on_buttonLn_clicked();
    void on_buttonLog_clicked();
    void on_buttonCos_clicked();
    void on_buttonSin_clicked();
    void on_buttonTan_clicked();
    void on_mButton_clicked();
    void on_mrButton_clicked();
    void on_mcButton_clicked();

private:
    Ui::Widget *ui;

    double firstNumber;
    double memoryNumber;
    Actions action;
    bool eqClicked;
    bool dtClicked;
    bool sgClicked;
    bool invClicked;
    bool isMem;

    void connectB();
};

#endif // WIDGET_H
