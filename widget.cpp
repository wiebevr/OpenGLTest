#include "widget.h"

#include <QGLShader>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::DirectRendering), parent)
{
    setWindowState(Qt::WindowFullScreen);
    _timer = new QTimer(this);
    
    connect(_timer, SIGNAL(timeout()), this, SLOT(update()));
    _shaderProgram = NULL;
    _yRotation = 0.0;

    _vertexData.append(QVector4D(-1.0f, -1.0f, 0.0f, 1.0f));
    _vertexData.append(QVector4D( 1.0f, -1.0f, 0.0f, 1.0f));
    _vertexData.append(QVector4D(-1.0f,  1.0f, 0.0f, 1.0f));
    _vertexData.append(QVector4D( 1.0f,  1.0f, 0.0f, 1.0f));
    
    _projectionMatrix.setToIdentity();
    _projectionMatrix.perspective(60.0, (qreal)width() / (qreal)height(), 1.0, 200.0);

    _modelViewMatrix.setToIdentity();
    _modelViewMatrix.translate(0.0, 0.0, -5.0);
}

Widget::~Widget()
{
}

void Widget::initializeGL()
{
    qDebug() << "isValid:" << this->context()->isValid();
    qDebug() << "isSharing:" << this->context()->isSharing();
    qDebug() << "hasOpenGL:" << this->context()->format().hasOpenGL();
    qDebug() << "Format:" << this->context()->format();


    glEnable(GL_DEPTH_TEST);

    QString vertexShaderSource(
        "uniform mat4 modelViewMatrix;\n"
        "uniform mat4 projectionMatrix;\n"
        "attribute vec4 vertexPosition;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = projectionMatrix * modelViewMatrix  * vertexPosition;\n"
        "}\n");

    QString fragmentShaderSource(
        "precision mediump float;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);\n"
        "}\n");

    QGLShader *vertexShader = new QGLShader(QGLShader::Vertex, this);
    QGLShader *fragmentShader = new QGLShader(QGLShader::Fragment, this);
    qDebug() << "After constuctor Shaders.";
    qDebug() << vertexShader->log();

    vertexShader->compileSourceCode(vertexShaderSource);
    fragmentShader->compileSourceCode(fragmentShaderSource);
    
    _shaderProgram = new QGLShaderProgram(this);

    _shaderProgram->addShader(vertexShader);
    _shaderProgram->addShader(fragmentShader);

    _shaderProgram->link();
    
    _shaderProgram->bind();

    qglClearColor(Qt::gray);
    _timer->start(10);
    qDebug() << vertexShader->log();
}

void Widget::resizeGL(int width, int height)
{
    _projectionMatrix.setToIdentity();
    _projectionMatrix.perspective(60.0, (qreal)width / (qreal)height, 1.0, 200.0);

    glViewport(0, 0, width, height);

}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _shaderProgram->setUniformValue("modelViewMatrix", _modelViewMatrix * _rotationMatrix);
    _shaderProgram->setUniformValue("projectionMatrix", _projectionMatrix);
    _shaderProgram->setAttributeArray("vertexPosition", _vertexData.constData());

    _shaderProgram->enableAttributeArray("vertexPosition");
    glDrawArrays(GL_TRIANGLE_STRIP, 0, _vertexData.size());
    _shaderProgram->disableAttributeArray("vertexPosition");
}

void Widget::update()
{
    if (_yRotation++ > 360.0)
        _yRotation = 0.0;
    _rotationMatrix.setToIdentity();
    _rotationMatrix.rotate(_yRotation, 0.0, 1.0, 0.0);
    
    updateGL();
}
