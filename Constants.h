//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#ifndef CONSTANS_H
#define CONSTANS_H

#include <QColor>

const int NUMBER_OF_HORIZONTAL_FIELDS = 32; // quantity of fields in horizontal axis
const int NUMBER_OF_VERTICAL_FIELDS = 32; // quantity of fields in vertical axis
const int FIELD_WIDTH = 16; // width of the single field on the 2D board (should be even number, otherwise ther will be errors in runtime)
const int FIELD_HEIGHT = 16; // height of the single field on the 2D board (should be even number, otherwise ther will be errors in runtime)
const int LINE_THICKNESS = 1; // thickness of the lines between the fields
const int NUMBER_OF_CITY_ELEMENTS = 15; // quantity of city elements
const int MAXIMAL_NUMBER_OF_CARS = 10; // maximal quantity of cars in the simulation
const int MAXIMAL_NUMBER_OF_PEDESTRIANS = 30; // maximal quantity of pedestrians in the simulation
const float SCALE_OF_BASIC_ELEMENT = 0.35; // scale for the city elements that have 2x2 size on the 2D board
const float SCALE_OF_TRAFFIC_LIGHT = 0.25; // scale for the traffic lights
const float SCALE_OF_CAMERA = 0.025; // scale for the cameras
const float SCALE_OF_PEDESTRIAN = 0.4; // scale for the pedestrian images
const QColor LINE_COLOR(100, 50, 0, 255);
const QColor FIELD_COLOR(50, 200, 50, 255);
const int SIZE_AUTOMOBILE = 12;
const int SIZE_TRUCK = 16;
const int SIZE_PEDESTRIAN = 8;
const qreal SPEED_AUTOMOBILE = 2.0f;
const qreal SPEED_TRUCK = 1.0f;
const qreal SPEED_PEDESTRIAN = 0.5f;
const int ANIMATION_TIMER_INTERVAL = 40; // przedzial czasowy w milisekundach, po ktorym qtimer cyklicznie wysyla sygnal timeout dla animacji
const int REAL_TIMER_INTERVAL = 1000; // przedzial czasowy = 1 sekunda, symulujacy uplyw rzeczywistego czasu, sterujacy czestotliwoscia probkowania obserwacji z kamer
const double PI = 3.14159265;
const int CAMERA_ANGLE = 45;

enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT,
    NONE,
};

enum class CarType
{
    AUTOMOBILE,
    TRUCK
};

enum class PointType
{
    VEHICLE_START_POINT,
    VEHICLE_END_POINT,
    PEDESTRIAN_START_POINT,
    PEDESTRIAN_END_POINT,
    NONE
};

#endif // CONSTANS_H
