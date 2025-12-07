
#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <thread>
#include <chrono>
#include <ctime>
#include <cmath>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;


const char* DB_FILE = "eduvault_db.dat";
const string ADMIN_PASS = "Aditya@123";


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"


class Utils {
public:
    static void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    }

    static void delay(int ms) {
    #ifdef _WIN32
        Sleep(ms);
    #else
        usleep(ms * 1000);
    #endif
    }

    static void printHeader(string title) {
        clearScreen();
        cout << CYAN << BOLD << "============================================================" << RESET << endl;
        cout << CYAN << BOLD << "   E D U V A U L T  |  " << title << RESET << endl;
        cout << CYAN << BOLD << "============================================================" << RESET << endl;
    }

    static void pause() {
        cout << "\nPress Enter to return...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    static void loadingBar(string task) {
        cout << YELLOW << task << " ";
        for (int i = 0; i < 20; i++) {
            cout << "▓";
            cout.flush();
            delay(30);
        }
        cout << GREEN << " [DONE]" << RESET << endl;
        delay(300);
    }
};

class Student {
private:
    int id;
    char name[50];
    char branch[10];
    float cgpa;
    float attendance;
    char badge[20];
    char ai_skill[50];

public:
    Student() {
        id = 0;
        cgpa = 0.0;
        attendance = 0.0;
        strcpy(name, "Unknown");
        strcpy(branch, "N/A");
        strcpy(badge, "None");
        strcpy(ai_skill, "Pending Analysis");
    }

    void calculateBadge() {
        if (cgpa >= 9.0 && attendance > 90) strcpy(badge, "ELITE SCHOLAR");
        else if (cgpa >= 8.0) strcpy(badge, "RISING STAR");
        else if (attendance < 75) strcpy(badge, "RISK ALERT");
        else strcpy(badge, "REGULAR");
    }

    void generateAISkill() {
        string b(branch);
        string skill;

        if (b == "CSE") skill = (cgpa > 8.5) ? "AI/ML Architect" : "Web Developer";
        else if (b == "ECE") skill = (cgpa > 8.5) ? "Embedded Designer" : "IoT Specialist";
        else if (b == "ME") skill = (cgpa > 8.5) ? "Robotics Eng." : "CAD Designer";
        else skill = "Data Analyst";

        strcpy(ai_skill, skill.c_str());
    }

    void input() {
        cout << "\n" << BOLD << ">>> INPUT DATA MODULE" << RESET << endl;
        cout << "ID: ";
        while (!(cin >> id)) {
            cout << RED << "Invalid ID. Enter numbers only: " << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        cout << "Name: ";
        cin.getline(name, 50);

        cout << "Branch (CSE/ECE/ME): ";
        cin.getline(branch, 10);

        cout << "CGPA (0-10): ";
        cin >> cgpa;

        cout << "Attendance (%): ";
        cin >> attendance;

        calculateBadge();
        generateAISkill();

        cout << GREEN << "✓ AI Skill Assigned: [" << ai_skill << "]" << RESET << endl;
        Utils::delay(500);
    }

    void displayRow() const {
        string color = GREEN;
        if (attendance < 75) color = RED;
        else if (cgpa > 9.0) color = CYAN;

        cout << left << setw(8) << id
             << setw(20) << name
             << setw(10) << branch
             << setw(8) << cgpa
             << color << setw(12) << attendance << RESET
             << setw(18) << badge
             << setw(20) << ai_skill << endl;
    }

    int getId() const { return id; }
    float getCgpa() const { return cgpa; }
    float getAttendance() const { return attendance; }
    string getName() const { return name; }
    string getBadge() const { return badge; }
};

class EduVaultSystem {
public:
    EduVaultSystem() {
        ofstream file(DB_FILE, ios::binary | ios::app);
        file.close();
    }

    bool login() {
        Utils::printHeader("ADMIN LOGIN");
        string pass;
        cout << "Enter Admin Password: ";
        cin >> pass;

        Utils::loadingBar("Verifying Credentials");

        if (pass == ADMIN_PASS) {
            cout << GREEN << "\nAccess Granted." << RESET << endl;
            Utils::delay(800);
            return true;
        } else {
            cout << RED << "\nAccess Denied!" << RESET << endl;
            Utils::delay(1000);
            return false;
        }
    }

    void addStudent() {
        Student s;
        s.input();

        ofstream file(DB_FILE, ios::binary | ios::app);
        file.write(reinterpret_cast<char*>(&s), sizeof(Student));
        file.close();

        cout << GREEN << "\nRecord Saved Successfully!" << RESET << endl;
        Utils::delay(800);
    }

    void viewAll() {
        Utils::printHeader("DATABASE VIEW");
        ifstream file(DB_FILE, ios::binary);
        Student s;
        bool found = false;

        cout << BOLD << "------------------------------------------------------------------------------------------------" << endl;
        cout << left << setw(8) << "ID" << setw(20) << "NAME" << setw(10) << "BRANCH"
             << setw(8) << "CGPA" << setw(12) << "ATT(%)"
             << setw(18) << "BADGE" << setw(20) << "AI SKILL" << endl;
        cout << "------------------------------------------------------------------------------------------------" << RESET << endl;

        while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
            s.displayRow();
            found = true;
        }

        file.close();
        if (!found) cout << YELLOW << "\n[EMPTY DATABASE]" << RESET << endl;

        Utils::pause();
    }

    void searchStudent() {
        int targetId;
        cout << "\nEnter ID to search: ";
        cin >> targetId;

        ifstream file(DB_FILE, ios::binary);
        Student s;
        bool found = false;

        cout << BOLD << "\nSearching..." << RESET << endl;
        while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
            if (s.getId() == targetId) {
                Utils::printHeader("PROFILE MATCH");
                cout << BOLD << "------------------------------------------------------------------------------------------------" << endl;
                cout << left << setw(8) << "ID" << setw(20) << "NAME" << setw(10) << "BRANCH"
                     << setw(8) << "CGPA" << setw(12) << "ATT(%)"
                     << setw(18) << "BADGE" << setw(20) << "AI SKILL" << endl;
                cout << "------------------------------------------------------------------------------------------------" << RESET << endl;
                s.displayRow();
                found = true;
                break;
            }
        }

        if (!found) cout << RED << "\nStudent with ID " << targetId << " not found!" << RESET << endl;
        Utils::pause();
    }

    void analyticsDashboard() {
        Utils::printHeader("ANALYTICS");

        ifstream file(DB_FILE, ios::binary);
        Student s;

        int count = 0;
        float totalCgpa = 0;
        int alerts = 0;
        int elites = 0;

        while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
            count++;
            totalCgpa += s.getCgpa();
            if (s.getAttendance() < 75) alerts++;
            if (s.getBadge() == string("ELITE SCHOLAR")) elites++;
        }
        file.close();

        if (count == 0) {
            cout << YELLOW << "No records available for analysis.\n" << RESET;
        } else {
            cout << BOLD << "Total Students   : " << RESET << count << endl;
            cout << BOLD << "Average CGPA     : " << RESET << fixed << setprecision(2) << totalCgpa / count << endl;
            cout << BOLD << "Elite Scholars   : " << CYAN << elites << RESET << endl;
            cout << BOLD << "Attendance Alerts: " << RED << alerts << RESET << endl;
        }

        Utils::pause();
    }
};

int main() {
#ifdef _WIN32
    system("color 07");
#endif

    EduVaultSystem eduvault;

    if (!eduvault.login()) return 0;

    int choice;
    while (true) {
        Utils::printHeader("MAIN MENU");
        cout << "1. Register Student\n";
        cout << "2. View All\n";
        cout << "3. Search Student\n";
        cout << "4. Analytics Dashboard\n";
        cout << "5. Exit\n";
        cout << "\nChoice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "Invalid input! Please enter a number." << RESET << endl;
            Utils::delay(1000);
            continue;
        }

        switch (choice) {
            case 1: eduvault.addStudent(); break;
            case 2: eduvault.viewAll(); break;
            case 3: eduvault.searchStudent(); break;
            case 4: eduvault.analyticsDashboard(); break;
            case 5:
                Utils::loadingBar("Shutting down");
                return 0;
            default:
                cout << RED << "Invalid Option!" << RESET << endl;
                Utils::delay(500);
        }
    }
}