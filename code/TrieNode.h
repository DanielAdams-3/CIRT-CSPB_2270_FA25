#ifndef TRIENODE_H__
#define TRIENODE_H__

#include "Course.h"
using namespace std;

class trieNode {
    private:
        trieNode* predecessor;
        bool isLeaf; //true only when we reach the end of the course subject code
        Course* coursePtr; //for leaf node's only, to point at a dynamically allocated course object
        bool to_delete;
        
    public:
        vector<trieNode*> descendants; //27 characters long, index 0 = '-' and rest are all capitals

        trieNode(); //constructor
        ~trieNode(); //destructor

        void markDeletion(bool new_status);
        bool getDeleteStatus();

        trieNode* getPredecessor(); //returns a pointer to the node's predecessor;
        void setPredecessor(trieNode* new_predecessor); //use right after initializing a new node. sets the node's predecessor pointer to what is passed as a parameter;
        
        bool getLeafStatus();
        void setLeafStatus(bool leaf_val);
        
        Course* getCoursePtr();
        void setCoursePtr(Course* new_course_ptr);

};
#endif //TRIENODE_H__