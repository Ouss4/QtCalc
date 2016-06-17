#include "widget.h"
#include "ui_widget.h"
#include <math.h>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    action = NONE;
    firstNumber = 0;
    //memoryNumber = 0; adding isMem bolean this initialisation does't matter.
    eqClicked = false;
    dtClicked = false;
    sgClicked = false;
    invClicked = false;
    isMem = false;

    setFixedSize(520,277);
    setWindowTitle("CalculatoR");

    connectB();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::connectB()
{
    connect(ui->button0, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->button1, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->button2, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->button3, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->button4, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->button5, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->button6, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->button7, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->button8, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->button9, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}
// One slot for all digit buttons (1-9). Connection done by the function above.
void Widget::buttonClicked()
{
    QPushButton *sButton = qobject_cast<QPushButton *>(sender());
    QString firstStr = "";

    if(ui->lineEdit->text() == "0" || eqClicked)
    {
        firstStr.append(sButton->text());
        eqClicked = false;
    }
    else
    {
        firstStr.append(sButton->text());
        firstStr = ui->lineEdit->text() + firstStr;
    }
    ui->lineEdit->setText(firstStr);
    firstStr.clear();
}

// Rest of buttons have a slot for each. Connection made directly the name (on_name_event()).
void Widget::on_buttonA_clicked()
{
    action = ADD;
    firstNumber = ui->lineEdit->text().toDouble();
    ui->lineEdit->setText("0");
    dtClicked = false;
}

void Widget::on_buttonM_clicked()
{
    action = SUB;
    firstNumber = ui->lineEdit->text().toDouble();
    ui->lineEdit->setText("0");
    dtClicked = false;
}

void Widget::on_buttonT_clicked()
{
    action = TIM;
    firstNumber = ui->lineEdit->text().toDouble();
    ui->lineEdit->setText("0");
    dtClicked = false;
}

void Widget::on_buttonD_clicked()
{
    action = DIV;
    firstNumber = ui->lineEdit->text().toDouble();
    ui->lineEdit->setText("0");
    dtClicked = false;
}

void Widget::on_buttonEq_clicked()
{
    double secondNumber = ui->lineEdit->text().toDouble();
    double sum = 0;
    switch(action)
    {
    case ADD:
        sum = firstNumber + secondNumber;
        break;
    case SUB:
        sum = firstNumber - secondNumber;
        break;
    case TIM:
        sum = firstNumber * secondNumber;
        break;
    case DIV:
        sum = firstNumber / secondNumber;
        break;
    case POWN:
        sum = pow(firstNumber, secondNumber);
        break;
    case SQRN:
        sum = pow(firstNumber, 1/secondNumber);
        break;
    default:
        break;
    }

    ui->lineEdit->setText(QString::number(sum, 'g', 9));
    eqClicked = true;
    sgClicked = false;
}

void Widget::on_buttonClear_clicked()
{
    ui->lineEdit->setText("0");
    firstNumber = 0;
    action = NONE;
    eqClicked = false;
    sgClicked = false;
    dtClicked = false;
}

void Widget::on_buttonDot_clicked()
{
    if(!dtClicked)
    {
        QString s = ".";
        QString ss = ui->lineEdit->text();
        ss += s;
        ui->lineEdit->setText(ss);
        dtClicked = true;
    }
}

void Widget::on_buttonSign_clicked()
{
    QString s = "-";
    QString ss = ui->lineEdit->text();
    if(!sgClicked)
    {
        ss = s + ss;
        ui->lineEdit->setText(ss);
        sgClicked = true;
    }
    else
    {
        ss.remove(0,1);
        ui->lineEdit->setText(ss);
        sgClicked = false;
    }
}

void Widget::on_buttonDel_clicked()
{
    QString s = ui->lineEdit->text();
    if(!eqClicked && s != "0" && s != "-0" && s != "0.")
    {
        int sz = s.size();
        s.remove(sz - 1, 1);

        if(sz != 1)
            ui->lineEdit->setText(s);

        else
            ui->lineEdit->setText("0");
    }
}

void Widget::on_buttonInv_clicked()
{
    if(!invClicked)
    {
        ui->buttonSqr->setText("sqrt(x)");
        ui->buttonLn->setText("exp");
        ui->buttonLog->setText("10^x");
        ui->buttonPow->setText("sqrty(x)");
        ui->buttonCos->setText("acos");
        ui->buttonSin->setText("asin");
        ui->buttonTan->setText("atan");
        invClicked = true;
    }
    else
    {
        ui->buttonSqr->setText("x²");
        ui->buttonLn->setText("ln");
        ui->buttonLog->setText("log");
        ui->buttonPow->setText("x^y");
        ui->buttonCos->setText("cos");
        ui->buttonSin->setText("sin");
        ui->buttonTan->setText("tan");
        invClicked = false;
    }
}

void Widget::on_buttonSqr_clicked()
{
    if(!invClicked)
    {
        double x;
        firstNumber = ui->lineEdit->text().toDouble();
        x = firstNumber*firstNumber;
        ui->lineEdit->setText(QString::number(x, 'g', 9));
        eqClicked = true;
    }
    else
    {
        double x;
        firstNumber = ui->lineEdit->text().toDouble();
        x = sqrt(firstNumber);
        ui->lineEdit->setText(QString::number(x, 'g', 9));
        eqClicked = true;
    }
}

void Widget::on_buttonPow_clicked()
{
    if(!invClicked)
    {
        action = POWN;
        firstNumber = ui->lineEdit->text().toDouble();
        ui->lineEdit->setText("0");
        dtClicked = false;
    }
    else
    {
        action = SQRN;
        firstNumber = ui->lineEdit->text().toDouble();
        ui->lineEdit->setText("0");
        dtClicked = false;
    }
}

void Widget::on_buttonInvers_clicked()
{
    firstNumber = ui->lineEdit->text().toDouble();
    double x = 1/firstNumber;
    ui->lineEdit->setText(QString::number(x, 'g', 9));
}

void Widget::on_buttonLn_clicked()
{
    if(!invClicked)
    {
        double x;
        firstNumber = ui->lineEdit->text().toDouble();
        x = log(firstNumber);
        ui->lineEdit->setText(QString::number(x, 'g', 9));
        eqClicked = true;
    }
    else
    {
        double x;
        firstNumber = ui->lineEdit->text().toDouble();
        x = exp(firstNumber);
        ui->lineEdit->setText(QString::number(x, 'g', 9));
        eqClicked = true;
    }
}

void Widget::on_buttonLog_clicked()
{
    if(!invClicked)
    {
        double x;
        firstNumber = ui->lineEdit->text().toDouble();
        x = log10(firstNumber);
        ui->lineEdit->setText(QString::number(x, 'g', 9));
        eqClicked = true;
    }
    else
    {
        double x;
        firstNumber = ui->lineEdit->text().toDouble();
        x = pow(10, firstNumber);
        ui->lineEdit->setText(QString::number(x, 'g', 9));
        eqClicked = true;
    }
}

void Widget::on_buttonCos_clicked()
{
    if(!invClicked)
    {
        double x;
        firstNumber = ui->lineEdit->text().toDouble();
        x = cos(firstNumber);
        ui->lineEdit->setText(QString::number(x, 'g', 9));
        eqClicked = true;
    }
    else
    {
        double x;
        firstNumber = ui->lineEdit->text().toDouble();
        x = acos(firstNumber);
        ui->lineEdit->setText(QString::number(x, 'g', 9));
        eqClicked = true;
    }
}

void Widget::on_buttonSin_clicked()
{
    if(!invClicked)
    {
        double x;
        firstNumber = ui->lineEdit->text().toDouble();
        x = sin(firstNumber);
        ui->lineEdit->setText(QString::number(x, 'g', 9));
        eqClicked = true;
    }
    else
    {
        double x;
        firstNumber = ui->lineEdit->text().toDouble();
        x = asin(firstNumber);
        ui->lineEdit->setText(QString::number(x, 'g', 9));
        eqClicked = true;
    }
}

void Widget::on_buttonTan_clicked()
{
    if(!invClicked)
    {
        double x;
        firstNumber = ui->lineEdit->text().toDouble();
        x = tan(firstNumber);
        ui->lineEdit->setText(QString::number(x, 'g', 9));
        eqClicked = true;
    }
    else
    {
        double x;
        firstNumber = ui->lineEdit->text().toDouble();
        x = atan(firstNumber);
        ui->lineEdit->setText(QString::number(x, 'g', 9));
        eqClicked = true;
    }
}

void Widget::on_mButton_clicked()
{
    memoryNumber = ui->lineEdit->text().toDouble();
    ui->lineEdit->setText("0");
    ui->lineEdit_2->setText("M");
    isMem = true;
}

void Widget::on_mrButton_clicked()
{
    if(isMem) ui->lineEdit->setText(QString::number(memoryNumber, 'g', 9));
}

void Widget::on_mcButton_clicked()
{
    memoryNumber = 0;
    ui->lineEdit_2->setText("");
    isMem = false;
}
