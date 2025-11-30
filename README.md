# Course Project - Trie (Prefix Tree) Implementation
Daniel Adams
CSPB 2270 Data Structures
Fall 2025 - Prof. Guinn
The project must be submitted by December 4 at 11:59pm MT.
## About the Project
Create a course information retrieval tool (CIRT), based on a trie (prefix tree) data structure.
The project will output course information based on a user-provided input string (course subject code).
## Video Summary
//TODO
## Project Goals
The goal is to create a rapid retrieval tool for pre-consolidated course information. CIRT will use a trie data structure, allowing a user to quickly access a comprehensive set of course information with one interface and limited required interactions. The prefix tree will be built and then available to be searched by the user. Trie leaf nodes will store a pointer to a Course object which will contain the stored course information. CIRT should quickly output the course information for the course matching the user-provided subject code. If the course does not exist, the program will notify the user of the failed search.
## Data Structure - Tries (Prefix Trees)
A trie is a tree made up of nodes, each of which represents a string character and points to as few as zero child nodes and may point to more than two child nodes. Each node has a vector pre-initialized with the number of possible characters that could be used (ex: 26 for each letter of the English alphabet). To indicate a node represents "C", for example, it would occupy index 2 of its predecessors' vector. This differs from binary trees whose nodes point to, at most, two child nodes. The traversal path, reminiscent of a Huffman tree, represents the full course subject code (ex: CSCI-5981) in this trie.
When a new course is added to the trie, new nodes are only created for the course's string characters that differ from the existing courses. When a course is removed, the trie would only need to delete the nodes that are unique to the to-be-removed course. This implementation instead un-marks the doom course's leaf node so it's no longer considered a leaf, reassigns the Course pointer to nullptr, and decrements the count of courses in the trie, which is tracked internally. Node deletion in this implementation are only done in tree deconstruction to reallocate dynamic memory.
Due to the storage method, search, insertion, autocomplete, and removal have a complexity of O(N), where N is the length of the subject code. Since these codes are only 9 characters in length, the actual execution time is short. 
Autocomplete using a prefix is a key feature of tries. Because we use prefix trees to store strings, we can provide a list of suggestions based on the leaf nodes in a given sub-tree. We just use a modified version of the Search function. If the user-provided string results in no results due to a character mismatch, we return no results. If the user-provided string has no remaining characters to read but we are still able to traverse the tree, we return a list of suggestions, consisting of all the leaf nodes in the sub-tree formed by the internal node we are currently at.
The trie is only built once and remains active until the user closes the program. The only actions taken by the user are Search & AutoComplete (modified search).

## Running the Demo - Instructions
#### 1. Download the repo
#### 2. Navigate to the ./code folder
#### 3. Run this command in the terminal:
##### g++ -std=c++17 server_main.cpp trie_server.cpp TrieNode.cpp Trie.cpp Course.cpp  -o trie_server
#### 4. Once it compiles, run this command in the terminal
##### ./trie_server 
#### 5. If the server runs as expected, copy the provided hyperlink
##### IMPORTANT - replace the phrase in <> (<daad2295>) with the identifier you use for JupyterLab
#### 6. Paste the edited hyperlink into a new tab and go
#### 7. Page should be active and you can use the Search and Autocomplete functions as described

## CIRT Implementation
My implementation of a Trie is built on the following file and data structures.
### test_cirt_data.csv
  This is the dataset I created and formatted for this task.
### Course
  ##### private:
    string courseSubjectCode;
    string courseDescription;
    string courseNotes;
    string courseTitle;
    string regRestricts; 
    string courseHours;
    string skillsLearnt;
  ##### public:
    Course();
    ~Course();
    map<string, string> plansNreqs;
    void getCourseInfo(string& title, string& description, string& notes, string& subjectCode, string& restricts, map<string,string>& plansandreqs, string& numHours, string& SkillsLearnt);
    void setCourseInfo(string new_title, string new_description, string new_notes, string new_subjectCode, string new_restricts, string new_plans, string num_hours, string newSkillsLearnt);
    //NOTE - The setter and getter functions also have companion setter/getters for each individual variable which simplifies various assignments and string parsing tasks.
    map<string, string> getPlansAndReqs();
    string getCreditHours();
    string getSkillsLearnt();

### TrieNode
  ##### private:
    TrieNode* predecessor;
    bool isLeaf; //true only when we reach the end of the course subject code
    Course* coursePtr; //for leaf node's only, to point at a dynamically allocated course object
    bool to_delete;
    bool prefix_finder;  
  ##### public:
    vector<TrieNode*> descendants;
    TrieNode();
    ~TrieNode();
    void markDeletion(bool new_status);
    bool getDeleteStatus();
    TrieNode* getPredecessor();
    void setPredecessor(TrieNode* new_predecessor);
    bool getLeafStatus();
    void setLeafStatus(bool leaf_val);
    Course* getCoursePtr();
    void setCoursePtr(Course* new_course_ptr);
    bool getPrefixFlag();
    void setPrefixFlag(bool new_flag_val);

### Trie
  ##### private:
    int numWords; //number of courses in the subtree
    TrieNode* root;
    bool userStatus; //used in command-line output
  ##### public:
    Trie(); //constructor
    ~Trie(); //destructor
    void treeDeleter(TrieNode* subtreeRoot, vector<TrieNode*>& to_delete);
    void setRoot(TrieNode* new_root);
    TrieNode* getRoot(); //returns a pointer to the node parameter;
    void setNumWords(int new_val); //returns the number of courses in the Trie
    int getNumWords();
    vector<Course*> readData(string file_name);
    bool searchTrie(string course_to_find);
    bool contains(string word);
    void insertNode(Course* course_to_add); //be sure to call searchTrie
    void removeNode(string doom_course_subject_code); 
    void buildTrie(string filename); 
    bool load(const string& filename);
    vector<string> autocomplete(const string& prefix, size_t max_results);
    vector<Course*> startsWithPrefix(string prefix);
    void prefixFinder(TrieNode* currentNode, vector<TrieNode*>& searchForMatches);
    Course* swapCodeforPtr(string course_subject_code);
    //NOTE: The following functions were used in an earlier version of output through a Command-Line Interface
    void outputCourseData(string course_subject_code);
    void getUserInput();
    void setUserStatus(bool new_status);
    bool getUserStatus();
    string consoleOutputWordWrapping(string course_subject_code, const int WIDTH_OF_LINE);

### Output Files for a Trie Server - with support from Prof. Guinn
Thanks to Prof. Guinn, I have a series of related files that host a simple front-end web user-interface through JupyterLab. 
  #### trie_server.h
    void start_trie_server(Trie& dict);
  #### server_main.cpp
  #### httplib.h
    //Copyright (c) 2025 Yuji Hirose. All rights reserved. MIT License
  #### index.html

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
The first issue that I experienced was procedural. I did not physically map the relationship between the Node and the Course classes clearly during ideation and planning, which resulted in erroneous understandings that I had to address during implementation. I corrected various logic errors in function calls and parameters, and removed superfluous functions and data members. For example, when I first created the Nodes, I thought the course was initially going to be directly stored in the leaf nodes. However, this would have made the nodes bloated and more difficult to read in data from the /csv file, so I separated course information into a separate class. The final structure is much cleaner and easie to understand.
### String Manipulation
As with previous assignments, there was some difficulty in reading in string data from a file. Thanks to the cpp documentation on the cpp website (see resources), these syntax errors were resolved. I also addressed this by doing data preparation beforehand in the csv file. Since many strings in the course descriptions and coures notes contain commas, I could not rely on comma-separated values alone to distinguish values in each cell. I added a '*' character at the end of each data value to facilitate easier reading. A tab-separated file may have sufficiently resolved this as well.
### Trie Implementation Notes
#### Node Insertion Logic Error
When implementing the trie, I  initially made a logic error. When first building the prefix tree, the trie was storing all new nodes in the root's descendants vector. After first node insertion, the root's descendants vector stored one trieNode* for each character in the first string. The issue occured during the second course insertion. Because both courses shared the same subject code ("CSCI"), the root's descendants vector could not be added to the tree. There was no space for it to be added because no new levels were being added to the tree. I fixed this by adding a line in the insert function to update the cursor value to the appropriate descedant of the current vector when there was not a nullptr in that index.
#### Unnecessary Helper Function
During initial implementation, I created a helper function to create a new Course object whenever I reached a leaf node, called createCourse(...). This function would create and popoulate a Course object with the relevant data read from the .csv file. It would also add a pointer to the course object and assign it in the leaf node. While I thought it would be helpful, this endd up creating an alternate constructor with parameters for Course(). Since this added some confusion and was not necessary, I removed it. 
#### Dynamic Memory Allocation & Trie() deconstruction
I decided to not dynamically allocated the trie() but to dynamically allocate the nodes and the Course objects. During Trie deconstruction, I addressed deletion of the dynamically allocated nodes by creating a bool data member for each trieNode, to_delete. This functions similarly to the visited bool variable/flag that one might find in certain versions of Breadth-First-Search for graphs, because it let me know which nodes I had 'visited' and marked for deletion. Without the bool, it would be very easy to attempt to free the memory twice for a given node.
#### Bad Design - Unnecessary Deletion in removeNode()
When I was writing the function to delete nodes, I made a bad design decision. I had the removeNode() function delete all nodes related to a course when removing it from the trie. After deleting a leaf node for the doom course, I would travel up to the dooom node's predecessor and if there was only one descendant (the leaf node), I would delete that internal node as well. The documentation I was referring to (see references) suggested that it was also acceptable to simply mark the leaf node as a non-leaf, reassign the node's Course* pointer to nullptr, and stop. I took the advice and did so. As noted previously, I decided to rely on the deconstructor to handle node deletion.
#### Maintaining a Data Member instead of Writing a New Function
Originally, I planned to add an internal search function that calculated the number of Course pointers in the trie. I decided to wait to implement this function because it was complicated to do before I had finished implementing the structure of the trie. When I re-visited the topic, I realized it would be very easy to create a private data member for trie objects to track this value. I created an int numWords variable in the Trie class, added a setter and getter function pair, and had the InsertNode and RemoveNode functions update the value accordingly.
### Prefix Autocomplete
As noted above, prefix autocomplete is a critical benefit of the Prefix Tree. In working to implement autocomplete, I found that after calling autocomplete once, subsequent calls yielded no results. Since multiple calls in a given 'session' is part of the desired functionality, I needed to debug this issue. The issue was simply that my method of tracking nodes I had 'searched' for possible Course matches relied on a bool variable. If the flag was true, we had already visited it and it would not be searched for a course match. However, after the first call to autocomplete, the flags were never reset because the tree was still active and had not been deconstructed and rebuilt. I resolved this by adding a line at the end of the autocomplete search to mark each visited node as un-visited so future searches could visit them.
### Custom Class Capitalization
I updated the class capitalization to match what Prof. Guinn shared was more in alignment with industry expectations:
  trie() to Trie()
  trieNode() to TrieNode()
### Web UI Implementation
I worked with Prof. Guinn to identify some libraries and general instructions to implement a Web UI for the user interface. 
#### Compilation Commands
The first mistake was that I did not include all of my project's .cpp files in the command to compile the project. Once I did so, the project files compiled.
The second issue was related to the -O2 flag command in this command line:
  g++ -std=c++17 <strong>-O2</strong> server_main.cpp trie_server.cpp Trie.cpp TrieNode.cpp Course.cpp-o trie_server
I ultimately removed it because it was preventing basic compilation. My basic web searching suggests that the VS Code IDE can struggle with that flag, depending on the version used.
#### File Pathing Variations
After finishing my own test cases, I started working on the file pathing for the web UI commands but I kept receiving this error message when I tried to run the web UI.
  ->file not open<-
  Starting trie HTTP server on http://localhost:8080
  Open: http://localhost:8080/index.html
Despite my test suite being able to access the file using "./code/static/test_cirt_data.csv", the server files could not open it using that filename. After attempting several iterations, the server file needed just the csv's file name without the pathing directions because it was in the same folder as the trie_server executable.
So I updated my buildTrie() command to accept a string parameter with the filename, letting me use the path-containing string for my test suite and then the path-less string for the server file. This also made the buildTrie() function in the Trie class more flexible.
#### Network Issues
Thanks to Prof. Guinn, he resolved a network issue that resolved a loookup error message anytime I tried to run searches using the html page: "Request failed: TypeError: NetworkError when attempting to fetch resource." This required me to use a different locally hosted URL for the web UI since the program uses JupyterHub as a proxy server.
### Command-Line Interface Output
The first attempt at the project relied on a Command-Line Interface. The following were relevant errors I resolved for that version of the output.
#### Stripping Whitespace, Data Preprocessing
I encontered a series of issues with string input and output but they were relatively simple to resolve. These were the result of my lack of familiarity with stringstream manipulation and the <iomanip> library. After a couple of hours fixing bugs related to output (e.g., removing whitespace from the beginning and end of strings) the output started to consistently work as expected to the console.
#### Word Wrapping
Word wrapping was a challenge. The primary issue was identifying how to best calculate the conditions for when to insert a newline into the stringstream so it would appear in output appropriately. At first, I tried to directly compare the line width of each line with a counter, but this resulted in a generally consistent output that often exceeded the intended line width parameter.
I resolved the issue by calculating a gap_to_end int variable. If the distance to the end of the current line was smaller than the length of the next word, the function inserted a newline character to the string stream. 

## Future Work
The following are areas of improvement that could improve the project.
### Section-Differentiated Courses
A challenge in implementing the trie is the (rare) circumstance where multiple courses share a course title. For example, Special Topics courses (CSCI-7000) share a subject code but have unique section-level titles. I would plan to address this by adding Course object pointers to the Special Topics node for each section. In initial implementation, CIRT would output all course data for each Special Topics section upon request. Then I would ask the user for input to isolate the desired section title and then output only the relevant section’s information.
### Search-by-(Partial)-Title Option
I was unable to add a search-by-title option. Instead of remaking a new trie, I would, within the trie structure, contain a 'dictionary' map structure where each course is added to the map, where the keys are the course titles and the values are the subject codes. Then when the user provided the course title, I would search the map for a key, and if it existed, then call the search and output functions based on the associated value, the course subject code.