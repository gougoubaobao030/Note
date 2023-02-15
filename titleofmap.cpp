#include "titleofmap.h"
#include "mission.h"
#include <QJsonObject>
#include <QGraphicsScene>
#include "note.h"

extern Note * note;

TitleOfMap::TitleOfMap(int index, QGraphicsItem *parent):QGraphicsTextItem(parent)
{
    //あとで　setplaintext使えばいいだと思う
    //constructor は新しい定義すべきだと思う 親からとあるコンストラクタをもっていくとか
    mapIndex = index;
    QFont font("ubuntu", 30);
    setFont(font);
}

void TitleOfMap::read()
{
    //ここはとあるarrayだと思うわ
//    for(int i = 0; i != mindArray.size(); i++){
//        QJsonObject mindObject = mindArray[i].toObject();
//        Mission * ms = new Mission();
//        ms->read(mindObject);
//    }


}

void TitleOfMap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    note->testOfMultiLoad(getMapIndex());
//    QGraphicsTextItem::mousePressEvent(event);
}

int TitleOfMap::getMapIndex() const
{
    return mapIndex;
}

void TitleOfMap::setMapIndex(int newMapIndex)
{
    mapIndex = newMapIndex;
}
