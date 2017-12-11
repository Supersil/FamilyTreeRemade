#include "treeleaf.h"

#include <QAction>
#include <QTextOption>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

TreeLeaf::TreeLeaf(QString strName, QString strPhotoPath, int iXPos, int iYPos):	m_strName(strName), m_imgPhoto(strPhotoPath), m_iXPos(iXPos), m_iYPos(iYPos)
{
	setToolTip(QObject::tr("Двойное нажатие ЛКМ - открыть информацию.\nПКМ - меню."));
	m_bMovability = false;
}


TreeLeaf::~TreeLeaf()
{
	emit destroyed_leaf(this);
}


QRectF TreeLeaf::boundingRect() const
{
	 return QRectF(0, 0, 300, 400);
}


QPainterPath TreeLeaf::shape() const
{
	 QPainterPath path;
	 path.addRect(0, 0, 300, 400);
	 return path;
}


void TreeLeaf::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	QMenu menu;
	menu.addAction("Добавить отца");
	menu.addAction("Добавить мать");
	menu.addAction("Добавить ребенка");
	menu.addAction("Удалить");

	QAction * replaceble = new QAction(&menu);
	replaceble->setText(tr("Перемещаемый объект"));
	replaceble->setCheckable(true);
	replaceble->setChecked(m_bMovability);
	connect(replaceble,SIGNAL(changed()),this,SLOT(changeMovability()));
	menu.addAction(replaceble);//,this,SLOT(changeMovability()));
	menu.addAction("Установить родительскую связь");
	QAction *selectedAction = menu.exec(event->screenPos());
	if (selectedAction)
	{
	if (selectedAction->text().contains("Удалить"))
		delete this;
	if (selectedAction->text().contains("отца"))
		emit addDad(this);
	if (selectedAction->text().contains("мать"))
		emit addMom(this);
	if (selectedAction->text().contains("ребенка"))
		emit addChild(this);
	if (selectedAction->text().contains("связь"))
		emit connectParent(this);
	}
}


void TreeLeaf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(widget);

	QTextOption to;
	to.setAlignment(Qt::AlignCenter);
	to.setWrapMode(QTextOption::WordWrap);

	QFont font;
	font.setPixelSize(20);
	painter->setFont(font);

	painter->drawImage(m_iXPos,m_iYPos,m_imgPhoto.scaled(300,380));
	painter->drawText(QRectF(m_iXPos,m_iYPos+380,300,20),m_strName,to);
	painter->drawRect(m_iXPos,m_iYPos,300,400);

}



void TreeLeaf::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	emit showInfo(this);
}


void TreeLeaf::changeInfo(QString strName, QString strPhotoPath)
{
	if (strName.size() != 0)
		m_strName = strName;
	if (strPhotoPath.size() != 0)
		m_imgPhoto = QImage(strPhotoPath);

}


QVariant TreeLeaf::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == ItemPositionChange && scene()) {
		QPointF oldPos	= mapToScene(0,0);
		QPointF newPos = value.toPointF();
		int delta_y = newPos.y()/100;
		delta_y -= (int)oldPos.y()/100;
		if (delta_y !=0)
			newPos.setY(oldPos.y());
		QPointF delta(newPos.x() - oldPos.x(),newPos.y() - oldPos.y());

		emit moved(this,delta);
		return newPos;
	 }
	 return QGraphicsItem::itemChange(change, value);
}


void TreeLeaf::changeMovability()
{
	m_bMovability = !(m_bMovability);
	setFlag(QGraphicsItem::ItemIsMovable,m_bMovability);
}


QPointF TreeLeaf::top()
{
	QPointF Pos = mapToScene(0,0);
	return QPointF(Pos.x()+150,Pos.y());
}


QPointF TreeLeaf::btm()
{
	QPointF Pos = mapToScene(0,0);
	return QPointF(Pos.x()+150,Pos.y()+400);
}


