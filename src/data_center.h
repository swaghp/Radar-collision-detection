#ifndef DATACENTER_H
#define DATACENTER_H

#include <QObject>
#include <QFileDialog>
#include <pthread.h>
#include <QVector>
#include <QMessageBox>
#include "lcm/lcm.h"
#include "Trajectory.h"
#include "mylcm_myBroadcast.h"

struct ObjectData
{
    int16_t heading;
    int16_t speed;
    // four coordinate
    int16_t coordinate1X;
    int16_t coordinate1Y;
    int16_t coordinate2X;
    int16_t coordinate2Y;
    int16_t coordinate3X;
    int16_t coordinate3Y;
    int16_t coordinate4X;
    int16_t coordinate4Y;
};

struct TrajectoryData
{
    int16_t myTrajectoryX;
    int16_t myTrajectoryY;
    int16_t speed;
};

class DataCenter : public QObject
{
    Q_OBJECT
public:
    DataCenter(void);
    ~DataCenter(void);

    bool inited(void);

    static DataCenter* instance(void);
    static void cleanup(void);

    static void onTrajectoryRecieve(const lcm_recv_buf_t *rbuf, const char *channel,
                                const Trajectory *msg, void *userdata);
    static void onBroadcastRecieve(const lcm_recv_buf_t *rbuf, const char *channel,
                                const mylcm_myBroadcast *msg, void *userdata);
    void startMpcProcessing(void);
    const QVector<ObjectData>& getObjectData();
    const QVector<TrajectoryData>& getCarPosData();

signals:
    void updateTrackRoute(TrajectoryData *,int16_t);
    void updateObject(ObjectData*, int32_t);

public slots:

private:
     QString _readFileInfo(QString mfilePath);
     static void *_mpcInfoProc(void *);
     u_int16_t typeChange(int16_t);

private:
    bool m_inited;
    lcm_t *m_lcm;
    pthread_t m_work;
    QVector<ObjectData> m_trajectoryData;
    QVector<TrajectoryData> m_objectData;
};
#endif // DATACENTER_H
