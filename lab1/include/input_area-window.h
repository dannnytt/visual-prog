#ifndef INPUT_AREA_WINDOW_H
#define INPUT_AREA_WINDOW_H

#include <QWidget>
#include <QDialog>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "shape.h"

class AreaInputWindow : public QDialog {

    Q_OBJECT
public:

    AreaInputWindow(Circle *circle, QWidget * parent = nullptr);
    AreaInputWindow(Parallelogram *parallelogram, QWidget * parent = nullptr);
    AreaInputWindow(Rectangle *rectangle, QWidget * parent = nullptr);
    AreaInputWindow(Rhombus *rhombus, QWidget * parent = nullptr);
    AreaInputWindow(Sector *sector, QWidget * parent = nullptr);
    AreaInputWindow(Square *square, QWidget * parent = nullptr);
    AreaInputWindow(Trapezoid *trapezoid, QWidget * parent = nullptr);
    AreaInputWindow(Triangle *triangle, QWidget * parent = nullptr);



private:
    QGridLayout *mainLayout;
    QVBoxLayout *leftLayout;
    QGridLayout *rightLayout;
    QHBoxLayout *h_layout;
    QLabel *imageLabel;
    QLabel *resultLabel;


private:
    void setupCircle();
    void setupParallelogram();
    void setupRectangle();
    void setupRhombus();
    void setupSector();
    void setupSquare();
    void setupTrapezoid();
    void setupTriangle();

    void setupShape(Shape* shape);

};


#endif // INPUT_AREA_WINDOW_H
