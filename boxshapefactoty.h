#ifndef BOXSHAPEFACTOTY_H
#define BOXSHAPEFACTOTY_H

#include <QObject>
#include <QGraphicsScene>
#include <memory>
#include <Box2D/Box2D.h>
#include <algorithm/dataclass.h>
#include <boxshape.h>
#include <boxshapesetting.h>
//#include <QApplication>
//#include <QStyle>
//#include <QIcon>

class BoxShapeFactoty
{
public:
    std::shared_ptr<BoxShapeFactoty> static create(QGraphicsScene *setscene, std::shared_ptr<b2World> setworld,RangeConvert setrac){
        auto out=new BoxShapeFactoty(setscene,setworld,setrac);
        return std::shared_ptr<BoxShapeFactoty>(out);
    }
    //静的図形の生成
    std::shared_ptr<BoxShape> genStaticBody(QPolygonF poly)
    {
        auto boxShape=std::shared_ptr<BoxShape>(new BoxShape());
        //初期化
        boxShape->RaCov=rac;
        boxShape->scene=(scene);
        boxShape->world=(world.get());
        boxShape->body=(nullptr);
        //表示データの生成;
        auto tgitem=boxShape->GenGitem(boxShape->scene,poly);
        tgitem->setBrush(QBrush(Qt::cyan,Qt::BrushStyle::SolidPattern));
        tgitem->setPen(QPen(QColor(0,0,0,1)));
        //box2dのデータを作成
        boxShape->DefBody(b2_staticBody);
        //図形の形状設定
        b2PolygonShape staticBox=boxShape->GenShape(poly);
        boxShape->body->CreateFixture(&staticBox,0.0f);

        return boxShape;
    }
    //動的矩形の生成
    std::shared_ptr<BoxShape> genDynamicRectBody(QRectF &rect,b2Vec2 velcocity=b2Vec2(0,0),QGraphicsPixmapItem * pitem=nullptr){
        auto poly=QPolygonF(rect);
        auto rbody=genDynamicBody(poly,velcocity);

        if(pitem){
            pitem->setPos(rect.x(),rect.y());
            pitem->setParentItem(rbody->GetGitem().get());
        }
        return rbody;

    }

    //動的図形の生成
    std::shared_ptr<BoxShape> genDynamicBody(QPolygonF &poly,b2Vec2 velcocity=b2Vec2(0,0))
    {
        auto boxShape=std::shared_ptr<BoxShape>(new BoxShape());
        //初期化
        boxShape->RaCov=rac;
        boxShape->scene=(scene);
        boxShape->world=(world.get());
        boxShape->body=(nullptr);

        //表示データの生成
        auto tgitem=boxShape->GenGitem(boxShape->scene,poly);
        //tgitem->setBrush(QBrush(Qt::gray,Qt::BrushStyle::SolidPattern));
        tgitem->setPen(QPen(QColor(0,0,0,0)));
        tgitem->setBrush(QBrush(Qt::transparent,Qt::BrushStyle::SolidPattern));

        //box2dのデータを作成
        boxShape->DefBody(b2_dynamicBody,velcocity);
        //図形の形状設定
        b2PolygonShape dynamicBox=boxShape->GenShape(poly);
        //図形の装備設定
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.1f;
        fixtureDef.restitution =0.7;
        boxShape->body->CreateFixture(&fixtureDef);

        return boxShape;

    }

    //動的円の生成
    std::shared_ptr<BoxShape> genDynamicCircleBody(QRectF &rect,b2Vec2 velcocity=b2Vec2(0,0),QGraphicsPixmapItem * pitem=nullptr)
    {

        auto boxShape=std::shared_ptr<BoxShape>(new BoxShape());
        //初期化
        boxShape->RaCov=rac;
        boxShape->scene=(scene);
        boxShape->world=(world.get());
        boxShape->body=(nullptr);
        //表示データの生成
        auto pixitem=std::make_shared<QGraphicsEllipseItem>(rect,nullptr);
        boxShape->gitem=pixitem;
        //アイテムデータの設定
        boxShape->scene->addItem(boxShape->gitem.get());
        //
        pixitem->setBrush(QBrush(Qt::gray,Qt::BrushStyle::SolidPattern));
        pixitem->setPen(QPen(QColor(0,0,0,1)));


        if(pitem){
            pitem->setPos(rect.x(),rect.y());
            pitem->setParentItem(boxShape->GetGitem().get());
            pixitem->setPen(QPen(QColor(0,0,0,0)));
            pixitem->setBrush(QBrush(Qt::transparent,Qt::BrushStyle::SolidPattern));
        }

        //box2dのデータを作成
        boxShape->DefBody(b2_dynamicBody,velcocity);
        //図形の形状設定
        b2CircleShape dynamicCircle;
        auto itempos=rect.center();
        dynamicCircle.m_p.Set(boxShape->RaCov.divForce(itempos.x()),boxShape->RaCov.divForce(itempos.y()));
        dynamicCircle.m_radius=boxShape->RaCov.divForce(rect.width()/2);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicCircle;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.1f;
        fixtureDef.restitution =0.3;
        boxShape->body->CreateFixture(&fixtureDef);



        return boxShape;
    }
private:
    explicit BoxShapeFactoty(QGraphicsScene *setscene, std::shared_ptr<b2World> setworld,RangeConvert setrac);
    QGraphicsScene *scene=nullptr;
    std::shared_ptr<b2World> world;
    std::shared_ptr<BoxShapeSetting> bss;
    RangeConvert rac;
};

#endif // BOXSHAPEFACTOTY_H
