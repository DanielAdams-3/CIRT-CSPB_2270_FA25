#include "Course.h"

using namespace std;

//constructor
Course::Course()
{
    courseSubjectCode="";
    courseDescription="";
    courseNotes = ""; //from classes.colorado.edu
    courseTitle = ""; //catalog, etc.
    regRestricts = ""; 
    courseHours="";
    skillsLearnt=""; //from 3. Skills Learnt; 
} 

//destructor
Course::~Course()
{
    //DONE
} 

void Course::getCourseInfo(string& title, string& description, string& notes, string& subjectCode, string& restricts, map<string,string>& plansandreqs, string& numHours, string& skillsLearnt)
{
    title=getCourseTitle();
    description=getCourseDescription();
    notes=getCourseNotes();
    subjectCode=getCourseSubjectCode();
    restricts=getRegRestricts();
    plansandreqs=getPlansAndReqs();
    numHours=getCreditHours();
    skillsLearnt=getSkillsLearnt();
}  
string Course::getCourseSubjectCode()
{
    return this->courseSubjectCode;
}
string Course::getCourseNotes() 
{
    return this->courseNotes;
}
string Course::getCourseDescription()
{
    return this->courseDescription;
}
string Course::getCourseTitle()
{
    return this->courseTitle;
}
string Course::getRegRestricts()
{
    return this->regRestricts;
}
string Course::getSkillsLearnt()
{
    return this->skillsLearnt;
}
string Course::getCreditHours()
{
    return this->courseHours;
}
map<string,string> Course::getPlansAndReqs()
{
    return this->plansNreqs;
}
void Course::setCourseInfo(string new_title, string new_description, string new_notes, string new_subjectCode, string new_restricts, string new_plans, string num_hours, string newSkillsLearnt)
{
    setCourseTitle(new_title); 
    setCourseDescription(new_description);
    setCourseNotes(new_notes);
    setCourseSubjectCode(new_subjectCode);
    setRegRestricts(new_restricts);
    setSkillsLearnt(newSkillsLearnt);
    setPlansandReqs(new_plans);
    setCreditHours(num_hours);
} 
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
void Course::setSkillsLearnt(string new_skills)
{
    this->skillsLearnt=new_skills;
}
void Course::setPlansandReqs(string degreePlansAndReqs)
{
    //currently, string broken up by ';' and ':'
    stringstream ss;
    ss<<degreePlansAndReqs; //puts the entire string into the stream
    while (ss.eof() != true)
    {
        string map_key="";
        string map_value="";
        getline(ss,map_key,':');

        //CLEAN-UP BEGINNING AND END OF KEY
        char garbage = map_key.front();
        while (garbage == '\"' || garbage == ',' || garbage == ' ')
        {
            map_key.erase(0,1); //erase 1 character at position 0
             garbage=map_key.front();
        }

        garbage = map_key.back();
        while (garbage == '\"' || garbage == ',' || garbage == ' ') 
        {
            map_key.pop_back();
            garbage=map_key.back();
        }


        getline(ss,map_value,';');

        garbage = map_value.front();
        while (garbage == '\"' || garbage == ',' || garbage == ' ')
        {
            map_value.erase(0,1); //erase 1 character at position 0
             garbage=map_value.front();
        }

        garbage = map_value.back();
        while (garbage == '\"' || garbage == ',' || garbage == ' ') 
        {
            map_value.pop_back();
            garbage=map_value.back();
        }

        this->plansNreqs.insert({map_key, map_value});
    }
}