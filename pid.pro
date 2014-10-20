TARGET = pid
TEMPLATE = app

DEFINES += BOOST_ASIO_DYN_LINK
win32 {
    DEFINES += WIN32_LEAN_AND_MEAN
}

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += libtorrent-rasterbar
}
win32 {
    load(moc)
    QMAKE_MOC = $$QMAKE_MOC -DBOOST_TT_HAS_OPERATOR_HPP_INCLUDED
    LIBS += -LC:/boost/lib -lpsapi\
            -LC:/libtorrent-rasterbar-1.0.2/bin/msvc-12.0/release/address-model-64/architecture-x86/boost-link-shared/boost-source/resolve-countries-off/threading-multi -ltorrent
    INCLUDEPATH += C:/boost/include/boost-1_56\
                   C:/libtorrent-rasterbar-1.0.2/include
}

QT += qml quick sql network multimediawidgets

SOURCES += src/main.cpp\
           src/pid.cpp\
	   src/password.cpp\
	   src/update.cpp\
	   src/tcpSocket.cpp\
           src/torrent.cpp\
           src/videoplayer.cpp

HEADERS += src/pid.h\
           src/password.h\
           src/update.h\
           src/tcpSocket.h\
           src/torrent.h\
           src/videoplayer.h

RESOURCES += resources.qrc
RC_FILE += resources/images/pid/icon.rc

unix {
#QMAKE_HOST.arch = x86
    #...
#QMAKE_HOST.arch = x86_64
    QMAKE_LFLAGS += -Wl,--rpath=/usr/lib64/pid
}

unix {
    target.path = /usr/bin/
    config.path = $$(HOME)/.pid
    config.files = .pid/*
    #config.extra = mkdir $$(HOME)/.pid -m 744 -p && chown $$(USER).users $$(HOME)/.pid -R
    INSTALLS += target config
}
win32 {
    target.path = C:\PID
    config.path = C:\PID\.pid
    update.path = C:\PID\.pid\
    config.files += .pid\*
    update.files = src\scripts\update\win32\update.bat
    INSTALLS += target config update
}
