# Data-Structures-and-Algorithms
Analysis of runtime and memory usage for selected data structures, with working code that sorts and prints a list of Computer Science courses in alphanumeric order

## What was the problem you were solving in the projects for this course?
I was tasked with developing an efficient course advising system for ABCU (ABC University). The goal was to give academic advisors a reliable way to load course data from a CSV file, display the full course list in alphanumeric order, and quickly search for individual courses along with their prerequisites. A major part of the challenge was selecting an appropriate data structure that could handle fast searches across hundreds of courses while still keeping the data organized for sorted output. The system also needed to verify that all prerequisite courses were valid before loading the data, helping maintain accuracy and data integrity for advisors using the system to support student planning.

## How did you approach the problem? Consider why data structures are important to understand.
I approached this problem by first looking at the runtime performance of different data structures. In Project One, I compared vectors, hash tables, and binary search trees based on how well they supported the main operations advisors would perform most often: searching for courses and displaying a sorted course list.

I ultimately selected a Binary Search Tree (BST) for several reasons:

• Search efficiency: Average search time is O(log n) compared to O(n) for an unsorted vector.

• Automatic ordering: An in-order traversal naturally produces courses in alphanumeric order without needing a separate sorting step.

• Balanced performance: Insert, search, and display operations all perform efficiently.

Understanding data structures was critical here because the wrong choice could introduce noticeable delays when working with a large course catalog. For instance, hash tables provide very fast O(1) lookups, but they do not maintain order, meaning extra processing would be required to sort the data before displaying it. The BST provided the best compromise between fast searches and maintaining a naturally ordered structure, which directly supports the advisor’s workflow.

The two-pass loading algorithm I implemented also reflects this understanding. I first loaded all courses into the structure, then performed prerequisite validation afterward. This approach ensured that every prerequisite could be verified efficiently while maintaining good memory usage and search performance.

## How did you overcome any roadblocks you encountered while going through the activities or project?
I encountered several roadblocks that required systematic problem-solving:

• Build Issue: My initial roadblock was Visual Studio reporting a successful build but not creating an executable. I learned to read MSBuild output carefully and discovered the ClCompile collection was empty—no source files were added to the project. This taught me the importance of understanding the build system, not just the code.

• Data Preservation Problem: During testing, I found that failed file loads would wipe out existing course data—a serious usability problem. If an advisor tried loading a file but encountered an error or changed their mind, all previously loaded courses disappeared.
I redesigned the loading mechanism to be non-destructive. New data loads into a separate tree structure first. All file reading, parsing, and prerequisite validation happens in this isolated space. The original data remains active and accessible. Only a completely successful load triggers replacement of the old tree.
This design protects advisors from accidental data loss and handles edge cases like typos in filenames, corrupted files, or simply deciding not to load after all.

• Input Validation: I initially had simple validation but realized users could enter empty fields or invalid prerequisites. I enhanced the validation to check for empty course numbers/names with contextual error messages showing what data was present, making debugging much easier for users.
The key lesson was to test thoroughly and think about what could go wrong, since applying defensive programming creates better user experiences.

## How has your work on this project expanded your approach to designing software and developing programs?
This project really changed the way I think about software design and development.

I learned to focus on the algorithm before jumping into coding. Now I start by outlining pseudocode and thinking about runtime complexity first. Looking at the Big-O performance early helps me choose the right approach from the beginning instead of trying to fix performance problems later.

It also reinforced the importance of designing with the user in mind. Adding the file-loading submenu made me realize that good software is not just about code that works, but about how people actually interact with it. Implementing the temporary tree to preserve existing data showed me that even a technically correct solution can be improved when real user behavior and edge cases are considered.

Another major takeaway was the value of modular design. Separating the program into focused functions such as loadCourses, printCourseInfo, split, and toUpper made the system easier to test, debug, and maintain. Giving each function a single responsibility helped keep the code organized and easier to extend.

The prerequisite validation requirement also introduced me to what I think of as two-pass thinking. I learned that some problems cannot be solved correctly in a single step, and that processing data in stages can be necessary to guarantee accuracy. That idea applies far beyond this project and changed how I approach more complex problems.

## How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
This project helped me improve my coding practices in several important ways.

One of the biggest lessons was about maintainability through meaningful comments. I learned that good comments should explain not only what the code is doing, but also why certain design decisions were made. For example, documenting why the BST uses an in-order traversal to produce automatic sorting makes the reasoning behind the implementation clear for anyone reading the code later, including myself. Each function now begins with a clear description of its purpose, and more complex sections include inline explanations to clarify the logic.

I also focused more on readability by organizing the program into clearly defined sections such as the Course structure, BST class, utility functions, and the main function. Using descriptive variable names like validCourseCount and prerequisiteFound helps the code communicate its intent without needing excessive explanation. Consistent formatting, indentation, and spacing also made a noticeable difference in how easy the program is to follow.

This project also helped me to refine my approach to error handling. Instead of allowing the program to fail when something goes wrong, I began planning for common problems such as missing files, invalid input, or empty datasets. The temporary tree loading strategy is a good example of this mindset, since it protects existing user data when a loading operation fails.

Overall, I now write code with the expectation that it will need to be maintained or modified later. I now see clear structure, meaningful documentation, and strong error handling as essential elements of creating dependable, professional software rather than optional improvements.
