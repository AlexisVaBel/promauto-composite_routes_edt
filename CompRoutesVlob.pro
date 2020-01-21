QT       += core gui widgets
CONFIG   +=c++17
TARGET   = CompRoutes
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++14



SOURCES += \
    controller/routeconf.cpp \
    controller/routesall.cpp \
    controller/subrouteconf.cpp \
    controller/uitodbtable.cpp \
    dataimpl/ibppdataprovider.cpp \
    main.cpp \
    ibpp/core/all_in_one.cpp \
    mainwindow.cpp \
    visual/buttonpanel.cpp \
    visual/routesui.cpp


INCLUDEPATH +=ibpp/core


win32{
    DEFINES += IBPP_WINDOWS=1
}else{
    DEFINES += IBPP_LINUX=1
    INCLUDEPATH += /opt/firebird/include
    LIBS += -L/opt/firebird/lib -lfbclient
    INCLUDEPATH +=/opt/boost/boost_build/include
    LIBS+= -L/opt/boost/boost_build/lib  -lboost_system
}

HEADERS += \
    common/userinput.h \
    controller/routeconf.h \
    controller/routesall.h \
    controller/subrouteconf.h \
    controller/uitodbtable.h \
    dataiface/idataprovider.h \
    dataimpl/ibppdataprovider.h \
    domain/columnnode.h \
    domain/roots.h \
    domain/sqlholder.h \
    mainwindow.h \
    visual/buttonpanel.h \
    visual/routesui.h

