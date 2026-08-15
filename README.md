# 🏠 Terminal-Based Smart Home Simulator

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Terminal-black?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

> A fully functional terminal-based Smart Home System built in **C++**, simulating
> real-world home automation with AI logic, security engines, and live dashboard
> rendering — all inside the console.

---

## 📌 Table of Contents
- [About The Project](#-about-the-project)
- [Features](#-features)
- [System Architecture](#-system-architecture)
- [Room Configuration](#-room-configuration)
- [How To Run](#-how-to-run)
- [Project Structure](#-project-structure)
- [Concepts Used](#-concepts-used)
- [Screenshots](#-screenshots)
- [Author](#-author)

---

## 📖 About The Project

This project simulates a **Smart Home Management System** entirely in the terminal.  
The user can configure multiple rooms, control devices (lights, AC, fans, cameras, locks),  
and run either an **AI Automatic Mode** or a full **Manual Control Mode**.

Built as a **university-level C++ project** demonstrating:
- Dynamic Memory Management
- 2D Matrix-based State Tracking
- Pointer Manipulation
- File I/O for Data Persistence
- Real-time Dashboard Rendering

---

## ✨ Features

| Feature | Description |
|---|---|
| 🤖 **AI Automatic Mode** | AI controls all devices based on room conditions |
| 🕹️ **Manual Control Mode** | Full manual override for every device in every room |
| 📊 **Live Dashboard** | Real-time terminal dashboard showing all room states |
| 🔒 **Security Engine** | Auto-lockdown on gas leak detection (>80%) |
| 💡 **Smart Lighting** | Auto ON/OFF based on room occupancy |
| ❄️ **AC Automation** | Auto temperature control based on room temp |
| 🚿 **Water Temp Control** | Smart hot/cold water for Kitchen & Bathroom |
| 📷 **Camera System** | Auto-activates on unknown person detection |
| 💾 **File Persistence** | Saves system state to `home_config.txt` |
| 🔧 **Hardware Repair** | Repair broken rooms through manual command |
| ⚠️ **Gas Hazard Detector** | Real-time hazard monitoring per room |
| 📝 **Security Log** | Dynamic auto-growing log system for alerts |

---

## 🏗️ System Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                  SMART HOME SYSTEM CORE                      │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│   USER INPUT                                                 │
│       │                                                      │
│       ▼                                                      │
│  ┌─────────────┐      ┌─────────────────────────────────┐   │
│  │  MAIN MENU  │────▶ │        AUTOMATIC MODE           │   │
│  │             │      │  • AI Presence Detection        │   │
│  │  1. Auto    │      │  • Smart AC Control             │   │
│  │  2. Manual  │      │  • Auto Lighting                │   │
│  │  3. Exit    │      │  • Camera Activation            │   │
│  └─────────────┘      │  • Water Temp Management        │   │
│       │               └─────────────────────────────────┘   │
│       │               ┌─────────────────────────────────┐   │
│       └─────────────▶ │         MANUAL MODE             │   │
│                       │  • Light Control                │   │
│                       │  • AC Adjustment                │   │
│                       │  • Presence Override            │   │
│                       │  • Hazard Simulation            │   │
│                       │  • Hardware Repair              │   │
│                       │  • LCD / Fan / Lock Control     │   │
│                       │  • Water Temp Override          │   │
│                       └─────────────────────────────────┘   │
│                                    │                         │
│                                    ▼                         │
│                    ┌───────────────────────────┐             │
│                    │   2D MATRIX STATE ENGINE  │             │
│                    │   int** house_matrix      │             │
│                    │   [rooms][12 columns]     │             │
│                    └───────────────────────────┘             │
│                                    │                         │
│                    ┌───────────────┴───────────┐             │
│                    ▼                           ▼             │
│         ┌─────────────────┐       ┌──────────────────┐      │
│         │  LIVE DASHBOARD │       │   FILE SAVE I/O  │      │
│         │  (Terminal UI)  │       │ home_config.txt  │      │
│         └─────────────────┘       └──────────────────┘      │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

### 📦 2D Matrix Column Map

```
house_matrix[room][column]
│
├── [0]  Presence     →  0=Empty      1=Unknown    2=Owner
├── [1]  Lock         →  0=Unlocked   1=Locked     2=Lockdown
├── [2]  Light        →  0=OFF        1=ON
├── [3]  AC Power     →  0=OFF        1=ON
├── [4]  AC Target    →  Temperature in °C
├── [5]  Room Temp    →  Current temperature in °C
├── [6]  LCD Screen   →  0=OFF        1=ON         2=MUTED
├── [7]  Hazard       →  Gas leak percentage (0-100%)
├── [8]  Camera       →  0=Standby    1=Recording
├── [9]  Status       →  0=BROKEN     1=Online
├── [10] Water Temp   →  Kitchen & Bathroom only (°C)
└── [11] Fan          →  0=OFF        1=ON
```

### ⚙️ Automation Engine Flow

```
runAutomationEngines() called every frame
│
├── STEP 1: HAZARD CHECK (Always runs first)
│   └── if Hazard > 80%
│       ├── Status   = BROKEN
│       ├── Lock     = LOCKDOWN
│       ├── Fan      = OFF
│       ├── Light    = ON (Emergency)
│       └── Log Alert added to Security Log
│
├── STEP 2: AUTO MODE RULES (if Automatic Mode ON)
│   ├── Presence == Owner  → Lock = UNLOCKED
│   ├── Presence == Empty  → Lock = LOCKED
│   ├── Temp >= 32°C       → AC ON, Target = 22°C
│   ├── Temp <= 24°C       → AC Target = 26°C
│   ├── Presence == Empty  → Light OFF, Fan OFF, LCD OFF
│   ├── Presence == Unknown → Camera = RECORDING
│   └── Water Temp:
│       ├── Temp <= 20°C   → Water = 40°C (Winter Mode)
│       └── Temp >= 30°C   → Water = 20°C (Summer Mode)
│
└── STEP 3: ROOM-SPECIFIC RULES
    ├── Bathroom  → No AC / No Fan / No LCD / No Camera
    ├── Kitchen   → No LCD / Has Water Temp / Has Camera
    └── Normal    → Full feature set enabled
```

---

## 🏠 Room Configuration

```
Total Rooms → User-defined (minimum 3 required)

┌────────────────────────────────────────────────────┐
│  Room 1   │  User-defined name  │  Full control    │
│  Room 2   │  User-defined name  │  Full control    │
│    ...    │        ...          │      ...         │
│  Room N-1 │  AUTO = Kitchen     │  No LCD          │
│  Room N   │  AUTO = Bathroom    │  No AC/Fan/LCD   │
└────────────────────────────────────────────────────┘
```

> ⚠️ Last room is **always Bathroom**.  
> ⚠️ Second last room is **always Kitchen**.  
> Both are auto-configured by the system — no manual naming needed.

---

## ▶️ How To Run

### ✅ Requirements
- Any C++ compiler → `g++`, `MSVC`, or `MinGW`
- Terminal / Command Prompt / VS Code

### 🐧 Linux / Mac
```bash
g++ -o smart_home smart_home.cpp
./smart_home
```

### 🪟 Windows (MinGW / CMD)
```bash
g++ -o smart_home.exe smart_home.cpp
smart_home.exe
```

### 💻 VS Code
```
1. Open folder in VS Code
2. Press Ctrl + Shift + B  →  Build
3. Open Terminal  →  Run executable
```

### 🎮 First Run Example
```
=== SMART HOME SYSTEM INSTALLATION ===
Enter total number of rooms in the house: 4

--- Room Configuration Engine ---
Enter name for Room 1: Living Room
Enter name for Room 2: Bedroom
[System] Room 3 automatically configured as 'Kitchen'.
[System] Room 4 automatically configured as 'Bathroom'.
```

---

## 📁 Project Structure

```
terminal-smart-home-simulator/
│
├── 📄 smart_home.cpp        ←  Main source code (all logic inside)
├── 📄 home_config.txt       ←  Auto-generated save file (after first run)
├── 📄 README.md             ←  Project documentation (this file)
├── 📄 LICENSE               ←  MIT License
└── 📄 .gitignore            ←  C++ gitignore rules
```

---

## 🧠 Concepts Used

| Concept | Where Used |
|---|---|
| `int** house_matrix` | 2D dynamic array for all room states |
| `new` / `delete[]` | Heap allocation and cleanup |
| `string* &logs` | Pointer by reference — auto-growing log array |
| `ofstream` | File I/O — saving system state to disk |
| `getline()` | Safe string input for room names |
| `switch-case` | Manual control command decoder |
| `while` + `cin.clear()` | Input validation loops |
| `continue` | Skip broken rooms in automation loop |
| Modular Functions | 7 separate function blocks for clean design |

### 🔍 Code Block Map

```
smart_home.cpp
│
├── BLOCK 1 → printPaddedText()       Text padding utility
├── BLOCK 2 → addSecurityLog()        Dynamic log array manager
├── BLOCK 3 → displayDashboard()      Live terminal UI renderer
├── BLOCK 4 → setRealisticDefaults()  Startup state initializer
├── BLOCK 5 → runAutomationEngines()  AI + Security logic core
├── BLOCK 6 → saveSystemState()       File I/O persistence
└── BLOCK 7 → main()                  Master control executive loop
```

---

## 📸 Screenshots

### 🖥️ Live Dashboard View
```
=============================================================================================================================
||                                              SMART HOME LIVE DASHBOARD                                                  ||
=============================================================================================================================
ID  Room Name      Presence  Lock      Status  Light   Fan   AC Pwr  Temp/Trgt   LCD     Camera      Hazard  Water
-----------------------------------------------------------------------------------------------------------------------------
1   Living Room    Owner     UNLOCKED  Online  ON      ON    ON      30C/22C     ON      Standby     0%      N/A
2   Bedroom        Empty     LOCKED    Online  OFF     OFF   OFF     22C/0C      OFF     Standby     0%      N/A
3   Kitchen        Owner     UNLOCKED  Online  ON      ON    ON      30C/22C     N/A     Standby     0%      25C
4   Bathroom       Empty     LOCKED    Online  OFF     N/A   N/A     22C         N/A     N/A         0%      25C
=============================================================================================================================
```

### 🎛️ Manual Control Terminal
```
--- MANUAL CONTROL TERMINAL ---
1. Light Control       6. LCD Control
2. AC Adjust           7. Door Lock Control
3. Presence Adjust     8. Bathroom/Kitchen Water Temp
4. Hazard Control      9. Fan Control
5. Hardware Repair    10. Return to Main Menu
Enter command:
```

### 🚨 Emergency Lockdown Trigger
```
[HAZARD DETECTED] Gas leak at 85% in Kitchen!
EMERGENCY: High Gas Leak Alert! System Lockdown triggered.
Status  → BROKEN
Lock    → LOCKDOWN
Fan     → OFF (prevent gas spread)
Light   → ON  (emergency alert)
```

---

## 👨‍💻 Author

**Hasnain Tahir**

[![GitHub](https://img.shields.io/badge/GitHub-hasnaintahir99--dev-black?style=flat-square&logo=github)](https://github.com/hasnaintahir99-dev)

---

## 📄 License

This project is licensed under the **MIT License**.  
See the [LICENSE](LICENSE) file for full details.

---

<div align="center">

**⭐ If you found this project helpful, please give it a star! ⭐**

*"Built with logic, powered by C++"* 🚀

</div>
```

---

