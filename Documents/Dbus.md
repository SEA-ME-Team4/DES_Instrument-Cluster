# Dbus

## Table of Contents

### [Dbus Server Registration](#1-dbus-server-registration)

### [Send Sensor Data to Dbus](#2-send-sensor-data-to-dbus)

### [Get Data from Dbus](#3-get-data-from-dbus)

---

# 1. Dbus Server Registration

## in `/register_server`

### Step 1. Code C++ file for Dbus Object

- We organized `carinformation.h` and `carinformation.cpp`  which are including variables and methods.

### Step 2. Compile C++ to xml

- Parse the C++ header file(`carinformation.h`) containing a QObject-derived class and produce the D-bus introspection XML.

```bash
qdbuscpp2xml -M -S carinformation.h -o carinformation.xml  
```

### Step 3. Add xml

- Add `carinformation.xml` file to `register_server.pro` file.

```bash
DBUS_ADAPTORS += carinformation.xml
```

- If you build this program, `carinformation_adaptor.h` is automatically generated.
- If you modify xml, you should **clean** and **rebuild**.

### Step4. main.cpp

- Declare CarInformation Object as `carinfo`

```cpp
CarInformation *carinfo = new CarInformation();
```

- Expose interface by `CarInformationAdaptor` (inherit `QDBusAbstractAdaptor`).
- with this, method of `carinfo` can called by Dbus.

```cpp
new CarInformationAdaptor(carinfo);
```

- Register Service and Object to Dbus

```cpp
QDBusConnection connection = QDBusConnection::sessionBus(); // Connect sessionBus 
connection.registerObject("/CarInformation", carinfo) // Register Object 
connection.registerService("org.team4.Des02") // Register service(Bus's name)
```

---

# 2. Send sensor data to Dbus

## in `/sender`

- We used **python** to send data such as speed, battery and brake.
- To use dbus in python, we installed `dbus-python`.

```bash
pip install dbus-python 
```

- Import `dbus` and `dbus.service` in **python**

```bash
import dbus
import dbus.service
```

- Connect with an interface which is placed in Dbus.
- If the server is not registered, it occurs an error.

```python
bus = dbus.SessionBus() # Connect with sessionBus
service = bus.get_object("org.team4.Des02", "/CarInformation") # Connect with Object by information of service and object path
car_interface = dbus.Interface(service, "org.team4.Des02.CarInformation") # Link interface with Object
```

- send data to Dbus.
- By using interface we can access to method of Object(`carinformation`).

```python
car_interface.setSpeed(speed_data)
```

---

# 3. Get data from Dbus

## in `/instrument_cluster`

### Step1. Copy carinformation.xml

- Copy `carinformation.xml` from `/register_server`.

### Step 2. Add xml

- Add `carinformation.xml` file to `instrument_cluster.pro` file.

```bash
DBUS_INTERFACES += carinformation.xml
```

- If you build this program, `carinformation_interface.h` is automatically generated.
- If you modify xml, you should **clean** and **rebuild**.

### Step 3. Set interface

- Without registering server, project of `instrument_cluster` can’t get information of **interface** from Dbus.
- So we include xml file to `instrument_cluster`, and it could notice which **interface will be registered.\**

- Declare in `car2qml.h`.
- `org::team4::Des02::CarInformation` is placed in `carinformation_interface.h`.

```cpp
org::team4::Des02::CarInformation *interface;
```

- Definition in `car2qml.cpp`.

```python
interface = new org::team4::Des02::CarInformation("org.team4.Des02", "/CarInformation", QDBusConnection::sessionBus());
```

### Step 4. Get data

- We can get data by `interface`.

```cpp
speed = interface->call("getSpeed");
```

- We can also check if the `interface` is valid or not.

```cpp
void Car2Qml::checkDbusValid()
{
    if (!interface->isValid() && dbusstatus==false) {
        dbusstatus = true;
        emit dbusstatusChanged(true);
    }
    else if (interface->isValid() && dbusstatus==true) {
        dbusstatus = false;
        emit dbusstatusChanged(false);
    }
}
```

---

### Reference

1. [D-Bus API Design Guidelines](https://dbus.freedesktop.org/doc/dbus-api-design.html)
2. [Qt D-Bus](https://doc.qt.io/qt-5/qtdbus-index.html)
3. [QDBusAbstractAdaptor Class](https://doc.qt.io/qt-5/qdbusabstractadaptor.html)
