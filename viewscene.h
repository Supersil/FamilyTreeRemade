#ifndef VIEWSCENE_H
#define VIEWSCENE_H

#include <QGraphicsView>
#include <QFrame>
#include <QLabel>
#include <QToolButton>
#include <QSlider>

class ViewScene;

class GraphicsView : public QGraphicsView
{
	 Q_OBJECT
public:
	 GraphicsView(ViewScene *v) : QGraphicsView(), view(v) { }

protected:
#ifndef QT_NO_WHEELEVENT
	 void wheelEvent(QWheelEvent *) override;
#endif

private:
	 ViewScene *view;
};


class ViewScene: public QFrame
{
	Q_OBJECT
public:
	explicit ViewScene(QWidget * parent = 0);
	QGraphicsView *view() const;
	void scroll(int dx, int dy);

public slots:
	void zoomIn(int level = 1);
	void zoomOut(int level = 1);

private slots:
	void resetView();
	void setResetButtonEnabled();
	void setupMatrix();


private:
	GraphicsView *graphicsView;
	QLabel *label;
	QToolButton *resetButton;
	QSlider *zoomSlider;

};

#endif // VIEWSCENE_H
