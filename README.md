# CIRT-CSPB_2270_FA25
Repository for course project for CSPB 2270, Fall 2025, Prof. Guinn, at CU Boulder. 
## About the Requirements
This repository is for my course project for CSPB 2270 Data Structures in Fall 2025.
The project must be submitted by December 4 at 11:59pm MT.
Project must include a README or other project description, and/or a video walkthrough/explanation.
## Project Summary
Create a course information retrieval tool (CIRT), based on a trie (prefix tree) data structure.
The project will output course information based on a user- provided input string (course subject code).
## Project Goals
The goal is to create a rapid retrieval tool for pre-consolidated course information. CIRT
will use a trie data structure, allowing a user to quickly access a comprehensive set of
course information with one interface and limited interactions. The trie will store key-value
pairs, where the key is the course subject code (e.g., CSCI-5981) and the value stored at
the relevant terminating node will be a Course object containing the stored course
information. CIRT should quickly output the course information for the course matching the
user-provided subject code. If the course does not exist, the program will notify the user of
the failed search.
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
## CIRT Implementation
My implementation of a Trie is built on 4 components.
### Custom Class: Course()
Each course object contains strings for each piece of course information and a map of key-value string pairs for my department's degree plans and how the course applies to them.
### Custom Class: TrieNode()
Each node contains a pointer to the previous node in the tree, a descendants vector<TrieNode*> with slots for 38 possible TrieNode 'childs', and a few bool variables to help in insert, search, and removal functions including a bool variable for whether it is a leaf node. Each leaf node contains a pointer to a corresponding course objct that contains the course information to be output upon retrieval.
### Custom Class: Trie()
Each Trie contains a root node, 
### Custom Class: Trie Server() - from Prof. Guinn
Thanks to Prof. Guinn, I have a series of related files that host a simple front-end web user-interface through JupyterLab. 
## Technical/Learning Hurdles
I needed to learn how to implement a trie in C++, as this was not covered in a homework assignment. I also needed to learn how to implement file streams to read the pre-consolidated course information from a .csv file, which required me to learn a great deal about parsing strings. Finally, I need to learn how to create my own repository in GitHub and how to structure the project’s files so they ‘build’ like our homework assignments. I will, as part of this, need to build a few test cases to verify correct construction of the trie, Course objects, and any related functions.
### References & Resources
  #### zyBook CSPB 2270: Data Structures - 7.12 Tries
  #### zyBook CSPB 2270: C++ Refresher - 9.5, 9.6, 9.7 File input and output
  #### Wikipedia – Trie
  #### Geeks4Geeks – Trie Data Structures
  #### https://www.geeksforgeeks.org/cpp/traversing-a-map-or-unordered_map-in-cpp-stl/
  #### https://www.geeksforgeeks.org/cpp/how-to-access-value-in-a-map-using-key-in-cpp/
  #### https://learn.zybooks.com/zybook/COLORADOCSPB2270DataStructuresGuinnFall2025/chapter/14/section/1
  #### https://www.geeksforgeeks.org/cpp/map-insert-in-c-stl/
  #### https://www.geeksforgeeks.org/cpp/stringstream-c-applications/
  #### https://www.geeksforgeeks.org/cpp/how-to-read-data-from-csv-file-to-a-2d-array-in-cpp/
  #### https://www.geeksforgeeks.org/cpp/getline-string-c/
  #### https://www.geeksforgeeks.org/cpp/file-handling-c-classes/
  #### https://www.geeksforgeeks.org/cpp/vector-erase-in-cpp-stl/
  #### https://en.cppreference.com/w/cpp/string/basic_string/begin
  #### https://www.geeksforgeeks.org/cpp/string-concatenation-in-cpp/
  #### https://cplusplus.com/reference/string/string/end/
  #### https://www.geeksforgeeks.org/cpp/stdstringinsert-in-c/
  #### https://en.cppreference.com/w/cpp/string/basic_string/insert
  #### https://www.geeksforgeeks.org/cpp/traversing-a-map-or-unordered_map-in-cpp-stl/
  #### https://en.cppreference.com/w/cpp/container/map/begin.html
  #### https://www.geeksforgeeks.org/dsa/auto-complete-feature-using-trie/
  
## Challenges & Errors (and their Resolutions)
### Procedure
The first issue that has been troublesome was procedural. Because I did not physically map the relationship between the Node and the Course classes more clearly during ideation and planning phases, I ended up with some erroneous understandings that I had to address during implementation. This led to taking an extra few hours collectively to correct various errors and remove superfluous functions and data members. For example, when I first created the Nodes, i thought the course was initially going tob e directly stored in the leaf nodes. However, this would have made the nodes bloated and more difficult to separate the ndoes from the courses when i read in data from the file. So I separated it out and the final structure is much cleaner and easie to understand but was hard at first.
### String Manipulation
As with previous assignments, there was some difficulty in reading in string data from a file but thanks to the cpp documentation I will list in the resources, this issue was relatively quickly resolved. I also addressed this by doing data preparation beforehand. Since many strings in the course descriptions and coures notes contain commas relying on comma-separated values alone to distinguish values we read in from the csv file, I added a '*' character at the end of each data value to facilitate easier reading.
### Trie Implementation Notes
#### Node Insertion Logic Error
When implementing the trie, I  initially made a logic error. When first building the prefix tree, the trie was storing all new nodes in the root's descendants vector. After first node insertion, the root's descendants vector stored one trieNode* for each character in the first string. The issue occured during the second course insertion. Because both courses shared the same subject code ('CSCI'), the root's descendants vector could not be added to the tree because there was no space for it to be added (since no new levels were being added to the tree). I fixed this by adding a line to update the cursor value to the appropriate descedant of the current vector when there was not a nullptr in that index.
#### Unnecessary Helper Function
During initial implementation, I created a 'helper' function to create a new Course* whenever I reached a leaf node, called createCourse(...). This function would create a new course object, populate it with the relevant data we had read from the .csv file, and would add a pointer to the course object for the leaf node. While I thought it would be helpful, I was just creating an alternate constructor with parameters for Course() that just combined it with the setter function for Course(). I removed it.  So I removed it. 
#### Dynamic Memory Allocation & Trie() deconstruction
I decided to not dynamically allocated the trie() but to dynamically allocate the nodes and the Course objects. During Trie deconstruction, I addressed deletion of the dynamically allocated memory by creating a bool data member for each trieNode called to_delete. This functions similarly to the visited bool variable/flag that one might find in certain versions of Breadth-First Searches in graphs. So this let me not ultimately re-attempt to delete eahc node because that was resuitlng in double free errors.it works!
#### Bad Design - unnecessary deletion in removeNode()
When I was writing the function to delete nodes, I made a bad design decision. I had the removeNode() function delete all nodes related to a course when removing it from the Trie (that is to say, after deleting a leaf node for the doom course, we would travel up to the Predecessor node and, if its only descendant was the doom leaf node, we would delete that internal node as well). The documentation I was referring to (see below) suggested that it may be better to simply mark the leaf node as a non-Leaf, point the Course object pointer to nullptr, and stop there. I took the advice and did so, relying on the deconstructor to handle node deletion.
#### Maintaining a data member instead of Writing a New Function
Originally, I planned to add a search function that calculated the number of Course pointers in the Trie, but decided to wait because it was complicated to do early in the project. I made a good decision to delay implementation of the getNumWords() function because when I re-visited the topic, I realized it would be very easy to create a private data member for Trie to track this value. So I created an int numWords variable in the Trie class, added a setter and getter function pair, and had the Trie increment the value when courses were added and decremented the value when a course was removed.
### Prefix Autocomplete
As noted above, prefix autocomplete is a critical benefit of the Prefix Tree. In working to implement autocomplete, I found that that after calling autocomplete once,  calls yielded no results after the first call. Since multiple calls in a given 'session' is part of the desired functionality, I needed to debug this issue. The issue was simply that my method of tracking nodes I had 'searched' for possible Course matches, relied on a bool variable for prefix searches. If the flag was true, we had already visited it and it wouldn't be searched for a course match. 
However, after the first call, the flags were never reset because the tree was still active. So I added a simple line at the end of the search where each visited node was marked as 'false' and could be visited again.
### Custom Class Capitalization
I updated the class capitalization to match what Prof. Guinn shared was more in alignment with industry expectations:
-trie() to Trie()
-trieNode() to TrieNode()
### Web UI Implementation
I worked with Prof. Guinn to get some files and general instructions to implement a Web UI for the user interface. 
#### Compilation Commands
The first mistake was that I did not include all of my project's .cpp files in the command to compile the project. Once I did so, the project files compiled.
The second mistake was trying to figure out why the -O2 flag command in this command line was not working. 
  g++ -std=c++17 <strong>-O2</strong> server_main.cpp trie_server.cpp Trie.cpp TrieNode.cpp Course.cpp-o trie_server
I ultimately removed it, my basic web searching suggested that some versions of the VS code compiler struggle with the flag. 
#### File Pathing Variations
After finishing my own test cases, I started working on the file pathing for the web UI commands but I kept receiving this error message when I tried to run the web UI.
  ->file not open<-
  Starting trie HTTP server on http://localhost:8080
  Open: http://localhost:8080/index.html
Despite my test suite being able to access the file using "./code/static/test_cirt_data.csv", the server files could not open it using that filename. After attempting several iterations, the server file needed just the csv's file name without the pathing directions because it was in the same folder as the trie_server executable. So I updated my buildTrie() command to accept a string parameter with the filename, letting me use the path-containing string for my test suite and then the path-less string for the server file. This also put buildTrie() more in alignment with the commmand.
#### Network Issues
Thanks to Prof. Guinn, he resolved a network issue that resolved a loookup error message anytime I tried to run searches using the html page: "Request failed: TypeError: NetworkError when attempting to fetch resource."
### Command-Line Interface Output
The first attempt at the project relied on a Command-Line interface. The following were some errors I worked through for that version of the implementation.
#### Stripping Whitespace, Data Preprocessing
I encontered a series of issues with string input and output but they were relatively simple to resolve. These were, admittedly, primarily due to lack of familiarity with stringstream manipulation and the <iomanip> library. After a couple of hours fixing bugs related to output (e.g., removing whitespace from the beginning and end of strings) the output started to consistently work as expected to the console.
#### Word Wrapping
One function that gave me more difficulty was word wrapping. The issue was identifying how to best calculate the conditions for when we should insert a newline into the stringstream that would ultimately be stored in string and then output to the console. At first, I tried to directly compare the line width with a counter, but this resulted in a generally consistent output but did not stop certain lines from exceeding the line width parameter. I resolved the issue by calculating a 'gap_to_end' variable and if the distance to the end of the current line was smaller than the length of the next word, the function inserts a newline character to the string stream. This resolved the issue.
## Future Work
The following are areas of improvement that could improve the project.
### Section-Differentiated Courses
A challenge in implementing the trie is the (rare) circumstance where multiple courses
share a course title. For example, Special Topics courses share a subject code but have
unique section-level titles. I plan to address this by adding Course object pointers to the
Special Topics node for each section. In initial implementation, CIRT will output all course
data for each Special Topics section upon request. Time permitting, I will ask the user for
input to isolate the desired section title and then output only the relevant section’s
information.
### Search-by-Title / Partial Title Option
I hope to be able to add a search-by-title option. Instead of remaking a new trie, 
I would, within the trie structure, contain a 'dictionary' map structure where each
 course is added to the map, where the keys are the Course titles and the values are the subject codes.
 Then when the user provided the course title, I would search the map for a key, and if it existed,
 then call the search and output functions based on the 'value' of the found key:value pair,
 the course subject code.