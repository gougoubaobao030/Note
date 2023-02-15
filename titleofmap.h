#ifndef TITLEOFMAP_H
#define TITLEOFMAP_H

#include <QGraphicsTextItem>
//#include <QJsonObject>
#include <QJsonArray>
//#include "mission.h"

class TitleOfMap : public QGraphicsTextItem
{
public:
    TitleOfMap(int index, QGraphicsItem * parent = nullptr);
    void read();

    int getMapIndex() const;
    void setMapIndex(int newMapIndex);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
private:
    int mapIndex;
//    QJsonObject & json;
//    QJsonArray mindArray; //多分 これ　&　いらない
};

#endif // TITLEOFMAP_H
