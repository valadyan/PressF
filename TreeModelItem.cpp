#include "TreeModelItem.h"
#include "TreeModel.h"


TreeModelItem::TreeModelItem(const QVector<QVariant> &data, TreeModelItem *parent)
    : m_itemData(data), m_parentItem(parent)
{}


TreeModelItem::~TreeModelItem()
{
    qDeleteAll(m_childItems);
}


void TreeModelItem::appendChild(TreeModelItem *item)
{
    m_childItems.append(item);
}


TreeModelItem *TreeModelItem::child(int row)
{
    if (row < 0 || row >= m_childItems.size())
	return nullptr;
    return m_childItems.at(row);
}


int TreeModelItem::childCount() const
{
    return m_childItems.count();
}


int TreeModelItem::columnCount() const
{
    return m_itemData.count();
}


QVariant TreeModelItem::data(int column) const
{
    if (column < 0 || column >= m_itemData.size())
	return QVariant();
    return m_itemData.at(column);
}


TreeModelItem *TreeModelItem::parentItem()
{
    return m_parentItem;
}


int TreeModelItem::row() const
{
    if (m_parentItem)
	return m_parentItem->m_childItems.indexOf(const_cast<TreeModelItem*>(this));

    return 0;
}
