#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;
class Parent;

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
    Parent* getParent() { return parent; }
    void setParent(Parent* newParent) { parent = newParent; }
private:
    vector<int> grades;
    bool isExcellent = true;
    std::string name;
    Parent* parent;
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

struct LessonInfo {
public:
    std::vector<Student*> wasOnLessonStudents;
    std::vector<Student*> gotGradeStudents;
    Teacher* teacher;
};

class Lesson {
public:
    Teacher* getTeacher() { return teacher; }
    void setTeacher(Teacher* newTeacher) { teacher = newTeacher; }

    void addStudent(Student* student) { students.push_back(student); }
    void clearStudents() { students.clear(); }

    LessonInfo* beginLesson(bool showLessonResult) {
        auto li = new LessonInfo;

        if (!teacher) {
            cout << "Lesson can't begin without Teacher!" << endl;
            return nullptr;
        }
        if (students.empty()) {
            cout << "Lesson can't begin without Students!" << endl;
            return nullptr;
        }
        cout << "Lesson begins!" << endl;
        int gradeCount = (teacher->getMood() ? rand() % 4 : rand() % 5 + 2); // good mood: 0-3 / bad mood: 2-6
        for (int i = gradeCount; i > 0; i--) {
            int studentIndex = rand() % students.size();
            if (showLessonResult) cout << "Student number " << studentIndex << " got grade " << teacher->giveGradeToStudent(students.at(studentIndex)) << endl;
            else teacher->giveGradeToStudent(students.at(studentIndex));
            bool isInVector = false;
            for (int j = 0; j < li->gotGradeStudents.size(); j++) {
                if (students.at(studentIndex) == li->gotGradeStudents.at(j)) isInVector = true;
            }
            if (!isInVector)
                li->gotGradeStudents.push_back(students.at(studentIndex));
        }
        li->teacher = teacher;
        li->wasOnLessonStudents = students;
        cout << "Lesson is over! Total grades: " << gradeCount << endl;
        return li;
    }
private:
    Teacher* teacher;
    std::vector<Student*> students;
};

class Parent {
public:
    Parent(bool isGrandma) {
        this->isGrandma = isGrandma;
    }
    void speakAboutExact(Student* child) {
        bool error = true;
        for (int i = 0; i < childs.size(); i++) {
            if (child == childs.at(i)) error = false;
        }
        if (!isGrandma) {
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
        else {
            if (error && mood) {
                cout << child->getName() << "is a good child, but it's not mine." << endl;
            }
            else if (error && !mood) {
                cout << "Eh, " << child->getName() << " is not a good child and it is not mine." << endl;
            }
            else if (!error) {
                cout << child->getName() << " is the best child!!!" << endl;
            }

        }
        
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

        if (!isGrandma) {
            if (!mood && avgBool)
                cout << "They are good students." << endl;
            else if (mood && !avgBool)
                cout << "They are my lovely childs!!" << endl;
            else if (!mood && !avgBool)
                cout << "They are my childs." << endl;
            else
                cout << "They are Excellent students and Excellent childs!!!" << endl;
        }
        else {
            cout << "They are the best childs!!!" << endl;
        }
    }

    void addChild(Student* child) {
        childs.push_back(child);
        child->setParent(this);
    }

    bool getMood() { return mood; }
    void setMood(bool newMood) { mood = newMood; }
private:
    bool mood;
    std::vector<Student*> childs;
    bool isGrandma = false;
};

class ParentsGathering {
public:
    void addParent(Parent* newParent) { parents.push_back(newParent); }
    void clearParents() { parents.clear(); }

    void addTeacher(Teacher* newTeacher) { teachers.push_back(newTeacher); }
    void clearTeachers() { teachers.clear(); }

    void beginGathering(std::vector<LessonInfo*> lessons) {
        std::vector<Student*> missing;
        cout << "Gathering begins!" << endl;
        for (int i = 0; i < lessons.size(); i++) {
            cout << "Lesson " << i+1 << ":" << endl;
            bool isDiscussed = false;
            for (int j = 0; j < teachers.size(); j++) {
                if (lessons.at(i)->teacher == teachers.at(j)) isDiscussed = true;
            }

            if (isDiscussed) {
                for (int j = 0; j < lessons.at(i)->gotGradeStudents.size(); j++) {
                    bool isSkippingStudent = true;
                    for (int o = 0; o < parents.size(); o++) {
                        if (parents.at(o) == lessons.at(i)->gotGradeStudents.at(j)->getParent())
                            isSkippingStudent = false;
                    }
                    if (isSkippingStudent) {
                        bool isInVector = false;
                        for (int i1 = 0; i1 < missing.size(); i1++) {
                            if (missing.at(i1) == lessons.at(i)->gotGradeStudents.at(j)) isInVector = true;
                        }
                        if (!isInVector)
                            missing.push_back(lessons.at(i)->gotGradeStudents.at(j));
                    }
                        
                    else
                        lessons.at(i)->gotGradeStudents.at(j)->getParent()->speakAboutExact(lessons.at(i)->gotGradeStudents.at(j));
                }
            }
            cout << endl;
        }
        if (!missing.empty()) {
            cout << "Parents of those students are missing:" << endl;
            for (int i = 0; i < missing.size(); i++) {
                cout << missing.at(i)->getName() << endl;
            }
        }
        cout << "Gathering is over!" << endl;
    }
private:
    std::vector<Parent*> parents;
    std::vector<Teacher*> teachers;
};

int main()
{
    srand(time(nullptr));
    std::vector<LessonInfo*> lessonsVector;

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
    lessonsVector.push_back(l1->beginLesson(0));
    lessonsVector.push_back(l1->beginLesson(0));
    cout << "S1 - "; s1->printGrades();
    cout << "S2 - "; s2->printGrades();
    cout << "S3 - "; s3->printGrades();
    cout << "S4 - "; s4->printGrades();


    Parent* p1 = new Parent(false);
    p1->addChild(s1);
    p1->addChild(s2);
    p1->addChild(s3);
    p1->setMood(1);

    Parent* p2 = new Parent(true);
    p2->addChild(s4);

    p1->speakAboutAll();
    p1->speakAboutRandom();
    p1->speakAboutExact(s1);
    p1->speakAboutEach();
    p1->speakAboutExact(s4);

    p2->speakAboutEach();
    cout << endl << endl;
    auto g1 = new ParentsGathering;
    g1->addParent(p1);
    g1->addParent(p2);
    g1->addTeacher(t1);
    g1->beginGathering(lessonsVector);


    delete s1; delete s2; delete s3; delete s4;
    delete t1;
    delete l1;
    delete p1; delete p2;
    delete g1;
}
