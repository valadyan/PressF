#include "TreeModel.h"

#include <QApplication>
#include <QDebug>
#include <QPointer>
#include <QTreeView>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QPointer<QAbstractItemModel> model = new TreeModel();

  QTreeView view;
  view.setModel(model);
  view.show();
  return a.exec();
}
