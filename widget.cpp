#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include "box2dscene.h"
#include <QDesktopWidget>
#include <QScreen>
#include <QPointF>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    SetBox2DScene(QSharedPointer<Box2dScene>(new Box2dScene(this,mode)));

    auto rectwindow= QApplication::screens().at(0);
    const double sf=(rectwindow->size().width()-4)/600.0;
    ui->graphicsView->scale(sf,sf);
    auto fixdw=rectwindow->size().width();
    auto fixdh=fixdw+(fixdw/3);
    ui->graphicsView->setMaximumSize(fixdw,fixdh);
    ui->graphicsView->setMinimumSize(fixdw,fixdh);
    //ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::SetBox2DScene(QSharedPointer<Box2dScene> scene){

    if(!scene){
        return;
    }
    b2s=scene;
    ui->graphicsView->setScene(b2s.data());

    connect(b2s.data(),&Box2dScene::GameEnd,[=]{
        on_pushButton_clicked();
    });

}

void Widget::on_pushButton_clicked()
{
    mode=0;
    SetBox2DScene(QSharedPointer<Box2dScene>(new Box2dScene(this,0)));
}

void Widget::on_pushButton_2_clicked()
{
    mode=1;
    SetBox2DScene(QSharedPointer<Box2dScene>(new Box2dScene(this,1)));
}
