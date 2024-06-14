#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

class CGPA
{
private:
    string name;                 // Student's name
    int Roll_no;                 // Student's roll number
    int num_semesters;           // Number of semesters
    vector<float> semester_GPAs; // GPAs for each semester

public:
    // Function to input student details and write to file
    void inputStudentDetails(fstream &file)
    {
        cin.ignore(); // Ignore the newline character from previous input
        cout << "Enter Name of Student: ";
        getline(cin, name);                                 // Get the student's name
        file << "The name of student is: " << name << endl; // Write name to file

        cout << "Enter Roll No of Student: ";
        cin >> Roll_no;                                           // Get the student's roll number
        file << "The Roll No of student is: " << Roll_no << endl; // Write roll number to file

        cout << "Enter the number of semesters: ";
        cin >> num_semesters;                                         // Get the number of semesters
        file << "The number of semesters: " << num_semesters << endl; // Write number of semesters to file
        file << endl;
        semester_GPAs.resize(num_semesters); // Resize the GPA vector to number of semesters

        // Loop through each semester to get grades and credits
        for (int i = 0; i < num_semesters; ++i)
        {
            int num_courses; // Number of courses in the semester
            cout << "\nEnter the number of courses for semester " << i + 1 << ": ";
            cin >> num_courses; // Get the number of courses
            file << "The number of courses for semester " << i + 1 << ": " << num_courses << endl;

            vector<float> grades(num_courses); // Vector to store grades
            vector<int> credits(num_courses);  // Vector to store credits

            cout << "\nEnter grades for " << num_courses << " courses (each grade separated by space): ";
            file << "Grades:" << endl;
            for (int j = 0; j < num_courses; ++j)
            {
                cin >> grades[j];          // Get the grades
                file << grades[j] << endl; // Write grades to file
            }

            cout << "\nEnter credits for " << num_courses << " courses (each credit separated by space): ";
            file << "Credit Hours" << endl;
            for (int j = 0; j < num_courses; ++j)
            {
                cin >> credits[j];          // Get the credits
                file << credits[j] << endl; // Write credits to file
            }

            display(grades, credits);                         // Display grades and credits
            semester_GPAs[i] = calculateGPA(grades, credits); // Calculate GPA for the semester
            cout << "\nGPA for semester (" << i + 1 << ") = " << semester_GPAs[i] << endl;
            file << "GPA for semester (" << i + 1 << ") = " << semester_GPAs[i] << endl;
        }

        // Display and write the overall CGPA
        cout << "The name of the student is: " << name << endl;
        cout << "The Roll No of the student is: " << Roll_no << endl;
        float cgpa = calculateCGPA();
        cout << "\nCGPA of (" << name << ") is: " << fixed << setprecision(2) << cgpa << endl;
        file << "\nCGPA of (" << name << ") is: " << fixed << setprecision(2) << cgpa << endl;
        file << endl;
    }

    // Function to calculate overall CGPA
    float calculateCGPA() const
    {
        float total_semester_points = accumulate(semester_GPAs.begin(), semester_GPAs.end(), 0.0); // Sum of all semester GPAs
        return total_semester_points / num_semesters;                                              // Average GPA
    }

    // Function to calculate GPA for a semester
    float calculateGPA(const vector<float> &grades, const vector<int> &credits) const
    {
        float total_grade_points = 0.0; // Total grade points
        int total_credits = 0;          // Total credits

        // Loop through each course to calculate total grade points and credits
        for (size_t i = 0; i < grades.size(); ++i)
        {
            total_grade_points += grades[i] * credits[i]; // Grade points for each course
            total_credits += credits[i];                  // Total credits
        }

        return total_grade_points / total_credits; // GPA for the semester
    }

    // Function to display grades and credits
    void display(const vector<float> &grades, const vector<int> &credits) const
    {
        cout << "\nGrades: ";
        for (float grade : grades)
        {
            cout << grade << " "; // Display grades
        }

        cout << "\nCredits: ";
        for (int credit : credits)
        {
            cout << credit << " "; // Display credits
        }

        cout << endl;
    }
};

int main()
{
    cout << "----------------------- CGPA Calculator ------------------------" << endl;
    char choice; // Choice for continuing input for another set of students
    do
    {
        int num_students;                 // Number of students
        string name_of_file = "CGPA.txt"; // Output file name
        cout << "Enter Number of Students: ";
        cin >> num_students;                                 // Get number of students
        vector<CGPA> students(num_students);                 // Vector to store student objects
        fstream datafile(name_of_file, ios::out | ios::app); // Open file for appending
        for (int i = 0; i < num_students; ++i)
        {
            cout << "\nEntering details for student " << i + 1 << ":\n";
            datafile << "---------------Detail For Student " << i + 1 << "---------------" << endl;
            students[i].inputStudentDetails(datafile); // Input details for each student
        }
        datafile.close(); // Ensure the file is properly closed after writing
        cin.ignore();
        cout << "Do you want to enter details for another set of students? (y/n): ";
        cin >> choice; // Get user's choice for continuing
    } while (choice == 'y'); // Continue if user inputs 'y'

    return 0;
}
