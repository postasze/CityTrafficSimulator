//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#ifndef CAMERA_H
#define CAMERA_H

#include "StreetElement.h"
#include <QDateTime>

class Pedestrian;
class Car;
class RoadUser;

const double VIEW_DISTANCE = 40;

class Camera : public StreetElement
{
public:
    Camera(const QPointF& scenePosition = QPointF(0, 0), const Direction& direction = Direction::UP,
           const QPixmap& pixmap = QPixmap(), double angle_ = 0);
    Camera(const Camera& camera);
    //~Camera();
    int getID() const;
    std::string getData();
    double getAngle() const;
    void observe(std::vector<Pedestrian*> pedestrians, std::vector<Car*> cars, QTime& observaionTime);
    void setObservationField();
    QString observeToTextField(std::vector<Pedestrian *> pedestrians, std::vector<Car *> cars, QTime& observaionTime);

    StreetElement* clone();

public slots:

private:
    virtual void advance(int phase);
    bool isRoadUserInRange(RoadUser* roadUser);

    static unsigned int currentCamerasId;
    QDateTime time;
    int id;
    double angle;
    QPointF leftCorner;   //Corner more on "left" according to camera direction
    QPointF rightCorner;    //Corner more on "right" according to camera direction
    double aLeft;   //Directional factor for straight line containing leftCorner and scenePosition
    double bLeft;   //Constant for straight line containing leftCorner and scenePosition
    double aRight;  //Directional factor for straight line containing rightCorner and scenePosition
    double bRight;  //Constant for straight line containing rightCorner and scenePosition
};

#endif // CAMERA_H
