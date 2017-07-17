#include "decisiontool.h"
#include <QApplication>
#include <QDesktopWidget>
#include "data_center.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<TrajectoryData>("TrajectoryData");
    qRegisterMetaType<ObjectData>("ObjectData");
    qRegisterMetaType<int32_t>("int32_t");
    qRegisterMetaType<int16_t>("int16_t");

    DecisionTool w;
    w.show();

    w.move ((QApplication::desktop()->width() - w.width())/2,(QApplication::desktop()->height() - w.height())/2);

    return a.exec();
}
