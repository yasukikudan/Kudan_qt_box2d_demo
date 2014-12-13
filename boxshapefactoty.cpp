#include "boxshapefactoty.h"

BoxShapeFactoty::BoxShapeFactoty(QGraphicsScene *setscene, std::shared_ptr<b2World> setworld, RangeConvert setrac)
{
    scene=setscene;
    world=setworld;
    rac=setrac;
    bss=BoxShapeSetting::create();

}
