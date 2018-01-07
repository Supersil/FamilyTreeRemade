#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QHBoxLayout>

#include "viewscene.h"
#include <memory>


class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = 0);
	~Widget();

private:
	std::unique_ptr<QGraphicsScene> m_scene;
	std::unique_ptr<ViewScene> view;
	std::unique_ptr<QHBoxLayout> lay;


	void createScene();
};

#endif // WIDGET_H
