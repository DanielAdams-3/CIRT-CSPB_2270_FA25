#ifndef TRIE_H__
#define TRIE_H__

#include "TrieNode.h"
#include "Course.h"
#include <fstream>
#include <iomanip>

class trie{
    private:
        int numWords; //number of courses in the subtree
        trieNode* root; //root of the tree;
        bool userStatus;

    public:
        trie(); //constructor
        ~trie(); //destructor
        void treeDeleter(trieNode* subtreeRoot, vector<trieNode*>& to_delete);
        
        void setRoot(trieNode* new_root);
        trieNode* getRoot(); //returns a pointer to the node parameter;

        void setNumWords(int new_val); //returns the number of courses in the Trie
        int getNumWords();

        //set up the string streams and prep the data to be read
        vector<Course*> readData(string file_name);

        //search/traversal function to help with insert_node as well
        bool searchTrie(string course_to_find);
        
        //this function creates and inserts a new node into the tree in the tree
        //if the searchTrie(string course_to_find) function returns false
        void insertNode(Course* course_to_add); //be sure to call searchTrie
        void removeNode(string doom_course_subject_code); 

        //we build the Trie as we read data from csv fstream
        //once this is done, we will be able to interact with the user
        void buildTrie(); 

        /*auto-complete options let's the user pass in a prefix that is less than or equal to the length of every course subject code.
        bool startsWithPrefix(string prefix);*/

        //user interaction functions
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