#include "Trie.h"

using namespace std;

//constructor, set default values
trie::trie()
{
    this->numWords=0;
    trieNode* root= new trieNode();
    this->setRoot(root);
    this->userStatus=false;
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
    trieNode* cursor = subtreeRoot;
    for (long unsigned int i=0;i<cursor->descendants.size();i++)
    {
        if (cursor->descendants.at(i) != nullptr)
        {
            if (cursor->descendants.at(i)->getDeleteStatus() != true) 
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
trieNode* trie::getRoot()
{
    return this->root;
}
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
        cursor=cursor->descendants.at(index);
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
void trie::removeNode(string doom_course_subject_code)
{
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

}
/*
bool trie::startsWithPrefix(string prefix)
{
    bool answer = false;
    return answer;
}*/

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
        string csv_line=""; //connect the string stream so it's ready
        getline(readf, csv_line); //puts a full line from the file into line variable
        stringstream ss;  
        ss<<csv_line; //put the line from the file into the stream
        string csv_cell="";
        string new_subj_code = "";
        string new_title="";
        string new_description="";
        string new_hours="";
        string new_notes="";
        string new_restricts="";
        string new_plans="";
        string new_skills="";

        for (long unsigned int i=0;i<8;i++)
        {
            csv_cell="";
            getline(ss,csv_cell,'*');

            //CLEAN-UP BEGINNING AND END OF STRINGS
            char garbage = csv_cell.front();
            while (garbage == '\"' || garbage == ',' || garbage == ' ' || garbage == ':')
            {
                csv_cell.erase(0,1); //erase 1 character at position 0
                garbage=csv_cell.front();
            }

            garbage = csv_cell.back();
            while (garbage == '\"' || garbage == ',' || garbage == ' ') 
            {
                csv_cell.pop_back();
                garbage=csv_cell.back();
            }

            //store the string into the right variable to then initialize new Course object
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
                new_restricts=csv_cell;
            }
            else if (i==6)
            {
                new_plans=csv_cell;
            }
            else if (i==7)
            {
                new_skills = csv_cell;
            }
        }
        if (new_subj_code != "")
        {
            Course* new_course = new Course();
            new_course->setCourseInfo(new_title, new_description, new_notes, new_subj_code, new_restricts, new_plans, new_hours, new_skills);
            courses_to_insert_into_trie.push_back(new_course);
        }
    }
    readf.close();

    courses_to_insert_into_trie.erase(courses_to_insert_into_trie.begin());     //remove headers
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

Course* trie::swapCodeforPtr(string course_subject_code)
{
    Course* answer = nullptr;
    if (this->searchTrie(course_subject_code) != true)
    {
        return answer;
    }

    if (this->getRoot() == nullptr)
    {
        cout << "error, root not set" << endl;
        return answer;
    }

    //set up a string stream to read the course 
    stringstream ss(course_subject_code);
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
        cursor=cursor->descendants.at(index);
        ss.get(current);
        index = 0;
    }
    //verify we found the right course and assign the answer to the Course Ptr so we can return it
    if (cursor->getLeafStatus() == true && cursor->getCoursePtr()->getCourseSubjectCode() == course_subject_code)
    {
        answer=cursor->getCoursePtr();
    }
    return answer;

}

void trie::outputCourseData(string course_subject_code)
{
    //40
    const int LINE_LENGTH = 40;
    const string LINE_WIDTH_40 = "----------------------------------------";

    //if not in there
    if (this->searchTrie(course_subject_code) != true)
    {
        cout << "Unfortunately, the course is not available." << endl;
        return;
    }

    Course* cursor = this->swapCodeforPtr(course_subject_code);

    //OUTPUT MESSAGE TO USER
    cout << LINE_WIDTH_40 << endl;
    cout << "Course found: " << course_subject_code << endl;
    cout << "Loading..." << endl;

    //PREPARE FOR OUTPUT
    string course_subject="";
    string course_title="";
    string course_description="";
    string course_notes="";
    string reg_restricts="";
    map<string,string> plansreqs;
    string credit_hours="";
    string course_skills="";
    cursor->getCourseInfo(course_title, course_description, course_notes, course_subject, reg_restricts,
    plansreqs, credit_hours, course_skills);

    //BEGIN OUTPUT
    cout << LINE_WIDTH_40 << endl;
    cout << LINE_WIDTH_40 << endl;
    cout << course_subject_code << endl;
    cout << LINE_WIDTH_40 << endl;
    cout << "COURSE TITLE: " << endl;    
    string title_output = consoleOutputWordWrapping(course_title, LINE_LENGTH);
    cout << title_output << endl;
    cout << LINE_WIDTH_40 << endl;

    cout << "COURSE DESCRIPTION: " << endl;
    string description_output = consoleOutputWordWrapping(course_description, LINE_LENGTH);
    cout << description_output << endl;
    cout << LINE_WIDTH_40 << endl;
    
    cout << "SKILLS LEARNED: " << endl;
    string skills_output = consoleOutputWordWrapping(course_skills,LINE_LENGTH);
    cout << skills_output << endl;
    cout << LINE_WIDTH_40 << endl;
    
    cout << "COURSE NOTES: " << endl;
    string notes_output = consoleOutputWordWrapping(course_notes,LINE_LENGTH);
    cout << notes_output << endl;
    cout << LINE_WIDTH_40 << endl;

    cout << "CREDIT HOURS: " << endl;
    string hours_output = consoleOutputWordWrapping(credit_hours,LINE_LENGTH);
    cout << hours_output << endl;
    cout << LINE_WIDTH_40 << endl;

    cout << "REGISTRATION RESTRICTIONS: " << endl;
    string restricts_output = consoleOutputWordWrapping(reg_restricts,LINE_LENGTH);
    cout << restricts_output << endl;
    cout << LINE_WIDTH_40 << endl;

    cout << "DEGREE PLAN REQUIREMENTS: " << endl;
    for (auto i  = plansreqs.begin(); i!= plansreqs.end(); i++)
    {
        stringstream ss;
        string this_line = "";
        int gap = 12-i->first.length();
        ss << i->first << left << setw(gap) << ": " << i->second;
        getline(ss,this_line);
        this_line=consoleOutputWordWrapping(this_line,LINE_LENGTH);
        cout << this_line << endl;
    }
    cout << LINE_WIDTH_40 << endl;
}

string trie::consoleOutputWordWrapping(string to_word_wrap, const int WIDTH_OF_LINE)
{
    string answer = "";

    stringstream originalSS;
    stringstream destinationSS;
    originalSS << to_word_wrap;
    int counter=0;
    int gap_to_end = 0;
    string word="";
    do
    {
        getline(originalSS,word,' ');
        word=word.append(" "); //re-add the ' ' that getline consumed
        gap_to_end = WIDTH_OF_LINE - counter;
        if (gap_to_end <= word.length())
        {
            destinationSS<<'\n';
            counter=0;
        }
        destinationSS<<word;
        counter = counter+word.length();
    } while (originalSS.eof() != true);

    char temp_val = ' ';
    while (destinationSS.eof() != true)
    {
        destinationSS.get(temp_val);
        //destinationSS >> temp_answer; //THIS IS WHERE WE'RE LOSING THE SPACE
        answer.push_back(temp_val);
    }

    if (answer.back() == ' ')
    {
        answer.pop_back();
    }
    return answer;
}

void trie::setUserStatus(bool new_status)
{
    this->userStatus=new_status;
}
bool trie::getUserStatus()
{
    return this->userStatus;
}

//this may just be the main.cpp function below, not sure we need this function as part of the Trie();
void trie::getUserInput()
{
    cout << "CIRT - Course Information Retrieval Tool" << endl;
    cout << "Status: On" << endl;
    cout << "-----------------------------------------" << endl;
    
    this->setUserStatus(true);
    
    string input="";
    cout << "MENU" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "SEARCH:" << endl;
    cout << "--1-- Enter the 4-digit subject code (eg 'CSCI')" << endl;
    cout << "--2-- Enter a dash or hyphen (eg '-')" << endl;
    cout << "--3-- Enter the 4-digit course number (eg '5832')" << endl;
    cout << "--4-- Press the Enter key" << endl;
    cout << "----- Example: CSCI 5832'" << endl;
    cout << "QUIT:" << endl;
    cout << "--1-- Press Q" << endl;
    cout << "--2-- Press Enter" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Waiting for user input...---->";

    do
    {
        cin >> input;
        if (input == "Q")
        {
            this->setUserStatus(false);
        }
        else
        {
            //ERROR HANDLING
            if (input.length() < 7 || input.length() >9)
            {
                cout << "Incorrect length provided. Please use 4 digits for the subject area, 1 digit for the dash/hyphen, and 4 digits for the course number." << endl;
            }

            //if they just put a space instead
            if (input.at(5) == ' ')
            {
                input.at(5) = '-';
            }

            cout << "Searching for: " << input << endl;

            outputCourseData(input);
            cout << "-----------------------------------------" << endl;
            cout << "Waiting for user input...---->";
        }
    } while(this->getUserStatus() == true);
    
    cout << "QUIT" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "CIRT Program status: Off" << endl;
}
