#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

class Student {
public:
    Student(std::string name) {
        this->name = name;
    }

    vector<int>* getGrades() { return &grades; }
    bool getIsExcellent() { return isExcellent; }

    std::string getName() { return name; }
    void setName(std::string newName) { name = newName; }

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
    std::string name;
};

class Teacher {
public:
    Teacher() {
        int seed = rand() % 100;
        if (seed < 20) setIsEvil(true);
        else if (seed > 80) setIsKind(true);

        seed = rand() % 100;
        if (seed < 20) constGradeMoodCount = 3;
        else if (seed > 80) constGradeMoodCount = 7;
        gradeMoodCount = constGradeMoodCount;
        cout << "ConstGradeMoodCount = " << constGradeMoodCount << endl;
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
        
        if (gradeMoodCount > 0) gradeMoodCount--;
        else {
            mood = rand() % 2;
            cout << "Teacher have " << (mood ? "good " : "bad ") << "mood now." << endl;
            gradeMoodCount = constGradeMoodCount;
        }
        return grade;
    }

private:
    bool mood = false; // 0 - bad; 1 - good;
    bool isKind = false;
    bool isEvil = false;
    int constGradeMoodCount = 5;
    int gradeMoodCount = 5;
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

class Parent {
public:
    void speakAboutExact(Student* child) {
        bool error = true;
        for (int i = 0; i < childs.size(); i++) {
            if (child == childs.at(i)) error = false;
        }
        if (error) {
            cout << "This is not my child! (ERROR MESSAGE)" << endl;
            return;
        }

        if (!mood && child->getIsExcellent())
            cout << child->getName() << " is a good student." << endl;
        else if (mood && !child->getIsExcellent())
            cout << child->getName() << " is my lovely child!!" << endl;
        else if (!mood && !child->getIsExcellent())
            cout << child->getName() << " is my child." << endl;
        else
            cout << child->getName() << " is an Excellent student and Excellent child!!!" << endl;
    }
    void speakAboutRandom() {
        int i = rand() % childs.size();
        speakAboutExact(childs.at(i));
    }
    void speakAboutEach() {
        for (int i = 0; i < childs.size(); i++) {
            speakAboutExact(childs.at(i));
        }
    }

    void speakAboutAll() {
        float avg = 0.f; bool avgBool = false;
        for (int i = 0; i < childs.size(); i++) {
            avg += childs.at(i)->getIsExcellent();
        }
        avg = avg / childs.size();
        if (avg >= 0.5f) avgBool = 1;
        else avgBool = 0;

        if (!mood && avgBool)
            cout << "They are good students." << endl;
        else if (mood && !avgBool)
            cout << "They are my lovely childs!!" << endl;
        else if (!mood && !avgBool)
            cout << "They are my childs." << endl;
        else
            cout << "They are Excellent students and Excellent childs!!!" << endl;
    }

    void addChild(Student* child) {
        childs.push_back(child);
    }

    bool getMood() { return mood; }
    void setMood(bool newMood) { mood = newMood; }
private:
    bool mood;
    std::vector<Student*> childs;
};

int main()
{
    srand(time(nullptr));

    Student* s1 = new Student("John"); Student* s2 = new Student("Alex"); Student* s3 = new Student("Kate"); Student* s4 = new Student("Rebecca");
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
    l1->beginLesson(0);
    cout << "S1 - "; s1->printGrades();
    cout << "S2 - "; s2->printGrades();
    cout << "S3 - "; s3->printGrades();
    cout << "S4 - "; s4->printGrades();


    Parent* p1 = new Parent;
    p1->addChild(s1);
    p1->addChild(s2);
    p1->addChild(s3);
    p1->setMood(1);

    Parent* p2 = new Parent;
    p2->addChild(s4);

    p1->speakAboutAll();
    p1->speakAboutRandom();
    p1->speakAboutExact(s1);
    p1->speakAboutEach();
    p1->speakAboutExact(s4);

    p2->speakAboutEach();


    delete s1; delete s2; delete s3; delete s4;
    delete t1;
    delete l1;
    delete p1; delete p2;
}
