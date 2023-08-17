#-------------------------------------------------
#
# Project created by QtCreator 2023-04-14T14:00:13
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BookLibrary
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


SOURCES += \
        main.cpp \
    Admin/adminaddbook.cpp \
    Admin/adminadduser.cpp \
    Admin/adminbook.cpp \
    Admin/adminbrrecord.cpp \
    Admin/adminfunc.cpp \
    Admin/adminmoney.cpp \
    Admin/adminperson.cpp \
    Admin/adminreturnrecord.cpp \
    Admin/adminuser.cpp \
    Admin/adminwarn.cpp \
    Reader/readerbook.cpp \
    Reader/readerfunc.cpp \
    Reader/readerjy.cpp \
    Reader/readerorder.cpp \
    Reader/readerperson.cpp \
    Reader/readertop.cpp \
    Reader/readerwarn.cpp \
    SuperAdmin/adminmanagerwidget.cpp \
    SuperAdmin/superadduser.cpp \
    SuperAdmin/superfunc.cpp \
    SuperAdmin/superperson.cpp \
    SuperAdmin/supersysset.cpp \
    booklibrary.cpp \
    login.cpp \
    userregis.cpp \
    commdef.cpp \
    commdefclass.cpp \
    rwfile.cpp \
    mysqlfunc.cpp

HEADERS += \
    Admin/adminaddbook.h \
    Admin/adminadduser.h \
    Admin/adminbook.h \
    Admin/adminbrrecord.h \
    Admin/adminfunc.h \
    Admin/adminmoney.h \
    Admin/adminperson.h \
    Admin/adminreturnrecord.h \
    Admin/adminuser.h \
    Admin/adminwarn.h \
    Reader/readerbook.h \
    Reader/readerfunc.h \
    Reader/readerjy.h \
    Reader/readerorder.h \
    Reader/readerperson.h \
    Reader/readertop.h \
    Reader/readerwarn.h \
    SuperAdmin/adminmanagerwidget.h \
    SuperAdmin/superadduser.h \
    SuperAdmin/superfunc.h \
    SuperAdmin/superperson.h \
    SuperAdmin/supersysset.h \
    booklibrary.h \
    login.h \
    userregis.h \
    allhead.h \
    commdef.h \
    commdefclass.h \
    rwfile.h \
    mysqlfunc.h \
    customtabstyle.h

FORMS += \
    Admin/adminaddbook.ui \
    Admin/adminadduser.ui \
    Admin/adminbook.ui \
    Admin/adminbrrecord.ui \
    Admin/adminfunc.ui \
    Admin/adminmoney.ui \
    Admin/adminperson.ui \
    Admin/adminreturnrecord.ui \
    Admin/adminuser.ui \
    Admin/adminwarn.ui \
    Reader/readerbook.ui \
    Reader/readerfunc.ui \
    Reader/readerjy.ui \
    Reader/readerorder.ui \
    Reader/readerperson.ui \
    Reader/readertop.ui \
    Reader/readerwarn.ui \
    SuperAdmin/adminmanagerwidget.ui \
    SuperAdmin/superadduser.ui \
    SuperAdmin/superfunc.ui \
    SuperAdmin/superperson.ui \
    SuperAdmin/supersysset.ui \
    booklibrary.ui \
    login.ui \
    userregis.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/mysql/lib/ -llibmysql
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/mysql/lib/ -llibmysqld

INCLUDEPATH += $$PWD/mysql/include
DEPENDPATH += $$PWD/mysql/include

RESOURCES += \
    booklibrary.qrc
