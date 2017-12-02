#ifndef TREELEAF_H
#define TREELEAF_H

#include <QObject>
#include <QGraphicsItem>
#include <QString>


class MyGraphicsItem: public QGraphicsItem, public QObject
{
};


class TreeLeaf: public MyGraphicsItem
{
	Q_OBJECT
public:
	TreeLeaf();
};


#endif // TREELEAF_H
