#include <QApplication>
#include "life.h"
#include "main.h"

MyOpenGLWidget::MyOpenGLWidget(unsigned long ratio, unsigned long framerate, QWidget * parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
      myLife(NULL),
      myLittleTimer(this),
      worldWidth(800 / ratio),
      worldHeight(600 / ratio)
{
    myLife = new bool * [worldWidth];
    for (unsigned long i = 0; i < worldWidth; i++) {
        myLife[i] = new bool [worldHeight];
        for (unsigned long j = 0; j < worldHeight; j++)
            myLife[i][j] = std::rand() % 4 == 0;
    }

    setFixedSize(800, 600);
    setAutoFillBackground(false);

    QObject::connect(&myLittleTimer, SIGNAL(timeout()), this, SLOT(step()));
    myLittleTimer.setInterval(framerate);
    myLittleTimer.start();
}

MyOpenGLWidget::~MyOpenGLWidget()
{
    for (unsigned long i = 0; i < worldWidth; i++)
    {
        delete[] myLife[i];
    }
    delete[] myLife;
}

void MyOpenGLWidget::step()
{
    changeMyLife(&myLife, worldWidth, worldHeight);
    repaint();
}

void MyOpenGLWidget::paintEvent(QPaintEvent * e) {
  QPen blackPen(Qt::black);
  QPen whitePen(Qt::white);
  QBrush blackBrush(Qt::black);
  QBrush whiteBrush(Qt::white);
  QPainter painter;
  painter.begin(this);
  painter.setPen(whitePen);
  painter.fillRect(e->rect(), QBrush(Qt::white));
  unsigned long dx = width() / worldWidth;
  unsigned long dy = height() / worldHeight;
  for (unsigned int x = 0; x < worldWidth; x++) {
      for (unsigned int y = 0; y < worldHeight; y++) {
        if (myLife[x][y]) {
            painter.setBrush(blackBrush);
        } else {
            painter.setBrush(whiteBrush);
        }
        painter.drawRect(x * dx, y * dy, dx, dy);
      }
  }
  painter.end();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyOpenGLWidget w(4, 1000 / 30);
    w.show();

    return a.exec();
}
