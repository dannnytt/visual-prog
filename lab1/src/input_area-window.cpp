#include <QLineEdit>
#include <QPixmap>
#include <QPushButton>
#include <QDoubleValidator>
#include <cmath>

#include "input_area-window.h"

void AreaInputWindow::setupShape(Shape* shape) {

    if (dynamic_cast<Circle*>(shape)) {
        setupCircle();
    } else if (dynamic_cast<Parallelogram*>(shape)) {
        setupParallelogram();
    } else if (dynamic_cast<Rectangle*>(shape)) {
        setupRectangle();
    } else if (dynamic_cast<Rhombus*>(shape)) {
        setupRhombus();
    } else if (dynamic_cast<Sector*>(shape)) {
        setupSector();
    } else if (dynamic_cast<Square*>(shape)) {
        setupSquare();
    } else if (dynamic_cast<Trapezoid*>(shape)) {
        setupTrapezoid();
    } else if (dynamic_cast<Triangle*>(shape)) {
        setupTriangle();
    }
}

AreaInputWindow::AreaInputWindow(Circle *circle, QWidget * parent) : QDialog(parent) {
    setupShape(circle);
}

AreaInputWindow::AreaInputWindow(Parallelogram *parallelogram, QWidget * parent) : QDialog(parent) {
    setupShape(parallelogram);
}

AreaInputWindow::AreaInputWindow(Rectangle *rectangle, QWidget * parent) : QDialog(parent) {
    setupShape(rectangle);
}

AreaInputWindow::AreaInputWindow(Rhombus *rhombus, QWidget * parent) : QDialog(parent) {
    setupShape(rhombus);
}

AreaInputWindow::AreaInputWindow(Sector *sector, QWidget * parent) : QDialog(parent) {
    setupShape(sector);
}

AreaInputWindow::AreaInputWindow(Square *square, QWidget * parent) : QDialog(parent) {
    setupShape(square);
}

AreaInputWindow::AreaInputWindow(Trapezoid *trapezoid, QWidget * parent) : QDialog(parent) {
    setupShape(trapezoid);
}

AreaInputWindow::AreaInputWindow(Triangle *triangle, QWidget * parent) : QDialog(parent) {
    setupShape(triangle);
}



void AreaInputWindow::setupCircle() {
    setFixedSize(700, 300);

    QGridLayout *mainLayout = new QGridLayout;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    QGridLayout *rightLayout = new QGridLayout;
    QHBoxLayout *h_layout = new QHBoxLayout;

    setLayout(mainLayout);

    mainLayout->addLayout(leftLayout, 0, 0);
    mainLayout->addLayout(rightLayout, 0, 1);
    rightLayout->addLayout(h_layout, 0, 0);

    QPixmap pixmap(":/images/circle-area.png");
    QLabel *imageLabel = new QLabel(this);


    QLabel *raduisLabel = new QLabel("<h1> r = </h1>", this);
    QLineEdit *radiusInput = new QLineEdit(this);

    QDoubleValidator *validator = new QDoubleValidator(0.0, 1000.0, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    radiusInput->setValidator(validator);

    QLocale locale(QLocale::English, QLocale::UnitedStates);
    validator->setLocale(locale);

    h_layout->addWidget(raduisLabel);
    h_layout->addWidget(radiusInput);
    rightLayout->setAlignment(Qt::AlignTop);

    QLabel *resultLabel = new QLabel(this);
    rightLayout->addWidget(resultLabel, 1, 0, Qt::AlignTop);
    connect(radiusInput, &QLineEdit::textChanged, this, [=] {
        bool ok;
        double radius = radiusInput->text().toDouble(&ok);
        if (ok) {
            double area = 3.14 * radius * radius;
            resultLabel->setText(QString("<h2>Площадь: %1</h2>").arg(area));
        } else {
            resultLabel->setText("<h2>Ввод некорректен!</h2>");
        }
    });

    imageLabel->setPixmap(pixmap.scaled(256, 256, Qt::KeepAspectRatio));
    leftLayout->addWidget(imageLabel, 0, Qt::AlignTop);
}

void AreaInputWindow::setupParallelogram() {
    setFixedSize(700, 300);
    QGridLayout *mainLayout = new QGridLayout;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    QGridLayout *rightLayout = new QGridLayout;
    QHBoxLayout *h_layout = new QHBoxLayout;

    setLayout(mainLayout);

    mainLayout->addLayout(leftLayout, 0, 0);
    mainLayout->addLayout(rightLayout, 0, 1);
    rightLayout->addLayout(h_layout, 0, 0);
    QPixmap pixmap(":/images/parallelogram-area.png");
    QLabel *imageLabel = new QLabel(this);

    QLabel *sideLabel = new QLabel("<h1>a = </h1>", this);
    QLabel *heightLabel = new QLabel("<h1>h = </h1>", this);
    QLineEdit *sideInput = new QLineEdit(this);
    QLineEdit *heightInput = new QLineEdit(this);

    QDoubleValidator *validator = new QDoubleValidator(0.0, 1000.0, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    sideInput->setValidator(validator);
    heightInput->setValidator(validator);

    QLocale locale(QLocale::English, QLocale::UnitedStates);
    validator->setLocale(locale);

    h_layout->addWidget(sideLabel);
    h_layout->addWidget(sideInput);
    h_layout->addWidget(heightLabel);
    h_layout->addWidget(heightInput);

    QLabel *resultLabel = new QLabel(this);
    rightLayout->addWidget(resultLabel, 1, 0, Qt::AlignTop);

    auto calculateArea = [=]() {
        bool ok1, ok2;
        double side = sideInput->text().toDouble(&ok1);
        double height = heightInput->text().toDouble(&ok2);

        if (ok1 && ok2) {
            double area = side * height;
            resultLabel->setText(QString("<h2>Площадь: %1</h2>").arg(area));
        } else {
            resultLabel->setText("<h2>Ввод неккоректен!</h2>");
        }
    };

    connect(sideInput, &QLineEdit::textChanged, this, calculateArea);
    connect(heightInput, &QLineEdit::textChanged, this, calculateArea);

    imageLabel->setPixmap(pixmap.scaled(256, 256, Qt::KeepAspectRatio));
    leftLayout->addWidget(imageLabel, 0, Qt::AlignTop);
}

void AreaInputWindow::setupRectangle() {
    setFixedSize(700, 300);
    QGridLayout *mainLayout = new QGridLayout;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    QGridLayout *rightLayout = new QGridLayout;
    QHBoxLayout *h_layout = new QHBoxLayout;

    setLayout(mainLayout);

    mainLayout->addLayout(leftLayout, 0, 0);
    mainLayout->addLayout(rightLayout, 0, 1);
    rightLayout->addLayout(h_layout, 0, 0);
    QPixmap pixmap(":/images/rectangle-area.png");
    QLabel *imageLabel = new QLabel(this);

    QLabel *side1Label = new QLabel("<h1>a = </h1>", this);
    QLabel *side2Label = new QLabel("<h1>b = </h1>", this);
    QLineEdit *side1Input = new QLineEdit(this);
    QLineEdit *side2Input = new QLineEdit(this);

    QDoubleValidator *validator = new QDoubleValidator(0.0, 1000.0, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    side1Input->setValidator(validator);
    side2Input->setValidator(validator);

    QLocale locale(QLocale::English, QLocale::UnitedStates);
    validator->setLocale(locale);
    h_layout->addWidget(side1Label);
    h_layout->addWidget(side1Input);
    h_layout->addWidget(side2Label);
    h_layout->addWidget(side2Input);

    QLabel *resultLabel = new QLabel(this);
    rightLayout->addWidget(resultLabel, 1, 0, Qt::AlignTop);

    auto calculateArea = [=]() {
        bool ok1, ok2;
        double side1 = side1Input->text().toDouble(&ok1);
        double side2 = side2Input->text().toDouble(&ok2);

        if (ok1 && ok2) {
            double area = side1 * side2;
            resultLabel->setText(QString("<h2>Площадь: %1</h2>").arg(area));
        } else {
            resultLabel->setText("<h2>Ввод неккоректен!</h2>");
        }
    };

    connect(side1Input, &QLineEdit::textChanged, this, calculateArea);
    connect(side2Input, &QLineEdit::textChanged, this, calculateArea);

    imageLabel->setPixmap(pixmap.scaled(256, 256, Qt::KeepAspectRatio));
    leftLayout->addWidget(imageLabel, 0, Qt::AlignTop);
}

void AreaInputWindow::setupRhombus() {
    setFixedSize(700, 300);
    QGridLayout *mainLayout = new QGridLayout;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    QGridLayout *rightLayout = new QGridLayout;
    QHBoxLayout *h_layout = new QHBoxLayout;

    setLayout(mainLayout);

    mainLayout->addLayout(leftLayout, 0, 0);
    mainLayout->addLayout(rightLayout, 0, 1);
    rightLayout->addLayout(h_layout, 0, 0);
    QPixmap pixmap(":/images/rhombus-area.jpg");
    QLabel *imageLabel = new QLabel(this);

    QLabel *diagonal1Label = new QLabel("<h1>d1 = </h1>", this);
    QLabel *diagonal2Label = new QLabel("<h1>d2 = </h1>", this);
    QLineEdit *diagonal1Input = new QLineEdit(this);
    QLineEdit *diagonal2Input = new QLineEdit(this);

    QDoubleValidator *validator = new QDoubleValidator(0.0, 1000.0, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    diagonal1Input->setValidator(validator);
    diagonal2Input->setValidator(validator);

    QLocale locale(QLocale::English, QLocale::UnitedStates);
    validator->setLocale(locale);
    h_layout->addWidget(diagonal1Label);
    h_layout->addWidget(diagonal1Input);
    h_layout->addWidget(diagonal2Label);
    h_layout->addWidget(diagonal2Input);

    QLabel *resultLabel = new QLabel(this);
    rightLayout->addWidget(resultLabel, 1, 0, Qt::AlignTop);

    auto calculateArea = [=]() {
        bool ok1, ok2;
        double diagonal1 = diagonal1Input->text().toDouble(&ok1);
        double diagonal2 = diagonal2Input->text().toDouble(&ok2);

        if (ok1 && ok2) {
            double area = (diagonal1 * diagonal2) / 2;
            resultLabel->setText(QString("<h2>Площадь: %1</h2>").arg(area));
        } else {
            resultLabel->setText("<h2>Ввод неккоректен!</h2>");
        }
    };

    connect(diagonal1Input, &QLineEdit::textChanged, this, calculateArea);
    connect(diagonal2Input, &QLineEdit::textChanged, this, calculateArea);

    imageLabel->setPixmap(pixmap.scaled(256, 256, Qt::KeepAspectRatio));
    leftLayout->addWidget(imageLabel, 0, Qt::AlignTop);
}

void AreaInputWindow::setupSector() {
    setFixedSize(700, 300);
    QGridLayout *mainLayout = new QGridLayout;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    QGridLayout *rightLayout = new QGridLayout;
    QHBoxLayout *h_layout = new QHBoxLayout;

    setLayout(mainLayout);

    mainLayout->addLayout(leftLayout, 0, 0);
    mainLayout->addLayout(rightLayout, 0, 1);
    rightLayout->addLayout(h_layout, 0, 0);
    QPixmap pixmap(":/images/sector-area.jpg");
    QLabel *imageLabel = new QLabel(this);

    QLabel *radiusLabel = new QLabel("<h1>r = </h1>", this);
    QLabel *angleLabel = new QLabel("<h1>θ (degrees) = </h1>", this);

    QLineEdit *radiusInput = new QLineEdit(this);
    QLineEdit *angleInput = new QLineEdit(this);

    QDoubleValidator *validator = new QDoubleValidator(0.0, 1000.0, 2, this);
    radiusInput->setValidator(validator);
    angleInput->setValidator(validator);

    QLocale locale(QLocale::English, QLocale::UnitedStates);
    validator->setLocale(locale);

    h_layout->addWidget(radiusLabel);
    h_layout->addWidget(radiusInput);
    h_layout->addWidget(angleLabel);
    h_layout->addWidget(angleInput);

    QLabel *resultLabel = new QLabel(this);
    rightLayout->addWidget(resultLabel, 1, 0, Qt::AlignTop);

    auto calculateArea = [=]() {
        bool ok1, ok2;
        double radius = radiusInput->text().toDouble(&ok1);
        double angle = angleInput->text().toDouble(&ok2);

        if (ok1 && ok2 && angle >= 0 && angle <= 360) {
            double angleInRadians = (M_PI * angle) / 180.0;
            double area = 0.5 * radius * radius * angleInRadians;
            resultLabel->setText(QString("<h2>Площадь: %1</h2>").arg(area));
        } else {
            resultLabel->setText("<h2>Ввод некорректен!</h2>");
        }
    };

    connect(radiusInput, &QLineEdit::textChanged, this, calculateArea);
    connect(angleInput, &QLineEdit::textChanged, this, calculateArea);

    imageLabel->setPixmap(pixmap.scaled(256, 256, Qt::KeepAspectRatio));
    leftLayout->addWidget(imageLabel, 0, Qt::AlignTop);

}

void AreaInputWindow::setupSquare() {
    setFixedSize(700, 300);
    QGridLayout *mainLayout = new QGridLayout;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    QGridLayout *rightLayout = new QGridLayout;
    QHBoxLayout *h_layout = new QHBoxLayout;

    setLayout(mainLayout);

    mainLayout->addLayout(leftLayout, 0, 0);
    mainLayout->addLayout(rightLayout, 0, 1);
    rightLayout->addLayout(h_layout, 0, 0);
    QPixmap pixmap(":/images/square-area.png");
    QLabel *imageLabel = new QLabel(this);

    QLabel *sideLabel = new QLabel("<h1> a = </h1>", this);
    QLineEdit *sideInput = new QLineEdit(this);

    QDoubleValidator *validator = new QDoubleValidator(0.0, 1000.0, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    sideInput->setValidator(validator);

    QLocale locale(QLocale::English, QLocale::UnitedStates);
    validator->setLocale(locale);

    h_layout->addWidget(sideLabel);
    h_layout->addWidget(sideInput);

    QLabel *resultLabel = new QLabel(this);
    rightLayout->addWidget(resultLabel, 1, 0, Qt::AlignTop);
    connect(sideInput, &QLineEdit::textChanged, this, [=] {
        bool ok;
        double side = sideInput->text().toDouble(&ok);
        if (ok) {
            double area = side * side;
            resultLabel->setText(QString("<h2>Площадь: %1</h2>").arg(area));
        } else {
            resultLabel->setText("<h2>Ввод некорректен!</h2>");
        }
    });

    imageLabel->setPixmap(pixmap.scaled(256, 256, Qt::KeepAspectRatio));
    leftLayout->addWidget(imageLabel, 0, Qt::AlignTop);
}

void AreaInputWindow::setupTrapezoid(){
    setFixedSize(700, 300);
    QGridLayout *mainLayout = new QGridLayout;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    QGridLayout *rightLayout = new QGridLayout;
    QHBoxLayout *h_layout = new QHBoxLayout;

    setLayout(mainLayout);

    mainLayout->addLayout(leftLayout, 0, 0);
    mainLayout->addLayout(rightLayout, 0, 1);
    rightLayout->addLayout(h_layout, 0, 0);
    QPixmap pixmap(":/images/trapezoid-area.png");
    QLabel *imageLabel = new QLabel(this);

    QLabel *side1Label = new QLabel("<h1>a = </h1>", this);
    QLabel *side2Label = new QLabel("<h1>b = </h1>", this);
    QLabel *heightLabel = new QLabel("<h1>h = </h1>", this);

    QLineEdit *side1Input = new QLineEdit(this);
    QLineEdit *side2Input = new QLineEdit(this);
    QLineEdit *heightInput = new QLineEdit(this);

    QDoubleValidator *validator = new QDoubleValidator(0.0, 1000.0, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    side1Input->setValidator(validator);
    side2Input->setValidator(validator);
    heightInput->setValidator(validator);

    QLocale locale(QLocale::English, QLocale::UnitedStates);
    validator->setLocale(locale);
    h_layout->addWidget(side1Label);
    h_layout->addWidget(side1Input);
    h_layout->addWidget(side2Label);
    h_layout->addWidget(side2Input);
    h_layout->addWidget(heightLabel);
    h_layout->addWidget(heightInput);

    QLabel *resultLabel = new QLabel(this);
    rightLayout->addWidget(resultLabel, 1, 0, Qt::AlignTop);

    auto calculateArea = [=]() {
        bool ok1, ok2, ok3;
        double side1 = side1Input->text().toDouble(&ok1);
        double side2 = side2Input->text().toDouble(&ok2);
        double height = heightInput->text().toDouble(&ok3);

        if (ok1 && ok2 && ok3) {
            double area = ((side1 + side2) * height) / 2 ;
            resultLabel->setText(QString("<h2>Площадь: %1</h2>").arg(area));
        } else {
            resultLabel->setText("<h2>Ввод неккоректен!</h2>");
        }
    };

    connect(side1Input, &QLineEdit::textChanged, this, calculateArea);
    connect(side2Input, &QLineEdit::textChanged, this, calculateArea);
    connect(heightInput, &QLineEdit::textChanged, this, calculateArea);

    imageLabel->setPixmap(pixmap.scaled(256, 256, Qt::KeepAspectRatio));
    leftLayout->addWidget(imageLabel, 0, Qt::AlignTop);
}

void AreaInputWindow::setupTriangle() {
    setFixedSize(700, 300);
    QGridLayout *mainLayout = new QGridLayout;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    QGridLayout *rightLayout = new QGridLayout;
    QHBoxLayout *h_layout = new QHBoxLayout;

    setLayout(mainLayout);

    mainLayout->addLayout(leftLayout, 0, 0);
    mainLayout->addLayout(rightLayout, 0, 1);
    rightLayout->addLayout(h_layout, 0, 0);
    QPixmap pixmap(":/images/triangle-area.png");
    QLabel *imageLabel = new QLabel(this);

    QLabel *side1Label = new QLabel("<h1>a = </h1>", this);
    QLabel *side2Label = new QLabel("<h1>b = </h1>", this);
    QLabel *side3Label = new QLabel("<h1>h = </h1>", this);

    QLineEdit *side1Input = new QLineEdit(this);
    QLineEdit *side2Input = new QLineEdit(this);
    QLineEdit *side3Input = new QLineEdit(this);

    QDoubleValidator *validator = new QDoubleValidator(0.0, 1000.0, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    side1Input->setValidator(validator);
    side2Input->setValidator(validator);
    side3Input->setValidator(validator);

    QLocale locale(QLocale::English, QLocale::UnitedStates);
    validator->setLocale(locale);
    h_layout->addWidget(side1Label);
    h_layout->addWidget(side1Input);
    h_layout->addWidget(side2Label);
    h_layout->addWidget(side2Input);
    h_layout->addWidget(side3Label);
    h_layout->addWidget(side3Input);

    QLabel *resultLabel = new QLabel(this);
    rightLayout->addWidget(resultLabel, 1, 0, Qt::AlignTop);

    auto calculateArea = [=]() {
        bool ok1, ok2, ok3;
        double side1 = side1Input->text().toDouble(&ok1);
        double side2 = side2Input->text().toDouble(&ok2);
        double side3 = side3Input->text().toDouble(&ok3);

        if (ok1 && ok2 && ok3) {
            if (side1 + side2 > side3 && side1 + side3 > side2 && side2 + side3 > side1) {
                double p = (side1 + side2 + side3) / 2;
                double area = sqrt(p * (p - side1) * (p - side2) * (p - side3));
                resultLabel->setText(QString("<h2>Площадь: %1</h2>").arg(area));
            } else {
                resultLabel->setText("<h2>Некорректные стороны треугольника!</h2>");
            }
        } else {
            resultLabel->setText("<h2>Ввод некорректен!</h2>");
        }
    };

    connect(side1Input, &QLineEdit::textChanged, this, calculateArea);
    connect(side2Input, &QLineEdit::textChanged, this, calculateArea);
    connect(side3Input, &QLineEdit::textChanged, this, calculateArea);

    imageLabel->setPixmap(pixmap.scaled(256, 256, Qt::KeepAspectRatio));
    leftLayout->addWidget(imageLabel, 0, Qt::AlignTop);
}

