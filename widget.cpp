#include "widget.h"
#include "treeleaf.h"

#include <QHBoxLayout>

Widget::Widget(QWidget *parent) :
	QWidget(parent)
{
	createScene();

	ViewScene * view = new ViewScene;
	QHBoxLayout * lay = new QHBoxLayout;
	view->view()->setScene(m_scene);
	lay->addWidget(view);
	setLayout(lay);
}

Widget::~Widget()
{

}


void Widget::createScene()
{
	m_scene = new QGraphicsScene;

	m_scene->addRect(-10000,-10000,1,1,QPen(QColor(255,255,255)), QBrush(QColor(255,255,255)));
	m_scene->addRect(10000,10000,1,1,QPen(QColor(255,255,255)), QBrush(QColor(255,255,255)));

	TreeLeaf * item = new TreeLeaf("Силков Александр", "://me.jpg", 0, 0);
	item->setPos(0,0);
	item->setFlag(QGraphicsItem::ItemSendsGeometryChanges);

	m_scene->addItem(item);

}
