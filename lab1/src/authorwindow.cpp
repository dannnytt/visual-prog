#include "authorwindow.h"

AboutAuthorWindow::AboutAuthorWindow(QWidget *parent) : QDialog(parent) {

    setWindowTitle("Об авторе");
    setFixedSize(600, 250);


    mainLayout = new QGridLayout(this);
    leftLayout = new QVBoxLayout;
    rightLayout = new QVBoxLayout;
    rightTopLayout = new QGridLayout;
    setLayout(mainLayout);

    mainLayout->addLayout(leftLayout, 0, 0);
    mainLayout->addLayout(rightLayout, 0, 1);
    rightLayout->addLayout(rightTopLayout);

    labNameLabel = new QLabel("<h1> Практическое занятие 1</h1>");
    authorLabel = new QLabel("<h2>Терновский Данил ИП-213</h2>");
    rightTopLayout->addWidget(labNameLabel, 0, 0);
    rightTopLayout->addWidget(authorLabel, 1, 0);
    rightLayout->setAlignment(Qt::AlignTop);

    QPixmap pixmap(":/images/cat.jpg");
    imageLabel = new QLabel(this);
    imageLabel->setPixmap(pixmap);
    leftLayout->addWidget(imageLabel, 0, Qt::AlignTop);
}
