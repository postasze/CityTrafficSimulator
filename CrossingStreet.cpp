//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#include "CrossingStreet.h"

CrossingStreet::CrossingStreet(const QPointF& scenePosition, const Direction& direction, const QPixmap& pixmap) :
    StreetElement(scenePosition, direction, pixmap)
{

}

CrossingStreet::CrossingStreet(const CrossingStreet& crossingStreet) :
    StreetElement(crossingStreet.pos(), crossingStreet.getDirection(), crossingStreet.pixmap())
{

}

StreetElement* CrossingStreet::clone()
{
    return new CrossingStreet(*this);
}
