#include "viewscene.h"

#include <QWheelEvent>
#include <QStyle>
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
	graphicsView = std::unique_ptr<GraphicsView>(new GraphicsView(this));
	graphicsView->setRenderHint(QPainter::Antialiasing, false);
	graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
	graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
	graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

	int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
	QSize iconSize(size, size);

	zoomInBtn = std::unique_ptr<QToolButton>(new QToolButton);
	zoomInBtn->setAutoRepeat(true);
	zoomInBtn->setAutoRepeatInterval(33);
	zoomInBtn->setAutoRepeatDelay(0);
	zoomInBtn->setIcon(QPixmap("://zoomin.png"));
	zoomInBtn->setIconSize(iconSize);

	zoomOutBtn = std::unique_ptr<QToolButton>(new QToolButton);
	zoomOutBtn->setAutoRepeat(true);
	zoomOutBtn->setAutoRepeatInterval(33);
	zoomOutBtn->setAutoRepeatDelay(0);
	zoomOutBtn->setIcon(QPixmap("://zoomout.png"));
	zoomOutBtn->setIconSize(iconSize);
	zoomSlider = std::unique_ptr<QSlider>(new QSlider);
	zoomSlider->setMinimum(0);
	zoomSlider->setMaximum(500);
	zoomSlider->setValue(250);
	zoomSlider->setTickPosition(QSlider::TicksRight);

	// Zoom slider layout
	zoomSliderLayout = std::unique_ptr<QVBoxLayout>(new QVBoxLayout);
	zoomSliderLayout->addWidget(zoomInBtn.get());
	zoomSliderLayout->addWidget(zoomSlider.get());
	zoomSliderLayout->addWidget(zoomOutBtn.get());

	resetButton = std::unique_ptr<QToolButton> (new QToolButton);
	resetButton->setText(tr(""));
	resetButton->setIcon(QPixmap("://reset.png"));
	resetButton->setToolTip(tr("Сбросить положение сцены"));
	resetButton->setEnabled(false);


	topLayout = std::unique_ptr<QGridLayout>(new QGridLayout);
	topLayout->addWidget(graphicsView.get(), 1, 0);
	topLayout->addLayout(zoomSliderLayout.get(), 1, 1);
	topLayout->addWidget(resetButton.get(), 2, 1);
	setLayout(topLayout.get());

	connect(resetButton.get(), SIGNAL(clicked()), this, SLOT(resetView()));
	connect(zoomSlider.get(), SIGNAL(valueChanged(int)), this, SLOT(setupMatrix()));
	connect(graphicsView->verticalScrollBar(), SIGNAL(valueChanged(int)),
		this, SLOT(setResetButtonEnabled()));
	connect(graphicsView->horizontalScrollBar(), SIGNAL(valueChanged(int)),
		this, SLOT(setResetButtonEnabled()));
	connect(zoomInBtn.get(), SIGNAL(clicked()), this, SLOT(zoomIn()));
	connect(zoomOutBtn.get(), SIGNAL(clicked()), this, SLOT(zoomOut()));

	graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

	setupMatrix();
	zoomSlider->setValue(250);
}

QGraphicsView *ViewScene::view() const
{
	 return static_cast<QGraphicsView *>(graphicsView.get());
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
	Q_UNUSED(dx);
	Q_UNUSED(dy);
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
