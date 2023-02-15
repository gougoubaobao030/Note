#include "note.h"
#include <QScrollBar>
#include <QApplication>

///home/gougou/project/qtPragmatism/Note/elite/
Note * note;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    note = new Note;
    note->show();
    note->horizontalScrollBar()->setValue(0);
    note->verticalScrollBar()->setValue(0);
    note->loadNote();
    return a.exec();
}
//try to do:
//


//fix an item on view
//https://www.qtcentre.org/threads/44154-How-to-draw-QGraphicsItem-at-the-same-location?highlight=setPos
//你全家自己去fix吧

//scroll bar

//
/*
QVariant item_to_variant(QGraphicsItem* item) {
  QVariantHash data;
  //save all needed attributes
  data["pos"] = item->pos();
  data["rotation"] = item->rotation();
  if(QGraphicsPixmapItem* pixmap_item = dynamic_cast(item)) {
    data["type"] = "pixmap";
    data["pixmap"] = pixmap_item->pixmap();
  } else { ... }
 //...
  return data;
}

QGraphicsItem* item_from_variant(QVariant v) {
  QVariantHash data = v.toHash();
  QGraphicsItem* result;
  if (data["type"].toString() == "pixmap") {
    result = new QGraphicsPixmapItem();
    result->setPixmap(data["pixmap"].value());
  } else { ...
 }
  result->setPos(data["pos"].toPointf());
  result->setRotation(data["rotation"].toDouble());
  //...
  return result;
}

void save_state() {
  QVariantList data_list;
  foreach(QGraphicsItem* item, items_list) {
    data_list << item_to_variant(item);
  }
  QSettings settings;
  settings.setValue("items", data_list);
}

void restore_state() {
  QSettings settings;
  foreach(QVariant data, settings.value("items").toList()) {
    QGraphicsItem* item = item_from_variant(data);
    scene->addItem(item);
    items_list << item;
  }

}
*/
