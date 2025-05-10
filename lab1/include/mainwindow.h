#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QPixmap>
#include <QLabel>


#include "authorwindow.h"
#include "input_area-window.h"
#include "clicked-label.h"
#include "shape.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QMenu *fileMenu;

    QAction *aboutAuthorAction;
    QAction *clearFormAction;
    QAction *quitAction;

    QGridLayout *layout;
    QWidget *centralWidget;

    ClickedLabel *circleLabel;
    ClickedLabel *parallelogramLabel;
    ClickedLabel *rectangleLabel;
    ClickedLabel *rhombusLabel;
    ClickedLabel *sectorLabel;
    ClickedLabel *squareLabel;
    ClickedLabel *trapezoidLabel;
    ClickedLabel *triangleLabel;

    AboutAuthorWindow *authorWindow;
    AreaInputWindow *areaInput;

private:
    void addImageToGrid(ClickedLabel *&label, QGridLayout *layout, const QString &imagePath, int row, int col);

private slots:
    void openAboutAuthorWindow();

    void openAreaInputWindow(Circle *shape_f);
    void openAreaInputWindow(Parallelogram *shape_f);
    void openAreaInputWindow(Rectangle *shape_f);
    void openAreaInputWindow(Rhombus *shape_f);
    void openAreaInputWindow(Sector *shape_f);
    void openAreaInputWindow(Square *shape_f);
    void openAreaInputWindow(Trapezoid *shape_f);
    void openAreaInputWindow(Triangle *shape_f);
};
#endif // MAINWINDOW_H
