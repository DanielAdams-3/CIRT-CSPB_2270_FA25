#include "Course.h"

using namespace std;

//constructor, set variables to empty string, false and nullptr;
Course::Course()
{
    //DONE
    courseSubjectCode="";
    courseDescription="";
    courseNotes = ""; //from classes.colorado.edu
    courseTitle = ""; //catalog, etc.
    regRestricts = ""; 
    courseHours="";
    //skills //from 3. Skills Learnt; 
} 

//destructor
Course::~Course()
{
    //DONE
} 

//returns all course info
void Course::getCourseInfo(string& title, string& description, string& notes, string& subjectCode, string& restricts, map<string,string>& plansandreqs, string& numHours)
{
    //DONE
    title=getCourseTitle();
    description=getCourseDescription();
    notes=getCourseNotes();
    subjectCode=getCourseSubjectCode();
    restricts=getRegRestricts();
    plansandreqs=*getPlansAndReqs();
    courseHours=getCreditHours();
}  

//returns just the class notes
string Course::getCourseNotes() 
{
    return this->courseNotes;
}

//returns just the course description
string Course::getCourseDescription()
{
    return this->courseDescription;
}
//returns the entire subject code of the course
string Course::getCourseSubjectCode()
{
    return this->courseSubjectCode;
}
string Course::getCourseTitle()
{
    return this->courseTitle;
}
string Course::getRegRestricts()
{
    return this->regRestricts;
}
/*
string Course::getSkillsLearnt()
{
    return this->skillsLearnt;
}*/

string Course::getCreditHours()
{
    return this->courseHours;
}

//returns the degree reqs as a string for given course_title. If key not found, return empty string
//for a given key, return the mapped value of PlansandReqs as a string
//https://www.geeksforgeeks.org/cpp/traversing-a-map-or-unordered_map-in-cpp-stl/
//https://www.geeksforgeeks.org/cpp/how-to-access-value-in-a-map-using-key-in-cpp/

map<string,string>* Course::getPlansAndReqs()
{
    //DONE
    return &this->plansNreqs;
}

//use C++ strings here, this is where we read in information for each course. - make life easy, just call each individual setter function
void Course::setCourseInfo(string new_title, string new_description, string new_notes, string new_subjectCode, string new_restricts, string new_plans, string num_hours)
{
    //DONE
    setCourseTitle(new_title); 
    setCourseDescription(new_description);
    setCourseNotes(new_notes);
    setCourseSubjectCode(new_subjectCode);
    setRegRestricts(new_restricts);
    //setSkillsLearnt(new_skillsLearnt);
    setPlansandReqs(new_plans);
    setCreditHours(num_hours);
} 
//the following helpers are all called by setCourseInfo;
void Course::setCreditHours(string num_hours)
{
    this->courseHours=num_hours;
}
void Course::setCourseNotes(string new_notes)
{
    this->courseNotes=new_notes;
}
void Course::setCourseDescription(string new_description)
{
    this->courseDescription=new_description;
}
void Course::setCourseSubjectCode(string new_subj_code)
{
    this->courseSubjectCode=new_subj_code;
}
void Course::setCourseTitle(string new_title)
{
    this->courseTitle=new_title;
}
void Course::setRegRestricts(string new_restricts)
{
    this->regRestricts = new_restricts;
}
/*
void Course::setSkillsLearnt(string new_skills)
{
    this->skillsLearnt=new_skills;
}*/
void Course::setPlansandReqs(string degreePlansAndReqs)
//https://learn.zybooks.com/zybook/COLORADOCSPB2270DataStructuresGuinnFall2025/chapter/14/section/1
//https://www.geeksforgeeks.org/cpp/map-insert-in-c-stl/
{
    //currently, string broken up by ';' and ':'
    stringstream ss;
    ss<<degreePlansAndReqs; //puts the entire string into the stream
    while (ss.eof() != true)
    {
        string map_key="";
        string map_value="";
        getline(ss,map_key,':');
        getline(ss,map_value,';');
        this->plansNreqs.insert({map_key, map_value});
    }
}