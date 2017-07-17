#include "decisiontool.h"
#include "ui_decisiontool.h"

DecisionTool::DecisionTool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DecisionTool)
{
    ui->setupUi(this);
     setStyleSheet("background: rgb(210,210,210); border: 2 groove rgb(115, 130, 122)");
     this->resize(QSize(500,650));
}

DecisionTool::~DecisionTool()
{
    delete ui;
}
