QT += dbus widgets

DBUS_INTERFACES += carinformation.xml
FORMS += controller.ui
HEADERS += controller.h
SOURCES += main.cpp controller.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/dbus/remotecontrolledcar/controller
INSTALLS += target
