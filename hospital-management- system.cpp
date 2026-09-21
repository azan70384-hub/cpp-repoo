#include <iostream>
#include <vector>
#include <unordered_map>
#include

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

   	vector<Patient> patient;
 	unordered_map<int, Patient>patientMap;
 	
//add patient 
void addpatient(){
	Patient p(id, name, severity, admitDate);
    patients.push_back(p);
    patientMap[id] = patients.size() - 1;
    actionlog.push("Patient added :" + to_string(id));
}

 
//searching patient

 void searchingPatient(){
 	cout<< "enter id : "<<endl;
    cin<< int id;	
    auto it= patientMap.find(id);
    if (it != patientMap.end()){
    	
    	cout<<"Patient is found" <<endl;
    	int index=it->second;
    	patients[index].display();
	}else{
		cout<<"Patient is not found"<<endl;
	}
 }
 //deleting a patient
 
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
    int lastindex= patient.size()-1;
    
    patient[index]=patient[lastindex];
    patientMap[patient[index].id]= index;
     
     patient.pop_back();
     
     patientMap.erase(id)
     actionlog.push("delete patient = "+ to_string(id));
    
        cout << "Patient deleted successfully!\n";
}
    
//   emergency queue;

struct emergencyQueue{
	bool operator()(const Patient&a,Patient&b ) cont{
	return  a.severity>b.severity;
	}
};

priority_queue<Patient , vector<Patient>, emergencyQueue> erqueue;

void addEr(patient p){
	erqueue.push(p);
	cout<< "patient is added to Queue"<<endl;
}

void showqueue(){
	if(erqueue.empty()){
		cout<<"queue is empty"<<endl;
	}
	auto temp = erqueue;
	
	while(!temp.empty()){
		Patient p = tem.top();
		p.display();
		tem.pop();
	}
}

void treatPatient(){
	if(erqueue.empty()){
		cout<< "Emergency spot is empty "
	}
	Patient p = erqueue.top();
	erqueue.pop();
	p.display();
	
	actionlog.push("patient is treated :"+ to_string(id));
}
    
//normal patient 

queue<int> normQueue;

// adding normal patient;

void addingPatient(){
	int id;
	cout<<"enter id : ";
	cin<< id;
	normQueue.push(id);
	
}

//show all patient

void showAll(){
	if(normQueue.empty()){
		cout<<"no patient is waiting"<<endl;
	}
	queue<int> temp = normQueue;
	while(!temp.empty()){
		cout<<"id : "<<temp.front<< endl;
		temp.pop();
	}
}
    
//treat patient
void treatpatient(){
	if(normQueue.empty()){
		cout<<"no patient is here"<<endl;
	}
	
	int id= normQueue.front();
	normQueue.pop();
	cout<<"treating Patient id :"<<id<<endl;
}

//sorting patient 
void merg(vector<Patient>arr, int left, int mid, int right){
	int n1 = mid - left + 1;
	int n2 = right - mid;
	
	vector <Patient> L(n1);
	vector<Patient> R(n2);
	
	for ( i=0; i<n1; i++){
		L[i]=arr[left + i];
	}
	for(i=0 ; i<n2; i++){
		R[i]=arr[mid+1+i];
	}
	
	int i =0;
	int j =0;
	int k =0;
	
	while(i<n1  && j<n2){
		if(L[i].name <= R[j]){		}
		arr[k] = L[i];
		i++;
	}else{
		arr[k] = R[j];
		j++;
	}
	k++;
	
	}
	
	while(i<n1){
		arr[k]= L[i];
		i++;
		k++;
	}
	while (j<n2){
		arr[k]=R[j];
	}
	
}
void mergSort(vector<Patient>arr, int lef, int right){
	if(left>= right){
		return;
	}
	
	int mid= left + (right- left)/2;
	mergSort(arr, left, mid);
	mergSort(arr, mid+1, right);
	merg(arr, left, midd, right);
}

void listAllSort(){
	if(patient.empty()){
		cout<<"No patient found"<<endl;
	}
	
	vector<Patient> sortedList = patient;
	
	mergSort(sortedlist, 0, sortedList.size()-1);
	
	for (Const Patient& p: sortedList){
		p.display;
	}
}

void undolastAction(){
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
 
 // Save file
 
 void saveToFile(){
 	ofstream file("hospital.txt");
 	
 	if (!file){
 		cout<<"error file opening"<<endl;
	 }
	 
	while (const Patient& p : patient){
	 	 file << p.id << ","
             << p.name << ","
             << p.severity << ","
             << p.admitDate << "\n"
	 }
    file.close();
    cout << "\nPatients saved successfully!\n";
 }
 
 // read file
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

}
//show manue
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

 
 int main(){


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
