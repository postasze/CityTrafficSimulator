//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QPointF>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "Constants.h"
#include "StreetElement.h"
#include "RoadUser.h"
#include "TrafficLight.h"
#include "Camera.h"
#include "Car.h"
#include "Pedestrian.h"
#include "MainWindow.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(QObject *parent = nullptr);
    ~Controller();

    void run();
    void addRoadUser(RoadUser *roadUser);
    //void addCamera(Camera *camera);
    void removeRoadUser(RoadUser *roadUser);
    //void removeCamera(Camera *camera);
    void deleteAllCityObjects();
    void clearArrays();
    void add_1x1_element(StreetElement *streetElement, const QPixmap& pixmap, const QPoint& eventPosition);
    void add_1x2_element(StreetElement *streetElement, const QPixmap& pixmap, const QPoint& eventPosition);
    void add_2x2_element(StreetElement *streetElement, const QPixmap& pixmap, const QPoint& eventPosition);
    void addNewPoint(const PointType& pointType, const QPoint& eventPosition);
    void drawGrid();

    QGraphicsScene *scene;
    StreetElement* streetArray[NUMBER_OF_HORIZONTAL_FIELDS][NUMBER_OF_VERTICAL_FIELDS]; // this array represents 2D board, it contains street elements that are located on specific fields
    TrafficLight* trafficLightsArray[NUMBER_OF_HORIZONTAL_FIELDS][NUMBER_OF_VERTICAL_FIELDS]; // this array represents deployment of traffic lights on the 2D board
    Camera* camerasArray[NUMBER_OF_HORIZONTAL_FIELDS][NUMBER_OF_VERTICAL_FIELDS]; // this array represents deployment of cameras on the 2D board
    QGraphicsEllipseItem* pointsArray[NUMBER_OF_HORIZONTAL_FIELDS][NUMBER_OF_VERTICAL_FIELDS]; // this array represents deployment of points on the 2D board
    std::vector<StreetElement*> streetElements;
    std::vector<TrafficLight*> trafficLights;
    std::vector<Camera*> cameras;
    std::vector<Car*> cars;
    std::vector<Pedestrian*> pedestrians;
    std::vector<QGraphicsEllipseItem*> points;

public slots:
    void startSimulation();
    void stopSimulation();
    void addNewRoadUser();
    void choseNextDirectionForRoadUsers();
    void createDefaultCity();
    void changeSimulationSpeed(int index);
    void clearBoard();
    void camerasObserve();
    void setMaxNumberOfCars();
    void setMaxNumberOfPedestrians();
    void addOneSecondToClock();
    void cameraObservationForTextField();
    void selectStreetElement(StreetElement* streetElement);
    void currentPointTypeChanged(PointType pointType);
    void streetElementDroppedOnScene(QPixmap pixmap, QPoint eventPosition);
    void leftMouseButtonPressedOnScene(QPoint eventPosition);
    void rightMouseButtonPressedOnScene(QPoint eventPosition);

signals:

private:
    void loadImages();
    void addNewPedestrian();
    void addNewCar();
    void choseNextDirectionForPedestrians();
    void choseNextDirectionForCars();
    void setCurrentTimeForClock();
    void setCameraToDisplay(Camera *camera);

    QTime clock;
    MainWindow mainWindow;
    unsigned int maxNumberOfPedestrians;
    unsigned int maxNumberOfCars;
    Camera *cameraForTextField;

    QTimer animationTimer;
    QTimer realTimer;
    bool simulationPaused;
    float simulationSpeed;

    QGraphicsLineItem* horizontalLinesArray[NUMBER_OF_HORIZONTAL_FIELDS-1]; // array of horizontal lines on the board
    QGraphicsLineItem* verticalLinesArray[NUMBER_OF_VERTICAL_FIELDS-1]; // array of vertical lines on the board

    QPixmap pedestrian1Pixmap;
    QPixmap pedestrian2Pixmap;
    QPixmap pedestrian3Pixmap;
    QPixmap smallCar1Pixmap;
    QPixmap smallCar2Pixmap;
    QPixmap smallCar3Pixmap;
    QPixmap smallCar4Pixmap;
    QPixmap smallCar5Pixmap;
    QPixmap smallCar6Pixmap;
    QPixmap bigCar1Pixmap;
    QPixmap bigCar2Pixmap;
    QPixmap bigCar3Pixmap;
    QPixmap bigCar4Pixmap;

    QPixmap cameraPixmap;
    QPixmap greenLightPixmap;
    QPixmap orangeLightPixmap;
    QPixmap redLightPixmap;
    QPixmap CrossingPixmap;
    QPixmap DivisionStreetPixmap;
    QPixmap StraightStreetPixmap;
    QPixmap TurnStreetPixmap;
    QPixmap PedestrianCrossingPixmap;
    QPixmap PavementPixmap;

    StreetElement *selectedStreetElement;
    PointType currentPointType;
};

#endif // CONTROLLER_H
