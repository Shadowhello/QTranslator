#include "BaiduTranslator.h"
#include "YoudaoTranslator.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQuick>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<BaiduTranslator>("Trans", 1, 0, "BaiduTranslator");
    qmlRegisterType<YoudaoTranslator>("Trans", 1, 0, "YoudaoTranslator");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
