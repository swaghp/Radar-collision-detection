#ifndef DECISIONTOOL_H
#define DECISIONTOOL_H

#include <QMainWindow>

namespace Ui {
class DecisionTool;
}

class DecisionTool : public QMainWindow
{
    Q_OBJECT

public:
    explicit DecisionTool(QWidget *parent = 0);
    ~DecisionTool();

private:
    Ui::DecisionTool *ui;
};

#endif // DECISIONTOOL_H
