#include <iostream>
#include <math.h>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <map>
#include <vector>
#include <functional>
#include <sstream>
#include <utility>

using namespace std;

struct StudentInfo
{
    string FirstName;
    string Faculty;
    string Address;
    string Phone;
    int Age;
    StudentInfo(const string& firstName, string faculty, const string& address, const string& phone, const int age) : FirstName(firstName), Faculty(faculty), Address(address), Phone(phone), Age(age)
    {
    }

    StudentInfo() : FirstName("Unknown"), Faculty("Unknown"), Address("Unknown"), Phone("Unknown"), Age(5)
    {
    }

    string ToString() const
    {
        stringstream stream;
        stream << "First name: " << FirstName << ";Faculty: " << Faculty << "; Address: " << Address << "; Phone: " << Phone << "; Age: " << Age << ".";
        return stream.str();
    }
};

struct CopyStudent {
    bool operator() (const pair< string, StudentInfo > student) {
        return student.second.Age >= 18;
    }
};

map<string, StudentInfo> CreateStudent()
{
    map<string, StudentInfo> student;
    student["Petrov"] = StudentInfo("Petrov", "FKP", "Petrovo", "22222", 19);
    student["Andreev"] = StudentInfo("Andreev", "IEF", "Ivanovo", "11111", 5);


    student["Ivanov"] = StudentInfo("Ivanov", "IEF", "Ivanovo", "11111", 5);

    return student;
}

void PrintStudent(const map<string,StudentInfo>& student)
{
    cout << "Students\n";

    for (const auto &studentPair: student)
    {
        cout << "Key: " << studentPair.first << endl;
        cout << "Information: " << studentPair.second.ToString() << endl << endl;
    }
}

void FindStudent(const map<string,StudentInfo>& student, string key) {
    auto foundElementIterator = student.find(key);
    if(foundElementIterator != student.end()) {
        cout << "Student found\n";
        cout << "Key: " << foundElementIterator->first << endl;
        cout << "Information: " << foundElementIterator->second.ToString() << endl << endl;
    } else {
        cout << "Student not found" << endl;
    }
}

bool pred(const pair< string, StudentInfo > &a, const pair< string, StudentInfo > &b)
{
    return a.second.FirstName > b.second.FirstName;
}

void SortStudent(const map<string,StudentInfo>& student) {
    cout << "Sorting" << endl << endl;
    vector< pair< string, StudentInfo > > vec(student.begin(), student.end());
    sort(vec.begin(), vec.end(), pred);
    for (auto &element: vec)
    {
        cout << "Key = " << element.first << endl;
        cout << "Information= " << element.second.ToString() << endl << endl;
    }
}

void AnyOfStudent(const map<string,StudentInfo>& student) {
    if(any_of(student.begin(), student.end(), [](const pair< string, StudentInfo > &s){
        return s.second.FirstName.length() < 10;
})) {
        cout << "At least one of the elements meets the condition" << endl << endl;
    } else {
        cout << "None of the items meet the condition" << endl << endl;
    }
}

void CopyIfStudent(const map<string,StudentInfo>& student) {
    cout << "Copy if\n";
    map<string, StudentInfo> student2;
    copy_if(student.begin(), student.end(), inserter(student2, student2.begin()), CopyStudent());
    PrintStudent(student2);
}

void StudentSort(const map<string,StudentInfo>& student) {
    cout << "Sorting" << endl << endl;
    vector< pair< string, StudentInfo > > vec(student.begin(), student.end());
    sort(vec.begin(), vec.end(), [](const pair< string, StudentInfo > &a, const pair< string, StudentInfo > &b){
        return a.second.Age > b.second.Age;
    });
    for (auto &element: vec)
    {
        cout << "Key = " << element.first << endl;
        cout << "Information= " << element.second.ToString() << endl << endl;
    }
}

int main()
{
    map<string, StudentInfo> student = CreateStudent();
    PrintStudent(student);
    if (student.count("Ivanov") == 1)
    cout << "Ivanov exists\n\n";
    student.erase("Ivanov");
    student["Petrov"].Address = "USA";
    FindStudent(student, "Petrov");
    SortStudent(student);
    AnyOfStudent(student);
    CopyIfStudent(student);
    StudentSort(student);

    return 0;
}
