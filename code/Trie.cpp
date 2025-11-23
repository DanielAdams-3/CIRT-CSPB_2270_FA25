#include "Trie.h"

using namespace std;

//constructor, set default values
trie::trie()
{
    this->numWords=0;
    trieNode* root= new trieNode();
    this->setRoot(root);
} 

//destructor
trie::~trie()
{
    //DYNAMIC MEMORY ALLOCATION
    vector<trieNode*> to_delete;
    trieNode* cursor=this->getRoot();
    treeDeleter(cursor, to_delete);
    for (long unsigned int i=0;i<to_delete.size();i++)
    {
        trieNode* doom_node = to_delete.at(i);
        delete doom_node;
    }
} 

//recursively finds nodes to delete
void trie::treeDeleter(trieNode* subtreeRoot, vector<trieNode*>& to_delete)
{
    //TODO
    trieNode* cursor = subtreeRoot;
    for (long unsigned int i=0;i<cursor->descendants.size();i++)
    {
        if (cursor->descendants.at(i) != nullptr)
        {
            if (cursor->descendants.at(i)->getDeleteStatus() != true) //ISSUE, ADDING EVERY NODE MULTIPLE TIMES
            {
                to_delete.push_back(cursor->descendants.at(i));
                cursor->descendants.at(i)->markDeletion(true);
                treeDeleter(cursor->descendants.at(i), to_delete);
            }
        }
    }
    if (cursor->getDeleteStatus() != true)
    {
        to_delete.push_back(cursor);
        cursor->markDeletion(true);
    }
}

void trie::setRoot(trieNode* new_root)
{
    this->root = new_root;
}

//returns a pointer to the node parameter;
trieNode* trie::getRoot()
{
    return this->root;
}


//returns the number of courses in the Trie
int trie::getNumWords()
{
    return this->numWords;
} 

void trie::setNumWords (int new_val)
{
    this->numWords=new_val;
}

bool trie::searchTrie(string course_to_find)
{
    bool answer = false;
    if (this->getRoot() == nullptr)
    {
        cout << "error, root not set" << endl;
        return answer;
    }

    //set up a string stream to read the course
    //for resetting and clearing if needed https://www.geeksforgeeks.org/cpp/stringstream-c-applications/
    stringstream ss(course_to_find);
    char current;
    ss.get(current);
    while (current == ' ')
    {
        ss.get(current);
    }
    trieNode* cursor = this->getRoot();
    int index = 0;
    while (ss.eof() != true && current != ' ')
    {
        //CALCULATE THE INDEX OF THE CHARACTER
        if (current=='-') //special character
        {
            index = 26;
        }
        else //accounts for 0-10 in 2nd half of subject code
        {
            if ( static_cast<int>(current) < 58 && static_cast<int>(current) >= 48 )
            {
                int subject_num=static_cast<int>(current) - 48; //48 is the difference between 0-9 and the ASCII value
                index = subject_num + 27; //avoid first 27 slots in descendants indexing 26 letters, '-'
            }
            else
            {
                index = current - 'A';
            }
        }
        //CHECK THE INDEXED THE LOCATION IS A POINTER OR NULLPTR - IF IT'S NULL, WE RETURN FALSE
        if (cursor->descendants.at(index) == nullptr) 
        {
            return answer;
        }
        //prep for next loop
        cursor=cursor->descendants.at(index); //REFLECTION
        ss.get(current);
        index = 0;
    }

    if (cursor->getLeafStatus() == true && cursor->getCoursePtr()->getCourseSubjectCode() == course_to_find)
    {
        answer=true;
    }
    return answer;
}

void trie::insertNode(Course* course_to_add)
{
    bool node_exists=this->searchTrie(course_to_add->getCourseSubjectCode());

    if (node_exists == true)
    {
        return;
    }
    //if the tree has no root;
    if (this->getRoot() == nullptr)
    {
        trieNode* new_root = new trieNode();
        this->setRoot(new_root);
    }
    trieNode* cursor=this->getRoot();

    //set up a string stream to read the course
    //for resetting and clearing if needed https://www.geeksforgeeks.org/cpp/stringstream-c-applications/
    stringstream ss(course_to_add->getCourseSubjectCode());
    char current;
    ss.get(current);
    while (current == ' ')
    {
        ss.get(current);
    }
    int index = 0;
    while (ss.eof() != true)
    {
        //CALCULATE THE INDEX OF THE CHARACTER
        if (current=='-') //special character
        {
            index = 26;
        }
        else //accounts for 0-10 in 2nd half of subject code
        {
            if ( static_cast<int>(current) < 58 && static_cast<int>(current) >= 48 )
            {
                int subject_num=static_cast<int>(current) - 48; //48 is the difference between 0-9 and the ASCII value
                index = subject_num + 27; //avoid first 27 slots in descendants indexing 26 letters, '-'
            }
            else
            {
                index = current - 'A';
            }
        }

        //CHECK THE INDEXED THE LOCATION IS A POINTER OR NULLPTR - IF IT'S NULL, we create a new node.
        if (cursor->descendants.at(index) == nullptr) 
        {
            //create a new node, UPDATE POINTER FROM CURRENT NODE, set predecessor and stuff
            trieNode* next_node = new trieNode();
            next_node->setPredecessor(cursor);
            cursor->descendants.at(index) = next_node;
        }
        //prep for next loop
        cursor=cursor->descendants.at(index);
        ss.get(current);
        index = 0;
    }
    cursor->setLeafStatus(true);
    cursor->setCoursePtr(course_to_add);
    this->setNumWords(this->getNumWords() + 1);
}

//REFLECTION
/*helper function - DELETE
Course* trie::createCourse(string new_title, string new_description, string new_notes, string new_subj_code, string new_skills, string new_plans, string new_hours)
{
    //DONE
    Course* course_ptr=nullptr;
    course_ptr = new Course();
    course_ptr->setCourseInfo(new_title, new_description, new_notes, new_subj_code, new_skills, new_plans, new_hours);
    return course_ptr;
}*/


void trie::removeNode(string doom_course_subject_code)
{
    //DONE
    if (searchTrie(doom_course_subject_code) == false)
    {
        return;
    }
    trieNode* cursor=this->getRoot();
    trieNode* predecessor=nullptr;

    stringstream ss(doom_course_subject_code);
    char current;
    ss.get(current);
    while (current == ' ')
    {
        ss.get(current);
    }
    int index = 0;
    while (ss.good() == true)
    {
        index = 0;
        //CALCULATE THE INDEX OF THE CHARACTER
        if (current=='-') //special character
        {
            index = 26;
        }
        else //accounts for 0-10 in 2nd half of subject code
        {
            if ( static_cast<int>(current) < 58 && static_cast<int>(current) > 48 )
            {
                int subject_num=static_cast<int>(current) - 48; //48 is the difference between 0-9 and the ASCII value
                index = subject_num + 27; //avoid first 27 slots in descendants indexing 26 letters, '-'
            }
            else
            {
                index = current - 'A';
            }
        }
        /*GOT THIS OF THIS - PUT IT AFTER WE ARRIVE AT THE RIGHT LOCATION.
        //CHECK THE INDEXED THE LOCATION IS A POINTER OR NULLPTR - IF IT'S NULL, we should skip
        if (cursor->descendants.at(index) != nullptr) 
        {
            predecessor=cursor;
            cursor=cursor->descendants.at(index);

            //remove reference from doom node
            if (cursor->getLeafStatus() == true)
            {
                predecessor->descendants.at(index) = nullptr;
            }
        }*/
        //prep for next loop
        if (cursor->descendants.at(index) != nullptr)
        {
            ss.get(current);
            cursor=cursor->descendants.at(index);
        }
    }
    
    //verify we're in the right spot and process
    if (cursor->getLeafStatus() == true)
    {
        Course* leafCoursePtr = cursor->getCoursePtr();
        string leaf_course_code=leafCoursePtr->getCourseSubjectCode();
        predecessor=cursor->getPredecessor();
        if (leaf_course_code == doom_course_subject_code)
        {
            cursor->setLeafStatus(false);
            predecessor->descendants.at(index)=nullptr;
            cursor->setCoursePtr(nullptr);
            this->setNumWords(this->getNumWords() - 1);
        }
    }

    //REFLECTION
    //keep checking predecessor nodes and deleting them IF there are no other node* in the descendants.
    //don't need to do this. may need to re-add, will be deleted all later anyway. 
    /*bool done = false;
    int counter=0;
    while (!done)
    {
        //check the predecessor's descendants for other nodes, and to clear out this one
        for (long unsigned int i=0;i<predecessor->descendants.size();i++)
        {
            if (cursor->descendants.at(i) != nullptr)
            {
                counter++;
            }
            if (cursor->descendants.at(i) == cursor)
            {
                cursor->descendants.at(i) = nullptr;
            }
        }
        
        //if we're at the root, we still need to update its descendants, which we did.
        if (cursor == this->getRoot())
        {
            done=true;
        }

        else //not the root
        {
            delete cursor;
            if (counter > 1)
            {
                done = true;
            }
            else
            {
                cursor = predecessor;
                predecessor=cursor->getPredecessor();
                counter=0;
            }
        }
    }*/
}
/*
bool trie::startsWithPrefix(string prefix)
{
    bool answer = false;
    return answer;
}*/

//set up the string streams and prep the data to be read
//https://www.geeksforgeeks.org/cpp/how-to-read-data-from-csv-file-to-a-2d-array-in-cpp/
vector<Course*> trie::readData(string file_name)
{
    vector<Course*> courses_to_insert_into_trie;

    string all_data_as_string="";
    ifstream readf;
    readf.open(file_name);

    //error handling
    if (readf.is_open() != true)
    {
        cout << "file not open" << endl;
        return courses_to_insert_into_trie;
    }
    if (readf.good() != true)
    {
        cout << "stream error" << endl;
    }
    //read all data into one big line; we'll use string streams later to split it up by ',' and endline.
    while(readf.eof() != true)
    {
        string csv_line="";
        //connect the string stream so it's ready
        //https://www.geeksforgeeks.org/cpp/getline-string-c/
        //https://www.geeksforgeeks.org/cpp/file-handling-c-classes/

        getline(readf, csv_line); //puts a full line from the file into line variable
        stringstream ss;  
        ss<<csv_line; //put the line from the file into the stream
        string csv_cell="";
        string new_subj_code = "";
        string new_title="";
        string new_description="";
        string new_hours="";
        string new_notes="";
        string new_skills="";
        string new_plans="";

        //now we can begin reading data
        for (long unsigned int i=0;i<7;i++) //iterate through the line to get each cell's value and store into 
        {
            csv_cell="";
            char garbage = ' ';
            char peek = ' ';
            while (ss.peek() == ',' || ss.peek() == '\"' || ss.peek() == '\.')
            {
                ss.get(garbage);
            }
            getline(ss,csv_cell,'*');
            
            //put the value in the right variable for the new Course
            if (i==0)
            {
                new_subj_code=csv_cell;
            }
            else if (i==1)
            {
                new_title=csv_cell;
            }
            else if (i==2)
            {
                new_description=csv_cell;
            }
            else if (i==3)
            {
                new_hours=csv_cell;
            }
            else if (i==4)
            {
                new_notes=csv_cell;
            }
            else if (i==5)
            {
                new_skills=csv_cell;
            }
            else if (i==6)
            {
                new_plans=csv_cell;
            }
        }
        if (new_subj_code != "")
        {
            Course* new_course = new Course();
            new_course->setCourseInfo(new_title, new_description, new_notes, new_subj_code, new_skills, new_plans, new_hours);
            courses_to_insert_into_trie.push_back(new_course);
        }
    }
    readf.close();

    //we need to remove the headers
    //https://www.geeksforgeeks.org/cpp/vector-erase-in-cpp-stl/
    courses_to_insert_into_trie.erase(courses_to_insert_into_trie.begin());
    return courses_to_insert_into_trie;
}

void trie::buildTrie()
{
    vector<Course*> new_courses = readData("../code/test_cirt_data.csv");

    for (long unsigned int i=0;i<new_courses.size();i++)
    {
        Course* cursor=new_courses.at(i);
        this->insertNode(cursor);
    }
}