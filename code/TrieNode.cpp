#include "TrieNode.h"

using namespace std;

//constructor
trieNode::trieNode()
{
    predecessor=nullptr;
    isLeaf=false; 
    to_delete = false;
    prefix_finder = false;
    
    for (long unsigned int i=0;i<38;i++)
    {
        descendants.push_back(nullptr);
    }
    coursePtr=nullptr;
} 
//destructor
trieNode::~trieNode()
{
    //DONE    
}
void trieNode::markDeletion(bool new_status)
{
    this->to_delete=new_status;
}

bool trieNode::getDeleteStatus()
{
    return this->to_delete;
}
bool trieNode::getPrefixFlag()
{
    return this->prefix_finder;
}
void trieNode::setPrefixFlag(bool new_flag_val)
{
    this->prefix_finder=new_flag_val;
}
trieNode* trieNode::getPredecessor()
{
    return this->predecessor;
}
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