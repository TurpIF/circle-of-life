#ifndef MAIN_H
#define MAIN_H

#include <QtOpenGL>

class MyOpenGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    MyOpenGLWidget(unsigned long ratio, unsigned long framerate, QWidget * parent = NULL);
    ~MyOpenGLWidget();

    virtual void paintEvent(QPaintEvent *e);

public slots:
    void step();

private:
    bool ** myLife;
    QTimer myLittleTimer;
    unsigned long worldWidth;
    unsigned long worldHeight;
};

#endif // MAIN_H
