//============================================================================
// Name        : CourseSearchTree.cpp
// Author      : John Barden
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Created a binary search tree taking in course objects that hold
// Description : the courseTitle and courseNumber.
//============================================================================

#include <iostream>
#include <vector>
#include "CSVparser.hpp"

// Global call std namespace
using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// Create a Course structure to hold the courseNumber and courseTitle
struct Course {
    string courseNumber;
    string courseTitle;

    // Holed prereq strings
    vector<string> prereqNumber;

};


// Create Node structure, take in a course structure and add a left and right pointer.
// Default constructor for Node, and a constructor to modify the node course information
struct Node {
    Course course;

    Node* left;
    Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }
    Node(Course addCourse) :
        Node() {
        course = addCourse;
    }

};

// Create a BinarySearchTree class for the node and sorts the node into a binary search tree
class BinarySearchTree {
private:
    // Initilize root node
    Node* root;

    // Create private methods to hide the use of pointers
    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void removeTreeNode(Node* node);


public:
    //Public methods to call and interact with private members if needed.
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();             // InOrder method used to call nodes inOrder and print them in alphabetical order by course number
    void Insert(Course courseNumber);       // Create a Course object using constructor that takes in a courseNumber.
    Course Search(string courseNumber);     // Search through Course object for an object with same courseNumber, 
    // **PrereqNumbers(Search for node and check prereq through pointers)** 


};

// Add node into BinarySearchTree data structure depending on the courseNumber.
void BinarySearchTree::addNode(Node* node, Course course)
{
    // if no left node
    if (node != nullptr && node->course.courseNumber.compare(course.courseNumber) > 0) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
            return;
            // else recurse down the left node
        }
        else {
            this->addNode(node->left, course);
        }
        // if no right node
    }
    else if (node != nullptr && node->course.courseNumber.compare(course.courseNumber) < 0) {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course);
            return;
        }
        // else recurse down the right node
        else {
            this->addNode(node->right, course);
        }
    }
}

// Iterate through tree inOrder and print each nodes information, 
// **Try to implement a prereq print**
void BinarySearchTree::inOrder(Node* node)
{
    // Iterate through the inOrder methods recursivly called and print course information.
    if (node != nullptr) {
        inOrder(node->left);
        cout << endl << "Course number: " << node->course.courseNumber << endl
            << "Course title: " << node->course.courseTitle << endl;
        
        for (int i = 0; i < node->course.prereqNumber.size(); i++)
        {
            cout << "Course prerequisite: ";
            cout << node->course.prereqNumber.at(i);
        }
        inOrder(node->right);

    }
}

// Remove all nodes by iterating each side and removing the nodes from left to right.
void BinarySearchTree::removeTreeNode(Node* node)
{
    // Iterate through the removeTreeNode moving left first then right.
    if (node != nullptr) {
        removeTreeNode(node->left);
        removeTreeNode(node->right);
        delete node;
    }
}

// Defaul constructor, set root node to nullptr
BinarySearchTree::BinarySearchTree()
{
    root = nullptr;
}

// Deconstructor when class goes out of scope, verify all objects within BinarySearchTree are deleted and set to null or nullptr
BinarySearchTree::~BinarySearchTree()
{
    removeTreeNode(root);
    root = nullptr;
}

// InOrder recurssion call from root node.
void BinarySearchTree::InOrder()
{
    inOrder(root);
}

// Insert a new node into the binary search tree, if root is empty create a new node
// Call this BinarySearchTree addNode method with root and course number as argumnets.
void BinarySearchTree::Insert(Course courseNumber)
{
    if (root == nullptr) {
        root = new Node(courseNumber);
    }
    else {
        this->addNode(root, courseNumber);
    }
}

// Return a Course struct that has the same courseNumber
Course BinarySearchTree::Search(string courseNumber)
{
    Node* currentNode = root;
    while (currentNode != nullptr)
    {
        if (currentNode->course.courseNumber.compare(courseNumber) == 0) {
            return currentNode->course;
        }
        else if (courseNumber.compare(currentNode->course.courseNumber) < 0) {
            currentNode = currentNode->left;
        }
        else {
            currentNode = currentNode->right;
        }
    }

    Course course;
    return course;
}

// Display the information of a course struct by calling the struct members.
void displayCourse(Course course) {
    
    cout << endl << "Course number: " << course.courseNumber << endl
        << "Course title: " << course.courseTitle;
    for (unsigned int i = 0; i < course.prereqNumber.size(); i++)
    {
        cout << course.prereqNumber.at(i);
    }
    cout << endl;
    return;
}

// Used predefined Parser to load the file and store within a course object
// Having issues loading file to test code functionality.
// 
void loadCourses(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file... " << csvPath << endl;

    csv::Parser file = csv::Parser(csvPath);


    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {
            
            // Create a data structure and add to the collection of bids
            Course course;
            course.courseNumber = file[i][0];
            course.courseTitle = file[i][1];
            for (unsigned int j = 2; j < file.columnCount(); j++)
            {
                course.prereqNumber.push_back(file[i][j]);
            }
            

            // Insert course object into BinarySearchTree through pointer.
            bst->Insert(course);

        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}

void displayMenu() {
    cout << "Menu:" << endl;
    cout << "  1. Load Binary search tree data structure." << endl;
    cout << "  2. Print course list" << endl;
    cout << "  3. Print course" << endl;
    cout << "  9. Exit" << endl; 
}

int menuChoice() {
    int choice = 0;

    cout << "Enter choice: ";
    cin >> choice;

    while (!cin.good())
    {
        cout << "Incorrect input type, Please enter a number from the menu.";
        cout << endl;

        cin.clear();
        // cin.ignore() can take in how many characters to ignore and what character to ignore.
        cin.ignore(INT_MAX, '\n');

        cout << endl;
        displayMenu();
        cout << "Enter choice: ";
        cin >> choice;
    }

    return choice;
}
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, courseNumber;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        courseNumber = "CSCI100";
        break;
    case 3:
        csvPath = argv[1];
        courseNumber = argv[2];
        break;
    default:
        csvPath = "Course_Info_example.csv";
        courseNumber = "CSCI100";
    }


    // Create a bst pointer to the BinarySearchTree class
    // Create a new BinarySearchTree class at the pointer.
    // Create a course object from the Course struct.
    // Create searchNumber for a courseNumber so user can search.
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;

    bool run = true;
    int choice = 0;
    while (run) {

        displayMenu();

        
        switch (menuChoice()) {
            // Call the loadCourses method using a comma-sperated values and take in the BinarySearchTree class to create nodes.
        case 1:
            
            cout << "Please enter the file you wish to load, Include file extension" << endl;
            cin >> csvPath;

            // Default try catch for exceptions.
            loadCourses(csvPath, bst);
            break;
            // Call the BinearySearchTree InOrder methgod through a pointer.
        case 2:
            bst->InOrder();
            break;

        case 3:
            cout << "Please enter course number to search" << endl;
            cin >> courseNumber;

            // set a course object equal the the node returned by calling the bst pointer to the search method.
            course = bst->Search(courseNumber);

            // If the objects courseNumber is not empty, call the displayCourse method with the course object
            if (!course.courseNumber.empty()) {
                displayCourse(course);
                cout << '\n';
            }
            else {
                cout << "Course number " << courseNumber << " not found.";
                cout << endl;
            }
            break;
        case 9:
            run = false;
            break;
        }
 
        cin.clear();
        // cin.ignore() can take in how many characters to ignore and what character to ignore.
        cin.ignore(INT_MAX, '\n');

    }
    cout << "Good bye." << endl;
    return 0;
}

