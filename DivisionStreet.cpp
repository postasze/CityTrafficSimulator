//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#include "DivisionStreet.h"

DivisionStreet::DivisionStreet(const QPointF& scenePosition, const Direction& direction, const QPixmap& pixmap) :
    StreetElement(scenePosition, direction, pixmap)
{

}

DivisionStreet::DivisionStreet(const DivisionStreet& divisionStreet) :
    StreetElement(divisionStreet.pos(), divisionStreet.getDirection(), divisionStreet.pixmap())
{

}

StreetElement* DivisionStreet::clone()
{
    return new DivisionStreet(*this);
}
