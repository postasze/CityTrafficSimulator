//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#include "TurnStreet.h"

TurnStreet::TurnStreet(const QPointF& scenePosition, const Direction& direction, const QPixmap& pixmap) :
    StreetElement(scenePosition, direction, pixmap)
{

}

TurnStreet::TurnStreet(const TurnStreet& turnStreet) :
    StreetElement(turnStreet.pos(), turnStreet.getDirection(), turnStreet.pixmap())
{

}

StreetElement* TurnStreet::clone()
{
    return new TurnStreet(*this);
}
