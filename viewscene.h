#ifndef VIEWSCENE_H
#define VIEWSCENE_H

#include <QGraphicsView>
#include <QFrame>
#include <QLabel>
#include <QToolButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QGridLayout>
#include <memory>

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
	std::unique_ptr<GraphicsView> graphicsView;
	std::unique_ptr<QToolButton> resetButton;
	std::unique_ptr<QSlider> zoomSlider;
	std::unique_ptr<QVBoxLayout> zoomSliderLayout;
	std::unique_ptr<QGridLayout> topLayout;
	std::unique_ptr<QToolButton> zoomInBtn;
	std::unique_ptr<QToolButton> zoomOutBtn;

};

#endif // VIEWSCENE_H
