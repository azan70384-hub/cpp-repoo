#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

// ============================================================
// PATIENT CLASS
// ============================================================

class Patient {
public:
    int id;
    string name;
    int severity;       // 1 = Critical, 5 = Mild
    string admitDate;

    Patient() {}

    Patient(int id, string name, int severity, string admitDate) {
        this->id = id;
        this->name = name;
        this->severity = severity;
        this->admitDate = admitDate;
    }

    void display() const {
        cout << "ID: " << id
             << " | Name: " << name
             << " | Severity: " << severity
             << " | Admit Date: " << admitDate << endl;
    }
};

// ============================================================
// PRIORITY QUEUE COMPARATOR
// Lowest severity number = highest priority
// ============================================================

struct EmergencyComparator {
    bool operator()(const Patient& a, const Patient& b) const {
        return a.severity > b.severity;
    }
};

// ============================================================
// GLOBAL DATA STRUCTURES
// ============================================================

vector<Patient> patients;

// Patient ID -> index in vector
unordered_map<int, int> patientMap;

// Emergency queue
priority_queue<
    Patient,
    vector<Patient>,
    EmergencyComparator
> erQueue;

// Normal appointment queue
queue<int> appointmentQueue;

// Undo action log
stack<string> actionLog;


// ============================================================
// ADD PATIENT
// ============================================================

void addPatient() {

    int id;
    string name;
    int severity;
    string admitDate;

    cout << "\nEnter Patient ID: ";
    cin >> id;

    // Check duplicate ID
    if (patientMap.find(id) != patientMap.end()) {
        cout << "Patient ID already exists!\n";
        return;
    }

    cin.ignore();

    cout << "Enter Patient Name: ";
    getline(cin, name);

    cout << "Enter Severity (1 = Critical, 5 = Mild): ";
    cin >> severity;

    if (severity < 1 || severity > 5) {
        cout << "Invalid severity!\n";
        return;
    }

    cin.ignore();

    cout << "Enter Admit Date (DD-MM-YYYY): ";
    getline(cin, admitDate);

    Patient p(id, name, severity, admitDate);

    // Add to vector
    patients.push_back(p);

    // Add to map
    patientMap[id] = patients.size() - 1;

    // Add to ER queue
    erQueue.push(p);

    // Add to normal appointment queue
    appointmentQueue.push(id);

    // Add action to undo log
    actionLog.push("Added patient: " + to_string(id));

    cout << "\nPatient added successfully!\n";
}


// ============================================================
// SEARCH PATIENT BY ID
// O(1) average
// ============================================================

void searchById() {

    int id;

    cout << "\nEnter Patient ID: ";
    cin >> id;

    auto it = patientMap.find(id);

    if (it == patientMap.end()) {
        cout << "Patient not found!\n";
        return;
    }

    int index = it->second;

    cout << "\nPatient Found:\n";
    patients[index].display();
}


// ============================================================
// DELETE PATIENT
// Swap and Pop = O(1)
// ============================================================

void deletePatient() {

    int id;

    cout << "\nEnter Patient ID to delete: ";
    cin >> id;

    auto it = patientMap.find(id);

    if (it == patientMap.end()) {
        cout << "Patient not found!\n";
        return;
    }

    int index = it->second;

    // Index of last patient
    int lastIndex = patients.size() - 1;

    // If target isn't already last
    if (index != lastIndex) {

        // Move last patient into deleted patient's position
        patients[index] = patients[lastIndex];

        // Update map for moved patient
        patientMap[patients[index].id] = index;
    }

    // Remove last element
    patients.pop_back();

    // Remove ID from map
    patientMap.erase(id);

    // Add action
    actionLog.push("Deleted patient: " + to_string(id));

    cout << "Patient deleted successfully!\n";
}


// ============================================================
// SHOW ER QUEUE
// Copy queue first so original is not destroyed
// ============================================================

void showERQueue() {

    if (erQueue.empty()) {
        cout << "\nEmergency queue is empty.\n";
        return;
    }

    cout << "\n===== EMERGENCY QUEUE =====\n";

    // Copy the queue
    auto temp = erQueue;

    while (!temp.empty()) {

        Patient p = temp.top();

        p.display();

        temp.pop();
    }
}


// ============================================================
// TREAT NEXT ER PATIENT
// ============================================================

void treatNextERPatient() {

    if (erQueue.empty()) {
        cout << "\nNo emergency patients waiting.\n";
        return;
    }

    Patient p = erQueue.top();

    erQueue.pop();

    cout << "\n===== TREATING PATIENT =====\n";

    p.display();

    actionLog.push("Treated patient: " + to_string(p.id));
}


// ============================================================
// LIST ALL PATIENTS
// ============================================================

void listAllPatients() {

    if (patients.empty()) {
        cout << "\nNo patients found.\n";
        return;
    }

    cout << "\n===== ALL PATIENTS =====\n";

    for (const Patient& p : patients) {
        p.display();
    }
}


// ============================================================
// MERGE SORT
// Sort patients by name
// ============================================================

void merge(vector<Patient>& arr, int left, int mid, int right) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Patient> L(n1);
    vector<Patient> R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }

    for (int i = 0; i < n2; i++) {
        R[i] = arr[mid + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = 0;

    while (i < n1 && j < n2) {

        if (L[i].name <= R[j].name) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


void mergeSort(vector<Patient>& arr, int left, int right) {

    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);

    mergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}


// ============================================================
// LIST SORTED BY NAME
// Sort a COPY so original vector and map stay unchanged
// ============================================================

void listAllSortedByName() {
 
    if (patients.empty()) {
        cout << "\nNo patients found.\n";
        return;
    }

    // Make a copy
    vector<Patient> sortedPatients = patients;

    // Sort copy
    mergeSort(
        sortedPatients,
        0,
        sortedPatients.size() - 1
    );

    cout << "\n===== PATIENTS SORTED BY NAME =====\n";

    for (const Patient& p : sortedPatients) {
        p.display();
    }
}


// ============================================================
// UNDO LAST ACTION
// Currently only removes the log entry
// ============================================================

void undoLastAction() {

    if (actionLog.empty()) {
        cout << "\nNothing to undo.\n";
        return;
    }

    cout << "\nLast Action: "
         << actionLog.top()
         << endl;

    actionLog.pop();

    cout << "Action removed from undo log.\n";

    cout << "\nNote: Real undo functionality is your next challenge.\n";
}


// ============================================================
// SAVE TO FILE
// Format:
// ID,Name,Severity,AdmitDate
// ============================================================

void saveToFile() {

    ofstream file("patients.txt");

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    for (const Patient& p : patients) {

        file << p.id << ","
             << p.name << ","
             << p.severity << ","
             << p.admitDate << "\n";
    }

    file.close();

    cout << "\nPatients saved successfully!\n";
}


// ============================================================
// LOAD FROM FILE
// ============================================================

void loadFromFile() {

    ifstream file("patients.txt");

    if (!file) {
        cout << "No previous patient file found.\n";
        return;
    }

    string line;

    while (getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        stringstream ss(line);

        string idStr;
        string name;
        string severityStr;
        string admitDate;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, severityStr, ',');
        getline(ss, admitDate, ',');

        int id = stoi(idStr);
        int severity = stoi(severityStr);

        Patient p(
            id,
            name,
            severity,
            admitDate
        );

        patients.push_back(p);

        patientMap[id] = patients.size() - 1;

        // Restore queues
        erQueue.push(p);

        appointmentQueue.push(id);
    }

    file.close();

    cout << "Patients loaded successfully!\n";
}


// ============================================================
// MAIN MENU
// ============================================================

void showMenu() {

    cout << "\n\n";
    cout << "====================================\n";
    cout << "      HOSPITAL MANAGEMENT SYSTEM\n";
    cout << "====================================\n";

    cout << "1. Add Patient\n";
    cout << "2. Search Patient by ID\n";
    cout << "3. Delete Patient\n";
    cout << "4. List All Patients\n";
    cout << "5. Show ER Queue\n";
    cout << "6. Treat Next ER Patient\n";
    cout << "7. Undo Last Action\n";
    cout << "8. Save & Exit\n";

    cout << "====================================\n";
    cout << "Enter your choice: ";
}


// ============================================================
// MAIN
// ============================================================

int main() {

    // Load previous data
    loadFromFile();

    int choice;

    while (true) {

        showMenu();

        cin >> choice;

        switch (choice) {

            case 1:
                addPatient();
                break;

            case 2:
                searchById();
                break;

            case 3:
                deletePatient();
                break;

            case 4:
                listAllPatients();
                break;

            case 5:
                showERQueue();
                break;

            case 6:
                treatNextERPatient();
                break;

            case 7:
                undoLastAction();
                break;

            case 8:
                saveToFile();

                cout << "\nThank you for using Hospital Management System!\n";

                return 0;

            default:
                cout << "\nInvalid choice! Please select 1-8.\n";
        }
    }

    return 0;
}
