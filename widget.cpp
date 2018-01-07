#include "widget.h"
#include "treeleaf.h"


Widget::Widget(QWidget *parent) :
	QWidget(parent)
{
	createScene();

	view = std::unique_ptr<ViewScene>(new ViewScene);
	lay = std::unique_ptr<QHBoxLayout>(new QHBoxLayout);
	view->view()->setScene(m_scene.get());
	lay->addWidget(view.get());
	setLayout(lay.get());

	setWindowTitle(tr("Генеалогия"));
	QIcon myIcon(":/tree.png");
	setWindowIcon(myIcon);

}

Widget::~Widget()
{

}


void Widget::createScene()
{
	m_scene.release();

	m_scene = std::unique_ptr<QGraphicsScene>(new QGraphicsScene);

	m_scene->addRect(-10000,-10000,1,1,QPen(QColor(255,255,255)), QBrush(QColor(255,255,255)));
	m_scene->addRect(10000,10000,1,1,QPen(QColor(255,255,255)), QBrush(QColor(255,255,255)));

	TreeLeaf *item = new TreeLeaf("Силков Александр", "://me.jpg");
	item->setPos(0,0);
	item->setFlag(QGraphicsItem::ItemSendsGeometryChanges);

	m_scene->addItem(item);

	TreeLeaf * item2 = new TreeLeaf("Силков Александр", "://me.jpg");
	item2->setPos(500,500);
	item2->setFlag(QGraphicsItem::ItemSendsGeometryChanges);

	m_scene->addItem(item2);


}
