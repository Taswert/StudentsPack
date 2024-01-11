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
    void printGrades() {
        for (int i = 0; i < grades.size(); i++) {
            cout << grades.at(i) << " ";
        }
        cout << endl;
    }
private:
    vector<int> grades;
    bool isExcellent = true;
};

class Teacher {
public:
    Teacher() {
        int seed = rand() % 100;
        if (seed < 20) setIsEvil(true);
        else if (seed > 80) setIsKind(true);
    }

    bool getMood() { return mood; }
    void setMood(bool newMood) { mood = newMood; }

    bool getIsEvil() { return isEvil; }
    void setIsEvil(bool isIt) { 
        isEvil = isIt;
        if (isIt) isKind = false;
    }
    bool getIsKind() { return isKind; }
    void setIsKind(bool isIt) {
        isKind = isIt;
        if (isIt) isEvil = false;
    }

    int giveGradeToStudent(Student* student) {
        int grade = 5;
        if (isKind)
            student->giveGrade(5);
        else if (isEvil)
            student->giveGrade(2);
        else {
            if (!mood && student->getIsExcellent())
                grade = rand() % 2 + 4;
            else if (mood && !student->getIsExcellent())
                grade = 4;
            else if (!mood && !student->getIsExcellent())
                grade = rand() % 2 + 2;
            student->giveGrade(grade);
        }

        return grade;
    }

private:
    bool mood = false; // 0 - bad; 1 - good;
    bool isKind = false;
    bool isEvil = false;
};

class Lesson {
public:
    Teacher* getTeacher() { return teacher; }
    void setTeacher(Teacher* newTeacher) { teacher = newTeacher; }

    void addStudent(Student* student) { students.push_back(student); }
    void clearStudents() { students.clear(); }

    void beginLesson(bool showLessonResult) {
        if (!teacher) {
            cout << "Lesson can't begin without Teacher!" << endl;
            return;
        }
        if (students.empty()) {
            cout << "Lesson can't begin without Students!" << endl;
            return;
        }
        cout << "Lesson begins!" << endl;
        int gradeCount = (teacher->getMood() ? rand() % 4 : rand() % 5 + 2); // good mood: 0-3 / bad mood: 2-6
        for (int i = gradeCount; i > 0; i--) {
            int studentIndex = rand() % students.size();
            if (showLessonResult) cout << "Student number " << studentIndex << " got grade " << teacher->giveGradeToStudent(students.at(studentIndex)) << endl;
            else teacher->giveGradeToStudent(students.at(studentIndex));
        }
        cout << "Lesson is over! Total grades: " << gradeCount << endl;
    }
private:
    Teacher* teacher;
    std::vector<Student*> students;
};

int main()
{
    srand(time(nullptr));

    Student* s1 = new Student; Student* s2 = new Student; Student* s3 = new Student; Student* s4 = new Student;
    s1->giveGrade(4);
    s1->giveGrade(5);
    s1->printGrades();
    cout << (s1->getIsExcellent() ? "Excellent Student!" : "Not excellent Student.") << endl;

    Teacher* t1 = new Teacher;
    cout << (t1->getIsKind() ? "Teacher is kind :)" : (t1->getIsEvil() ? "Teacher is evil :(" : "Teacher is normal.")) << endl;
    t1->giveGradeToStudent(s1);

    s1->printGrades();
    cout << endl << endl;

    Lesson* l1 = new Lesson;
    l1->setTeacher(t1);
    l1->addStudent(s1); l1->addStudent(s2); l1->addStudent(s3); l1->addStudent(s4);
    l1->beginLesson(0);
    cout << "S1 - "; s1->printGrades();
    cout << "S2 - "; s2->printGrades();
    cout << "S3 - "; s3->printGrades();
    cout << "S4 - "; s4->printGrades();



    delete s1; delete s2; delete s3; delete s4;
    delete t1;
    delete l1;
}
