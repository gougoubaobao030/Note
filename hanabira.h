#ifndef HANABIRA_H
#define HANABIRA_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimerEvent>

class Hanabira :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Hanabira();

protected:
    void timerEvent(QTimerEvent * e);
private:
    int hanabiraId;
};

#endif // HANABIRA_H
