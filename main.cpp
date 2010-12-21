#include <QApplication>
#include "widget.h"
#include <QWidget>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget parentWidget;
    QVBoxLayout *layout = new QVBoxLayout(&parentWidget);
    parentWidget.showFullScreen();

    Widget widget;
    layout->addWidget(&widget);
    parentWidget.show();

    
    return app.exec();
}
