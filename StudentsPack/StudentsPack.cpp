#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

class Student {
public:
    vector<int>* getGrades() { return &grades; }
    bool getIsExcellent() { return isExcellent; }

    void checkIsExcellentNow() {
        isExcellent = true;
        for (int i = 0; i < grades.size(); i++) {
            if (grades.at(i) != 5) {
                isExcellent = false;
                return;
            }
        }
    }

    void giveGrade(int grade) {
        grades.push_back(grade);
        checkIsExcellentNow();
    }

private:
    vector<int> grades;
    bool isExcellent = false;
};

class Teacher {
public:
    bool getMood() { return mood; }
    void setMood(bool newMood) { mood = newMood; }

    void giveGradeToStudent(Student& student) {
        srand(time(nullptr));
        int grade = 5;
        if (!mood && student.getIsExcellent())
            grade = rand() % 2 + 4;
        else if (mood && !student.getIsExcellent())
            grade = 4;
        else if (!mood && !student.getIsExcellent())
            grade = rand() % 2 + 2;
        student.giveGrade(grade);
    }

private:
    bool mood = false; // 0 - bad; 1 - good;
};

int main()
{
    Student s1;
    s1.giveGrade(4);
    s1.giveGrade(5);
    for (int i = 0; i < s1.getGrades()->size(); i++) {
        cout << s1.getGrades()->at(i) << " ";
    }
    cout << endl;
    cout << (s1.getIsExcellent() ? "Excellent Student!" : "Not excellent Student.") << endl;

    Teacher t1;
    t1.giveGradeToStudent(s1);

    for (int i = 0; i < s1.getGrades()->size(); i++) {
        cout << s1.getGrades()->at(i) << " ";
    }
    cout << endl;
}
