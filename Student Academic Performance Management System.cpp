#include <iostream>
using namespace std;
class Student {
protected:
    int rollno;
    string name, dept;
    int year;
    float marks;
public:
    virtual void getData() {
        cout<<"Enter your Name: ";
        cin>>name;
        cout<<"Enter your Roll.no (last 4-no.): ";
        cin>>rollno;
        cout<<"Enter your Department: ";
        cin>>dept;
        cout<<"Enter your Year: ";
        cin>>year;
        cout<<"Enter your Marks: ";
        cin>>marks;
    }
    virtual void calculateGrade() {
        cout<<"Grade Calculation\n";
    }
    virtual void display() {
        cout<<"Roll No: "<<rollno<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Department: "<<dept<<endl;
        cout<<"Year: "<<year<<endl;
        cout<<"Marks: "<<marks<<endl;
    }
    float getMarks() {
        return marks;
    }
    friend istream& operator>>(istream& in, Student &s);
    friend ostream& operator<<(ostream& out, Student &s);
    friend Student* findTopper(Student* s[], int n);
};
istream& operator>>(istream& in, Student& s) {
    in >> s.rollno >> s.name >> s.dept >> s.year >> s.marks;
    return in;
}
ostream& operator<<(ostream& out, Student& s) {
    out << "Roll No: " << s.rollno << endl;
    out << "Name: " << s.name << endl;
    out << "Department: " << s.dept << endl;
    out << "Year: " << s.year << endl;
    out << "Marks: " << s.marks << endl;
    return out;
}
class Undergraduate : public Student {
    char grade;
    int internalMarks;
public:
    void getData() {
        Student::getData();
        cout << "Enter Internal Marks: ";
        cin >> internalMarks;
    }
    void calculateGrade() {
        float total = marks + internalMarks;
        if (total >= 90) grade = 'A';
        else if (total >= 75) grade = 'B';
        else if (total >= 50) grade = 'C';
        else grade = 'F';
    }
    void display() {
        cout<<"\n--- Undergraduate (UG) ---\n";
        Student::display();
        cout<<"Internal Marks: "<<internalMarks<<endl;
        cout<<"Grade: "<<grade<<endl;
        cout<<"GPA: "<<calculateGPA()<<endl;
    }
    float calculateGPA() {
        return marks / 10;
    }
    float calculateGPA(float extra) {
        return (marks + extra) / 10;
    }
};
class Postgraduate : public Student {
    char grade;
    int researchMarks;
public:
    void getData() {
        Student::getData();
        cout << "Enter Research Marks: ";
        cin >> researchMarks;
    }
    void calculateGrade() {
        float total = marks + researchMarks;
        if (total >= 90) grade = 'A';
        else if (total >= 75) grade = 'B';
        else if (total >= 50) grade = 'C';
        else grade = 'F';
    }
    void display() {
        cout<<"\n--- Postgraduate (PG) ---\n";
        Student::display();
        cout<<"Research Marks: "<<researchMarks<<endl;
        cout<<"Grade: "<<grade<<endl;
        cout<<"GPA: "<<calculateGPA()<<endl;
    }
    float calculateGPA() {
        return marks / 10;
    }
    float calculateGPA(float researchMarks) {
        return (marks + researchMarks) / 20;
    }
};
Student* findTopper(Student* s[], int n) {
    Student* top = s[0];
    for(int i=1;i<n;i++){
        if(s[i]->getMarks() > top->getMarks()){
            top = s[i];
        }
    }
    return top;
}
int main() {
    int n;
    cout<<"Enter number of students: ";
    cin>>n;
    Student** s = new Student*[n];
    for(int i=0;i<n;i++){
        int choice;
        cout<<"\nEnter 1 for UG, 2 for PG: ";
        cin>>choice;

        if(choice == 1)
            s[i] = new Undergraduate();
        else
            s[i] = new Postgraduate();

        s[i]->getData();
        s[i]->calculateGrade();
    }
    cout<<"\n===== STUDENT DETAILS =====\n";
    for(int i=0;i<n;i++){
        s[i]->display();
    }
    Student* topper = findTopper(s,n);
    cout<<"\n===== TOPPER DETAILS =====\n";
    topper->display();
    for(int i=0;i<n;i++){
        delete s[i];
    }
    delete[] s;
    return 0;
}