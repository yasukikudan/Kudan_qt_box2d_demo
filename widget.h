#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QThread>
#include <box2dscene.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void SetBox2DScene(QSharedPointer<Box2dScene> scene);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    QThread th;
    QSharedPointer<Box2dScene> b2s;
    int mode=0;
};

#endif // WIDGET_H
