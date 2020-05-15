#-------------------------------------------------
#
# Project created by QtCreator 2019-03-24T15:40:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trie
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    trienode.cpp \
    trie.cpp \
    dialoginitialize.cpp \
    dialogsearch.cpp \
    interactiveview.cpp \
    dialogsize.cpp \
    threaddataform.cpp \
    threadfileini.cpp \
    threadsortfrequency.cpp \
    trieshow.cpp \
    windowsort.cpp \
    windowfile.cpp \
    dialoginsert.cpp \
    completewinnertree.cpp \
    threadsortinsidefrequency.cpp \
    completewinnertree.cpp \
    dialoginitialize.cpp \
    dialoginsert.cpp \
    dialogsearch.cpp \
    dialogsize.cpp \
    double_array_trie.cpp \
    interactiveview.cpp \
    main.cpp \
    mainwindow.cpp \
    threaddataform.cpp \
    threadfileini.cpp \
    threadsortfrequency.cpp \
    threadsortinsidefrequency.cpp \
    trie.cpp \
    trienode.cpp \
    trieshow.cpp \
    utils.cpp \
    windowfile.cpp \
    windowsort.cpp

HEADERS += \
        mainwindow.h \
    trienode.h \
    trie.h \
    stacknode.h \
    dialoginitialize.h \
    dialogsearch.h \
    interactiveview.h \
    sortitem.h \
    dialogsize.h \
    threaddataform.h \
    threadfileini.h \
    threadsortfrequency.h \
    trieshow.h \
    windowsort.h \
    windowfile.h \
    dialoginsert.h \
    completewinnertree.h \
    firstplayer.h \
    winnertree.h \
    threadsortinsidefrequency.h \
    completewinnertree.h \
    dialoginitialize.h \
    dialoginsert.h \
    dialogsearch.h \
    dialogsize.h \
    double_array_trie.h \
    firstplayer.h \
    interactiveview.h \
    mainwindow.h \
    sortitem.h \
    stacknode.h \
    threaddataform.h \
    threadfileini.h \
    threadsortfrequency.h \
    threadsortinsidefrequency.h \
    trie.h \
    trienode.h \
    trieshow.h \
    utils.h \
    windowfile.h \
    windowsort.h \
    winnertree.h

FORMS += \
        mainwindow.ui \
    dialoginitialize.ui \
    dialogsearch.ui \
    dialogsize.ui \
    trieshow.ui \
    windowsort.ui \
    windowfile.ui \
    dialoginsert.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
