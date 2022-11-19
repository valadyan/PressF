#include "TreeModel.h"
#include "TreeModelItem.h"

#include <QStringList>


TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    rootItem = new TreeModelItem({"tree", "wef"});
    setupModelData(rootItem);
}


TreeModel::~TreeModel()
{
    delete rootItem;
}


int TreeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
    if (parent.isValid())
	return static_cast<TreeModelItem*>(parent.internalPointer())->columnCount();
    return rootItem->columnCount();
}


QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
	return QVariant();

    if (role != Qt::DisplayRole)
	return QVariant();

    TreeModelItem *item = static_cast<TreeModelItem*>(index.internalPointer());

    return item->data(index.column());
}


Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
	return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}


QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
			       int role) const
{
//    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
//	return rootItem->data(section);

    return QVariant();
}


QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
	return QModelIndex();

    TreeModelItem *parentItem;

    if (!parent.isValid())
	parentItem = rootItem;
    else
	parentItem = static_cast<TreeModelItem*>(parent.internalPointer());

    TreeModelItem *childItem = parentItem->child(row);

    if (childItem)
	return createIndex(row, column, childItem);
    return QModelIndex();
}


QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
	return QModelIndex();

    TreeModelItem *childItem = static_cast<TreeModelItem*>(index.internalPointer());
    TreeModelItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
	return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}


int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeModelItem *parentItem;
    if (parent.column() > 0)
	return 0;

    if (!parent.isValid())
	parentItem = rootItem;
    else
	parentItem = static_cast<TreeModelItem*>(parent.internalPointer());

    return parentItem->childCount();
}


void TreeModel::setupModelData(TreeModelItem *parent)
{
    TreeModelItem* qobj = new TreeModelItem({"wefw", "wef"}, parent);
    TreeModelItem* par = new TreeModelItem({"par", "wef"}, qobj);
    qobj->appendChild(par);

    par->appendChild(new TreeModelItem({"333"}, par));
    qobj->appendChild(new TreeModelItem({"objProp1", "objProp2", }, qobj));
    qobj->appendChild(new TreeModelItem({"22"}, qobj));
    qobj->appendChild(new TreeModelItem({"444"}, qobj));
    parent->appendChild(qobj);
}
