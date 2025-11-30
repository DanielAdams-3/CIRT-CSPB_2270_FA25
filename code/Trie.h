#ifndef TRIE_H__
#define TRIE_H__

#include "TrieNode.h"
#include "Course.h"
#include <fstream>
#include <iomanip>

class Trie{
    private:
        int numWords; //number of courses in the subtree
        TrieNode* root; //root of the tree;
        //bool userStatus; 

    public:
        Trie(); //constructor
        ~Trie(); //destructor

        void setRoot(TrieNode* new_root);
        TrieNode* getRoot(); //returns a pointer to the node parameter;
        void setNumWords(int new_val); //returns the number of courses in the Trie
        int getNumWords();

        //helper function to deallocate memory called by the destructor function
        void treeDeleter(TrieNode* subtreeRoot, vector<TrieNode*>& to_delete);



        //search/traversal function
        bool searchTrie(string course_to_find);
        //server-specific function call - calls searchTrie;
        bool contains(string word);

        //this function creates and inserts a new node into the tree in the tree
        //if the searchTrie(string course_to_find) function returns false
        void insertNode(Course* course_to_add); //calls searchTrie
        void removeNode(string doom_course_subject_code); 

        
        //buildTrie() calls readData we read data from csv fstream
        //once this is done, we will be able to interact with the user
        void buildTrie(string filename); 
        //set up the string streams and prep the data to be read
        vector<Course*> readData(string file_name);
        //helper function for the server output
        bool load(const string& filename);
        //load is what we're doing to replace buildTrie();

        //server-specific function call - calls startsWithPrefix
        vector<string> autocomplete(const string& prefix, size_t max_results);
        //auto-complete options let's the user pass in a prefix that is less than or equal to the length of every course subject code.
        vector<Course*> startsWithPrefix(string prefix);
        //recursive helper function for startsWithPrefix;
        void prefixFinder(TrieNode* currentNode, vector<TrieNode*>& searchForMatches);
        
        //CLI input and output which were replaced by server_main.cpp, trie_server.cpp/.h, httplib.h, and index.html
        void outputCourseData(string course_subject_code);
        void getUserInput();
        void setUserStatus(bool new_status);
        bool getUserStatus();

        //helper functions for outputCourseData
        ////this one returns the Course* for a given course_subject_code
        Course* swapCodeforPtr(string course_subject_code);
        ////this one returns a string that has been prepraed for Word wrapping
        ////which is to say, it maintains a conssitent output every given characters
        string consoleOutputWordWrapping(string course_subject_code, const int WIDTH_OF_LINE);

};

#endif //TRIE_H__