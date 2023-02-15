#include "button.h"

Button::Button(QGraphicsItem *parent): QObject(), QGraphicsEllipseItem(parent)
{
    setRect(0, 0, 60, 60);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit shited();
}
