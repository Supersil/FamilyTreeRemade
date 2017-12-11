#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>

#include "viewscene.h"

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = 0);
	~Widget();

private:
	QGraphicsScene * m_scene;

	void createScene();
};

#endif // WIDGET_H
