#ifndef AUTHORWINDOW_H
#define AUTHORWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>


class AboutAuthorWindow : public QDialog {

    Q_OBJECT

public:
    explicit AboutAuthorWindow(QWidget *parent = nullptr);

private:
    QGridLayout *mainLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
    QGridLayout *rightTopLayout;
    QLabel *labNameLabel;
    QLabel *authorLabel;
    QLabel *imageLabel;
};


#endif // AUTHORWINDOW_H
