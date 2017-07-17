#ifndef COLLISIONWEIGET_H
#define COLLISIONWEIGET_H

#include <QWidget>
#include <QPaintEvent>
#include <data_center.h>

class CollisionWeiget : public QWidget
{
    Q_OBJECT
public:
    explicit CollisionWeiget(QWidget *parent = 0);
    ~CollisionWeiget();

public:
    void paintEvent(QPaintEvent*);

private:
    void _drawGrid();
    void _drawCenter();
    void _drawobject();
    void _drawTrajectory();
    void _getPiexlCoord(int data);
    void _drawArrow();

signals:

public slots:
    void onRecieveTrack(TrajectoryData*, int16_t);
    void onRecieveObject(ObjectData*, int32_t);

private:
    int m_originX;
    int m_originY;
    DataCenter* m_dc;
    TrajectoryData *m_carData;
    ObjectData *m_obj;
    int m_carPosNum;
    int m_objNum;
};

#endif // COLLISIONWEIGET_H
