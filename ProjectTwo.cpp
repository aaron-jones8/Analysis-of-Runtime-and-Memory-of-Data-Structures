#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class Course {
public:
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;

    Course(string number, string title, vector<string> prereqs) {
        courseNumber = number;
        courseTitle = title;
        prerequisites = prereqs;
    }
};

vector<Course> courseData;

// Method for loading data from the file into the data structure
void loadDataStructure(string fileName) {
    ifstream file(fileName);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, courseTitle, prereq;

        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');

        vector<string> prereqs;
        while (getline(ss, prereq, ',')) {
            prereqs.push_back(prereq);
        }

        Course newCourse(courseNumber, courseTitle, prereqs);
        courseData.push_back(newCourse);
    }

    cout << "Data loaded into the data structure successfully." << endl;
}

// Method to print an alphanumeric list of all courses
void printCourseList() {
    sort(courseData.begin(), courseData.end(), [](const Course& a, const Course& b) { // sorting algorithm
        return a.courseNumber < b.courseNumber;
    });

    cout << "Alphnumeric List of Courses:" << endl;
    for (const Course& course : courseData) {
        cout << course.courseNumber << ": " << course.courseTitle << endl;
    }
}

// Method to print course information based on the course number
void printCourseInfo(string courseNumber) {
    auto it = find_if(courseData.begin(), courseData.end(), [&](const Course& course) {
        return course.courseNumber == courseNumber;
    });

    if (it != courseData.end()) {
        cout << "Course Information for " << courseNumber << ":" << endl;
        cout << "Title: " << it->courseTitle << endl;
        cout << "Prerequisites: ";

        if (it->prerequisites.empty()) {
            cout << "None";
        } else {
            for (const string& prereq : it->prerequisites) {
                cout << prereq << " ";
            }
        }

        cout << endl;
    } else {
        cout << "Course not found." << endl;
    }
}

int main() {
    cout << "ABCU Advising Program" << endl;

    // Loop for outputting menu to user and collecting user's input
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Load Data Structure\n";
        cout << "2. Print Course List\n";
        cout << "3. Print Course Information\n";
        cout << "9. Exit\n";
        cout << "\nEnter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter the file name containing the course data: ";
                string fileName;
                cin >> fileName;
                loadDataStructure(fileName);
                break;
            }
            
            case 2:
                printCourseList();
                break;
            
            case 3: {
                cout << "Enter the course number: ";
                string courseNumber;
                cin >> courseNumber;
                printCourseInfo(courseNumber);
                break;
            }

            case 9:
                cout << "Exiting program..." << endl;
                return 0;

            default:
                cout << "Invalid selection. Please enter valid selection." << endl;
        }
    }

    return 0;
}