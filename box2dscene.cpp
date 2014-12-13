#include "box2dscene.h"
#include "labyrinthfactory.h"
#include <cmath>


constexpr double minx=-300,miny=-400;
constexpr double w=(std::abs(minx)*2),h=(std::abs(miny)*2);


//表示モード設定

QPointF RangeAdaptor(const int bx,const int by,const int boxsize){
    const int vx=minx+(bx*boxsize)+(boxsize/4);
    const int vy=miny+(by*boxsize)+(boxsize/4);
    return QPointF(vx,vy);
}

int RangeMaxX(const int boxsize){
    return w/boxsize;
}
int RangeMaxY(const int boxsize){
    return h/boxsize;
}

Box2dScene::Box2dScene(QObject *parent, const int mode):
    QGraphicsScene(parent),Accelerometer(new QAccelerometer(this))
{

    //senser
    Accelerometer->setAccelerationMode(QAccelerometer::Gravity);
    Accelerometer->setActive(true);

    //gen scene
    setSceneRect(minx,miny,w,h);

    RaCov=RangeConvert(32);
    connect(&update_timer,SIGNAL(timeout()),this,SLOT(update()));
    update_timer.start(30);


    //set world
    b2Vec2 grabity(0.0f, 0.0f);
    world=std::make_shared<b2World>(grabity);

    //set boxfactoty
    bsf=BoxShapeFactoty::create(this,world,RaCov);


    //マップ端のオブジェクト
    QPolygonF  poly2(QRectF(minx-10,miny,10,h));
    Edge.append(bsf->genStaticBody(poly2));

    QPolygonF  poly3(QRectF(-minx,miny,10,h));
    Edge.append(bsf->genStaticBody(poly3));

    QPolygonF  poly4(QRectF(minx,miny-10,w,10));
    Edge.append(bsf->genStaticBody(poly4));

    QPolygonF  poly5(QRectF(minx,-miny,w,10));
    Edge.append(bsf->genStaticBody(poly5));


    QPixmap qpix(":image/lgpl_icons/kde.png");
    QPixmap qpix2(":image/lgpl_icons/applications-internet.png");

    std::random_device seed_gen;
    std::mt19937 randgen(seed_gen());

    const int cellsize=100;
    LabyrinthData ldata=LabyrinthFactory::create(w/cellsize,h/cellsize);
    for(int i=0;i<ldata.isY();i++){
        for(int j=0;j<ldata.isX();j++){
            const int index=j+(i*ldata.isX());
            const LabyrinthCell cell=ldata.cells2d[index];
            qDebug() << index << cell.cellnum <<cell.top <<cell.bottom << cell.left << cell.right;
            if(mode==0){
                if(cell.bottom==true)
                {
                    const int wch=cellsize/5;
                    const int wcx=j*cellsize;
                    const int wcy=(i+1)*cellsize-wch;
                    const int wcw=cellsize+wch;
                    QPolygonF  polycell(QRectF(minx+wcx,miny+wcy,wcw,wch));
                    auto p=bsf->genStaticBody(polycell);
                    objShapeList.append(p);
                }
                if(cell.right==true)
                {
                    const int wcw=cellsize/5;
                    const int wcx=(j+1)*cellsize;
                    const int wcy=(i)*cellsize;
                    const int wch=cellsize;
                    QPolygonF  polycell(QRectF(minx+wcx,miny+wcy,wcw,wch));
                    auto p=bsf->genStaticBody(polycell);
                    objShapeList.append(p);
                }
            }
            if(mode==1){
                const int wcw=cellsize/2;
                const int wcx=(j+1)*cellsize;
                const int wcy=(i)*cellsize;
                const int wch=cellsize/2;
                QRectF base(minx+wcx,miny+wcy,wcw,wch);
                std::uniform_int_distribution<int> d(0,1);
                if(d(randgen)){
                    auto p=bsf->genDynamicRectBody(base,b2Vec2(0,0),new QGraphicsPixmapItem(qpix.scaled(wcw,wch),nullptr));
                    objShapeList.append(p);
                }else{
                    auto p1=bsf->genDynamicCircleBody(base,b2Vec2(0,0),new QGraphicsPixmapItem(qpix2.scaled(wcw,wch),nullptr));
                    objShapeList.append(p1);
                }
            }

        }
    }
    qDebug() << objShapeList.size();


    if(mode==0){
        std::uniform_int_distribution<int> d(0,RangeMaxX(cellsize)-1);

        QRectF poly(RangeAdaptor(d(randgen),0,cellsize),QSizeF(cellsize/2,cellsize/2));
        auto b=bsf->genDynamicCircleBody(poly);
        b->GetBody()->SetBullet(true);
        b->GetBody()->SetSleepingAllowed(false);
        pcobj=b;


        QRectF polye(RangeAdaptor(d(randgen),RangeMaxY(cellsize)-1,cellsize),QSizeF(cellsize/2,cellsize/2));
        exit=std::shared_ptr<QGraphicsEllipseItem>(new QGraphicsEllipseItem(polye,nullptr));
        exit->setBrush(QBrush(Qt::red,Qt::BrushStyle::SolidPattern));
        exit->setPen(QPen(QColor(0,0,0,0)));
        exit->setOpacity(0.5);
        addItem(exit.get());
    }
}

Box2dScene::~Box2dScene()
{
}

void Box2dScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    auto pos=event->scenePos();
    oldpos=std::make_shared<QPointF>(pos);
}

void Box2dScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    auto pos=event->scenePos();
    oldpos=std::make_shared<QPointF>(pos);
}


void Box2dScene::update()
{
    if(exit){
        auto rect=exit->rect();
        auto itemlist=items(rect,Qt::IntersectsItemShape);
        for(const int i:SmartCountor(itemlist.count())){
            if(itemlist[i]==pcobj->GetGitem().get()){
                update_timer.stop();
                GameEnd();
                return;
            }
        }
    }
    const float32 timeStep =1.0f/60.0f;
    const int32 velocityIterations = 6;
    const int32 positionIterations = 2;
    //重力設定
    auto acceler=Accelerometer->reading();
    if(acceler!=nullptr){
        b2Vec2 aaaaa((-acceler->x()*3),(acceler->y()*3));
        world->SetGravity(aaaaa);
    }
    //物理演算
    world->Step(timeStep, velocityIterations, positionIterations);
    //表示のアップデート
    for(const int i:SmartCountor(ShapeList.count())){
        ShapeList[i]->update();
    }
    for(const int i:SmartCountor(Edge.count())){
        Edge[i]->update();
    }
    if(pcobj){
        pcobj->update();
    }
    for(const int i:SmartCountor(objShapeList.count())){
        objShapeList[i]->update();
    }
}
