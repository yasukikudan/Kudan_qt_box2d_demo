#include "boxshapesetting.h"

std::shared_ptr<BoxShapeSetting> BoxShapeSetting::this_ptr;

BoxShapeSetting::BoxShapeSetting()
{
}

std::shared_ptr<BoxShapeSetting>  BoxShapeSetting::create()
{
    if(!this_ptr){
        this_ptr=std::shared_ptr<BoxShapeSetting>(new BoxShapeSetting());
    }
    return this_ptr;
}

QPixmap BoxShapeSetting::load(QString path)
{
    if(pixhash.contains(path)){
       auto pix= QPixmap(path);
       pixhash[path]=pix;
       return pix;
    }
    return pixhash[path];
}
