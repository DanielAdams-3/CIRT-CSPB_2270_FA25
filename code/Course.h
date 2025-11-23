#ifndef COURSE_H__
#define COURSE_H__ 

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

class Course {
    private:
        string courseSubjectCode; //the main thing.
        string courseDescription; //from catalog or classes.colorado.edu
        string courseNotes; //from classes.colorado.edu
        string courseTitle; //catalog, etc.
        string skillsLearnt; //from 3. Skills Learnt;
        string courseHours;
        //string regRestricts;

    public:

        Course(); //constructor, set variables to empty string, false and nullptr;
        ~Course(); //destructor
        map<string, string> plansNreqs; //from the csv
        
        void getCourseInfo(string& title, string& description, string& notes, string& subjectCode, string& skillsLearnt, map<string,string>& plansandreqs, string& numHours);
        string getCourseSubjectCode(); //returns the entire subject code of the course
        string getCourseNotes(); //returns just the class notes
        string getCourseDescription(); //returns just the course description
        string getCourseTitle(); //return just the course title
        string getSkillsLearnt(); //returns just the skills learnt
        map<string, string>* getPlansAndReqs(); //returns a pointer to a map you can iterate through
        string getCreditHours();
        //string getRegRestricts();

        void setCourseInfo(string new_title, string new_description, string new_notes, string new_subjectCode, string new_skillsLearnt, string new_plans, string num_hours);
        void setCourseNotes(string new_notes); //called by setCourseInfo;
        void setCourseDescription(string new_description); //called by setCourseInfo;
        void setCourseSubjectCode(string new_subj_code);//called by setCourseInfo;
        void setCourseTitle(string new_title);//called by setCourseInfo;
        void setSkillsLearnt(string new_skillsLearnt);//called by setCourseInfo;
        void setPlansandReqs(string degreePlansAndReqs); //we take in that string value and populate the map, separted by ';'
        void setCreditHours(string num_hours);
        //void setRegRestricts(string reg_issues);
};

#endif //COURSE_H__