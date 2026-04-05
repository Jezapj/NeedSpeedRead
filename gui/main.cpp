#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCoreApplication>

#include "backend/document_controller.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    backend::DocumentController controller;
    engine.rootContext()->setContextProperty("controller", &controller);

#ifdef QT_DEBUG
    engine.load(QUrl::fromLocalFile(
        QCoreApplication::applicationDirPath() + "/qml/Main.qml"
    ));
#else
    engine.loadFromModule("NeedSpeedRead", "Main"); // For Release Build
#endif

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
