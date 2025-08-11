#include <iostream>
#include <string>
#include <vector>


using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::vector;

class Student
{
protected:
    string name;
    int age;
    float gpa;
public:
    Student() : name(""), age(0), gpa(0.0f) {}

    void setName(const string& studentName) { name = studentName; }
    void setAge(int studentAge) { age = studentAge; }
    void setGPA(float studentGPA) { gpa = studentGPA; }
    string getName() const { return name; }
    int getAge() const { return age; }
    float getGPA() const { return gpa; }

};


class Classroom:public Student
{
    private:
        vector<Student> students;
    public:
        Classroom() = default;

        void addStudent(const Student& student)    
        {
            students.push_back(student);
        }
        void avgGPA() const 
        {
            if (students.empty()) 
            {
                cout << "No students in the classroom." << endl;
                return;
            }

            float totalGPA = 0.0f;
            for (const auto& student : students) 
            {
                totalGPA += student.getGPA(); // Assuming Student class has a gpa member
            }
            cout << "Average GPA: " << (totalGPA / students.size()) << endl;
        }

        void bestStudent() const 
        {
            if (students.empty()) 
            {
                cout << "No students in the classroom." << endl;
                return;
            }

            const Student* best = &students[0];
            for (const auto& student : students) 
            {
                if (student.getGPA() > best->getGPA()) 
                {
                    best = &student;
                }
            }
            cout << "Best Student: " << best->getName() << " with GPA: " << best->getGPA() << endl;
        }
};


int main()
{
    Classroom classroom;
    cout << "Enter number of students: ";
    int numStudents;
    cin >> numStudents;
    cin.ignore(); // Clear the newline character from the input buffer
    for (int i = 0; i < numStudents; ++i) 
    {
        Student student;
        string name;
        int age;
        float gpa;

        cout << "Enter name of student " << (i + 1) << ": ";
        getline(cin, name);
        if(name.empty()) 
        {
            cout << "Name cannot be empty. Please enter a valid name." << endl;
            --i; 
            continue; 
        }
        else if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos) 
        {
            cout << "Name can only contain letters and spaces. Please enter a valid name." << endl;
            --i; 
            continue; 
        }
        student.setName(name);
        cout << "Enter age of student " << (i + 1) << ": ";
        cin >> age;
        if(age <= 0) 
        {
            cout << "Age must be a positive integer. Please enter a valid age." << endl;
            --i; 
            cin.ignore(); 
            continue; 
        }
        else if (age!= static_cast<int>(age)) 
        {
            cout << "Age must be an integer. Please enter a valid age." << endl;
            --i; 
            cin.ignore(); 
            continue; 
        }
        student.setAge(age);
        cin.ignore();

        cout << "Enter GPA of student " << (i + 1) << ": ";
        cin >> gpa;
        student.setGPA(gpa);
        cin.ignore(); // Clear the newline character from the input buffer

        classroom.addStudent(student);
    }
    classroom.avgGPA();
    classroom.bestStudent();
    return 0; 
}