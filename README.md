# Course Project - Trie (Prefix Tree) Implementation
Daniel Adams
CSPB 2270 Data Structures
Fall 2025 - Prof. Guinn
The project must be submitted by December 4 at 11:59pm MT.
## About the Project
Create a course information retrieval tool (CIRT), based on a trie (prefix tree) data structure.
The project will output course information based on a user-provided input string (course subject code).
### Project Functionality
The goal was to create a rapid retrieval tool for pre-consolidated course information. CIRT uses a trie data structure, allowing a user to quickly access a comprehensive set of course information with one interface and limited required interactions. The prefix tree will be built and then available to be searched by the user. 
### Search by User
The first function that the user will be able to use is searching for course informatoin by providing a 9-digit string representing a course subject code (e.g., CSCI-5202). If the course is in the trie, it will output all of the stored course information with headers for each section (e.g., CREDIT HOURS, 3). There are error messages provided based on scenarios such as whether the server is active, whether the input is of acceptable length, and if the course subject code does not match anything in the trie. Multiple requests can be made in a single session.
### AutoComplete (Prefix Search) by User
The second function that the user will be able to use is to receive suggestions through a partial search. The user provides a string of minimum length 1 and maximum length 9 charactesr to get a list of courses whose first 'n' characters match the user-provided string of length 'n'. As long as there are any course subject codes taht match the user-provided string, all matching course subject codes will be displayed to the user (along with the corresponding course title). Then the user can copy the relevant course subject code and paste it into the Search function to access that course's information. There are error messages provided based on scenarios such as whether the server is active, whether the input is of acceptable length, and if the course subject code prefix does not match anything in the trie. Multiple requests can be made in a single session.

## Brief Overview
### Reading in Data
To start, the program reads in data. This is done by calling buildTrie which itself calls readData.
  void trie::buildTrie(string filename);
  void trie::readData(string filename);
The buildTrie function reads in data, creates a vector of Course* popoulated with the course information, creates a new Trie object, then populates the trie with each course until the vector is done iterating.
### Building the Trie
A new Trie is initialized, a dynamically allocated root TrieNodeode is created, and the Trie creates a series of dynamically allocated TrieNodes based on the course subject codes. At the end of each path is a leaf node that represents the final character in each string. Each leaf node stores a pointer to a Course object which will contain the stored course information. 
### Starting the Server
Once the trie is built, the server will be created and is ready to be used. The locally-hosted web address that is associated with the server is provided to output. 
### User can use the tool
Once at the web address, the user can use the tool for searches or to get autocomplete suggestions.

## Video Walkthrough
//IN PROGRESS

## Running the Demo - Instructions
#### 1. Download the repo
#### 2. Navigate to the ./code folder
#### 3. Run this command in the terminal:
##### g++ -std=c++17 server_main.cpp trie_server.cpp TrieNode.cpp Trie.cpp Course.cpp  -o trie_server
#### 4. Once it compiles, run this command in the terminal
##### ./trie_server 
#### 5. If the server runs as expected, copy the provided hyperlink AND -- make the following edit:
##### Replace the bracketed text (<daad2295>) with your appropriate JupyterHub/Lab identifier
#### 6. Paste the edited hyperlink into a new tab and press Enter
#### 7. Page should be active and you can use the Search and Autocomplete functions as described

## Data Structure - Trie (Prefix Tree)
### About Tries
A trie is a tree made up of nodes, each of which represents a string character and points to as few as zero child nodes and may point to more than two child nodes. Each node has a vector pre-initialized with the number of possible characters that could be used (ex: 26 for each letter of the English alphabet). To indicate a node represents "C", for example, it would occupy index 2 of its predecessors' vector. This differs from binary trees whose nodes point to, at most, two child nodes.
#### Traversal & Search
The traversal path represents a complete string based on how it is traversed. In this case, a full path through the trie represents a course subject code (ex: CSCI-5981). Each node in the tree represents a single character in the string. 
To traverse the tree, each trieNode does not contain a string character. Instead, we use the traversal path to track the string we store. Each TrieNode stores a vector called descendants of TrieNode* pointers. The vector is pre-initialized with 37 slots, each of which points to NULL. Each index is associated with one for the 37 possible characters we could read in the user input: A-Z are associated with indices 0-25, 26 is teh dash character, and indicies 27-36 are associated with the string characters 0-9. 
So to traverse the tree based on a string, we will calculate the index of each character by doing some index arithmetic. We can use the ASCII value of the current character and subtract it from an appropriate ‘base’ to provide the correct offset in the descendants vector. If the current character is a “C”, we subtract “C” and  “A”, giving us index 2. So we access the current node's descendants vector at index 2. To handle 0-9, we subtract the string “4” from string “0”, then add 26 to skip past “A-Z”. This indexing approach helps achieve faster traversal because we don’t need to iterate through each node’s descendant’s vector at every level of the trie. If we calculate an index and there’s a nullptr, for search, the function returns null.
#### Insertion
When a new course is added to the trie, new nodes are only created for the course's string characters that differ from the existing courses. Importantly, each node does not actually store the string character but instad the travel pathway helps us track the string we are storing. We use the same traversal method as with searching but whenever we reach a nullptr and need to insert a new node, we create a new node, insert at eh appropriate index, and proceed with creating a new node for each remaining character in the string.
#### Removal 
When a course is removed, the trie would only need to delete the nodes that are unique to the to-be-removed course. Because this implementation and use cases do not use this function, I simply un-marked the doom course's leaf node so it's no longer considered a leaf, reassigned the Course pointer to nullptr, and decremented the count of courses in the trie. Node deletion in this implementation are only done in tree deconstruction to reallocate dynamic memory.

### Why a Trie?
#### Usage Alignment
First, tries are desigend to work with strings, and since all the course information is string-based, there is natural alignment. 
Second, the trie is only built once and remains in-place until the user closes the program. The only actions taken by the user are Search & AutoComplete (modified search--see next section). As a result, the benefits of trie's excellent time complexity are well utilized.
#### AutoComplete (Prefix search)
Third, autocomplete using a prefix is a key benefit of tries. Because tries store each character as a separate node, tries can accept an input string of non-zero length and quickly provide a list of suggestions based on the existing trie. All that is needed is to modify the original search function to stop once there is a mismatch between the characters given and the available paths of the tree, or when the user input has stopped. In the second case, we return a list of suggestions pulled from the available leaf nodes in the subtree.
Put another way, if the user-provided string has no remaining characters to read but we are still able to traverse the tree up until the user-string ends, we can return a list of suggestions. The suggestions consist of all the leaf nodes in the sub-tree formed by the internal node we are currently at. And again, if the user-provided string results in no results due to a character mismatch, we return no results.
#### Time & Space Complexity
Search, insertion, autocomplete, and removal have a complexity of O(N), where N is the length of the subject code.
My implementation features very short actual run time because the course subject codes used are only 9 characters in length. Additionally, insertion only happens when the trie is built and there is not a use case for us to remove just one course from the trie. Trie deconstruction is the only time nodes are removed and deleted. 
The only two functions used repeatedly by the user are Search and AutoComplete which are efficient. As noted by GeeksforGeeks, "The main disadvantage of the trie is that it takes a lot of memory to store all the strings. For each node, we have too many node pointers which are equal to the no of characters in the worst case.". 
| Trie Operation | Time Complexity | Space Complexity |
| -------------- | --------------- | ---------------- |
| Insertion      | O(N)            | O(1)             |
| Deletion       | O(N)            | O(m*k)           |
| Search         | O(N)            | O(1)             |
| Prefix Search  | O(N)            | O(1)             |

  *n = length of string searched/inserted/removed
  **m = key length of longest word
  **k = total number of words

#### See the following for complexity information:
##### https://learn.zybooks.com/zybook/COLORADOCSPB2270DataStructuresGuinnFall2025/chapter/7/section/12 
##### https://www.geeksforgeeks.org/dsa/introduction-to-trie-data-structure-and-algorithm-tutorials/
##### https://www.geeksforgeeks.org/dsa/trie-insert-and-search/
##### https://www.geeksforgeeks.org/dsa/trie-delete/

## File Structure
Here is the breakdown of the repo.
### /code directory
#### Course Data
This folder holds the bulk of the program files.
##### /code/test_cirt_data.csv
This is the dataset I consolidated and formatted for this task. I originally tried to rely on comma-separated values but since there are commas within certain fields, I ultimately had to add '*' characters to the end of each cell to help parse each line.
#### Custom Classes
##### TrieNode.h & TrieNode.cpp
These support a custom class TrieNode. Each node contains a pointer to its predecessor, a pointer to a Course object (only used by leaf nodes), a bool value isLeaf to mark it as a leaf node, a bool value to_delete to help identify when we've visited a node that we need to dynamically deallocate, and a bool for prefix_finder so we know when we've visited a node to possibly suggest to the user for autocomplete. Each node also contains a vector of TrieNode* pointers called descendants.
  ```
  private:
    TrieNode* predecessor;
    bool isLeaf; //true only when we reach the end of the course subject code
    Course* coursePtr; //for leaf node's only, to point at a dynamically allocated course object
    bool to_delete;
    bool prefix_finder;
  public:
    vector<TrieNode*> descendants; //37 characters long, A-Z, 0-9, "-"
    TrieNode(); //constructor
    ~TrieNode(); //destructor
    void markDeletion(bool new_status);
    bool getDeleteStatus();
    TrieNode* getPredecessor(); //returns a pointer to the node's predecessor;
    void setPredecessor(TrieNode* new_predecessor); //use right after initializing a new node. sets the node's predecessor pointer to what is passed as a parameter;
    bool getLeafStatus();
    void setLeafStatus(bool leaf_val);
    Course* getCoursePtr();
    void setCoursePtr(Course* new_course_ptr);
    bool getPrefixFlag();
    void setPrefixFlag(bool new_flag_val);
```
##### Trie.h & Trie.cpp
These support a custom class Trie. Each trie stores the number of courses in the trie and a pointer to the root of the tree. 
  ```
  private:
    int numWords; //number of courses in the subtree
    TrieNode* root; //root of the tree;
    //bool userStatus;  //only used in the CLI version of input/output
  public:
    Trie(); //constructor
    ~Trie(); //destructor
    //helper function to deallocate memory called by the destructor function
    void treeDeleter(TrieNode* subtreeRoot, vector<TrieNode*>& to_delete);
    void setRoot(TrieNode* new_root);
    TrieNode* getRoot(); //returns a pointer to the root node;
    void setNumWords(int new_val); 
    int getNumWords(); //returns the number of courses in the Trie
    
    bool searchTrie(string course_to_find); //search/traversal function
    bool contains(string word); //calls searchTrie so it works with the trie_server files.

    void insertNode(Course* course_to_add); //calls searchTrie. Creates and inserts a new node into the tree in the tree. if the searchTrie(string course_to_find) function returns false
    void removeNode(string doom_course_subject_code); //removes a course from the trie by marking the leaf node as an intenal node, points Course* to nullptr, and decrements the trie's numWords variable by 1.
    
    void buildTrie(string filename); //buildTrie() calls readData we read data from csv fstream
    vector<Course*> readData(string file_name); //set up the string streams and prep the data to be read
    bool load(const string& filename); //calls buildTrie so it works with the trie_server files. 

    vector<string> autocomplete(const string& prefix, size_t max_results);//calls startsWithPrefix so it works with the trie_server files.
    vector<Course*> startsWithPrefix(string prefix);
    void prefixFinder(TrieNode* currentNode, vector<TrieNode*>& searchForMatches); //recursive helper function for startsWithPrefix;

    Course* swapCodeforPtr(string course_subject_code); //helper function to return a Course* for a given string subject code.
    
    //the following are related to CLI and are not used with the server implementation.   
    void outputCourseData(string course_subject_code);
    void getUserInput();
    void setUserStatus(bool new_status);
    bool getUserStatus();
    string consoleOutputWordWrapping(string course_subject_code, const int WIDTH_OF_LINE); ////this one returns a string that has been prepraed for Word wrapping
   ```
##### Course.h & Course.cpp
These support a custom classes Course that stores course information we read in from the .csv file. One course object corresponds to one row in the .csv file.
  ```
    private:
        string courseSubjectCode; //the main thing.
        string courseDescription; //from catalog or classes.colorado.edu
        string courseNotes; //from classes.colorado.edu
        string courseTitle; //catalog, etc.
        string regRestricts; 
        string courseHours;
        string skillsLearnt; //from 3. Skills Learnt

    public:

        Course(); //constructor, set variables to empty string, false and nullptr;
        ~Course(); //destructor
        map<string, string> plansNreqs; //from the csv
        
        void getCourseInfo(string& title, string& description, string& notes, string& subjectCode, string& restricts, map<string,string>& plansandreqs, string& numHours, string& SkillsLearnt);
        string getCourseSubjectCode(); //returns the entire subject code of the course
        string getCourseNotes(); //returns just the class notes
        string getCourseDescription(); //returns just the course description
        string getCourseTitle(); //return just the course title
        string getRegRestricts(); //returns just the skills learnt
        //returns the degree reqs as a string for given course_title. If key not found, return empty string
        //for a given key, return the mapped value of PlansandReqs as a string
        map<string, string> getPlansAndReqs();
        string getCreditHours();
        string getSkillsLearnt();

        //Set by calling each individual setter function
        void setCourseInfo(string new_title, string new_description, string new_notes, string new_subjectCode, string new_restricts, string new_plans, string num_hours, string newSkillsLearnt);
        void setCourseNotes(string new_notes); //called by setCourseInfo;
        void setCourseDescription(string new_description); //called by setCourseInfo;
        void setCourseSubjectCode(string new_subj_code);//called by setCourseInfo;
        void setCourseTitle(string new_title);//called by setCourseInfo;
        void setRegRestricts(string new_reg_restricts);//called by setCourseInfo;
        void setPlansandReqs(string degreePlansAndReqs); //we take in that string value and populate the map, separted by ';'
        void setCreditHours(string num_hours);
        void setSkillsLearnt(string new_skills)
  ```
#### Web UI for Input & Output
Thanks to Prof. Guinn for his support in implementation of the web interface.
##### /code/trie_server.h && /code/trie_server.cpp
Two of the files used in the web UI version of the input/output functionality
These support a trie server, a small HTTP server allowing access for the webpage to use my Trie search and autocomplete functions.
##### /code/server_main.cpp
One of the files used in the web UI version of the input/output functionality
This file sets up and runs the server, so this serves as the 'main.cpp' file for the web UI version of input/output.
##### httplib.h
One of the files used in the web UI version of the input/output functionality -Copyright (c) 2025 Yuji Hirose. All rights reserved. MIT License
This library is what lets us call http functions. It's an all-in-one library.
##### index.html
This html page is the web user interface.

### Run_App & Run_Tests Files - defunct
#### ./app directory & /test directory -- Run_App & Run_Tests Issue
Note that I refer to 'Run App' here and 'Run Tests' below because the program is structured like a homework; I used a homework repo as a template so 'Run App' and 'Run Tests' worked like in a homework. In VS Code, it's a debugging option you can select: <strong>Run Tests</strong> or <strong>Run App</strong>. 
These are no longer actively supported features but this does not affect the functionality of the program or the web UI.
However, once I integrated the new web UI, the file structure could not accommmodate this and therefore neither feature works as it did previously.
#### ./app directory
This directory stores main.cpp. This supports the original input/output mechanism facilitated through a Command-Line-Interface (CLI).  
##### /app/main.cpp
This file originally ran the 'Run Apps' button by reading the data from the .csv file (see below), building the trie, and handling input/ouput through the terminal via CLI. 
THis is no longer an actively supported feature and I was unable to make the necessary changes in time. This does not affect the functionality of the program or the web UI.
To 'Run App' or 'Run Tests', you would need to remove the server_main.cpp file, test_server.cpp/.h, the static directory, and httplib.h. Otherwise, the 'Run App' feature will not work because there are two files with main in them. 
#### /test directory 
This contains my test file.
##### /test/test_proj.cpp
This file contains my Unit tests for my 3 custom classes: Trie, TrieNode, and Course related function,s including setter/getters, constructor and deconstructors, key functions like buildTrie, readData, and more.
This is no longer an actively supported feature and I was unable to make the necessary changes in time. This does not affect the functionality of the program or the web UI.
As noted above, To 'Run Tests', you would need to remove the server_main.cpp file, test_server.cpp/.h, the static directory, and httplib.h. Otherwise, the 'Run Tests' feature will not work because there are two files with main in them. 

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
   ```
  ->file not open<-
  Starting trie HTTP server on http://localhost:8080
  Open: http://localhost:8080/index.html
  ```
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
### Hosting through Live, Persistent Server
If this tool is to be useful by others, I need to be able to host it through a service like AWS. I need to learn how to do that in order to share this, or another version of this tool, with my colleagues for more regular use.

## References & Resources
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
