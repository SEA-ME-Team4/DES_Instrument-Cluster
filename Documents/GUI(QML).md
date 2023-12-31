# GUI (QML)

## ****Table of Contents****

### [LCD window](#1-lcd-window)

### [Flow of GUI](#2-flow-and-relation-between-qml-files)

### [Display by Status](#3-display-by-status)

---

# 1. LCD window

<img src = "https://github.com/SEA-ME/SEA-ME-course-book/assets/97211801/658aecc0-0895-4b53-94e0-f36aa14efdd6" width="90%" height="90%">



---

# 2. Flow and Relation between QML files

<p align="center"><img src = "/Documents/QMLArchitecture.svg" width="80%" height="80%"></p>

---

# 3. Display by Status

### 1. **D-Bus and Sender is Stable (without temperature sender)**
    
<img src = "https://github.com/SEA-ME/SEA-ME-course-book/assets/97211801/aa9b5e41-38ad-4eb6-b799-fd71ed29dfd9" width="80%" height="80%">

- The `StateIndicator` lights up white without temperature.
 
### 2. **All sensor turn on (with temperature)**
    
<img src = "https://github.com/SEA-ME/SEA-ME-course-book/assets/97211801/0f3ed479-bb7b-4d27-a031-feb2216d03c1" width="80%" height="80%">
    
- All `StateIndicator` are illuminated in white.
- `Gear` remains `N` because `speed` is zero and `brake` is off.

### 3. **Disconnect D-Bus (DbusTimeout Occured)**
    
<img src = "https://github.com/SEA-ME/SEA-ME-course-book/assets/97211801/b05ae43f-104a-4a3b-a18b-b141e5df5e65" width="80%" height="80%">
    
- All `StatusIndicator` are illuminated in red.

### 4. **Positive Speed with No Brake**
    
<img src = "https://github.com/SEA-ME/SEA-ME-course-book/assets/97211801/550705e4-59de-458f-9871-34d43a343ede" width="80%" height="80%">
    
- The `StateIndicator` are illuminated in white.
- `Gear-D` light up white with `CenterCar` because of positive `speed` and `brake` off.

### 5. **Zero Speed with Brake**
    
<img src = "https://github.com/SEA-ME/SEA-ME-course-book/assets/97211801/26d56bd8-8d48-4622-a804-12e4cd957914" width="80%" height="80%">
    
- `Gear-P` light up white because of zero `speed` and `brake` on.
- `CenterCar` emits red light because `brake` is on.

### 6. **Negative Speed with Brake**
    
<img src = "https://github.com/SEA-ME/SEA-ME-course-book/assets/97211801/d469fe20-546b-409d-9669-5cc0b14cb1ba" width="80%" height="80%">
    
- `Gear-R` light up white because of negative `speed`.
- In our project, `Brake` is treated same with reverse manipulation, so in reverse, `CenterCar` emits red light.
 
---

## Reference

- [Qt Quick Ultralite Automotive Cluster Demo (Image Source)](https://doc.qt.io/QtForMCUs-2.5/quickultralite-automotive-example.html)
- [Indicator Image (Icon Source)](https://www.flaticon.com/kr/free-icons/)
