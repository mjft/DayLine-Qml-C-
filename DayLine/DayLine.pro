QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

RESOURCES += qml.qrc \
    ../icon.qrc

TRANSLATIONS += \
    DayLine_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$quote(C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\SDK\ScopeCppSDK\vc15\SDK\include\ucrt)
LIBS += -L$$quote(C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\SDK\ScopeCppSDK\vc15\SDK\lib)

HEADERS +=

DISTFILES +=
