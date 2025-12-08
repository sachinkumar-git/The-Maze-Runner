# 🎓 EduVault: Intelligent Student Management System

**EduVault** is a terminal-based Student Database Management System written in C++. It goes beyond simple data storage by automatically analyzing student performance to assign badges and predict suitable AI career paths.

## 🚀 Key Features

### 1. 🔐 Secure Access
* **Admin Authentication:** The system is protected by a login layer.
* **Default Password:** `admin123`

### 2. 📊 Automated Analytics
The system automatically calculates attributes based on raw data:
* **Smart Badge System:**
    * 🌟 **ELITE SCHOLAR:** CGPA ≥ 9.0 & Attendance > 90%
    * ⭐ **RISING STAR:** CGPA ≥ 8.0
    * ⚠️ **RISK ALERT:** Attendance < 75%
* **AI Career Prediction:** Assigns skills (e.g., "Robotics Eng.", "Web Developer") based on Branch + CGPA logic.

### 3. 💾 Persistent Storage
* Uses **File Handling (`fstream`)** to save data permanently.
* Data is stored in `nexus_db.dat`.
* Data remains available even after closing the program.

### 4. 🎨 Visual Interface
* **ANSI Color Codes:** Color-coded outputs for warnings (Red), success (Green), and elites (Cyan).
* **Loading Animations:** Custom loading bars and transitions.

## 🛠️ Tech Stack
* **Language:** C++ (Standard 11+)
* **Concepts:** OOP (Classes/Objects), File I/O, Vectors.
* **Cross-Platform:** Works on Windows (`windows.h`) and Linux/macOS (`unistd.h`).

## 💻 How to Run

1.  **Compile:**
    ```bash
    g++ -o nexus nexus_main.cpp
    ```

2.  **Execute:**
    * **Windows:** `nexus.exe`
    * **Linux/Mac:** `./nexus`

3.  **Login:**
    * Enter Password: `admin123`
