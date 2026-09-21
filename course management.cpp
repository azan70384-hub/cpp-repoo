#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <fstream>

using namespace std;
//------------------------
class Student{
	public:
		int id;
		string name;
		double gpa;

	     Student(){};
		 Student(int id , string name, double gpa){
		 	this->id = id;
		 	this->name = name;
		 	this->gpa = gpa;
		 }
		
};
//------------------------
class Course{
	public:
    	int id;
		string name;

		Course(int id , string name){
			this->id = id;
			this->name = name;
		}
};
//------------------------
class Professor{
	public:
		int id;
		string name;
		string department;

		Professor(int id, string name, string department){
			this->id=id;
			this->name = name;
			this->department;
		}
};

//------------------------
void searchStudent(int id, vector<Student>& student, unordered_map<int, int> studentMap){
    if (studentMap.find(id) == studentMap.end()) {
        cout << "Student not found!" << endl;
        return;  
    }
	
	int index = studentMap[id];
	Student& s = student[index];
	
	cout << "===== Search student =====" << endl;
	
    cout << "Student found!" << endl;
    cout << "ID: " << s.id << endl;
    cout << "Name: " << s.name << endl;
    cout << "GPA: " << s.gpa << endl;
}
//-----------------------
bool cheackCycle(string course  ,
            map<string, vector<string>>& prerequesties,
			map<string, bool>& visited,
			map<string, bool>& currentPath){
				
				visited[course] = true;
				currentPath[course]= true;
				
				for(string prerequestie : prerequesties[course]){
					if(!visited[prerequestie]){
						if(cheackCycle(prerequestie,
						               prerequesties,
									   visited,
									   currentPath)){
									   	return true;
									   }
					}
					else if(currentPath[prerequestie]){
						return true;
					}
				}
			currentPath[course]= false;
			return false;
			}


bool cycle(
map<string , vector<string>>& prerequesties){
	map<string, bool> visited;
	map<string,bool> currentPath;
	for(auto& entry :prerequesties){
		string course = entry.first;
     
        if(!visited[course]){
        	if(cheackCycle(course,
			prerequesties,
			visited,
			currentPath)){
				return true;
			}
			}
		}
	return false;
}
//toupological sorting
void  toupologicalSorting(
        string course,
		map<string, vector<string>>& prerequesties,
		map<string, bool>& visited,
		vector<string>& order){
			
			visited[course]= true;
			
			for(const string prerequestie : prerequesties[course]){
				if(!visited[prerequestie]){
					toupologicalSorting(
					prerequestie,
					prerequesties,
					visited,
					order
					);}
						
					
				
			}
			order.push_back(course);
		}
		
vector<string> toupologicalsort(
       map<string, vector<string>>& prerequesties
 ){
 	map<string, bool>visited;
 	vector<string>order;
 	
 	for(auto& entry :prerequesties){
 		string course= entry.first;
 		if(!visited[course]){
 			toupologicalSorting(
 			course,
 			prerequesties,
 			visited,
 			order
			 );
		 }
	 }
	 return order;
 }
 // sorting students by gpa
 void sortStudent(vector<Student>& student){
 	int n=student.size();
 	for(int i=0 ; i< n-1; i++){
 		int high= i;
 		for(int j=i+1; j<n; j++){
 			if(student[j].gpa> student[high].gpa){
 				high=j;
			 }
		 }
	swap(student[i],student[high]);
	 }
	
 }
 
 //saving student in file
// void saveSt(vector<Student>& student){
// 	ofstream file(students.txt);
// 	for(Student s: student){
// 		file<<s.id<<","<<s..name<<","<<s.gpa<<endl;
//	 }
//	 file.close;
//	 cout"file save succesfully";
// }
// // readinng file
// void loodst( vector<Student>& student,
//       unordered_map<int , int> studentMap){
//       	ifstream file(students.txt);
//       	if(!file){
//       		cout << "sory file doesnt exist";
//		   }
//		for(getline(file,line)){
//			stringstream ss(line);
//			string idstr;
//			string name;
//			string gpastr;
//			
//			getline(ss,idstr ,",");
//			getline(ss, name, ",");
//			getline(ss, gpastr, ",");
//			
//			int id= stoi(idstr);
//			double gpa= stod(gpastr);
//			
//			Student s(id, name, gpa);
//			
//			student.push_back(s);
//			studentMap[id]=student.size()-1;
//		}
//		file.close();
//		cout<<"file looded successfully "<<endl;
//	   }

//------------------------
int main(){

    
    vector<Student> student;
    unordered_map<int, int> studentMap;
    
    Student s1(101, "Ali", 3.5);
    student.push_back(s1);
    studentMap[s1.id] = student.size() - 1;
    
    Student s2(102, "Ahmed", 3.8);
    student.push_back(s2);
    studentMap[s2.id] = student.size() - 1;  
    
    Student s3(103, "Hamza", 3.2);
    student.push_back(s3);
    studentMap[s3.id] = student.size() - 1;
    
    Student s4(104, "zain", 3.5);
    student.push_back(s4);
    studentMap[s4.id] = student.size() - 1;
    
    Student s5(105, "usman", 3.8);
    student.push_back(s5);
    studentMap[s5.id] = student.size() - 1;
    
    Student s6(106, "usama", 3.0);
    student.push_back(s6);
    studentMap[s6.id] = student.size() - 1;
	   

    
    vector<Course> course;
    course.push_back(Course(101, "networking"));
    course.push_back(Course(102, "dsa"));
    course.push_back(Course(103, "data base"));

    vector<Professor> professor;
    professor.push_back(Professor(501, "Jeangir", "Software engineering"));

    map<string, vector<Student>> enrolment;

    

    cout << "===== STUDENTS =====" << endl;
     sortStudent(student);
    for (Student s : student) {
        cout << "ID: " << s.id
             << " | Name: " << s.name
             << " | GPA: " << s.gpa << endl;
    }


    // Print courses
    cout << endl;
    cout << "===== COURSES =====" << endl;

    for (Course c : course) {
        cout << "ID: " << c.id
             << " | Name: " << c.name << endl<<endl;
    }
 
     cout << "===== enrollment =====" << endl;   
     
    map<string, vector<Student>> enrollment;
     
     enrollment["dsa"].push_back(s1);
     enrollment["dsa"].push_back(s1);
     
     enrollment["data base"].push_back(s3);
     enrollment["data base"].push_back(s4);
     
    enrollment["networking"].push_back(s5);
    enrollment["networking"].push_back(s6);
    
    //print enrolment
    
    for(auto& entry : enrollment){
    	cout<<endl;
    	cout<< "course : "<< entry.first<< endl;
    	for(Student& s : entry.second){
            cout << "  ID: " << s.id
                 << " | Name: " << s.name
                 << " | GPA: " << s.gpa << endl;
		}
	}
    cout<<endl;

    //prerequite grafhs

    map<string, vector<string>> prerequesties;


    // Database requires DSA
    prerequesties["Database"].push_back("DSA");


    // Networking requires DSA
    prerequesties["Networking"].push_back("DSA");


    // Make sure DSA exists in the graph
    prerequesties["DSA"];
    
    vector<string> order= toupologicalsort(prerequesties);
    cout<<endl;
    cout<<"sorting courses"<<endl;
    for(int i=0; i<order.size(); i++){
    cout << i + 1 << ". " << order[i] << endl;
	}
    

    cout << endl;
    cout << "========================================" << endl;
    cout << "          CYCLE DETECTION" << endl;
    cout << "========================================" << endl;


    if (cycle(prerequesties)) {

        cout << "Cycle detected!" << endl;
        cout << "Invalid prerequisite setup." << endl;

    }
    else {

        cout << "No cycle detected." << endl;
        cout << "Prerequisites are valid." << endl;
    }

    
    cout << "===== COURSE PREREQUISITES =====" << endl;
    for( auto&entry :prerequesties){

    	   cout << entry.first << " requires: ";
    	   for(string prerequestie : entry.second){
    	   	cout << prerequestie << " ";
		   }
		    cout << endl;
	}
    
    
    searchStudent(101, student, studentMap);
    
//    savest(student);
//    loodst(studetn, studentMap);

    return 0;
    	
}
