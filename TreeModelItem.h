#ifndef HIERARCHYTREEMODELITEM_H
#define HIERARCHYTREEMODELITEM_H

#include <QVariant>
#include <QVector>


class TreeModelItem
{
public:
    explicit TreeModelItem(const QVector<QVariant> &data, TreeModelItem *parentItem = nullptr);
    ~TreeModelItem();

    void appendChild(TreeModelItem *child);

    TreeModelItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeModelItem *parentItem();

private:
    QVector<TreeModelItem*> m_childItems;
    QVector<QVariant> m_itemData;
    TreeModelItem *m_parentItem;
};

#endif // HIERARCHYTREEMODELITEM_H
