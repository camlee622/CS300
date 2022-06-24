/*
 Cameron Lee
 CS-300 Project Two
 Last Revised: 06/19/2022
 Note: I went with using a vector data structure as I could not get the
       binary search tree data structure to work. After setting up a BST
	   and completing the code, I kept getting errors relating to the
	   placement of the left and right nodes. So, I had to start over by
	   using a basic vector data structure.
*/

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;



struct Course { // Initial course structure creation
	string courseID; // Corresponding course number
	string courseName; // Corresponding course name
	vector <string> prereqs; // Corresponding prequisites (if any) for course
};


// Set up vector tokenizer to split the text using delimiter
vector <string> tokenize(string target, string delimiter = " ") {
	vector<string> stringArray;
	int start = 0;
	int end = target.find(delimiter);
	while (end != -1) {
		stringArray.push_back(target.substr(start, end - start));
		start = end + delimiter.size();
		end = target.find(delimiter, start);
	}

	stringArray.push_back(target.substr(start, end - start));

	return stringArray;
}

vector<Course> loadDataStructure() { // Menu Option 1 - Load the data into data structure
	ifstream fin("ABCU_Advising_Program_Input.txt", ios::in); // Open provided file with read properties

	vector<Course> courses; 

	string dataLine; // Variable for each separate line of data in file

	while (1) { // While loop
		getline(fin, dataLine); // Read data file line by line

		if (dataLine == "  ") // If the line is empty...
			break; // ... then it's reached eof and exits

		Course course;

		vector<string> tokenInfo = tokenize(dataLine, ","); // Split strings with the comma delimiter 

		course.courseID = tokenInfo[0]; // Set course id to the first substring
		course.courseName = tokenInfo[1]; // Set the course name to the second substring

		for (int i = 2; i < tokenInfo.size(); i++) { // if there are any prerequisites
			course.prereqs.push_back(tokenInfo[i]); // Store after second substring
		}

		courses.push_back(course);
	}

	fin.close(); // close file

	return courses; // return courses
}



void outputSpecificCourse(Course course) { // Specific course information
	string courseID = course.courseID; // CourseID
	string courseName = course.courseName; // CourseName
	vector<string> prereqs = course.prereqs; // Prerequisites

	cout << endl; // Output line for cleaner formatting
	cout << "Course Name: " << courseName << endl; // Output course name
	cout << "Course ID: " << courseID << endl; // Output course ID
	cout << "Course Prerequisites (if applicable): "; // Output prerequisites (if there are any)
	cout << endl; // Output line for cleaner format

	// Prerequisites for loop to iterate and find prerequisites if there are any
	for (int i = 0; i < prereqs.size(); i++) {
		cout << prereqs[i] << " " << endl;
	}
}

void printCourseList(vector<Course> courses) { // Menu Option 2 - Print all courses on the course list
	int courseList = courses.size(); // Create variable equal to the size of courses that holds all courses

	for (int i = 0; i < courseList; i++) { // For loop to iterate course list
		for (int j = 0; j < courseList - 1; j++) { // For loop to iterate course list
			
			if (courses[j].courseID > courses[j + 1].courseID) { // If condition to swap courses
				swap(courses[j + 1], courses[j]);
			}
		}
	}
	for (int i = 0; i < courseList; i++) {
		outputSpecificCourse(courses[i]);
	}
}


void courseSearch(vector<Course> courses) { // Menu option 3 - Ouput specific course using user output specific course created above
	int courseList = courses.size(); // Create variable courseList equal to the size of all the courses
	
	string courseID; // create courseID for user to search with

	int x = 0; // set integer x equal to 0 for the for loop

	cout << "Please enter the Course ID you would like to search: " << endl; // Output search
	cin >> courseID; // Input from user gathered

	for (int i = 0; i < courseList; i++) { // for loop to iterate through list
		if (courses[i].courseID == courseID) { // if course id's match
			x = 1; // set x equal to 1
			outputSpecificCourse(courses[i]); // output specific course information
			break; // break from loop
		}
	}

	if (courseList == 0) { // if course id doesn't match
		cout << "No matching course ID found in search."; // output no match found
		cin >> courseID; // get another course id from user to search
	}
}

void printMenu() { // print menu function to lower clutter in main
	cout << "1. Load Data Structure" << endl; // Menu option 1
	cout << "2. Print Course List" << endl; // Menu option 2
	cout << "3. Print Specific Course" << endl; // Menu option 3
	cout << "4. Exit Program" << endl; // Menu option 4
}


string userChoice; // Create user choice variable for menu options

int main() {

	vector<Course> courses; // vector for courses

	printMenu(); // Print menu function

	int userChoice;// User choice declaration

	
	do {
		
		cout << "Please select an option from the menu: "; // Ask user what menu item they would like to choose
		cin >> userChoice; // Get input from user using userChoice variable
		switch (userChoice) { // Set switch using userChoice

			case 1: // Load data structure - menu option 1

				courses = loadDataStructure(); // function to load data structure
				cout << "Course data loaded successfully" << endl << endl; // successful output
				break; // break from case
			
			case 2: // Print course list - menu option 2
				printCourseList(courses); // function to print course list using courses from vector data
			
			case 3: // Print specific course - menu option 3
				courseSearch(courses); // function to use course search using courses from vector data
				break; // break from case
			
			case 4: // Exit program - menu option 4
				cout << "Thank you for using my program, goodbye!" << endl; // goodbye statement
				break; // break from case

			default: // Invalid entry
				cout << "Invalid menu option entered... " << endl; // invalid option case
				cout << "Please select a valid menu option (1, 2, 3, 4): "; // remind user of correct options
			}
	} while (userChoice != 4); // while to keep user in loop
	return 0;
}
	



