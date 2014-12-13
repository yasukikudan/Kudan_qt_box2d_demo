#ifndef BOXSHAPESETTING_H
#define BOXSHAPESETTING_H
#include <QPixmap>
#include <QHash>
#include <memory>

class BoxShapeSetting
{
public:
    static std::shared_ptr<BoxShapeSetting> create();
    QPixmap load(QString path);
private:
    BoxShapeSetting();
    QHash<QString,QPixmap> pixhash;
    static std::shared_ptr<BoxShapeSetting> this_ptr;
};

#endif // BOXSHAPESETTING_H
