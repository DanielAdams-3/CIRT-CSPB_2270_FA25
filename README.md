# CIRT-CSPB_2270_FA25
-Repository for course projct for CSPB 2270, Fall 2025, Prof. Guinn, at CU Boulder. 
About the requirements
-This repository is for my course project for CSPB 2270 Data Structures in Fall 2025.
-The project must be submitted by December 4 at 11:59pm MT
-Project must include a README or other project description, and/or a video walkthrough/explanation.

## Project Summary
-Create a course information retrieval tool (CIRT), based on a trie (prefix tree) data structure.
The project will output course information based on a user- provided input string (course subject code).

## Project Goals
The goal is to create a rapid retrieval tool for pre-consolidated course information. CIRT
will use a trie data structure, allowing a user to quickly access a comprehensive set of
course information with one interface and limited interactions. The trie will store key-value
pairs, where the key is the course subject code (e.g., CSCI-5981) and the value stored at
the relevant terminating node will be a Course object containing the stored course
information. CIRT should quickly output the course information for the course matching the
user-provided subject code. If the course does not exist, the program will notify the user of
the failed search and give these reasons.

## About Tries (Prefix Trees)
A trie is a multi-pronged tree made up of nodes, each of which contains a string
character and points to as few as zero child nodes and may point to more than two child
nodes, unlike a binary tree whose nodes point to at most two child nodes. The traversal
path, like a HuƯman tree, represents the key to each key-value pair, formed by
concatenating the string characters, stored in each node on the path, except the leaf node
which does not contain a character. Instead, it stores the value (Course object). When a
new entry is added to the trie, new nodes are only created for the key’s string characters
that diƯer from the existing keys. When a key is removed, the trie only deletes the nodes
that are unique to the to-be-removed key. Each node will also contain metadata about the
number of courses in the node’s subtree and a list of those courses to aid in search and
insertion functions.

## CIRT Structure
Each Course object will contain strings for each course information item as well as a
map of key-value pairs of strings, representing the degree plans that the course applies to,
and the list of degree requirements that the course can satisfy for that degree plan.
Course information is not confidential, and subject codes are already required to be
unique (see exception below), suggesting a hash-based solution is not strictly necessary.
Search, CIRT’s primary task, has a computational complexity of O(N) where N is the
number of characters in the key. Since subject codes are limited to nine string characters
(see exception below), search will, in most cases, be quick.

## Limitations
### Prefix-based Autocomplete
A major benefift of Prefix trees is that auto-complete is easier to implement. For any number of characters provided, we can easily search the tree and return the first or all results that start with the provided characters, or nothing if not provided. I hope to add a secondary search feature that lets users input 

### Section-differentiated courses
A challenge in implementing the trie is the (rare) circumstance where multiple courses
share a course title. For example, Special Topics courses share a subject code but have
unique section-level titles. I plan to address this by adding Course object pointers to the
Special Topics node for each section. In initial implementation, CIRT will output all course
data for each Special Topics section upon request. Time permitting, I will ask the user for
input to isolate the desired section title and then output only the relevant section’s
information.

### Upgrading from Command-Line Interface to Front End Web Interface
Time permitting, I will create a simple front-end, locally hosted web interface to
facilitate a better user experience and given my lack of experience, I anticipate this to be a
challenge. If I am unable to complete the interface by the due date, I will exclude it from the
submitted version and work on it after the class ends.

### Search-by-Title search option
I hope to be able to add a search-by-title option. Instead of remaking a new trie, I would, within the trie structure, contain a 'dictionary' map structure where each course is added to the map, where the keys are the Course titles and the values are the subject codes. Then when the user provided the course title, I would search the map for a key, and if it existed, then call the search and output functions based on the 'value' of the found key:value pair, the course subject code.

## Technical/Learning Hurdles
I need to learn how to implement a trie in C++, as this was not covered in a homework
assignment. I also need to learn how to implement file streams to read the pre-
consolidated course information from a .csv file, which may require finding a suitable C++
library. Finally, I need to learn how to create my own repository in GitHub and how to
structure the project’s files so they ‘build’ like our homework assignments. I will, as part of
this, need to build a few test cases to verify correct construction of the trie, Course objects,
and any related functions.

### References & Resources
  zyBook CSPB 2270: Data Structures - 7.12 Tries
  zyBook CSPB 2270: C++ Refresher - 9.5, 9.6, 9.7 File input and output
  Wikipedia – Trie
  Geeks4Geeks – Trie Data Structures
  //https://www.geeksforgeeks.org/cpp/traversing-a-map-or-unordered_map-in-cpp-stl/
  //https://www.geeksforgeeks.org/cpp/how-to-access-value-in-a-map-using-key-in-cpp/
  //https://learn.zybooks.com/zybook/COLORADOCSPB2270DataStructuresGuinnFall2025/chapter/14/section/1
  //https://www.geeksforgeeks.org/cpp/map-insert-in-c-stl/
  //https://www.geeksforgeeks.org/cpp/stringstream-c-applications/
  //https://www.geeksforgeeks.org/cpp/how-to-read-data-from-csv-file-to-a-2d-array-in-cpp/
  //https://www.geeksforgeeks.org/cpp/getline-string-c/
  //https://www.geeksforgeeks.org/cpp/file-handling-c-classes/
  //https://www.geeksforgeeks.org/cpp/vector-erase-in-cpp-stl/
  

## Errors I encountered and how I resolved them
-The primary issue was procedural. Because I did not physically map the relationship between the Node and the Course classes more clearly during ideation and planning phases, I ended up with some erroneous understandings that I had to address during implementation. This led to taking an extra few hours collectively to correct various errors and remove superfluous functions and data members. For example, when I first created the Nodes, i thought the course was initially going tob e directly stored in the leaf nodes. However, this would have made the nodes bloated and more difficult to separate the ndoes from the courses when i read in data from the file. So I separated it out and the final structure is much cleaner and easie to understand but was hard at first.
-As with previous assignments, there was some difficulty in reading in string data from a file but thanks to the cpp documentation I will list in the resources, this issue was relatively quickly resolved. I also addressed this by doing data preparation beforehand. Since many strings in the course descriptions and coures notes contain commas relying on comma-separated values alone to distinguish values we read in from the csv file, I added a '*' character at the end of each data value to facilitate easier reading.
-Another error was relying purely on .good() as a read condition for reading data from the csv file and from related string streams. Once I replaced that loop condition with while .eof() != true, the file and string streams were more effective and resulted in accurate reading and storage. 
-another error was a logic error. When I was first building the prefix tree, the tree was keeping alln oes at the first level past the root, so the root node's descendants vector had one trieNode* for each character in the first string. When the second course tried to be added, it could not be added because there was no space for it. During careful review, i found that I simply neglected to update the cursor value to the appropriate descedant in cases where there was not a nullptr in the calculated index for descendants.
-//REFLECTION - the trie structure relies on more efficient ways of capturing what words are listed than what I initially tried, which was to store the subject code, as it was being built, at each level. it's a small data cost but starts to eat away at the benfit of using iti n the  first place, where navigation provides that information.
-I unnecessaarily created a 'helper' function to create a new course, called setCourseInfo(title, description, notes, code, leartn, plans/reqs). to add it to the vector we just created, during readData and buildTrie(). However, this essentially just recreated the Course() constructor and the primary setter function. So I removed it. Course* createCourse(string new_title, string new_description, string new_notes, string new_subj_code, string new_skills, string new_plans, string new_hours);
-I had to decide whether or not to dynamicaly allocate the trie() itself. I decided agaisnt it, and dynamically allocated the Nodes. 
-During trie() deconstruction, I dealt with the need to delete all the doom_nodes by creating a bool data member, to_delete, whihc is basically the visited tag from DFS/BFS searches. So this let me not ultimately re-attempt to delete eahc node because that was resuitlng in double free errors.it works!
-I made a good decision to delay implementation of the getNumWords() function. Oriignally, i was going to do a more complicated search through the tree but decided to wait because it was complicated to do early-on. When I re-implemented it, it was easy to just add a increment and decrement lines of code in the insert and remove functions of the trie() itself.
-made a bad design decision and corrected it based on where Iput the following code: decided to remove it from the inner loop and put all of the edits about leafstatus nd stuff only at the end when we stop reading in data. 
        /*GOT THIS OF THIS - PUT IT AFTER WE ARRIVE AT THE RIGHT LOCATION.
        //CHECK THE INDEXED THE LOCATION IS A POINTER OR NULLPTR - IF IT'S NULL, we should skip
        if (cursor->descendants.at(index) != nullptr) 
        {
            predecessor=cursor;
            cursor=cursor->descendants.at(index);

            //remove reference from doom node
            if (cursor->getLeafStatus() == true)
            {
                predecessor->descendants.at(index) = nullptr;
            }
        }*/
-originally, I deleted all nodes related to a course (that is to say, If a node had 1 descendnat and it was the one I deleted, I would delete that node too.
-instead, I just marked the doom_node as a non-leaf and made the coursePTR point to nullptr. The insert and remove and search always check for isLeaf and for the CoursePTR information, so we can't accidentally 'arrive' at a node. In this way, we mimic an efficiency of the Huffman code process, where we mark deleted nodes 'empty after deletion', we mark deleted nodes in a similar way.