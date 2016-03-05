TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    BaiduTranslator.cpp \
    Translator.cpp \
    Utils.cpp \
    YoudaoTranslator.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    BaiduTranslator.h \
    Translator.h \
    Utils.h \
    YoudaoTranslator.h

LIBS += -lssl -lcrypto -lcurl -ljsoncpp -lboost_system -lboost_thread
