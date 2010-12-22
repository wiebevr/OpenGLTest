#include <QApplication>
#include "widget.h"
#include <QWidget>
#include <QVBoxLayout>

#define PARENT_WIDGET

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
#ifdef PARENT_WIDGET
    QWidget parentWidget;
    QVBoxLayout *layout = new QVBoxLayout(&parentWidget);
    parentWidget.showFullScreen();
#endif
    Widget widget;
#ifdef PARENT_WIDGET
    layout->addWidget(&widget);
    parentWidget.show();
#else
    widget.show();
#endif
    
    return app.exec();
}
