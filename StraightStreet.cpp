//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#include "StraightStreet.h"

StraightStreet::StraightStreet(const QPointF& scenePosition, const Direction& direction, const QPixmap& pixmap) :
    StreetElement(scenePosition, direction, pixmap)
{

}

StraightStreet::StraightStreet(const StraightStreet& straightStreet) :
    StreetElement(straightStreet.pos(), straightStreet.getDirection(), straightStreet.pixmap())
{

}

StreetElement* StraightStreet::clone()
{
    return new StraightStreet(*this);
}
