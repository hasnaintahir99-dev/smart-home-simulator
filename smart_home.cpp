#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// =====================================================================
// GLOBAL CONSTANTS FOR MATRIX COLUMNS
// These are simple names for array indexes to make code easy to read.
// =====================================================================
const int COL_PRESENCE   = 0;
const int COL_LOCK       = 1;  // 0=UNLOCKED, 1=LOCKED, 2=LOCKDOWN
const int COL_LIGHT      = 2;
const int COL_AC_POWER   = 3;
const int COL_AC_TARGET  = 4;
const int COL_TEMP       = 5;
const int COL_LCD        = 6;
const int COL_HAZARD     = 7;  // Gas leak percentage
const int COL_CAMERA     = 8;
const int COL_STATUS     = 9;  // 0=BROKEN, 1=Online
const int COL_WATER_TEMP = 10; // For Bathroom and Kitchen
const int COL_FAN        = 11; 

// =====================================================================
// BLOCK 1: UTILITY FUNCTIONS (TEXT PADDING ENGINE)
// =====================================================================
void printPaddedText(string text, int requiredWidth) {
    cout << text;
    int spacesToAdd = requiredWidth - text.length();
    for (int i = 0; i < spacesToAdd; i++) {
        cout << " ";
    }
}

// =====================================================================
// BLOCK 2: DYNAMIC MEMORY LOG MANAGEMENT (AUTO-GROWING ARRAY)
// POINTERS USE CASE: Passing pointer by reference & dynamic array resizing
// =====================================================================
void addSecurityLog(string* &logs, int &currentLogs, int &maxLogs, string newAlert) {
    if (currentLogs == maxLogs) { 
        int newSize = maxLogs * 2; 
        
        // POINTERS: Allocating new larger dynamic 1D array
        string* newLogArray = new string[newSize]; 
        
        // FILLING: Copying old log strings into the new array
        for (int i = 0; i < currentLogs; i++) {
            newLogArray[i] = logs[i]; 
        }
        
        // POINTERS & MEMORY CLEANUP: Deleting old array from heap
        delete[] logs; 
        logs = newLogArray; // Pointing to the new larger memory space
        maxLogs = newSize; 
    }
    logs[currentLogs++] = newAlert;
}

// =====================================================================
// BLOCK 3: TELEMETRY DISPLAY INTERFACE (LIVE DASHBOARD RENDERING)
// 2D ARRAY USE CASE: Accessing 2D array data row by row using double pointers
// =====================================================================
void displayDashboard(int** house, string* roomNames, int totalRooms) {
    cout << "\n=============================================================================================================================\n";
    cout << "||                                              SMART HOME LIVE DASHBOARD                                                  ||\n";
    cout << "=============================================================================================================================\n";
    
    // Printing Table Columns Headers
    printPaddedText("ID", 4);
    printPaddedText("Room Name", 15); 
    printPaddedText("Presence", 10);
    printPaddedText("Lock", 10);      
    printPaddedText("Status", 8);
    printPaddedText("Light", 8);
    printPaddedText("Fan", 6);        
    printPaddedText("AC Pwr", 8);
    printPaddedText("Temp/Trgt", 12);
    printPaddedText("LCD", 8);
    printPaddedText("Camera", 12);
    printPaddedText("Hazard", 8);      
    printPaddedText("Water", 8);      
    cout << "\n-----------------------------------------------------------------------------------------------------------------------------\n";

    // Loop through each room row to print its current matrix state
    for (int i = 0; i < totalRooms; i++) {
        printPaddedText(to_string(i + 1), 4); // Display room numbers starting from 1
        printPaddedText(roomNames[i], 15); 
        
        // 2D ARRAY ACCESSING: Accessing specific column index values of the 2D array matrix
        printPaddedText((house[i][COL_PRESENCE] == 0 ? "Empty" : (house[i][COL_PRESENCE] == 1 ? "Unknown" : "Owner")), 10);
        printPaddedText((house[i][COL_LOCK] == 0 ? "UNLOCKED" : (house[i][COL_LOCK] == 1 ? "LOCKED" : "LOCKDOWN")), 10);
        printPaddedText((house[i][COL_STATUS] == 1 ? "Online" : "BROKEN"), 8);
        printPaddedText((house[i][COL_LIGHT] == 0 ? "OFF" : "ON"), 8);
        
        // CONDITION 1: Check if this row is the Bathroom (Absolute Last Room)
        if (i == totalRooms - 1) {
            printPaddedText("N/A", 6);   // No Fan in Bathroom
            printPaddedText("N/A", 8);   // No AC in Bathroom
            printPaddedText(to_string(house[i][COL_TEMP]) + "C", 12); 
            printPaddedText("N/A", 8);   // No LCD in Bathroom
            printPaddedText("N/A", 12);  // No Camera in Bathroom
            printPaddedText(to_string(house[i][COL_HAZARD]) + "%", 8); 
            printPaddedText((to_string(house[i][COL_WATER_TEMP]) + "C"), 8); // Water Temp Enabled
        } 
        // CONDITION 2: Check if this row is the Kitchen (Second Last Room)
        else if (i == totalRooms - 2) {
            printPaddedText((house[i][COL_FAN] == 0 ? "OFF" : "ON"), 6); 
            printPaddedText((house[i][COL_AC_POWER] == 0 ? "OFF" : "ON"), 8);
            string tempText = to_string(house[i][COL_TEMP]) + "C/" + to_string(house[i][COL_AC_TARGET]) + "C";
            printPaddedText(tempText, 12);
            printPaddedText("N/A", 8);   // LCD turned OFF/Not Applicable for Kitchen
            printPaddedText((house[i][COL_CAMERA] == 0 ? "Standby" : "RECORDING"), 12);
            printPaddedText(to_string(house[i][COL_HAZARD]) + "%", 8); 
            printPaddedText((to_string(house[i][COL_WATER_TEMP]) + "C"), 8); // Water Temp Enabled
        }
        // CONDITION 3: Normal Rooms
        else {
            printPaddedText((house[i][COL_FAN] == 0 ? "OFF" : "ON"), 6); 
            printPaddedText((house[i][COL_AC_POWER] == 0 ? "OFF" : "ON"), 8);
            string tempText = to_string(house[i][COL_TEMP]) + "C/" + to_string(house[i][COL_AC_TARGET]) + "C";
            printPaddedText(tempText, 12);
            printPaddedText((house[i][COL_LCD] == 0 ? "OFF" : (house[i][COL_LCD] == 1 ? "ON" : "MUTED")), 8);
            printPaddedText((house[i][COL_CAMERA] == 0 ? "Standby" : "RECORDING"), 12);
            printPaddedText(to_string(house[i][COL_HAZARD]) + "%", 8); 
            printPaddedText("N/A", 8);   // No Water Temp in normal rooms
        }
        cout << "\n";
    }
    cout << "=============================================================================================================================\n";
}

// =====================================================================
// BLOCK 4: INITIALIZATION SUBSYSTEM (SET REALISTIC DEFAULTS)
// FILLING USE CASE: Overwriting 2D array entries with non-zero default values
// =====================================================================
void setRealisticDefaults(int** house, int totalRooms) {
    for (int i = 0; i < totalRooms; i++) {
        if (house[i][COL_STATUS] == 0) continue; 

        // FILLING: Populating matrix indexes based on odd/even rooms
        if (i % 2 == 0) {
            house[i][COL_PRESENCE] = 2; // Owner present
            house[i][COL_TEMP] = 30;    // Warm temp
            house[i][COL_LIGHT] = 1;    
        } else {
            house[i][COL_PRESENCE] = 0; // Empty room
            house[i][COL_TEMP] = 22;    // Cool temp
            house[i][COL_LIGHT] = 0;    
        }
        house[i][COL_WATER_TEMP] = 25;
    }
}

// =====================================================================
// BLOCK 5: AUTOMATION LOGIC CORE (AI & CYBER SECURITY ENGINES)
// =====================================================================
void runAutomationEngines(int** house, int totalRooms, string* &logs, int &logCount, int &maxLogs, bool isAutoMode) {
    for (int i = 0; i < totalRooms; i++) {
        
        // 1. CRITICAL CYBER HAZARD DETECTOR (Always active)
        if (house[i][COL_HAZARD] > 80) {
            house[i][COL_STATUS] = 0; 
            house[i][COL_LIGHT] = 1;  
            house[i][COL_LOCK] = 2;   
            house[i][COL_FAN] = 0;    
            addSecurityLog(logs, logCount, maxLogs, "EMERGENCY: High Gas Leak Alert! System Lockdown triggered.");
            continue; 
        }

        // 2. AUTOMATIC MODE RULES
        if (isAutoMode) {
            if (house[i][COL_PRESENCE] == 2) {
                house[i][COL_LOCK] = 0; 
            } else if (house[i][COL_PRESENCE] == 0) {
                house[i][COL_LOCK] = 1; 
            }

            // Automatic Water Temp Management (For both Kitchen and Bathroom)
            if (i == totalRooms - 1 || i == totalRooms - 2) { 
                if (house[i][COL_TEMP] <= 20) {
                    house[i][COL_WATER_TEMP] = 40; // Winter mode
                } else if (house[i][COL_TEMP] >= 30) {
                    house[i][COL_WATER_TEMP] = 20; // Summer mode
                }
            }

            // AI Rules for Normal Rooms and Kitchen (Excluding Bathroom completely from AC/Fan/Cam)
            if (i != totalRooms - 1) { 
                house[i][COL_CAMERA] = (house[i][COL_PRESENCE] == 1) ? 1 : 0; 
                
                if (house[i][COL_TEMP] >= 32) {
                    house[i][COL_AC_POWER] = 1; 
                    house[i][COL_AC_TARGET] = 22; 
                } else if (house[i][COL_TEMP] <= 24 && house[i][COL_AC_POWER] == 1) {
                    house[i][COL_AC_TARGET] = 26; 
                }

                if (house[i][COL_PRESENCE] == 0) {
                    house[i][COL_LIGHT] = 0; house[i][COL_LCD] = 0; house[i][COL_FAN] = 0;   
                } else {
                    house[i][COL_LIGHT] = 1;
                    if (house[i][COL_TEMP] > 26) house[i][COL_FAN] = 1;
                }
                
                // Enforce LCD always OFF in Kitchen
                if (i == totalRooms - 2) {
                    house[i][COL_LCD] = 0;
                }
            } else {
                // Bathroom automated lights
                if (house[i][COL_PRESENCE] == 0) house[i][COL_LIGHT] = 0;
                else house[i][COL_LIGHT] = 1;
            }
        }
    }
}

// =====================================================================
// BLOCK 6: FILE I/O SUBSYSTEM (DATA PERSISTENCE & BACKUP SYSTEM)
// =====================================================================
void saveSystemState(int** house, int totalRooms) {
    ofstream outFile("home_config.txt");
    outFile << totalRooms << endl;
    for (int i = 0; i < totalRooms; i++) {
        for (int j = 0; j < 12; j++) {
            outFile << house[i][j] << " ";
        }
        outFile << endl;
    }
    outFile.close();
}

// =====================================================================
// BLOCK 7: PROGRAM ENTRY POINT (MAIN CONTROL EXECUTIVE LOOP)
// =====================================================================
int main() {
    int totalRooms;
    
    // -----------------------------------------------------------------
    // MAIN SUB-BLOCK A: HARDWARE INITIALIZATION & INPUT VALIDATION
    // -----------------------------------------------------------------
    cout << "=== SMART HOME SYSTEM INSTALLATION ===\n";
    cout << "Enter total number of rooms in the house: ";
    
    // Minimum 3 rooms required now (At least 1 normal room + 1 Kitchen + 1 Bathroom)
    while (!(cin >> totalRooms) || totalRooms < 3) {
        cout << "[ERROR] Please enter a valid number (minimum 3 rooms required for House, Kitchen & Bathroom): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(); 

    // -----------------------------------------------------------------
    // MAIN SUB-BLOCK B: DYNAMIC ARRAYS ALLOCATION & POINTER INITIALIZATION
    // POINTERS & 2D ARRAY ALLOCATION: Allocating memory dynamically on the heap
    // -----------------------------------------------------------------
    
    // POINTERS & 2D ARRAY: Allocating an array of row pointers (int*)
    int** house_matrix = new int*[totalRooms];
    
    // POINTERS: Allocating dynamic 1D array for room name strings
    string* roomNames = new string[totalRooms]; 

    cout << "\n--- Room Configuration Engine ---\n";
    cout << "Note: Second last room is automatically the Kitchen, and the last room is the Bathroom.\n";
    
    // FILLING: Taking room names string input from user to populate the dynamic array
    for (int i = 0; i < totalRooms - 2; i++) {
        cout << "Enter name for Room " << i + 1 << ": ";
        getline(cin, roomNames[i]);
    }
    
    // FILLING: Directly assigning hardcoded trailing strings to tail elements
    roomNames[totalRooms - 2] = "Kitchen";
    roomNames[totalRooms - 1] = "Bathroom";
    cout << "[System] Room " << totalRooms - 1 << " automatically configured as 'Kitchen'.\n";
    cout << "[System] Room " << totalRooms << " automatically configured as 'Bathroom'.\n";

    // 2D ARRAY & POINTERS: Allocating 12 columns for each single row pointer
    for (int i = 0; i < totalRooms; i++) {
        house_matrix[i] = new int[12]; 
        
        // FILLING: Resetting all matrix indices to baseline zero values
        for (int j = 0; j < 12; j++) {
            house_matrix[i][j] = 0; 
        }
        
        // FILLING: Instantiating active state values for critical status parameters
        house_matrix[i][COL_STATUS] = 1; 
        house_matrix[i][COL_TEMP] = 25;  
        house_matrix[i][COL_LOCK] = 1; 
    }
    
    // POINTERS: Allocating basic log container pointer array
    int logCount = 0, maxLogs = 2; 
    string* securityLogs = new string[maxLogs];

    // FILLING: Triggering realistic sample configurations mapping
    setRealisticDefaults(house_matrix, totalRooms);

    // -----------------------------------------------------------------
    // MAIN SUB-BLOCK C: PRIMARY UI MENU LOOP
    // -----------------------------------------------------------------
    int mainMode = 0;
    while (mainMode != 3) { 
        cout << "\n=====================================\n";
        cout << "        MAIN SYSTEM BOOT MENU          \n";
        cout << "=====================================\n";
        cout << "1. Automatic Mode (AI Controls Everything)\n";
        cout << "2. Manual Control Mode (You Control Everything)\n";
        cout << "3. Save Data & Exit System\n";
        cout << "Select mode (1/2/3): ";
        cin >> mainMode;

        // -------------------------------------------------------------
        // RUNTIME INTERFACE BRANCH 1: AUTOMATED ENGINE CONTEXT
        // -------------------------------------------------------------
        if (mainMode == 1) {
            cout << "\n[System] Running Automatic Simulation...\n";
            setRealisticDefaults(house_matrix, totalRooms); 
            runAutomationEngines(house_matrix, totalRooms, securityLogs, logCount, maxLogs, true);
            displayDashboard(house_matrix, roomNames, totalRooms); 
            
            string pauseKey; 
            cout << "\n[Note] Automated dashboard. Enter any key to return: "; 
            cin >> pauseKey;
        }
        // -------------------------------------------------------------
        // RUNTIME INTERFACE BRANCH 2: INTERACTIVE MANUAL CONTROL TERMINAL
        // -------------------------------------------------------------
        else if (mainMode == 2) {
            cout << "\n[System] Booting Manual Control Interface...\n";
            
            int choice = 0;
            while (choice != 10) { 
                runAutomationEngines(house_matrix, totalRooms, securityLogs, logCount, maxLogs, false);
                displayDashboard(house_matrix, roomNames, totalRooms);
                
                cout << "\n--- MANUAL CONTROL TERMINAL ---\n";
                cout << "1. Light Control       6. LCD Control\n";
                cout << "2. AC Adjust           7. Door Lock Control\n";
                cout << "3. Presence Adjust     8. Bathroom/Kitchen Water Temp\n";
                cout << "4. Hazard Control      9. Fan Control\n";
                cout << "5. Hardware Repair    10. Return to Main Menu\n";
                cout << "Enter command: ";
                
                while (!(cin >> choice)) {
                    cout << "[ERROR] Invalid choice! Please enter a number from 1 to 10: ";
                    cin.clear(); cin.ignore(10000, '\n');
                }

                if (choice == 10) break; 
                
                int displayRoomID;
                if (choice >= 1 && choice <= 9) {
                    cout << "\nAvailable Registered Rooms:\n";
                    for(int i = 0; i < totalRooms; i++) {
                        cout << i + 1 << ". " << roomNames[i] << "\n"; 
                    }
                    cout << "Select Room ID (1 to " << totalRooms << "): ";
                    cin >> displayRoomID;
                    
                    int roomID = displayRoomID - 1; 
                    
                    if (roomID < 0 || roomID >= totalRooms) {
                        cout << "\n[ERROR] Request Denied: Invalid Room ID entered!\n";
                        continue; 
                    }

                    // SECURITY FILTER 1: Block AC, Fan, and LCD for Bathroom
                    if (roomID == totalRooms - 1 && (choice == 2 || choice == 6 || choice == 9)) {
                        cout << "\n[ERROR] Request Denied: Bathroom does not support AC, Fan, or LCD operations!\n";
                        continue;
                    }

                    // SECURITY FILTER 2: Block LCD for Kitchen
                    if (roomID == totalRooms - 2 && choice == 6) {
                        cout << "\n[ERROR] Request Denied: Kitchen does not support LCD operations!\n";
                        continue;
                    }

                    // ---------------------------------------------------------
                    // MANUAL SELECTION DECODER SWITCH-CASE
                    // FILLING USE CASE: Manual explicit overriding/filling of array cells
                    // ---------------------------------------------------------
                    switch (choice) {
                        case 1:
                            if (house_matrix[roomID][COL_STATUS] == 1) {
                                cout << "Enter state (1=ON, 0=OFF): "; 
                                // FILLING: Changing light column value manually
                                cin >> house_matrix[roomID][COL_LIGHT];
                                cout << "\n[SYSTEM LOG] Request Completed -> Light turned " 
                                     << (house_matrix[roomID][COL_LIGHT] == 1 ? "ON" : "OFF") 
                                     << " in " << roomNames[roomID] << ".\n";
                            } else cout << "\n[ERROR] Request Failed -> Hardware framework is offline or broken in " << roomNames[roomID] << ".\n";
                            break;
                            
                        case 2:
                            cout << "Enter Target Temp (16-30): "; 
                            // FILLING: Writing manual temperature values to index slots
                            cin >> house_matrix[roomID][COL_AC_TARGET];
                            house_matrix[roomID][COL_AC_POWER] = 1; 
                            cout << "\n[SYSTEM LOG] Request Completed -> AC compressor unit activated in " 
                                 << roomNames[roomID] << " set to " << house_matrix[roomID][COL_AC_TARGET] << "C.\n";
                            break;
                            
                        case 3:
                            cout << "Presence State Configuration (0=Empty, 1=Unknown Person, 2=Owner): "; 
                            // FILLING: Overwriting occupancy state configuration cell
                            cin >> house_matrix[roomID][COL_PRESENCE];
                            cout << "\n[SYSTEM LOG] Sensor Updated -> Room occupancy parameters altered for " << roomNames[roomID] << ".\n";
                            break;
                            
                        case 4:
                            cout << "Enter environmental hazard ratio simulation value (0-100%): "; 
                            // FILLING: Forcing user hazard ratio parameter directly into cell
                            cin >> house_matrix[roomID][COL_HAZARD];
                            cout << "\n[SYSTEM LOG] Request Completed -> Hazard data intercept forced to " 
                                 << house_matrix[roomID][COL_HAZARD] << "% inside " << roomNames[roomID] << ".\n";
                            break;
                            
                        case 5:
                            // FILLING: Restoring clean safe defaults to targeted room cells
                            house_matrix[roomID][COL_STATUS] = 1; 
                            house_matrix[roomID][COL_HAZARD] = 0; 
                            house_matrix[roomID][COL_LOCK] = 0; 
                            cout << "\n[SYSTEM LOG] Maintenance Completed -> Structural components completely cleared and online for " << roomNames[roomID] << ".\n";
                            break;
                            
                        case 6:
                            cout << "Enter LCD state metrics (0=OFF, 1=ON, 2=MUTED): "; 
                            // FILLING: Writing manual display profile states
                            cin >> house_matrix[roomID][COL_LCD];
                            cout << "\n[SYSTEM LOG] Request Completed -> Entertainment cluster state modified in " << roomNames[roomID] << ".\n";
                            break;
                            
                        case 7:
                            cout << "Enter Manual Door Lock instruction overrides (0=Unlock, 1=Lock, 2=Lockdown): "; 
                            // FILLING: Applying override lock value to cell
                            cin >> house_matrix[roomID][COL_LOCK];
                            cout << "\n[SYSTEM LOG] Security Overrides Applied -> Door servo metrics changed for " << roomNames[roomID] << ".\n";
                            break;
                            
                        case 8:
                            // Allows Water Temp configuration for both Kitchen and Bathroom row slots
                            if (roomID == totalRooms - 1 || roomID == totalRooms - 2) {
                                cout << "Enter Water Temperature specification: "; 
                                // FILLING: Updating hot water telemetry threshold index
                                cin >> house_matrix[roomID][COL_WATER_TEMP];
                                cout << "\n[SYSTEM LOG] Request Completed -> Thermostat core target aligned to " 
                                     << house_matrix[roomID][COL_WATER_TEMP] << "C in " << roomNames[roomID] << ".\n";
                            } else {
                                cout << "\n[ERROR] Request Denied -> Thermal liquid lines are exclusively routed to Kitchen and Bathroom!\n";
                            }
                            break;
                            
                        case 9:
                            if (house_matrix[roomID][COL_STATUS] == 1) {
                                cout << "Enter Fan motor state link (1=ON, 0=OFF): "; 
                                // FILLING: Modifying fan actuator target index cell value
                                cin >> house_matrix[roomID][COL_FAN];
                                cout << "\n[SYSTEM LOG] Request Completed -> Ventilation hardware set " 
                                     << (house_matrix[roomID][COL_FAN] == 1 ? "ON" : "OFF") 
                                     << " inside " << roomNames[roomID] << ".\n";
                            } else cout << "\n[ERROR] Request Failed -> Structural fault locks active in " << roomNames[roomID] << ".\n";
                            break;
                    }
                    saveSystemState(house_matrix, totalRooms); 
                    
                    cout << "Press Enter to update live telemetry dashboard tracker...";
                    cin.ignore();
                    cin.get();
                }
            }
        }
    }

    // -----------------------------------------------------------------
    // MAIN SUB-BLOCK D: CLEANUP & SYSTEM RESOURCE DEALLOCATION
    // POINTERS & 2D ARRAY CLEANUP: Deallocating dynamic heap space using delete[]
    // -----------------------------------------------------------------
    for (int i = 0; i < totalRooms; i++) {
        delete[] house_matrix[i]; // Deleting individual dynamic rows
    }
    delete[] house_matrix; // Deleting top-level double pointer array
    delete[] roomNames;    // Deleting room names string array pointer
    delete[] securityLogs; // Deleting tracking buffer array pointer

    cout << "\n[System] Core configurations successfully committed to file. Hardware threads terminated cleanly. Allah Hafiz!\n";
    return 0;
}