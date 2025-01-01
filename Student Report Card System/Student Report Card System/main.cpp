//
//  main.cpp
//  Student Report Card System
//
//  Created by SUMEDH PATIL on 01/01/25.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct student {
    int id;
    string name;
    float marks[3];
    float average;
    char grade;
    
};

char calculategrade(float average){
    if (average>=90) return 'A';
    if (average>=70) return 'B';
    if (average>=50) return 'C';
    else return 'F';
}

void addstudent(){
    student s;
    
    cout<<"Enter student Id:";
    cin>>s.id;
    
    cout<<"Enter Student Name:";
    cin>>s.name;
    getline(cin,s.name);
    
    cout<<"Enter marks for three subject:";
    for (int i=0; i<3; i++) {
        cout << "Subject " << i + 1 << ": ";
        cin >> s.marks[i];
    }
    
    s.average = (s.marks[0] + s.marks[1] + s.marks[2]) / 3.0f;
    s.grade = calculategrade(s.average);
    
    cout << "\n--- Student Details ---\n";
        cout << "ID: " << s.id << "\n";
        cout << "Name: " << s.name << "\n";
        cout << "Marks: ";
    for (int i = 0; i < 3; i++) {
        cout << s.marks[i] << " ";
    }
    
    cout << "\nAverage: " << s.average << "\n";
      cout << "Grade: " << s.grade << "\n";

}

void displayAllStudents() {
    student s;
    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        cout << "No records found.\n";
        return;
    }
    cout << "ID\tName\t\tAverage\tGrade\n";
    while (inFile.read((char*)&s, sizeof(s))) {
        cout << s.id << "\t" << s.name << "\t\t" << s.average << "\t" << s.grade << "\n";
    }
    inFile.close();
}

void searchStudent() {
    int searchId;
    cout << "Enter Student ID to search: ";
    cin >> searchId;

    student s;
    ifstream inFile("students.dat", ios::binary);
    bool found = false;
    while (inFile.read((char*)&s, sizeof(s))) {
        if (s.id == searchId) {
            cout << "Student Found:\n";
            cout << "ID: " << s.id << "\nName: " << s.name << "\nAverage: " << s.average << "\nGrade: " << s.grade << "\n";
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) cout << "Student not found.\n";
}


void deleteStudent() {
    int deleteId;
    cout << "Enter Student ID to delete: ";
    cin >> deleteId;

    student s;
    ifstream inFile("students.dat", ios::binary);
    ofstream tempFile("temp.dat", ios::binary);

    bool found = false;
    while (inFile.read((char*)&s, sizeof(s))) {
        if (s.id == deleteId) {
            found = true;
        } else {
            tempFile.write((char*)&s, sizeof(s));
        }
    }
    inFile.close();
    tempFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) cout << "Student record deleted successfully.\n";
    else cout << "Student not found.\n";
}


void menu() {
    int choice;
    do {
        cout << "\n--- Student Report Card System ---\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search for a Student\n";
        cout << "4. Delete a Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addstudent(); break;
            case 2: displayAllStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);
}


int main(){
    menu();
    return 0;
    
}

