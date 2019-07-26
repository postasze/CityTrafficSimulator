//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#include "TrafficLight.h"

TrafficLight::TrafficLight(const QPointF& scenePosition, const Direction& direction, const QPixmap& pixmap) :
    StreetElement(scenePosition, direction, pixmap)
{

}

TrafficLight::TrafficLight(const TrafficLight& trafficLight) :
    StreetElement(trafficLight.pos(), trafficLight.getDirection(), trafficLight.pixmap())
{

}

StreetElement* TrafficLight::clone()
{
    return new TrafficLight(*this);
}
