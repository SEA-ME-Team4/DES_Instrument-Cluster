# Exception Handling

## Table of Contents

### 1. [TIMER](https://www.notion.so/Exception-Handling-79058715db0b423d95118a507c0c7bab?pvs=21)

### 2. [Register Server](https://www.notion.so/Exception-Handling-79058715db0b423d95118a507c0c7bab?pvs=21)

### 3. [Car2Qml](https://www.notion.so/Exception-Handling-79058715db0b423d95118a507c0c7bab?pvs=21)

### 4. [Instrument Cluster](https://www.notion.so/Exception-Handling-79058715db0b423d95118a507c0c7bab?pvs=21)

# TIMER

- Our system use Multiple Timer. First one is  `system_timer` in `register_server` and Second one is `app_timer` in `Car2Qml`, and these timer have different purposes.
- The purpose of `system_timer` is to check Senders are working correctly on time. Also, It emits signal for updating variables in application. So, It needs to be more faster than refresh rate of display.
- In this way, Multiple application can share this fast (expensive) timer together.
- `app_timer` is woking for check validity of Dbus Interface. It cannot be accomplished just with `system_timer`. Without `app_timer`, when `register_server` is broken, we cannot detect and display the status of `Interface` (Dbus status). Based on the purpose of `app_timer`, it doesn’t need to be fast, so we set slow (also cheap) timer here.

# 1. register_server

## (1) VariableStatusTimer

- **Initialized** in `carinformation.h`.

```cpp
QElapsedTimer speed_timer;
QElapsedTimer battery_timer;
QElapsedTimer temp_timer;
QElapsedTimer brake_timer;
```

- It **starts** in Constructor of  `carinformation.cpp`.

```cpp
speed_timer.start();
battery_timer.start();
temp_timer.start();
brake_timer.start();
```

- It **restarts** when `setVariable` is called.

```cpp
void CarInformation::setSpeed(qreal speed)
{
    this->speed = speed;
    speed_timer.restart();
}

void CarInformation::setBattery(qreal battery)
{
    this->battery = battery;
    battery_timer.restart();
}

void CarInformation::setTemp(qreal temp)
{
    this->temp = temp;
    temp_timer.restart();
}

void CarInformation::setBrake(bool brake)
{
    this->brake = brake;
    brake_timer.restart();
}
```

## (2) SystemTimer

- In `carinformation.h`, we set `system_timer`.

```cpp
QTimer *system_timer;
```

- This `system_timer` is initialized in `carinformation.cpp`.

```cpp
system_timer = new QTimer(this);
system_timer->start(1000.0f/120.0f);
```

- And Connect `timout` signal of `system_timer` with `onTimespend` slot.

```cpp
connect(system_timer, SIGNAL(timeout()), this, SLOT(onTimeSpend()));
```

- `onTimespend` is also declared in `carinformation.cpp`.

```cpp
void CarInformation::onTimeSpend()
{
    if (speed_timer.elapsed()>MAX_INTERVAL && speed_status==false) {
        speed_status = true;
        emit speedTimeout(true);
    }
    else if (speed_timer.elapsed()<=MAX_INTERVAL && speed_status==true) {
        speed_status = false;
        emit speedTimeout(false);
    }

    if (battery_timer.elapsed()>MAX_INTERVAL && battery_status==false) {
        battery_status = true;
        emit batteryTimeout(true);
    }
    else if (battery_timer.elapsed()<=MAX_INTERVAL && battery_status==true) {
        battery_status = false;
        emit batteryTimeout(false);
    }

    if (temp_timer.elapsed()>MAX_INTERVAL && temp_status==false) {
        temp_status = true;
        emit tempTimeout(true);
    }
    else if (temp_timer.elapsed()<=MAX_INTERVAL && temp_status==true) {
        temp_status = false;
        emit tempTimeout(false);
    }

    if (brake_timer.elapsed()>MAX_INTERVAL && brake_status==false) {
        brake_status = true;
        emit brakeTimeout(true);
    }
    else if (brake_timer.elapsed()<=MAX_INTERVAL && brake_status==true) {
        brake_status = false;
        emit brakeTimeout(false);
    }

    emit sendTimeSpend();
}
```

`elapsed` returns the number of milliseconds since this VariableStatusTimer was last started (or restarted).

So elapsed time is compared with `MAX_INTERVAL`, and check `variable_status` is changed or not.

If timer and status satisfied condition (which means Timeout is occured), `emit variableTimeout` with `true`. If not, `emit variableTimeout` with `false`.

`sendTimeSpend` is emitted with every `timeout` of `system_timer`. It is just for update display.

# 2. Car2Qml

## (1) VariableStatus

- In `car2qml.cpp`, `variableTimeout` signal is connected to `setVariableStatus` .

```cpp
connect(interface, SIGNAL(speedTimeout(bool)), this, SLOT(setSpeedStatus(bool)));
connect(interface, SIGNAL(batteryTimeout(bool)), this, SLOT(setBatteryStatus(bool)));
connect(interface, SIGNAL(tempTimeout(bool)), this, SLOT(setTempStatus(bool)));
connect(interface, SIGNAL(brakeTimeout(bool)), this, SLOT(setBrakeStatus(bool)));
```

- `setVariableStatus` is also declared in `car2qml.cpp`.

```cpp
void Car2Qml::setSpeedStatus(bool status)
{
    speedstatus = status;
    emit speedstatusChanged(status);
}

void Car2Qml::setBatteryStatus(bool status)
{
    batterystatus = status;
    emit batterystatusChanged(status);
}

void Car2Qml::setTempStatus(bool status)
{
    tempstatus = status;
    emit tempstatusChanged(status);
}

void Car2Qml::setBrakeStatus(bool status)
{
    brakestatus = status;
    emit brakestatusChanged(status);
}
```

So, with `timeout` signal of `system_timer` in `register_server`, `setVariableStatus` in `car2qml` emits `variableStatusChanged` signal.

## (2) AppTimer

- In `car2qml.h`, we set `app_timer`.

```cpp
QTimer *app_timer;
```

- This `app_timer` is initialized in `car2qml.cpp`.

```cpp
app_timer = new QTimer(this);
app_timer->start(1000);
```

- And Connect `timout` signal of `app_timer` with `checkDbusValid` slot.

```cpp
connect(app_timer, SIGNAL(timeout()), this, SLOT(checkDbusValid()));
```

- `checkDbusValid` is declared in `car2qml.cpp`.

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

`checkDbusValid` works similar to `onTimespend` in `carinformation.cpp`.

But this function use `isValid` for check `interface`(Dbus status).

It emits `dbusstatusChanged` signal with boolean decided by if statement.

# 3. Instrument Cluster

- In `InstrumentCluster.qml`, `Car2Qml` is property that makes qml can connect with cpp.

```cpp
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

`variableStatusChanged` and `dbusstatusChanged` is connected with `variable_timout` and `dbus_timeout`. 

---

## **Reference**

1. [QElapsedTimer Class](https://doc.qt.io/qt-5/qelapsedtimer.html#QElapsedTimer)
2. [QTimer Class](https://doc.qt.io/qt-5/qtimer.html)
