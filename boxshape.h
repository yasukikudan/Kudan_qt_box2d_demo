#ifndef BOXSHAPE_H
#define BOXSHAPE_H



#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QAbstractGraphicsShapeItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QList>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <algorithm/dataclass.h>
#include <algorithm/algorithm.h>
#include "Box2D/Box2D.h"
#include <QAccelerometer>
#include <memory>
#include <QDebug>
#include <random>
#include <QDataStream>

constexpr double cr=100;
class BoxShapeFactoty;

//2D図形
class BoxShape
{

    friend class BoxShapeFactoty;
public:
    ~BoxShape()
    {
        if(gitem.unique()==true){
            world->DestroyBody(body);
            scene->removeItem(gitem.get());
        }
    }
    //表示データの更新
    void update(){
        auto toDegree=[](double rad){
            constexpr double pi=3.141592653589793;
            double degree =(rad*180.0)/pi;
            return degree;
        };
        b2Vec2 position=body->GetPosition();
        const double rad=body->GetAngle();
        const double deg=toDegree(rad);
        if(gitem){
            gitem->setPos(RaCov.mulForce(position.x),RaCov.mulForce(position.y));
            gitem->setRotation(deg);
        }
    }

    b2Body* GetBody(){return body;}
    std::shared_ptr<QGraphicsItem> GetGitem(){return gitem;}
private:
    QGraphicsScene *scene=nullptr;
    b2World *world=nullptr;
    b2Body *body=nullptr;
    std::shared_ptr<QGraphicsItem> gitem;
    RangeConvert RaCov;
    //プライベートコンストラクタ
    BoxShape(){;}
    //シリアライズ処理
    //表示テータ生成

    std::shared_ptr<QGraphicsPolygonItem> GenGitem(QGraphicsScene *scene,QPolygonF &poly)
    {
        //表示データの生成
        auto out=std::shared_ptr<QGraphicsPolygonItem>(new QGraphicsPolygonItem(poly,nullptr));
        gitem=out;
        //アイテムデータの設定
        scene->addItem(gitem.get());
        return out;
    }
    //図形の定義
    void DefBody(b2BodyType btype,b2Vec2 velcocity=b2Vec2(0,0))
    {
        if(gitem&&(world!=nullptr)){
            b2BodyDef bodyDef;
            auto itempos=gitem->pos();
            bodyDef.type = btype;
            bodyDef.position.Set(RaCov.divForce(itempos.x()),RaCov.divForce(itempos.y()));
            bodyDef.linearVelocity=velcocity;;
            body=world->CreateBody(&bodyDef);
        }
    }
    //box2d図形データの生成
    b2PolygonShape GenShape(QPolygonF &poly)
    {
        b2PolygonShape dynamicBox;
        QVector<b2Vec2> vect=ConvertB2Vec2(poly,RaCov);
        dynamicBox.Set(vect.data(),vect.count());
        return dynamicBox;
    }

    //座標の変換
    QVector<b2Vec2> ConvertB2Vec2(QPolygonF &poly,RangeConvert &r){
        QVector<b2Vec2> vect(poly.count());
        for(const int i:SmartCountor(poly.count())){
            vect[i].x=r.divForce(poly[i].x());
            vect[i].y=r.divForce(poly[i].y());
        }
        return vect;
    }
};

#endif // BOXSHAPE_H
