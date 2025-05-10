#ifndef CLICKED_LABEL_H
#define CLICKED_LABEL_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class ClickedLabel : public QLabel {

    Q_OBJECT

public:
    explicit ClickedLabel(QWidget *parent = nullptr);
    ~ClickedLabel();

protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void clicked();
};

#endif // CLICKED_LABEL_H
