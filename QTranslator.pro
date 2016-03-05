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

linux {
LIBS += -lssl -lcrypto -lcurl -ljsoncpp -lboost_system -lboost_thread
}

win32 {
        INCLUDEPATH += $$PWD/../../../libraries/boost/include
        INCLUDEPATH += $$PWD/../../../libraries/openssl/include
        INCLUDEPATH += $$PWD/../../../libraries/jsoncpp/include
        INCLUDEPATH += $$PWD/../../../libraries/curl-7.47.1/builds/libcurl-vc12-x86-debug-dll-ipv6-sspi-winssl/include

        LIBS += -L$$PWD/../../../libraries/boost/lib
        #LIBS += -LC:/libraries/openssl/lib
        #LIBS += -LC:/libraries/jsoncpp/build/src/lib_json/Debug
        #LIBS += -LC:/libraries/curl-7.47.1/builds/libcurl-vc12-x86-debug-dll-ipv6-sspi-winssl/lib
        #LIBS +=  -lboost_system-vc120-mt-gd-1_60 -lboost_thread-vc120-mt-gd-1_60

        LIBS += $$PWD/../../../libraries/boost/lib/libboost_system-vc120-mt-gd-1_60.lib \
                $$PWD/../../../libraries/boost/lib/libboost_thread-vc120-mt-gd-1_60.lib \

        LIBS += $$PWD/../../../libraries/openssl/lib/libeay32.lib \
                $$PWD/../../../libraries/openssl/lib/ssleay32.lib

        LIBS += $$PWD/../../../libraries/jsoncpp/build/src/lib_json/Debug/jsoncpp.lib
        LIBS += $$PWD/../../../libraries/curl-7.47.1/builds/libcurl-vc12-x86-debug-dll-ipv6-sspi-winssl/lib/libcurl_debug.lib
}
