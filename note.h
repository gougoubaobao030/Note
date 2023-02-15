#ifndef NOTE_H
#define NOTE_H

#include <QWidget>
#include <QGraphicsView>
#include <QLineEdit>
#include <QJsonObject>
#include <QVector>
#include "mission.h"
#include <QTimer>
#include <hanabira.h>
//#include <button.h>

class Note : public QGraphicsView
{
    Q_OBJECT

public:
    QGraphicsScene * scene;
    QVector<Mission*> saveV;
//    QTimer * saveHint;
    Hanabira * saveHintHe;
    Note(QWidget *parent = nullptr);
    ~Note();

    void read(const QJsonObject & json);
    void write(QJsonObject &json);

    void testOfMultiLoad(int index); //scene of title button clicked
    void testOfMultiRead(const QJsonObject & json); //call this fuc by title of map
    void testOfMultiWrite(QJsonObject & json);
private:
    QLineEdit * ml;
    int maxValueOfVerticalBar;
    int maxValueOfHorizontalBar;
    QList<QString> tmpTitlesOfJson;
    int tmpMapIndex;
//    int randomPosX;
//    int randomPosY;
//    Button * memoButton;

    void exampleMoveStone();

public slots:
    void message();
    void memoButtonarPos();
    void loadNote();
    void saveNote();

    void extendVertical();
    void extendHorizontal();

    void testShowMapLoadList(); //set text do scene clear,get index to
    void testOfMultiSave();

//    void deleteSaveHint();
};
#endif // NOTE_H
