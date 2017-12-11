#ifndef TREELEAF_H
#define TREELEAF_H

#include <QObject>
#include <QGraphicsItem>
#include <QString>
#include <QImage>
#include <QPainter>

class MyGraphicsItem: public QGraphicsItem, public QObject
{
};


class TreeLeaf: public MyGraphicsItem
{
	Q_OBJECT
public:
	TreeLeaf(QString strName, QString strPhotoPath, int iXPos, int iYPos);
	~TreeLeaf();
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
	QPointF top();
	QPointF btm();

	void changeInfo(QString strName = QString(), QString strPhotoPath = QString());
protected:
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
	QString m_strName;
	QImage m_imgPhoto;
	int m_iXPos;
	int m_iYPos;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
	bool m_bMovability;

private slots:
	void changeMovability();

signals:
	void destroyed_leaf(TreeLeaf*);
	void addDad(TreeLeaf*);
	void addMom(TreeLeaf*);
	void addChild(TreeLeaf*);
	void showInfo(TreeLeaf*);
	void moved(TreeLeaf*,QPointF delta);
	void connectParent(TreeLeaf *);

};


#endif // TREELEAF_H
