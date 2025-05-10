#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    fileMenu = menuBar()->addMenu("Меню");

    aboutAuthorAction  = new QAction("Автор", this);
    fileMenu->addAction(aboutAuthorAction);
    connect(aboutAuthorAction, &QAction::triggered, this, &MainWindow::openAboutAuthorWindow);

    clearFormAction = new QAction("Очистить", this);
    fileMenu->addAction(clearFormAction);

    quitAction = new QAction("Выход", this);
    fileMenu->addAction(quitAction);
    connect(quitAction, &QAction::triggered, this, &QMainWindow::close);


    centralWidget = new QWidget(this);
    layout = new QGridLayout(centralWidget);

    addImageToGrid(circleLabel, layout, ":/images/circle.png", 0, 0);
    connect(circleLabel, &ClickedLabel::clicked, this, [this] {
        // circle = new Circle;
        openAreaInputWindow(new Circle);
    });

    addImageToGrid(parallelogramLabel, layout, ":/images/parallelogram.png", 0, 1);
    connect(parallelogramLabel, &ClickedLabel::clicked, this, [this] {
        openAreaInputWindow(new Parallelogram);
    });

    addImageToGrid(rectangleLabel, layout, ":/images/rectangle.png", 0, 2);
    connect(rectangleLabel, &ClickedLabel::clicked, this, [this] {
        openAreaInputWindow(new Rectangle);
    });

    addImageToGrid(rhombusLabel, layout, ":/images/rhombus.png", 0, 3);
    connect(rhombusLabel, &ClickedLabel::clicked, this, [this] {
        openAreaInputWindow(new Rhombus);
    });

    addImageToGrid(sectorLabel, layout, ":/images/sector.png", 1, 0);
    connect(sectorLabel, &ClickedLabel::clicked, this, [this] {
        openAreaInputWindow(new Sector);
    });

    addImageToGrid(squareLabel, layout, ":/images/square.png", 1, 1);
    connect(squareLabel, &ClickedLabel::clicked, this, [this] {
        openAreaInputWindow(new Square);
    });

    addImageToGrid(trapezoidLabel, layout, ":/images/trapezoid.png", 1, 2);
    connect(trapezoidLabel, &ClickedLabel::clicked, this, [this] {
        openAreaInputWindow(new Trapezoid);
    });

    addImageToGrid(triangleLabel, layout, ":/images/triangle.png", 1, 3);
    connect(triangleLabel, &ClickedLabel::clicked, this, [this] {
        openAreaInputWindow(new Triangle);
    });


    setCentralWidget(centralWidget);
}

void MainWindow::openAboutAuthorWindow() {
    authorWindow = new AboutAuthorWindow(this);
    authorWindow->exec();
}


void MainWindow::openAreaInputWindow(Circle *shape_f) {
    areaInput = new AreaInputWindow(shape_f, this);
    areaInput->exec();
}
void MainWindow::openAreaInputWindow(Parallelogram *shape_f) {
    areaInput = new AreaInputWindow(shape_f, this);
    areaInput->exec();
}

void MainWindow::openAreaInputWindow(Rectangle *shape_f) {
    areaInput = new AreaInputWindow(shape_f, this);
    areaInput->exec();
}

void MainWindow::openAreaInputWindow(Rhombus *shape_f) {
    areaInput = new AreaInputWindow(shape_f, this);
    areaInput->exec();
}

void MainWindow::openAreaInputWindow(Sector *shape_f) {
    areaInput = new AreaInputWindow(shape_f, this);
    areaInput->exec();
}

void MainWindow::openAreaInputWindow(Square *shape_f) {
    areaInput = new AreaInputWindow(shape_f, this);
    areaInput->exec();
}

void MainWindow::openAreaInputWindow(Trapezoid *shape_f) {
    areaInput = new AreaInputWindow(shape_f, this);
    areaInput->exec();
}

void MainWindow::openAreaInputWindow(Triangle *shape_f) {
    areaInput = new AreaInputWindow(shape_f, this);
    areaInput->exec();
}

void MainWindow::addImageToGrid(ClickedLabel *&label, QGridLayout *layout, const QString &imagePath, int row, int col) {
    label = new ClickedLabel(this);
    QPixmap pixmap(imagePath);
    label->setPixmap(pixmap.scaled(128, 128, Qt::KeepAspectRatio));
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label, row, col);
}

MainWindow::~MainWindow() {}
