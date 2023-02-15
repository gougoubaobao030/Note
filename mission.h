#ifndef MISSION_H
#define MISSION_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>

class Mission : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Mission();
    ~Mission();
    void read(const QJsonObject & json);
    void write(QJsonObject &json) const; //const cant change menber attruibute in this function.

    const QString &getPhrase() const;
    void setPhrase(const QString &newPhrase);

private:
    QGraphicsTextItem * mission;
    QString phrase;
    int randNum;

public slots:
    void moveAway();
};

#endif // MISSION_H
