#include "hanabira.h"
#include <QGraphicsScene>
#include <QDebug>
Hanabira::Hanabira()
{
    setPixmap(QPixmap("/home/gougou/project/qtPragmatism/Note/elite/he.png").scaled(80, 80));
//    scene()->addItem(this);
//    setPos(500, 500);
    hanabiraId = startTimer(600);
}

void Hanabira::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == hanabiraId){
        killTimer(hanabiraId);
        scene()->removeItem(this);
        delete this;
    }
}
