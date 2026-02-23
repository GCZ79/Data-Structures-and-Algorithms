//=========================================================================//
// Name        : ProjectTwo.cpp                                            //
// Author      : GCZ79                                                     //
// Version     : 1.0                                                       //
// Date        : 02/21/2026                                                //
// Description : ABCU Advising Assistance Program using Binary Search Tree //
//=========================================================================//

#include <algorithm> // transform() - strings to uppercase for case-insensitive search
#include <fstream>   // ifstream - reads the CSV file
#include <iostream>  // cout/cin - console input/output
#include <sstream>   // stringstream - parses CSV lines in split() function
#include <string>    // string type - course names, numbers, filenames
#include <vector>    // vector<string> - stores prerequisites and temporary course list
using namespace std; // standard namespace to avoid typing std:: prefix repeatedly

//=============================//
// Course Structure Definition //
//=============================//

struct Course {
    string courseNumber;          // Unique identifier for the course (e.g., "CS101")
    string courseName;            // Full descriptive name of the course
    vector<string> prerequisites; // Course numbers that must be taken before this course

    // Default constructor - creates an empty course object
    Course() {}
};

//===================================//
// Binary Search Tree Node Structure //
//===================================//

struct Node {
    Course course; // Course data stored in this node
    Node* left;    // Pointer to left child node (courses that come before this one)
    Node* right;   // Pointer to right child node (courses that come after this one)

    // Default constructor - initializes pointers to nullptr
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Initialize with a course - creates a node containing the given course
    Node(Course aCourse) : Node() {
        course = aCourse;
    }
};

//=====================================//
// Binary Search Tree Class Definition //
//=====================================//

class BinarySearchTree {
private:
    Node* root;                              // Pointer to the root node of the tree

    void addNode(Node* node, Course course); // Recursively finds correct position and inserts a node
    void inOrder(Node* node);                // Recursively traverses tree in sorted order
    void destroyTree(Node* node);            // Recursively deletes all nodes to free memory

public:
    BinarySearchTree();                 // Constructor - initializes empty tree
    virtual ~BinarySearchTree();        // Destructor - cleans up memory
    void Insert(Course course);         // Insert a course into the tree
    Course Search(string courseNumber); // Finds and returns a course by its number
    void PrintCourseList();             // Displays all courses in alphanumeric order
    int Size();                         // Returns the total number of courses in the tree

private:
    int countNodes(Node* node);         // Recursively counts nodes in the tree
};

/**
 * Default constructor - Initializes an empty binary search tree with null root pointer
 */
BinarySearchTree::BinarySearchTree() {
    root = nullptr;                     // Start with empty tree - no nodes
}

/**
 * Destructor - Frees all dynamically allocated memory when tree is destroyed
 */
BinarySearchTree::~BinarySearchTree() { 
    destroyTree(root);                  // Start recursive deletion from the root
}

/**
 * Recursively destroy tree to free memory - Performs post-order traversal to delete all nodes
 */
void BinarySearchTree::destroyTree(Node* node) {
    if (node != nullptr) {        // Base case: if node is null, nothing to delete
        destroyTree(node->left);  // Recursively delete entire left subtree first
        destroyTree(node->right); // Then recursively delete entire right subtree
        delete node;              // Finally delete the current node itself
    }
}

/**
 * Insert a course into the tree
 */
void BinarySearchTree::Insert(Course course) {
	if (root == nullptr) {        // If tree is empty..
		root = new Node(course);  // Create a new node with the course and set it as the root
    }
    else {                        // If tree already has nodes..
        addNode(root, course);    // Call recursive helper to find insertion point
    }
}

/**
 * Add a course to some node (recursive)
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // Compare course numbers to determine insert position
    if (course.courseNumber < node->course.courseNumber) {
        // Course number is smaller - should go in left subtree
        if (node->left == nullptr) {       // If left child doesn't exist..
            node->left = new Node(course); // Insert new node as left child
        }
        else {                             // If left child exists..
            addNode(node->left, course);   // Recursively continue searching in left subtree
        }
    }
    else if (course.courseNumber > node->course.courseNumber) {
        // Course number is larger - should go in right subtree
        if (node->right == nullptr) {       // If right child doesn't exist..
            node->right = new Node(course); // Insert new node as right child
        }
        else {                              // If right child exists..
            addNode(node->right, course);   // Recursively continue searching in right subtree
        }
    }
    else {
        // Course already exists - update it with new data
        node->course = course;              // Replace existing course with new information
    }
}

/**
 * Search for a course by course number
 */
Course BinarySearchTree::Search(string courseNumber) {
    // Convert search key to uppercase for case-insensitive search
    transform(courseNumber.begin(), courseNumber.end(),
        courseNumber.begin(), ::toupper);

    Node* current = root; // Start searching from the root

    // Continue searching while we haven't reached a leaf
    while (current != nullptr) {
        // Check if current node contains the course we are looking for
        if (current->course.courseNumber == courseNumber) {
            return current->course; // Found it! Return the course
        }

        // Decide whether to go left or right based on comparison
        if (courseNumber < current->course.courseNumber) {
            current = current->left; // Search key is smaller - go left
        }
        else {
            current = current->right; // Search key is larger - go right
        }
    }

    // Return empty course if not found
    Course course; // Create empty course object
    return course; // Return empty course
}

/**
 * Print all courses in alphanumeric order
 */
void BinarySearchTree::PrintCourseList() {
    cout << "Here is a sample schedule:" << endl << endl;
    inOrder(root);
}

/**
 * In-order traversal to print courses in sorted order
 */
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {    // Base case: if node is null, do nothing
        inOrder(node->left);  // First, recursively process left subtree (smaller values)
        cout << node->course.courseNumber << ", "
            << node->course.courseName << endl; // Then, print current node's data
        inOrder(node->right); // Finally, recursively process right subtree (larger values)
    }
}

/**
 * Count total number of courses in tree
 */
int BinarySearchTree::Size() {
    return countNodes(root);  // Start recursive counting from root
}

/**
 * Recursively count nodes
 */
int BinarySearchTree::countNodes(Node* node) {
    if (node == nullptr) {    // Base case: empty subtree has 0 nodes
        return 0;
    }
    // Recursive case: count this node plus all nodes in left and right subtrees
    return 1 + countNodes(node->left) + countNodes(node->right);
}

//===================//
// Utility Functions //
//===================//

/**
 * Parse comma-separated values from CSV file lines
 */
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;          // Hold the resulting tokens
    string token;                   // Temporary storage for each token
    istringstream tokenStream(str); // Create string stream from input string

    // Extract tokens separated by delimiter
    while (getline(tokenStream, token, delimiter)) {
        // Trim leading whitespace (spaces, tabs, carriage returns, newlines)
        token.erase(0, token.find_first_not_of(" \t\r\n"));
        token.erase(token.find_last_not_of(" \t\r\n") + 1); // Trim trailing whitespace
        tokens.push_back(token);    // Add cleaned token to result vector
    }

    return tokens;                  // Return vector of all tokens found
}

/**
 * Convert string to uppercase for case-insensitive comparisons and searches
 */
string toUpper(string str) {
    // Apply toupper function to each character in the string
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;                // Return the uppercase string
}

//=====================//
// Load Data Functions //
//=====================//

/**
 * Load courses from CSV file into Binary Search Tree
 * Uses two-pass approach to validate prerequisites before insertion:
 * 1. First pass: Read and parse all courses
 * 2. Second pass: Validate prerequisites and insert into tree
 */
void loadCourses(string filename, BinarySearchTree* bst) {
    cout << "Loading data structure..." << endl;

    ifstream file(filename); // Attempt to open the specified file

    // Check if file opened successfully
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;              // Exit function if file can't be opened
    }

    // Temporary vector to store all courses for prerequisite validation
    vector<Course> tempCourses;
    string line;             // Buffer for each line read from file
    int lineNumber = 0;      // Track line numbers for error reporting

    // FIRST PASS: Read and parse each line
    while (getline(file, line)) {
        lineNumber++;        // Increment line counter

        if (line.empty()) {  // Skip empty lines
            continue;
        }

        // Parse the comma-separated values
        vector<string> tokens = split(line, ',');

        // Validate minimum parameters (course number and name)
        if (tokens.size() < 2) {
            cout << "Warning: Line " << lineNumber
                << " skipped - Invalid format (missing course number or name)"
                << endl;
            continue;         // Skip this line and continue with next
        }

        // Validate that course number is not empty
        if (tokens[0].empty()) {
            cout << "Warning: Line " << lineNumber
                << " skipped - Course number is empty";
            // Show the course name if it exists
            if (!tokens[1].empty()) {
                cout << " (Course name: " << tokens[1] << ")";
            }
            cout << endl;
            continue;
        }

        // Validate that course name is not empty
        if (tokens[1].empty()) {
            cout << "Warning: Line " << lineNumber
                << " skipped - Course name is empty"
                << " (Course number: " << tokens[0] << ")"
                << endl;
            continue;
        }

        // Create course object
        Course tempCourse;
        tempCourse.courseNumber = toUpper(tokens[0]); // First token is course number
        tempCourse.courseName = tokens[1];            // Second token is course name

        // Add prerequisites if they exist (starting at index 2)
        // Any remaining tokens are prerequisite course numbers
        for (size_t i = 2; i < tokens.size(); i++) {
            if (!tokens[i].empty()) {                 // Only add non-empty prerequisites
                tempCourse.prerequisites.push_back(toUpper(tokens[i])); // Store as uppercase
            }
        }

        // Add this course to temporary vector for validation in second pass
        tempCourses.push_back(tempCourse);
    }

    file.close(); // Close the file after first pass

    // SECOND PASS: Validate prerequisites and insert valid courses into BST
    int validCourseCount = 0; // Counter for successfully loaded courses

    // Check each course for prerequisite validity
    for (const Course& course : tempCourses) {
        bool isValid = true;  // Assume course is valid until proven otherwise

        // Check each prerequisite of the current course
        for (const string& prerequisite : course.prerequisites) {
            bool prerequisiteFound = false; // Flag to track if prerequisite exists

            // Search for prerequisite in the list of all courses
            for (const Course& validCourse : tempCourses) {
                if (validCourse.courseNumber == prerequisite) {
                    prerequisiteFound = true; // Prerequisite exists
                    break;                    // Exit inner loop once found
                }
            }

            // If prerequisite doesn't exist, mark course as invalid
            if (!prerequisiteFound) {
                cout << "Warning: Course " << course.courseNumber
                    << " skipped - Invalid prerequisite: " << prerequisite
                    << endl;
                isValid = false; // Course is invalid due to missing prerequisite
                break;           // Exit prerequisite checking loop
            }
        }

        // Only insert validated course into BST
        if (isValid) {
            bst->Insert(course); // Add valid course to binary search tree
            validCourseCount++;  // Increment counter for valid courses
        }
    }

    // Report loading results to user
    cout << validCourseCount << " courses loaded." << endl << endl;
}

/**
 * Print course information including prerequisites
 */
void printCourseInfo(BinarySearchTree* bst, string courseNumber) {
    // Search for the course in the BST
    Course course = bst->Search(courseNumber);

    // Check if course was found (Search returns empty course if not found)
    if (course.courseNumber.empty()) {
        cout << "Course " << courseNumber << " not found." << endl << endl;
        return; // Exit function if course doesn't exist 
    }

    // Print course information
    cout << course.courseNumber << ", " << course.courseName << endl;

    // Print prerequisites (if any)
    if (!course.prerequisites.empty()) {
        cout << "Prerequisites: ";
        // Iterate through prerequisites, adding commas between them
        for (size_t i = 0; i < course.prerequisites.size(); i++) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) { // Don't add comma after last item
                cout << ", ";
            }
        }
        cout << endl;
    }
    else {
        cout << "Prerequisites: None" << endl; // No prerequisites for this course
    }

    cout << endl; // Add blank line for readability
}

/**
 * Display the menu
 */
void displayMenu() {
    cout << "1. Load Data Structure." << endl; // Option to load course data from file
    cout << "2. Print Course List." << endl;   // Option to display all courses
    cout << "3. Print Course." << endl;        // Option to view specific course details
    cout << "9. Exit" << endl;                 // Option to exit program
    cout << "What would you like to do? ";     // Prompt for user input
}

//===============//
// Main Function //
//===============//

int main() {
    // Define a binary search tree to hold all courses
    BinarySearchTree* bst = new BinarySearchTree();

    string filename;         // Stores the name of the file to load
    string courseNumber;     // Stores course number for search operations
    int choice = 0;          // Stores user's main menu choice
    int loadChoice = 0;      // Stores user's file loading submenu choice
    bool dataLoaded = false; // Flag to track if data has been successfully loaded

    // Display welcome message
    cout << "Welcome to the course planner." << endl << endl;

    // Main program loop - continues until user chooses to exit (option 9)
    while (choice != 9) {
        displayMenu(); // Show menu options

        // Get user input and validate it's a number
        if (!(cin >> choice)) {     // Input was not a number
            cin.clear();            // Clear error state   
            cin.ignore(1000, '\n'); // Discard invalid input up to 1000 characters
            choice = 0;             // Set choice to 0 (invalid option)
        }

        // Clear any remaining characters from input buffer
        cin.ignore(1000, '\n');

        // Process user's choice using switch statement
        switch (choice) {
        case 1:
			// Sub-menu for loading files (added default file option for convenience)
            cout << endl;
            cout << "Load Options:" << endl;
            cout << "  1. Load \"CS 300 ABCU_Advising_Program_Input.csv\"" << endl;
            cout << "  2. Enter custom file name" << endl;
            cout << "  3. Cancel" << endl;
            cout << "Select an option: ";

            cin >> loadChoice; // Get user's loading preference

            // Validate input
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input." << endl << endl;
                break;
            }

            cin.ignore(1000, '\n');

            // Process loading submenu choice
            if (loadChoice == 1) {
                // Create temporary tree to test load before replacing current data
                BinarySearchTree* tempBst = new BinarySearchTree();

                // Load default file into temporary tree
                filename = "CS 300 ABCU_Advising_Program_Input.csv";
                cout << "Loading " << filename << "..." << endl;
                loadCourses(filename, tempBst);

                // Only replace main tree if load was successful (preserves data on failure)
                if (tempBst->Size() > 0) {
                    delete bst;              // Delete old tree
                    bst = tempBst;           // Replace with successfully loaded tree
                    dataLoaded = true;       // Set flag indicating data is now loaded
                }
                else {
                    delete tempBst;          // Clean up failed temporary tree
                    cout << "Load failed. Previous data preserved." << endl;
                    // dataLoaded flag unchanged - preserves previous state
                }
            }
            else if (loadChoice == 2) {
                // Create temporary tree to test load before replacing current data
                BinarySearchTree* tempBst = new BinarySearchTree();

                // Prompt for custom filename
                cout << "Enter the file name: ";
                getline(cin, filename);      // Get filename from user (may contain spaces)
                loadCourses(filename, tempBst);

                // Only replace main tree if load was successful (preserves data on failure)
                if (tempBst->Size() > 0) {
                    delete bst;              // Delete old tree
                    bst = tempBst;           // Replace with successfully loaded tree
                    dataLoaded = true;       // Set flag indicating data is now loaded
                }
                else {
                    delete tempBst;          // Clean up failed temporary tree
                    cout << "Load failed. Previous data preserved." << endl;
                    // dataLoaded flag unchanged - preserves previous state
                }
            }
            else if (loadChoice == 3) {
                cout << "Load cancelled." << endl; // User chose to cancel
            }
            else {
                cout << "Invalid option." << endl; // Invalid submenu choice
            }
            cout << endl;
            break;

        case 2:
            // Print course list option
            // Check if data has been loaded and tree is not empty
            if (!dataLoaded || bst->Size() == 0) {
                cout << "No data loaded. Please load data first." << endl << endl;
            }
            else {
                bst->PrintCourseList(); // Display all courses in alphanumeric order
                cout << endl;
            }
            break;

        case 3:
            // Print course information option
            // Check if data has been loaded and tree is not empty
            if (!dataLoaded || bst->Size() == 0) {
                cout << "No data loaded. Please load data first." << endl << endl;
            }
            else {
                cout << "What course do you want to know about? ";
                getline(cin, courseNumber);         // Get course number from user
                printCourseInfo(bst, courseNumber); // Display course details
            }
            break;

        case 9:
			// Exit option - will break out of the loop and end the program
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            // Invalid option - any number not 1,2,3,9
            cout << choice << " is not a valid option." << endl << endl;
            break;
        }
    }

    // Clean up dynamically allocated memory before program exit
    delete bst; // Destructor will recursively delete all nodes

    return 0;   // Program completed successfully
}