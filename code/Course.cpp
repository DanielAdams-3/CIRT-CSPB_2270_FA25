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
    //skills //from 3. Skills Learnt; 
} 

//destructor
Course::~Course()
{
    //DONE
} 

void Course::getCourseInfo(string& title, string& description, string& notes, string& subjectCode, string& restricts, map<string,string>& plansandreqs, string& numHours)
{
    title=getCourseTitle();
    description=getCourseDescription();
    notes=getCourseNotes();
    subjectCode=getCourseSubjectCode();
    restricts=getRegRestricts();
    plansandreqs=*getPlansAndReqs();
    courseHours=getCreditHours();
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
/*
string Course::getSkillsLearnt()
{
    return this->skillsLearnt;
}*/
string Course::getCreditHours()
{
    return this->courseHours;
}
map<string,string>* Course::getPlansAndReqs()
{
    return &this->plansNreqs;
}
void Course::setCourseInfo(string new_title, string new_description, string new_notes, string new_subjectCode, string new_restricts, string new_plans, string num_hours)
{
    setCourseTitle(new_title); 
    setCourseDescription(new_description);
    setCourseNotes(new_notes);
    setCourseSubjectCode(new_subjectCode);
    setRegRestricts(new_restricts);
    //setSkillsLearnt(new_skillsLearnt);
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
/*
void Course::setSkillsLearnt(string new_skills)
{
    this->skillsLearnt=new_skills;
}*/
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
        getline(ss,map_value,';');
        this->plansNreqs.insert({map_key, map_value});
    }
}