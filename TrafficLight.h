//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "StreetElement.h"

class TrafficLight : public StreetElement
{
public:
    TrafficLight(const QPointF& scenePosition = QPointF(0, 0), const Direction& direction = Direction::UP,
                 const QPixmap& pixmap = QPixmap());
    TrafficLight(const TrafficLight& trafficLight);

    StreetElement* clone();
};

#endif // TRAFFICLIGHT_H
