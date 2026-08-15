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
- [Room Configuration & State Matrix](#-room-configuration--state-matrix)
- [Core Logic & Rules Engine](#-core-logic--rules-engine)
- [How To Run](#-how-to-run)
- [Project Structure](#-project-structure)
- [Concepts Used](#-concepts-used)
- [Live Terminal Dashboard Preview](#-live-terminal-dashboard-preview)
- [Author](#-author)

---

## 📖 About The Project

This project simulates an integrated **Smart Home Management System** entirely within the terminal. It provides deep architectural control over an arbitrary number of rooms, handling dynamic telemetry data, environmental sensors, automated safety measures, and granular manual overrides.

Built as an advanced **C++ Systems Project** demonstrating:
- Dynamic Heap Memory Management with Raw Double Pointers
- 2D Matrix-based State Tracking Engine
- Amortized Array Resizing for Security Telemetry
- File I/O for State Persistence
- Real-time Column-Formatted Console Dashboard

---

## ✨ Features

| Feature | Description |
|---|---|
| 🤖 **AI Automatic Mode** | Automated sensor reaction engine controlling AC, fans, lights, and locks based on real-time presence. |
| 🕹️ **Manual Control Mode** | Granular interactive CLI command terminal to override device states per room. |
| 📊 **Live Telemetry Dashboard** | Formatted tabular display rendering continuous updates across all rooms and parameters. |
| 🔒 **Critical Cyber/Hazard Shield** | Automated lockdown protocol and incident logging triggered when gas hazard ratio exceeds 80%. |
| 💡 **Occupancy-Driven Lighting** | Intelligent light actuation tied directly to motion sensors and room occupancy state. |
| ❄️ **Climate Control System** | Dynamic target temperature calibration and compressor switching based on thermal metrics. |
| 🚿 **Dual-Zone Water Management** | Automated summer/winter water temperature adjustment exclusively for Kitchen and Bathroom. |
| 📷 **Intruder Camera System** | Automatic camera activation upon detecting unidentified/unknown persons in active zones. |
| 💾 **State Persistence** | Complete house matrix serialization to `home_config.txt` upon clean system exit. |
| 🔧 **Hardware Maintenance Engine** | Built-in diagnostics and reset capabilities to restore offline or malfunctioning room controllers. |

---

## 🏠 Room Configuration & State Matrix

The house is modeled using a dynamic 2D array (`int** house_matrix`), where each row represents a distinct room and each column maps directly to a hardware actuator or sensor state:

### State Column Mapping (`house_matrix[i][j]`)

| Column Index | Identifier | Data Representation / Possible Values |
|---|---|---|
| `0` | `COL_PRESENCE` | `0`: Empty, `1`: Unknown Person, `2`: Owner |
| `1` | `COL_LOCK` | `0`: Unlocked, `1`: Locked, `2`: Lockdown |
| `2` | `COL_LIGHT` | `0`: OFF, `1`: ON |
| `3` | `COL_AC_POWER` | `0`: OFF, `1`: ON |
| `4` | `COL_AC_TARGET` | Target Temperature in Celsius (`16°C - 30°C`) |
| `5` | `COL_TEMP` | Current Ambient Temperature in Celsius |
| `6` | `COL_LCD` | `0`: OFF, `1`: ON, `2`: Muted |
| `7` | `COL_HAZARD` | Environmental Hazard / Gas Leak (`0% - 100%`) |
| `8` | `COL_CAMERA` | `0`: Standby, `1`: Recording |
| `9` | `COL_STATUS` | `0`: Broken / Offline, `1`: Online |
| `10` | `COL_WATER_TEMP`| Water Line Temperature in Celsius |
| `11` | `COL_FAN` | `0`: OFF, `1`: ON |

### Special Room Constraints
- **Normal Rooms (Index `0` to `N-3`)**: Support full features (AC, Fan, LCD, Lights, Camera).
- **Kitchen (Index `N-2`)**: LCD is hard-disabled (`N/A`). Water temperature control enabled.
- **Bathroom (Index `N-1`)**: AC, Fan, LCD, and Cameras are restricted (`N/A`). Dedicated water temperature control enabled.

---

## ⚙️ Core Logic & Rules Engine

### 1. Safety & Hazard Protocol (Priority Override)
- If `COL_HAZARD > 80%`:
  - Room status set to **BROKEN** (`COL_STATUS = 0`).
  - Door status set to **LOCKDOWN** (`COL_LOCK = 2`).
  - Ventilation shut down (`COL_FAN = 0`).
  - Incident appended to dynamic security audit log heap buffer.

### 2. Automatic Presence & Surveillance Rules
- **Owner Present (`2`)**: Unlocks doors, enables lights.
- **Empty Room (`0`)**: Locks doors, turns off lights, fans, and LCD displays.
- **Unknown Presence (`1`)**: Activates security cameras into **RECORDING** mode.

### 3. Thermal Management
- If `COL_TEMP >= 32°C`: AC turns **ON** and target sets to `22°C`.
- If `COL_TEMP <= 24°C`: AC target relaxes to `26°C`.
- If `COL_TEMP > 26°C`: Ventilation fans automatically turn **ON**.

---

## 🚀 How To Run

### Prerequisites
- GCC / G++ compiler supporting **C++11** or higher.
- Terminal / Command Prompt.

### Compilation & Execution

#### Linux / macOS
```bash
# 1. Compile source code
g++ -std=c++11 main.cpp -o smart_home_sim

# 2. Run executable
./smart_home_sim

```

#### Windows (MinGW / Command Prompt / PowerShell)

```cmd
:: 1. Compile source code
g++ -std=c++11 main.cpp -o smart_home_sim.exe

:: 2. Run executable
smart_home_sim.exe

```

---

## 📁 Project Structure

```text
terminal-smart-home-simulator/
├── main.cpp              # Core source code containing system engines, dashboard, and main loop
├── .gitignore            # Ignores build artifacts, executables, and config files
├── home_config.txt       # Auto-generated persistent matrix state file (generated at runtime)
└── README.md             # Project documentation and specifications

```

---

## 🧠 Concepts Used

* **Dynamic Memory Allocation**: Manual heap allocation using raw pointers (`new` and `delete[]`) for jagged 2D matrices and runtime-allocated string arrays.
* **Pointer-by-Reference & Auto-Growing Arrays**: Dynamic doubling strategy ($O(1)$ amortized insertion) implemented in `addSecurityLog` to resize security event buffers without memory leaks.
* **Defensive Resource Cleanup**: Comprehensive memory deallocation loops to ensure zero heap leaks upon process termination.
* **Matrix-Based Telemetry**: Tabular data structure modeling real-world IoT hardware nodes.
* **Formatted Stream Output**: Custom text-padding formatting engine for aligning CLI columns dynamically.
* **File Serialization / Deserialization**: Low-level stream serialization for saving matrix states across application lifecycles.

---

## 📸 Live Terminal Dashboard Preview

```text
=============================================================================================================================
||                                                SMART HOME LIVE DASHBOARD                                                ||
=============================================================================================================================
ID  Room Name      Presence  Lock      Status  Light   Fan   AC Pwr  Temp/Trgt   LCD     Camera      Hazard  Water   
-----------------------------------------------------------------------------------------------------------------------------
1   Master Bed     Owner     UNLOCKED  Online  ON      ON    ON      30C/22C     ON      Standby     0%      N/A     
2   Living Room    Empty     LOCKED    Online  OFF     OFF   OFF     22C/0C      OFF     Standby     0%      N/A     
3   Kitchen        Empty     LOCKED    Online  OFF     OFF   OFF     22C/0C      N/A     Standby     0%      25C     
4   Bathroom       Owner     UNLOCKED  Online  ON      N/A   N/A     30C         N/A     N/A         0%      25C     
=============================================================================================================================

```

---

## 👤 Author

**Hafiz Hasnain Tahir**

* **GitHub**: [@hasnaintahir99-dev](https://github.com/hasnaintahir99-dev)
* **Domain**: Cyber Security & Software Development

```

```
