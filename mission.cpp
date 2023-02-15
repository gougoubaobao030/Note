#include "mission.h"
#include <QPixmap>
#include <QFont>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <button.h>
#include <QDebug>
#include <QJsonObject>
#include <note.h>

extern Note * note;

Mission::Mission()
{
//    this->phrase = phrase;


    //QStringじゃなければ、大変な目に合う
    srand(time(NULL));
    randNum = rand() % 21;
//    qInfo() << num;
    setPixmap(
         QPixmap(QString("/home/gougou/project/qtPragmatism/Note/elite/")+ QString::number(randNum) + QString("n.png")).scaled(100, 100)
           );
//    setPos(100, 100);
    setFlag(ItemIsMovable);

    //set mission text
//    mission = new QGraphicsTextItem(this);
//    QFont font = QFont("ubuntu", 20);
//    mission->setFont(font);
//    mission->setOpacity(0.5);
////    mission->setFlag(ItemIsMovable);
//    mission->setPlainText(QString(this->phrase));
//    mission->setPos(this->boundingRect().width() + this->x() + 10, this->y() +(this->boundingRect().height() - mission->boundingRect().height()) / 2);

    //button
//    Button * b = new Button(this);
//    b->setPos(this->boundingRect().width() + this->x() + mission->boundingRect().width() + 10,
//              (this->boundingRect().height() - b->boundingRect().height()) / 2 + this->y());
//    connect(b, &Button::shited, this, &Mission::moveAway);
}

Mission::~Mission()
{
    //    qInfo() << __FUNCTION__;
}

void Mission::read(const QJsonObject &json)
{
    int x = 0, y = 0, num = 0;
    QString newPhrase;

    if(json.contains("num") && json["num"].isDouble()){
        num = json["num"].toInt();
    }
    if(json.contains("posX") && json["posX"].isDouble()){
        x = json["posX"].toInt();
    }
    if(json.contains("posY") && json["posY"].isDouble()){
        y = json["posY"].toInt();
    }
    if(json.contains("phrase") && json["phrase"].isString()){
        newPhrase = json["phrase"].toString();
    }

//    qInfo() << newPhrase;
    randNum = num;
    this->setPixmap(QPixmap(QString("/home/gougou/project/qtPragmatism/Note/elite/")+ QString::number(num) + QString("n.png")).scaled(100, 100));
    this->setPos(x, y);
    this->setPhrase(newPhrase);
}

void Mission::write(QJsonObject &json) const
{
    json["num"] = this->randNum;
    json["posX"] = this->x();
    json["posY"] = this->y();
    json["phrase"] = this->phrase;
}

const QString &Mission::getPhrase() const
{
    return phrase;
}

void Mission::setPhrase(const QString &newPhrase)
{
    phrase = newPhrase;

    mission = new QGraphicsTextItem(this);
    QFont font = QFont("ubuntu", 19);
    mission->setFont(font);
    mission->setOpacity(0.5);
    mission->setPlainText(QString(this->phrase));
//    mission->setPos(this->boundingRect().width() + this->x() + 10, this->y() +(this->boundingRect().height() - mission->boundingRect().height()) / 2);
    if(mission->boundingRect().width() > 500){

        mission->setTextWidth(500);
    }

    mission->setPos(this->boundingRect().width() + 10, (this->boundingRect().height() - mission->boundingRect().height()) / 2);

//    qInfo() << this->boundingRect().width() << ": " << this->x() + 10;
    Button * b = new Button(this);
//    b->setPos(this->boundingRect().width() + this->x() + mission->boundingRect().width() + 10,
//              (this->boundingRect().height() - b->boundingRect().height()) / 2 + this->y());
    b->setPos(this->boundingRect().width() +  mission->boundingRect().width() + 10,
              (this->boundingRect().height() - b->boundingRect().height()) / 2 );
    //has a relationship of parent it's x not the x of scene but x from parent
    connect(b, &Button::shited, this, &Mission::moveAway);

}

void Mission::moveAway()
{
    note->scene->removeItem(this);
    note->saveV.removeAll(this);
    delete this;
}


