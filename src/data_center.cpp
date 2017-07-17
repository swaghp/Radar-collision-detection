#include "data_center.h"
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>

#define URL "udpm://239.255.76.67:7667?ttl=1"
#define CHANNELTRA "TRAJECTORY"
#define CHANNELBROAD "myBroadcast"
#define UNUSED(o) ((o) = (o))
#define CarRouteWidth 1.5
#define WidenDistance 3.75/2
static DataCenter* g_instance = NULL;

DataCenter* DataCenter::instance(void)
{
    if (!g_instance)
    {
        g_instance = new DataCenter;
    }
    if (!g_instance->inited())
    {
        return NULL;
    }
    return g_instance;
}

void DataCenter::cleanup(void)
{
    delete g_instance;
    g_instance = NULL;
}

DataCenter::DataCenter()
{
    m_work = 0;
    m_inited = false;

    m_lcm = lcm_create(URL);
    if(m_lcm == NULL)
    {
        return ;
    }
    Trajectory_subscribe(m_lcm, CHANNELTRA, &onTrajectoryRecieve, this);
    mylcm_myBroadcast_subscribe(m_lcm, CHANNELBROAD, &onBroadcastRecieve, this);
    m_inited = true;
}

DataCenter::~DataCenter()
{
    if(m_inited)
    {
        m_inited = false;
        if(m_work)
        {
            pthread_cancel(m_work);
            pthread_join(m_work, NULL);
        }
        if(m_lcm)
        {
            lcm_destroy(m_lcm);
            m_lcm = NULL;
        }
    }
}

bool DataCenter::inited(void)
{
    return m_inited;
}



void DataCenter::startMpcProcessing(void)
{
    int ret = pthread_create(&m_work, NULL, _mpcInfoProc, this);
    if(ret != 0)
    {
        QMessageBox::warning(NULL, "Info", "create thread failed!");
    }
}

void *DataCenter::_mpcInfoProc(void *p)
{
    DataCenter *thiz = (DataCenter *)p;
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    while (true)
    {
        pthread_testcancel();
        lcm_handle(thiz->m_lcm);
    }
    return NULL;
}

void DataCenter::onTrajectoryRecieve(const lcm_recv_buf_t *rbuf, const char *channel,
                                  const Trajectory *msg, void *userdata)
{
    UNUSED(rbuf);
    UNUSED(channel);
    UNUSED(userdata);

    TrajectoryData *carPos = (TrajectoryData *)malloc(1024);
    for(int i = 0; i < msg->count; ++i)
    {
        carPos[i].myTrajectoryX = msg->trajectory[i].point.x;
        carPos[i].myTrajectoryY = msg->trajectory[i].point.y;
    }
    emit g_instance->updateTrackRoute(carPos, msg->count);
}

void DataCenter::onBroadcastRecieve(const lcm_recv_buf_t *rbuf, const char *channel,
                                  const mylcm_myBroadcast *msg, void *userdata)
{
    UNUSED(rbuf);
    UNUSED(channel);
    UNUSED(userdata);

    ObjectData* obj =(ObjectData *)malloc(1024);
    for(int i = 0; i < msg->objNum; ++i)
    {
        qDebug()<<msg->objs[0].orient0;
        obj[i].heading = msg->objs[i].orient0;
        obj[i].speed = msg->objs[i].speed0;
        obj[i].coordinate1X = msg->objs[i].contour0[0];
        obj[i].coordinate1Y = msg->objs[i].contour0[1];
        obj[i].coordinate2X = msg->objs[i].contour0[2];
        obj[i].coordinate2Y = msg->objs[i].contour0[3];
        obj[i].coordinate3X = msg->objs[i].contour0[4];
        obj[i].coordinate3Y = msg->objs[i].contour0[5];
        obj[i].coordinate4X = msg->objs[i].contour0[6];
        obj[i].coordinate4Y = msg->objs[i].contour0[7];
    }
   qDebug()<<"abcabc";
    emit g_instance->updateObject(obj, msg->objNum);
}

u_int16_t DataCenter::typeChange(int16_t data)
{
        return data;
}

