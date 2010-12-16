#ifndef WIDGET_H
#define WIDGET_H

#include <QGLShaderProgram>
#include <QVector>
#include <QVector4D>
#include <QMatrix4x4>
#include <QTimer>

class Widget
    : public QGLWidget
{
    Q_OBJECT

    public:
        Widget(QWidget *parent = 0);
        ~Widget();

    protected:
        void initializeGL();
        void paintGL();
        void resizeGL(int width, int height);

    private slots:
        void update();

    private:
        QGLShaderProgram *_shaderProgram;
        QVector<QVector4D> _vertexData;
        QMatrix4x4 _projectionMatrix;
        QMatrix4x4 _modelViewMatrix;
        QMatrix4x4 _rotationMatrix;
        qreal _yRotation;
        QTimer *_timer;

};
#endif // WIDGET_H
