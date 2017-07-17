#include "collisionweiget.h"
#include <QPainter>
#include <data_center.h>
#include <string.h>
#include <QDebug>
#define GET_PIXELCOORDX(data) (m_originX - ((float)(data)/20)*m_originY/6)
#define GET_PIXELCOORDY(data1) (m_originY - ((float)(data1)/100)*m_originY)

CollisionWeiget::CollisionWeiget(QWidget *parent) : QWidget(parent)
{
    connect(DataCenter::instance(), SIGNAL(updateTrackRoute(TrajectoryData *, int16_t)),
            this, SLOT(onRecieveTrack(TrajectoryData *, int16_t)));
    connect(DataCenter::instance(), SIGNAL(updateObject(ObjectData*, int32_t)),
            this, SLOT(onRecieveObject(ObjectData*, int32_t)));
    DataCenter::instance()->startMpcProcessing();
    m_objNum=0;
m_carPosNum = 0;
    m_carData = NULL;
}

CollisionWeiget::~CollisionWeiget()
{
    m_objNum=0;
    m_carPosNum = 0;
    m_obj = NULL;
    m_carData = NULL;

}

void CollisionWeiget::paintEvent(QPaintEvent*)
{
    _drawGrid();
    _drawCenter();
    _drawobject();
    _drawTrajectory();
}

void CollisionWeiget::_drawGrid()
{
    int w,h;
    w = rect().width();
    h = rect().height();
    m_originX = w/2;
    m_originY = h*5/6;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen, pen2;
    pen.setWidth(1);
    pen2.setWidth(1);
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);

    QPoint pt0(m_originX - m_originY/6, m_originY);
    QPoint pt1(m_originX + m_originY/6, m_originY);
    painter.drawLine(pt0, pt1);

    QPoint pt2(m_originX, 0);
    QPoint pt3(m_originX, h);
    painter.drawLine(pt2, pt3);

    painter.setPen(pen2);
    QPoint pt4(m_originX - m_originY/6, h);
    QPoint pt5(m_originX - m_originY/6, 0);
    painter.drawLine(pt4, pt5);

    QPoint pt6(m_originX + m_originY/6, h);
    QPoint pt7(m_originX + m_originY/6, 0);
    painter.drawLine(pt6, pt7);
}

void CollisionWeiget::_drawCenter()
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPoint p1(m_originX, m_originY + 18), p2(m_originX, m_originY - 18);
    QPoint p3(m_originX - 4, m_originY - 10), p4(m_originX + 4, m_originY - 10);

    painter.drawLine(p1, p2);
    painter.drawLine(p3, p2);
    painter.drawLine(p4, p2);
}

void CollisionWeiget::_drawobject()
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);

    for(int i = 0; i < m_objNum; ++i)
    {
        float x1 ,y1 ;
        x1 = m_obj[i].coordinate1Y/100;
        y1 = m_obj[i].coordinate1X/100;
//        x2 = m_obj[i].coordinate2Y/100;
//        y2 = m_obj[i].coordinate2X/100;
//        x3 = m_obj[i].coordinate3Y/100;
//        y3 = m_obj[i].coordinate3X/100;
//        x4 = m_obj[i].coordinate4Y/100;
//        y4 = m_obj[i].coordinate4X/100;

        QPoint p1(GET_PIXELCOORDX(m_obj[i].coordinate1X/100), GET_PIXELCOORDY(m_obj[i].coordinate1Y/100)),
                p2(GET_PIXELCOORDX(m_obj[i].coordinate2X/100), GET_PIXELCOORDY(m_obj[i].coordinate2Y/100)),
                p3(GET_PIXELCOORDX(m_obj[i].coordinate3X/100), GET_PIXELCOORDY(m_obj[i].coordinate3Y/100)),
                p4(GET_PIXELCOORDX(m_obj[i].coordinate4X/100), GET_PIXELCOORDY(m_obj[i].coordinate4Y/100));

        painter.drawLine(p1,p2);
        painter.drawLine(p2,p3);
        painter.drawLine(p3,p4);
        painter.drawLine(p4,p1);

        painter.save();
        painter.translate(GET_PIXELCOORDX(y1), GET_PIXELCOORDY(x1));
        QPoint pt1(p1.x(), p1.y()-25),
                pt2(p1.x() - 4, pt1.y() + 4),
                pt3(p1.x() + 4, pt1.y() + 4);

        painter.rotate(m_obj[i].heading);
        //qDebug()<< ;
        painter.translate(-GET_PIXELCOORDX(y1), -GET_PIXELCOORDY(x1));

        painter.drawLine(p1,pt1);
        painter.drawLine(pt1,pt2);
        painter.drawLine(pt1,pt3);
        painter.restore();
        //_drawArrow(p2);
    }
    qDebug()<<"asdasd";
}

void CollisionWeiget::onRecieveTrack(TrajectoryData* myCarData, int16_t num)
{
    m_carData = myCarData;
    m_carPosNum = num;
    update();
}

void CollisionWeiget::onRecieveObject(ObjectData* myObj, int32_t num)
{
    m_obj = myObj;
    m_objNum = num;
    update();
}

void CollisionWeiget::_drawTrajectory()
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);

    for(int i = 0;i < m_carPosNum; ++i)
    {
        QPoint p1(GET_PIXELCOORDX(m_carData[i].myTrajectoryX), GET_PIXELCOORDY(m_carData[i].myTrajectoryY));
        painter.drawPoint(p1);
    }
}
