#ifndef BOX2DSCENE_H
#define BOX2DSCENE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QAbstractGraphicsShapeItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QList>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
//#include <QSensorGesture>
//#include <cocos2dx/include/cocos2d.h>
//#include <Box2D/Box2D.h>
#include <algorithm/dataclass.h>
#include <algorithm/algorithm.h>
#include "Box2D/Box2D.h"
#include <QAccelerometer>
#include <memory>
#include <QDebug>
#include <random>
#include <boxshapefactoty.h>
#include <boxshape.h>
#include <thread>


class Box2dScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Box2dScene(QObject *parent=nullptr,const int mode=0);
    ~Box2dScene();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
signals:
    void NowGravtey(QPointF);
    void GameEnd();
private slots:
    void update();
private:
    QTimer update_timer;
    QStringList strlist;
    QAccelerometer *Accelerometer=nullptr;
    std::shared_ptr<QPointF> oldpos;
    std::shared_ptr<b2World> world;
    b2Body* groundBody=nullptr;
    b2Body* body=nullptr;
    std::shared_ptr<QGraphicsEllipseItem> exit;
    std::shared_ptr<BoxShape> pcobj;
    RangeConvert RaCov;
    std::shared_ptr<BoxShapeFactoty> bsf;
    QList<std::shared_ptr<BoxShape>> objShapeList;
    QList<std::shared_ptr<BoxShape>> ShapeList;
    QList<std::shared_ptr<BoxShape>> Edge;
    std::mt19937 genrand;
};

#endif // BOX2DSCENE_H
