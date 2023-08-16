# Connect CPP to QML

## CPP Property setting

### 1. In `car2qml.h`, we set `variable`, `status of variable` and `status of dbus` connection.

```cpp
QDBusReply<qreal> speed;
QDBusReply<qreal> battery;
QDBusReply<qreal> temp;
QDBusReply<bool> brake;

bool speedstatus;
bool batterystatus;
bool tempstatus;
bool brakestatus;

bool dbusstatus;
```

- `variable` is declared as `QDBusReply`, which means that `variable` will be updated by Dbus Interface.

 

### 2. To Expose Attributes of C++ Types to QML, we used `Q_PROPERTY` macro.

```cpp
Q_PROPERTY(qreal speed READ getSpeed)
Q_PROPERTY(qreal battery READ getBattery)
Q_PROPERTY(qreal temp READ getTemp)
Q_PROPERTY(bool brake READ getBrake)

Q_PROPERTY(bool speedstatus READ getSpeedStatus CONSTANT)
Q_PROPERTY(bool batterystatus READ getBatteryStatus CONSTANT)
Q_PROPERTY(bool tempstatus READ getTempStatus CONSTANT)
Q_PROPERTY(bool brakestatus READ getBrakeStatus CONSTANT)

Q_PROPERTY(bool dbusstatus READ getDbusStatus CONSTANT)
```

- It looks like name in `Q_PROPERTY` and name of `variable` is same, but they are different.
- `Name` in `Q_PROPERTY` is used for exposing to QML and used as property name.
- `READ` associate function (`getVariable`) with property (`Name`).
- (Optional) `WRITE` can be used for set value of property.
- `CONSTANT` is for preventing `depends on non-NOTIFYable properties` error.

 

## Connect to QML

### 1. Expose C++ types to QML in `main.cpp`

```cpp
qmlRegisterType<Car2Qml>("Car2Qml", 1, 0, "Car2Qml");
```

### 2. Declare in QML

(1) Import `Car2Qml` Class as Property of QML in `instrumentCluster.qml`

```jsx
 import Car2Qml 1.0
```

(2) Define Property and Connect Signal of Class in `instrumentCluster.qml`

```jsx
Car2Qml{
        id: carinfo

        onSpeedChanged: {instrumentcluster.speed = carinfo.speed}
        onBatteryChanged: {instrumentcluster.battery = carinfo.battery}
        onTempChanged: {instrumentcluster.temp = carinfo.temp}
        onBrakeChanged: {instrumentcluster.brake = carinfo.brake}

        onSpeedstatusChanged: {instrumentcluster.speed_timeout = status}
        onBatterystatusChanged: {instrumentcluster.battery_timeout = status}
        onTempstatusChanged: {instrumentcluster.temp_timeout = status}
        onBrakestatusChanged: {instrumentcluster.brake_timeout = status}

        onDbusstatusChanged: {instrumentcluster.dbus_timeout = status}

    }
```

- As we set in `car2qml.h` by using `Q_PROPERTY` macro, we can access to `getVariable` and `getVaraibleStatus` functions by `Name` in `Q_PROPERTY`.
- However, we only update `variable property` by using `Q_PROPERTY`.
- `variableStatus property` is updated by signal.

### 3. About property Initialization  in `instrumentCluster.qml`

```jsx
property int speed: 0
property int battery: 0
property int temp: 0
property bool brake: false

property bool speed_timeout: carinfo.speedstatus
property bool battery_timeout: carinfo.batterystatus
property bool temp_timeout: carinfo.tempstatus
property bool brake_timeout: carinfo.brakestatus

property bool dbus_timeout: carinfo.dbusstatus
```

- Here, `getVaraibleStatus` is used for initialization.
- In this way, we can detect sender status when application starts.

---

## **Reference**

1. [Exposing Attributes of C++ Types to QML](https://doc.qt.io/qt-5/qtqml-cppintegration-exposecppattributes.html)
2. [QQmlEngine Class (qmlRegisterType)](https://doc.qt.io/qt-6/qqmlengine.html#qmlRegisterType)
3. [QDBusReply Class](https://doc.qt.io/qt-5/qdbusreply.html)
