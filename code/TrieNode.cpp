#include "TrieNode.h"

using namespace std;

//constructor, set default values
trieNode::trieNode()
{
    //READY-TO-TEST
    predecessor=nullptr;
    isLeaf=false; //true only when we reach the end of the course subject code
    
    //REFLECTION - the trie structure relies on more efficient ways of capturing what words are listed than what I initially tried
    for (long unsigned int i=0;i<38;i++)
    {
        descendants.push_back(nullptr);
    }
    coursePtr=nullptr;
} 

//destructor
trieNode::~trieNode()
{
    //REVISIT WHEN READY TO DO DYNAMIC MEMORY ALLOCATION
} 

//returns a pointer to the node's predecessor;
trieNode* trieNode::getPredecessor()
{
    return this->predecessor;
}
//sets the node's predecessor pointer to what is passed as a parameter;

void trieNode::setPredecessor(trieNode* new_predecessor)
{
    this->predecessor=new_predecessor;
}

bool trieNode::getLeafStatus()
{
    return this->isLeaf;
}

void trieNode::setLeafStatus(bool leaf_val)
{
    this->isLeaf = leaf_val;
}

Course* trieNode::getCoursePtr()
{
    return this->coursePtr;
}
void trieNode::setCoursePtr(Course* new_course_ptr)
{
    this->coursePtr = new_course_ptr;
}