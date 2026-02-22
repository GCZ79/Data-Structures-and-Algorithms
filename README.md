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

Build Issue: My initial roadblock was Visual Studio reporting a successful build but not creating an executable. I learned to read MSBuild output carefully and discovered the ClCompile collection was empty—no source files were added to the project. This taught me the importance of understanding the build system, not just the code.

Data Preservation Problem: During testing, I found that failed file loads would wipe out existing course data—a serious usability problem. If an advisor tried loading a file but encountered an error or changed their mind, all previously loaded courses disappeared.
I redesigned the loading mechanism to be non-destructive. New data loads into a separate tree structure first. All file reading, parsing, and prerequisite validation happens in this isolated space. The original data remains active and accessible. Only a completely successful load triggers replacement of the old tree.
This design protects advisors from accidental data loss and handles edge cases like typos in filenames, corrupted files, or simply deciding not to load after all.

Input Validation: I initially had simple validation but realized users could enter empty fields or invalid prerequisites. I enhanced the validation to check for empty course numbers/names with contextual error messages showing what data was present, making debugging much easier for users.
The key lesson was to test thoroughly and think about what could go wrong, since applying defensive programming creates better user experiences.

## How has your work on this project expanded your approach to designing software and developing programs?
#### Answer

## How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
#### Answer
