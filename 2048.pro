QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    changepswd.cpp \
    checkerboard.cpp \
    classes.cpp \
    forget.cpp \
    front.cpp \
    gameS3.cpp \
    gameS4.cpp \
    gameS5.cpp \
    gameS6.cpp \
    gameS7.cpp \
    gameS8.cpp \
    gift.cpp \
    giftsetting.cpp \
    help.cpp \
    history.cpp \
    home.cpp \
    intString.cpp \
    logon.cpp \
    main.cpp \
    login.cpp \
    manage.cpp \
    online.cpp \
    rankboard.cpp \
    security.cpp \
    style.cpp \
    systemsetting.cpp \
    timethread.cpp \
    verificationCode.cpp \
    version.cpp

HEADERS += \
    admin.h \
    changepswd.h \
    checkerboard.h \
    classes.h \
    forget.h \
    front.h \
    gameS3.h \
    gameS4.h \
    gameS5.h \
    gameS6.h \
    gameS7.h \
    gameS8.h \
    gift.h \
    giftsetting.h \
    help.h \
    history.h \
    home.h \
    implementation.h \
    login.h \
    logon.h \
    manage.h \
    online.h \
    rankboard.h \
    security.h \
    systemsetting.h \
    timethread.h \
    version.h

FORMS += \
    admin.ui \
    changepswd.ui \
    forget.ui \
    front.ui \
    gameS3.ui \
    gameS4.ui \
    gameS5.ui \
    gameS6.ui \
    gameS7.ui \
    gameS8.ui \
    gift.ui \
    giftsetting.ui \
    help.ui \
    history.ui \
    home.ui \
    login.ui \
    logon.ui \
    manage.ui \
    online.ui \
    rankboard.ui \
    security.ui \
    systemsetting.ui \
    version.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

RC_ICONS = myappico.ico
