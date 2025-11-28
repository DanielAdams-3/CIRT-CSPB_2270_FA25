#include "TrieNode.h"

using namespace std;

//constructor
TrieNode::TrieNode()
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
TrieNode::~TrieNode()
{
    //DONE    
}
void TrieNode::markDeletion(bool new_status)
{
    this->to_delete=new_status;
}

bool TrieNode::getDeleteStatus()
{
    return this->to_delete;
}
bool TrieNode::getPrefixFlag()
{
    return this->prefix_finder;
}
void TrieNode::setPrefixFlag(bool new_flag_val)
{
    this->prefix_finder=new_flag_val;
}
TrieNode* TrieNode::getPredecessor()
{
    return this->predecessor;
}
void TrieNode::setPredecessor(TrieNode* new_predecessor)
{
    this->predecessor=new_predecessor;
}
bool TrieNode::getLeafStatus()
{
    return this->isLeaf;
}
void TrieNode::setLeafStatus(bool leaf_val)
{
    this->isLeaf = leaf_val;
}
Course* TrieNode::getCoursePtr()
{
    return this->coursePtr;
}
void TrieNode::setCoursePtr(Course* new_course_ptr)
{
    this->coursePtr = new_course_ptr;
}