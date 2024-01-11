#include <iostream>
#include <vector>
using namespace std;

class Student {
public:
    vector<int>* getGrades() {
        return &grades;
    }

    bool getIsExcellent() {
        return isExcellent;
    }

    void checkIsExcellentNow() {
        isExcellent = true;
        for (int i = 0; i < grades.size(); i++) {
            if (grades.at(i) != 5) {
                isExcellent = false;
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
}
