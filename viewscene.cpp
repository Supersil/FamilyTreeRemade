#include "viewscene.h"

#include <QWheelEvent>
#include <QStyle>
#include <QVBoxLayout>
#include <QGridLayout>
#include <qmath.h>
#include <QScrollBar>

#ifndef QT_NO_WHEELEVENT
void GraphicsView::wheelEvent(QWheelEvent *e)
{
	 if (e->modifiers() & Qt::ControlModifier) {
		  if (e->delta() > 0)
				view->zoomIn(6);
		  else
				view->zoomOut(6);
		  e->accept();
	 } else {
		  QGraphicsView::wheelEvent(e);
	 }
}
#endif

ViewScene::ViewScene(QWidget *parent)
	 : QFrame(parent)
{
	setFrameStyle(Sunken | StyledPanel);
	graphicsView = new GraphicsView(this);
	graphicsView->setRenderHint(QPainter::Antialiasing, false);
	graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
	graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
	graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

	int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
	QSize iconSize(size, size);

	QToolButton *zoomInIcon = new QToolButton;
	zoomInIcon->setAutoRepeat(true);
	zoomInIcon->setAutoRepeatInterval(33);
	zoomInIcon->setAutoRepeatDelay(0);
	zoomInIcon->setIcon(QPixmap(":/zoomin.png"));
	zoomInIcon->setIconSize(iconSize);
	QToolButton *zoomOutIcon = new QToolButton;
	zoomOutIcon->setAutoRepeat(true);
	zoomOutIcon->setAutoRepeatInterval(33);
	zoomOutIcon->setAutoRepeatDelay(0);
	zoomOutIcon->setIcon(QPixmap(":/zoomout.png"));
	zoomOutIcon->setIconSize(iconSize);
	zoomSlider = new QSlider;
	zoomSlider->setMinimum(0);
	zoomSlider->setMaximum(500);
	zoomSlider->setValue(250);
	zoomSlider->setTickPosition(QSlider::TicksRight);

	// Zoom slider layout
	QVBoxLayout *zoomSliderLayout = new QVBoxLayout;
	zoomSliderLayout->addWidget(zoomInIcon);
	zoomSliderLayout->addWidget(zoomSlider);
	zoomSliderLayout->addWidget(zoomOutIcon);

	resetButton = new QToolButton;
	resetButton->setText(tr(""));
	resetButton->setIcon(QPixmap("://reset.png"));
	resetButton->setToolTip(tr("Сбросить положение сцены"));
	resetButton->setEnabled(false);


	QGridLayout *topLayout = new QGridLayout;
	topLayout->addWidget(graphicsView, 1, 0);
	topLayout->addLayout(zoomSliderLayout, 1, 1);
	topLayout->addWidget(resetButton, 2, 1);
	setLayout(topLayout);

	connect(resetButton, SIGNAL(clicked()), this, SLOT(resetView()));
	connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(setupMatrix()));
	connect(graphicsView->verticalScrollBar(), SIGNAL(valueChanged(int)),
		this, SLOT(setResetButtonEnabled()));
	connect(graphicsView->horizontalScrollBar(), SIGNAL(valueChanged(int)),
		this, SLOT(setResetButtonEnabled()));
	connect(zoomInIcon, SIGNAL(clicked()), this, SLOT(zoomIn()));
	connect(zoomOutIcon, SIGNAL(clicked()), this, SLOT(zoomOut()));

	graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

	setupMatrix();
	zoomSlider->setValue(250);
}

QGraphicsView *ViewScene::view() const
{
	 return static_cast<QGraphicsView *>(graphicsView);
}

void ViewScene::resetView()
{
	 zoomSlider->setValue(250);
	 setupMatrix();
	 graphicsView->ensureVisible(QRectF(-500, -200, 1000, 600));

	 resetButton->setEnabled(false);
}

void ViewScene::setResetButtonEnabled()
{
	 resetButton->setEnabled(true);
}

void ViewScene::setupMatrix()
{
	 qreal scale = qPow(qreal(2), (zoomSlider->value() - 250) / qreal(50));

	 QMatrix matrix;
	 matrix.scale(scale, scale);

	 graphicsView->setMatrix(matrix);
	 setResetButtonEnabled();
}

void ViewScene::scroll(int dx, int dy)
{
	update();
}

void ViewScene::zoomIn(int level)
{
	 zoomSlider->setValue(zoomSlider->value() + level);
}

void ViewScene::zoomOut(int level)
{
	 zoomSlider->setValue(zoomSlider->value() - level);
}
