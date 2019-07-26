//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#include "PedestrianCrossing.h"

PedestrianCrossing::PedestrianCrossing(const QPointF& scenePosition, const Direction& direction, const QPixmap& pixmap) :
    StreetElement(scenePosition, direction, pixmap)
{

}

PedestrianCrossing::PedestrianCrossing(const PedestrianCrossing& pedestrianCrossing) :
    StreetElement(pedestrianCrossing.pos(), pedestrianCrossing.getDirection(), pedestrianCrossing.pixmap())
{

}

StreetElement* PedestrianCrossing::clone()
{
    return new PedestrianCrossing(*this);
}
