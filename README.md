# 🏠 Terminal-Based Smart Home Simulator

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Terminal-black?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

> A fully functional terminal-based Smart Home System built in **C++**, simulating real-world home automation with AI logic, security engines, and live dashboard rendering — all inside the console.

---

## 📌 Table of Contents
- [About The Project](#-about-the-project)
- [Features](#-features)
- [System Architecture](#-system-architecture)
- [How To Run](#-how-to-run)
- [Project Structure](#-project-structure)
- [Concepts Used](#-concepts-used)
- [Screenshots](#-screenshots)
- [Author](#-author)

---

## 📖 About The Project

This project simulates a **Smart Home Management System** entirely in the terminal.
The user can configure multiple rooms and control devices like lights, AC, fans, cameras, and locks — using either an **AI Automatic Mode** or a full **Manual Control Mode**.

Built as a **university-level C++ project** demonstrating:
- Dynamic Memory Management
- 2D Matrix-based State Tracking
- Pointer Manipulation
- File I/O for Data Persistence
- Real-time Terminal Dashboard Rendering

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
| 🚿 **Water Temp Control** | Smart hot/cold water for Kitchen and Bathroom |
| 📷 **Camera System** | Auto-activates on unknown person detection |
| 💾 **File Persistence** | Saves system state to `home_config.txt` |
| 🔧 **Hardware Repair** | Repair broken rooms through manual command |
| ⚠️ **Gas Hazard Detector** | Real-time hazard monitoring per room |
| 📝 **Security Log** | Dynamic auto-growing log system for alerts |

---

## 🏗️ System Architecture

```
┌──────────────────────────────────────────────┐
│           SMART HOME SYSTEM CORE             │
├──────────────────────────────────────────────┤
│                                              │
│  USER INPUT                                  │
│      │                                       │
│      ▼                                       │
│  ┌──────────┐    ┌────────────────────────┐  │
│  │   MENU   │───▶│    AUTOMATIC MODE      │  │
│  │ 1. Auto  │    │  • AI Presence Logic   │  │
│  │ 2. Manual│    │  • Smart AC & Lighting │  │
│  │ 3. Exit  │    │  • Camera Activation   │  │
│  └──────────┘    │  • Water Temp Control  │  │
│      │           └────────────────────────┘  │
│      │           ┌────────────────────────┐  │
│      └──────────▶│     MANUAL MODE        │  │
│                  │  • Light / Fan / AC    │  │
│                  │  • Lock / LCD / Camera │  │
│                  │  • Hazard / Repair     │  │
│                  │  • Water Temp Override │  │
│                  └────────────────────────┘  │
│                           │                  │
│                           ▼                  │
│              ┌────────────────────────┐      │
│              │  2D MATRIX ENGINE      │      │
│              │  int** house_matrix    │      │
│              │  [rooms × 12 columns]  │      │
│              └────────────────────────┘      │
│                    │             │           │
│                    ▼             ▼           │
│           ┌──────────────-┐ ┌──────────────┐ │
│           │ LIVE DASHBOARD│ │ FILE SAVE I/O│ │
│           │ (Terminal UI) │ │home_config   │ │
│           └──────────────-┘ └──────────────┘ │
└──────────────────────────────────────────────┘
```

### 📦 2D Matrix Column Map

```
house_matrix[room][column]
│
├── [0]  Presence   →  0=Empty     1=Unknown   2=Owner
├── [1]  Lock       →  0=Unlocked  1=Locked    2=Lockdown
├── [2]  Light      →  0=OFF       1=ON
├── [3]  AC Power   →  0=OFF       1=ON
├── [4]  AC Target  →  Temperature in C
├── [5]  Room Temp  →  Current temperature in C
├── [6]  LCD        →  0=OFF       1=ON        2=MUTED
├── [7]  Hazard     →  Gas leak percentage (0-100)
├── [8]  Camera     →  0=Standby   1=Recording
├── [9]  Status     →  0=BROKEN    1=Online
├── [10] Water Temp →  Kitchen and Bathroom only
└── [11] Fan        →  0=OFF       1=ON
```

### ⚙️ Automation Engine Flow

```
runAutomationEngines()
│
├── STEP 1: HAZARD CHECK (Always First)
│   └── Hazard > 80%
│       ├── Status = BROKEN
│       ├── Lock   = LOCKDOWN
│       ├── Fan    = OFF
│       └── Light  = ON (Emergency)
│
├── STEP 2: AUTO MODE RULES
│   ├── Owner present   → Lock = UNLOCKED
│   ├── Room empty      → Lock = LOCKED
│   ├── Temp >= 32C     → AC ON, Target = 22C
│   ├── Unknown person  → Camera = RECORDING
│   └── Water Temp:
│       ├── Temp <= 20C → Water = 40C (Winter)
│       └── Temp >= 30C → Water = 20C (Summer)
│
└── STEP 3: ROOM RULES
    ├── Bathroom → No AC, No Fan, No LCD
    ├── Kitchen  → No LCD, Has Water Temp
    └── Normal   → Full feature set
```

---

## ▶️ How To Run

### Requirements
- C++ compiler — `g++` (MinGW on Windows, GCC on Linux/Mac)
- Terminal or Command Prompt

### Compile & Run

**Linux / macOS**
```bash
g++ -std=c++11 smart_home.cpp -o smart_home
./smart_home
```

**Windows (CMD or PowerShell)**
```bash
g++ -std=c++11 smart_home.cpp -o smart_home.exe
smart_home.exe
```

**VS Code**
```
Open smart_home.cpp → Click ▶ Run button (top right)
```

> **Note:** No pre-built binary is included. Compile from source using the commands above.

---

## 📁 Project Structure

```
terminal-smart-home-simulator/
│
├── smart_home.cpp      ← Complete source code
├── home_config.txt     ← Auto-generated on first run
├── README.md           ← Project documentation
├── LICENSE             ← MIT License
└── .gitignore          ← C++ gitignore
```

---

## 🧠 Concepts Used

| Concept | Where Used |
|---|---|
| `int** house_matrix` | 2D dynamic array for all room states |
| `new` / `delete[]` | Heap allocation and deallocation |
| `string* &logs` | Pointer by reference — auto-growing log array |
| `ofstream` | File I/O to save system state |
| `getline()` | Safe string input for room names |
| `switch-case` | Manual control command decoder |
| `while` + `cin.clear()` | Input validation |
| Modular Functions | 7 clean function blocks |

### 🔍 Code Block Map

```
smart_home.cpp
│
├── BLOCK 1 → printPaddedText()       Text padding utility
├── BLOCK 2 → addSecurityLog()        Dynamic log manager
├── BLOCK 3 → displayDashboard()      Terminal UI renderer
├── BLOCK 4 → setRealisticDefaults()  Startup initializer
├── BLOCK 5 → runAutomationEngines()  AI and security core
├── BLOCK 6 → saveSystemState()       File I/O handler
└── BLOCK 7 → main()                  Master control loop
```

---

## 📸 Screenshots

### 🖥️ Live Dashboard
```
===========================================================================================================================
||                                         SMART HOME LIVE DASHBOARD                                                     ||
===========================================================================================================================
ID  Room Name      Presence  Lock      Status  Light  Fan  AC Pwr  Temp/Trgt  LCD   Camera     Hazard  Water
---------------------------------------------------------------------------------------------------------------------------
1   Living Room    Owner     UNLOCKED  Online  ON     ON   ON      30C/22C    ON    Standby    0%      N/A
2   Bedroom        Empty     LOCKED    Online  OFF    OFF  OFF     22C/0C     OFF   Standby    0%      N/A
3   Kitchen        Owner     UNLOCKED  Online  ON     ON   ON      30C/22C    N/A   Standby    0%      25C
4   Bathroom       Empty     LOCKED    Online  OFF    N/A  N/A     22C        N/A   N/A        0%      25C
===========================================================================================================================
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

### 🚨 Emergency Lockdown
```
EMERGENCY: High Gas Leak Alert! System Lockdown triggered.
Status → BROKEN   |   Lock → LOCKDOWN
Fan    → OFF      |   Light → ON (Emergency)
```

---

## 👨‍💻 Author

**Hafiz Hasnain Tahir**

[![GitHub](https://img.shields.io/badge/GitHub-hasnaintahir99--dev-black?style=flat-square&logo=github)](https://github.com/hasnaintahir99-dev)

---

## 📄 License

This project is licensed under the **MIT License** — see [LICENSE](LICENSE) for details.

---

<div align="center">

**⭐ If you found this helpful, please give it a star! ⭐**

*"Built with logic, powered by C++"* 🚀

</div>

