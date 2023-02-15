#include "note.h"
#include "mission.h"
#include <QLineEdit>
#include "button.h"
#include <QDebug>
#include <QFont>
#include <QScrollBar>
#include <QTimer>
#include <QPushButton>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
//#include <hanabira.h>
#include <QShortcut>
#include "titleofmap.h"

Note::Note(QWidget *parent)
    : QGraphicsView(parent)
{
    scene = new QGraphicsScene;
    setSceneRect(0, 0, 3000, 3500);
//    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    setFixedSize(1304, 702); //when nofixedSize just find allitem's center.
    setScene(scene);
//            qInfo() << horizontalScrollBar()->value() << ": " <<
//                       verticalScrollBar()->value();
    scene->setBackgroundBrush(QBrush(QPixmap(QString("/home/gougou/project/qtPragmatism/Note/elite/") + QString("bg2.png"))));
    maxValueOfVerticalBar = 2800;
    maxValueOfHorizontalBar = 1700;
//    horizontalScrollBar()->setValue(1000);
//    verticalScrollBar()->setValue(1000);
//    qInfo() << horizontalScrollBar()->value() << ": " << verticalScrollBar()->value();

//    memoButtonarPos();

    ml = new QLineEdit(this);
    ml->setGeometry(600, 600, 600, 40);
    ml->setFont(QFont("ubuntu", 15));
//    Button * yuan = new Button;
//    yuan->setPos(100 + ml->width() + 10, 30);
//    scene->addItem(yuan);
    connect(ml, &QLineEdit::returnPressed, this, &Note::message);

//    randomPosX = 250;
//    randomPosY = 250;

    exampleMoveStone();

//    memoButton = new Button();
//    memoButton->setRect(0, 0, 100, 100);
////    memoButton->setPos(1000, 600);
//    scene->addItem(memoButton);
//    QPushButton * memoButton = new QPushButton(this);
//    memoButton->setGeometry(600, 600, 50, 50);
//    connect(memoButton, &QPushButton::clicked, this, &Note::memoButtonarPos);

//    QPointF barPoint(0, 0);
//    if(barPoint.x() != horizontalmemoButtonar()->value() ||
//       barPoint.y() != verticalmemoButtonar()->value())
//    {

//    }
//    QTimer * time = new QTimer;
//    connect(time, &QTimer::timeout, this, &Note::memoButtonarPos);
//    time->start(1500);

      QPushButton * save = new QPushButton(this);
      QPushButton * load = new QPushButton(this);
      QPushButton * createNew = new QPushButton(this);
      QPushButton * toOriginal = new QPushButton(this);
      save->setGeometry(1160, 80, 80, 80);
      load->setGeometry(1160, 160, 80, 80);
      createNew->setGeometry(1160, 240, 80, 80);
      toOriginal->setGeometry(1160, 320, 80, 80);
      QPixmap hanzi_shi = QPixmap("/home/gougou/project/qtPragmatism/Note/elite/shi.png");
      QPixmap hanzi_li = QPixmap("/home/gougou/project/qtPragmatism/Note/elite/li.png");
      QPixmap hanzi_zhi = QPixmap("/home/gougou/project/qtPragmatism/Note/elite/zhi.png");
      QPixmap hanzi_shang = QPixmap("/home/gougou/project/qtPragmatism/Note/elite/shang.png");

      save->setIcon(hanzi_shi);
      save->setIconSize(QSize(80, 80));
      save->setToolTip(QString("SAVE YOUR HEART"));
      load->setIcon(hanzi_li);
      load->setIconSize(QSize(80, 80));
      load->setToolTip(QString("LOAD MY WISH"));
      createNew->setIcon(hanzi_zhi);
      createNew->setIconSize(QSize(80, 80));
      toOriginal->setIcon(hanzi_shang);
      toOriginal->setIconSize(QSize(80, 80));
      connect(save, &QPushButton::clicked, this, &Note::saveNote);
      connect(load, &QPushButton::clicked, this, &Note::loadNote);
      connect(createNew, &QPushButton::clicked, this, &Note::testOfMultiSave);
      connect(toOriginal, &QPushButton::clicked, this, &Note::testShowMapLoadList);


//      saveHintHe->setPixmap(QPixmap("/home/gougou/project/qtPragmatism/Note/elite/he.png").scaled(80, 80));

      //QTimerEvent override 自力のオーバーライド(only blog)　ワクワク
//      Hanabira * bira = new Hanabira;
//      scene->addItem(bira);

      //try to set short cut
      QShortcut * sload = new QShortcut(this);
      sload->setKey(Qt::CTRL + Qt::Key_L);
      connect(sload, &QShortcut::activated, this, &Note::loadNote);
      QShortcut * scSave = new QShortcut(this);
      scSave->setKey(Qt::CTRL + Qt::Key_S);
      connect(scSave, &QShortcut::activated, this, &Note::saveNote);

      //try setrenderhint anti-aliasing  効果ですか？どうかな
//      setRenderHint(QPainter::Antialiasing);

      QScrollBar * vers = verticalScrollBar();
      connect(vers, &QScrollBar::valueChanged, this, &Note::extendVertical);
      QScrollBar * hors = horizontalScrollBar();
      connect(hors, &QScrollBar::valueChanged, this, &Note::extendHorizontal);

      //multimap_tmp
      tmpTitlesOfJson << QString("jupiter") << QString("sirius");
}

Note::~Note()
{
}

void Note::read(const QJsonObject &json)
{
//    Mission *ms = new Mission;
//    ms->read(json);
//    scene->addItem(ms);
//    saveV.push_back(ms);
//    qInfo() << json["phrase"].toString();
    if(json.contains("missions") && json["missions"].isArray()){
        QJsonArray missArray = json["missions"].toArray();
        for (int i = 0; i != missArray.size(); i++) {
            QJsonObject missObject = missArray[i].toObject();
            Mission * ms = new Mission;
            ms->read(missObject);
            scene->addItem(ms);
            saveV.push_back(ms);
        }
    }

//    qInfo() << scene->items().size();
}

void Note::write(QJsonObject &json)
{
//    json["name"] = "綾小路清隆";

//        saveV[0]->write(json);
        QJsonArray missArray;
//        qInfo() << saveV.size();
        for(Mission *mission: saveV){
            QJsonObject missObject;
            mission->write(missObject);
            missArray.append(missObject);
        }
        json["missions"] = missArray;

}

void Note::loadNote()
{
    scene->clear();
    exampleMoveStone();

    QFile loadFile(QStringLiteral("save.json"));

    if (!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open save.json");
        return;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc.object());
}

void Note::saveNote()
{

    //    saveHint = new QTimer;
    //    connect(saveHint, &QTimer::timeout, this, &Note::deleteSaveHint);

    QFile saveFile(QStringLiteral("save.json"));

    if(!saveFile.open(QIODevice::WriteOnly)){
        qWarning("Couldn't open save file");
    }

    QJsonObject noteObject;


    write(noteObject);
    //    saveFile.write(QJsonDocument(noteObject).toJson());
    QJsonDocument saveDoc(noteObject);
    saveFile.write(saveDoc.toJson());


    //        saveHint->start(500);
    saveHintHe = new Hanabira;
    scene->addItem(saveHintHe);
    saveHintHe->setPos(horizontalScrollBar()->value() + 1160, verticalScrollBar()->value() + 400);
}

void Note::extendVertical()
{
    if(verticalScrollBar()->value() > maxValueOfVerticalBar){
        //scene is 无限的, scenerect is a range of 可视化
        setSceneRect(0, 0, sceneRect().width(), sceneRect().height() + 1000);
        maxValueOfVerticalBar += 1000;
    }
}

void Note::extendHorizontal()
{
    if(horizontalScrollBar()->value() > maxValueOfHorizontalBar){
        setSceneRect(0, 0, sceneRect().width() + 1000, sceneRect().height());
        maxValueOfHorizontalBar += 1000;
    }

}

void Note::testShowMapLoadList()
{
    scene->clear();
    verticalScrollBar()->setValue(0);
    horizontalScrollBar()->setValue(0);

    for (int i = 0; i != tmpTitlesOfJson.size(); i++) {
        TitleOfMap * tm = new TitleOfMap(i);
        tm->setPlainText("test" + QString::number(i));
        tm->setPos(i * 200, i * 200);
        scene->addItem(tm);
    }
}

void Note::testOfMultiSave()
{
    QString fileName = tmpTitlesOfJson[tmpMapIndex] + QString(".json");
    QFile saveFile(fileName);
    if(!saveFile.open(QIODevice::WriteOnly)){
        qWarning("couldn't open multiSave.json");
        return;
    }

    QJsonObject mapObject;
    testOfMultiWrite(mapObject);
    QJsonDocument saveDoc(mapObject);
    saveFile.write(saveDoc.toJson());
}

void Note::testOfMultiLoad(int index)
{
    scene->clear();

    tmpMapIndex = index;
//    qInfo() << "do it well 3";
    QString fileName = tmpTitlesOfJson[tmpMapIndex] + QString(".json");
    qInfo() << fileName;
    QFile loadFile(fileName);

    if (!loadFile.open(QIODevice::ReadOnly))
    {
        //load からのsave はブブですね、フアイルなしので、Noteさん怒るわよ.
//        QFile newCreateFile(fileName);
        qWarning("can't open this file");
        //因为平常第一件事是新建文件 ) ) )
        return;
    }
//    qInfo() << "do it well 4";

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    testOfMultiRead(loadDoc.object());
}

void Note::testOfMultiRead(const QJsonObject &json)
{
//    qInfo() << "do it well 5";

//    if(json.contains("mapList") && json["mapList"].isArray()){
//        qInfo() << "do it well 6";

//        QJsonArray missArray = json["mapList"].toArray();

//        QJsonObject mindObject = missArray[index].toObject();
//        qInfo() << index;
//        qInfo() << "do it well 1";
    saveV.clear();
    QString oath(tmpTitlesOfJson[tmpMapIndex]);
    if(json.contains(oath) && json[oath].isArray())
    {
        QJsonArray mindArray = json[oath].toArray();
        //            qInfo() << mindArray.size();
        for (int i = 0; i != mindArray.size(); i++) {
            QJsonObject missObject = mindArray[i].toObject();
            Mission * ms = new Mission;
            ms->read(missObject);
            scene->addItem(ms);
            saveV.push_back(ms);
            //            qInfo() << "do it well 7";

        }
    }
//        qInfo() << "do it well 2";

    //    }
}

void Note::testOfMultiWrite(QJsonObject &json)
{
    qInfo() << tmpMapIndex << ": " << tmpTitlesOfJson[tmpMapIndex];
       QJsonArray mapList;
       for(Mission *ms: saveV){
           QJsonObject msObject;
           ms->write(msObject);
           mapList.append(msObject);
       }
       json[tmpTitlesOfJson[tmpMapIndex]] = mapList;
}

//void Note::deleteSaveHint()
//{

//    saveHint->disconnect();
//    scene->removeItem(saveHintHe);
//    delete saveHintHe;
//}

void Note::exampleMoveStone()
{
    //"亲爱的西西弗，今天也在鄙视命运，嘲笑上帝吗\n今日も全力を尽くしたんだよね"
    Mission * ms = new Mission();
    ms->setPixmap(QPixmap(QString("/home/gougou/project/qtPragmatism/Note/elite/0.png")).scaled(150, 200));
    ms->setPhrase("用鄙视的态度，就没有战胜不了的命运\n生きることは考えることだ");

//    if(horizontalScrollBar()->value() == 0 &&
//       verticalScrollBar()->value() == 0)
//    {
//        qInfo() << horizontalScrollBar()->value() << ": " <<
//                   verticalScrollBar()->value();
        ms->setPos(150, 150);

//    }
//    else{
//        ms->setPos(horizontalScrollBar()->value(), verticalScrollBar()->value());
//    }

    scene->addItem(ms);
}

void Note::message()
{
    QString s = ml->text();
    ml->setText(QString(""));
    Mission * ms = new Mission();
    ms->setPhrase(s);
    scene->addItem(ms);
//    if(horizontalScrollBar()->value() == 0 &&
//       verticalScrollBar()->value() == 0)
//    {
//        qInfo() << horizontalScrollBar()->value() << ": " <<
//                   verticalScrollBar()->value();

        ms->setPos(horizontalScrollBar()->value() + 800, verticalScrollBar()->value() + 400);

//    }
//    else{
//        ms->setPos(horizontalScrollBar()->value(), verticalScrollBar()->value());
//        qInfo() << horizontalScrollBar()->value() << ": " <<
//                   verticalScrollBar()->value();
//    }
//    randomPosX += 100;
//    randomPosY += 100;
    saveV.push_back(ms);

}

void Note::memoButtonarPos()
{
    qInfo( ) << horizontalScrollBar()->value() << "h :  v:" << verticalScrollBar()->value();
//        horizontalScrollBar()->setValue(0);
//        verticalScrollBar()->setValue(0);
}

