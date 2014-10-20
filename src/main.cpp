#include "pid.h"

#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQuickView *view = new QQuickView(QUrl("qrc:/src/qml/main.qml"));
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->setIcon(QIcon("qrc:/resources/images/pid/icon.png"));

    PID pid;
    pid.set_root_object(view->rootObject());
    pid.container = QWidget::createWindowContainer(view);
    pid.container->setFocusPolicy(Qt::TabFocus);
    pid.layout->addWidget(pid.container);

    view->rootContext()->setContextProperty("cppSignals", &pid);

    pid.showFullScreen();

    return app.exec();
}
