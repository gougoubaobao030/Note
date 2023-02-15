#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsEllipseItem>
#include <QObject>

class Button :public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Button(QGraphicsItem * parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

signals:
    void shited();
};

#endif // BUTTON_H
