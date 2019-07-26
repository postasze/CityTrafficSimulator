//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#include "Pavement.h"

Pavement::Pavement(const QPointF& scenePosition, const Direction& direction, const QPixmap& pixmap) :
    StreetElement(scenePosition, direction, pixmap)
{

}

Pavement::Pavement(const Pavement& pavement) :
    StreetElement(pavement.pos(), pavement.getDirection(), pavement.pixmap())
{

}

StreetElement* Pavement::clone()
{
    return new Pavement(*this);
}
