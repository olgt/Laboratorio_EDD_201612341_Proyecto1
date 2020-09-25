QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Arbol_AVL.cpp \
        Cabecera.cpp \
        Lista_Niveles.cpp \
        Matriz.cpp \
        Nodo_Matriz.cpp \
        Nodo_Nivel.cpp \
        Nodo_Objeto.cpp \
        arbol_binario.cpp \
        cargador_proyectos.cpp \
        cargador_save.cpp \
        cargadorreportes.cpp \
        lista_puntos.cpp \
        main.cpp \
        menuPrincipal.cpp \
        menueditarnivel.cpp \
        menueditarnivel2.cpp \
        nodo_binario.cpp \
        nodo_puntos.cpp \
        nodoarbol.cpp \
        utilities.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Arbol_AVL.h \
    Cabecera.h \
    Lista_Niveles.h \
    Matriz.h \
    Nodo_Matriz.h \
    Nodo_Nivel.h \
    Nodo_Objeto.h \
    arbol_binario.h \
    cargador_proyectos.h \
    cargador_save.h \
    cargadorreportes.h \
    lista_puntos.h \
    menuPrincipal.h \
    menueditarnivel.h \
    menueditarnivel2.h \
    nodo_binario.h \
    nodo_puntos.h \
    nodoarbol.h \
    utilities.h
