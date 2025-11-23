#ifndef TRIE_H__
#define TRIE_H__

#include "TrieNode.h"
#include "Course.h"
#include <fstream>

class trie{
    private:
        //int numWords; //number of courses in the subtree (recursively call?)
        trieNode* root; //root of the tree;

    public:
        trie(); //constructor
        ~trie(); //destructor
        void setRoot(trieNode* new_root);
        trieNode* getRoot();

        //helper function
        //to create a new course, setCourseInfo(title, description, notes, code, leartn, plans/reqs)
        //and we add it to the vector we just created
        Course* createCourse(string new_title, string new_description, string new_notes, string new_subj_code, string new_skills, string new_plans, string new_hours);

        //set up the string streams and prep the data to be read
        vector<Course*> readData(string file_name);

        //search/traversal function to help with insert_node as well
        bool searchTrie(string course_to_find);
        void insertNode(Course* course_to_add); //be sure to call searchTrie
        void removeNode(string doom_course_subject_code); 


        //this  is the function
        //where we build the Trie as we read data from csv fstream
        //once this is done, we will be able to interact with the user
        void buildTrie(); 

        //user interaction functions
        //void outputResults
        //void getUserInput

        /*auto-complete options let's the user pass in a prefix
        bool startsWithPrefix(string prefix);*/
};

#endif //TRIE_H__