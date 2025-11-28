
// Chekout TEST_F functions below to learn what is being tested.
#include <cmath>
#include <ctime>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

// in order to access private members, we have to defeat the safety
// mechanisms. This is acceptable for unit testing, but not much
// else. It is also not portable because it is not supported by the
// C++ spec, and therefore might not work with all compilers.
#define private public
#include "../code/Course.h"
#include "../code/TrieNode.h"
#include "../code/Trie.h"

using namespace std;

// Unit Tests - Node
class test_TrieNode : public ::testing::Test{
protected:
  // this function runs before every TEST_F function
  void SetUp() override {}
};

TEST_F(test_TrieNode, SetGetLeafStatus) {
  TrieNode* a = new TrieNode();
  TrieNode* base = new TrieNode();
  a->setLeafStatus(true);
  ASSERT_EQ(a->getLeafStatus(), true);
  ASSERT_EQ(base->getLeafStatus(), false);
};

TEST_F(test_TrieNode, SetGetDeleted) {
  TrieNode* first = new TrieNode();
  first->markDeletion(true);
  ASSERT_EQ(first->getDeleteStatus(), true);
};

TEST_F(test_TrieNode, SetGetPredecessor) {
  TrieNode* second = new TrieNode();
  TrieNode* first = new TrieNode();
  second->setPredecessor(first);
  ASSERT_EQ(second->getPredecessor(), first);
};

TEST_F(test_TrieNode, SetGetCoursePtr) {
  Course* csci_5525 = new Course();
  TrieNode* new_node = new TrieNode();
  new_node->setCoursePtr(csci_5525);
  ASSERT_EQ(new_node->getCoursePtr(), csci_5525);
};

TEST_F(test_TrieNode, descendantsVector) {
  TrieNode* new_node = new TrieNode();
  TrieNode* parent_node = new TrieNode();
  TrieNode* child_node = new TrieNode();
  new_node->setPredecessor(parent_node);
  child_node->setPredecessor(new_node);
  new_node->descendants.at(2) = child_node;
  ASSERT_EQ(new_node->descendants.size(), 38);
  ASSERT_EQ(new_node->descendants.at(0), nullptr);
  ASSERT_EQ(new_node->descendants.at(2), child_node);
};

// Unit Tests - Course
class test_Course : public ::testing::Test{
protected:
  // this function runs before every TEST_F function
  void SetUp() override {}

};

TEST_F(test_Course, Constructor) {
  Course* new_course = new Course();
  ASSERT_EQ(new_course->courseSubjectCode, "");
  ASSERT_EQ(new_course->courseDescription,"");
  ASSERT_EQ(new_course->courseNotes,""); //from classes.colorado.edu
  ASSERT_EQ(new_course->courseTitle,""); //catalog, etc.
  ASSERT_EQ(new_course->regRestricts, "");
  ASSERT_EQ(new_course->skillsLearnt,""); //from 3. Skills Learnt;
  ASSERT_EQ(new_course->plansNreqs.size(),0); //from Daniel's brain
  ASSERT_EQ(new_course->courseHours,"");
};

TEST_F(test_Course, GetSetfunctions) {
  Course* new_course = new Course();

  string title="Datacenter Scale Computing";
  string description="This is a course description.";
  string notes="Section 002: restricted to ROBO students.";
  string subjectCode="CSCI-5253";
  string restricts="Restricted to grad students only.";
  string degreeplans="CSEN-MS: Electives, Bin 3; CSEN-MSCPS: Electives, Bin 3";
  string credithrs="3";
  string skills="mad skills.";
  new_course->setCourseInfo(title, description, notes, subjectCode,restricts,degreeplans,credithrs, skills);
  ASSERT_EQ(new_course->getCourseTitle(),title);
  ASSERT_EQ(new_course->getCourseDescription(),description);
  ASSERT_EQ(new_course->getCourseNotes(),notes);
  ASSERT_EQ(new_course->getCourseSubjectCode(),subjectCode);
  ASSERT_EQ(new_course->getRegRestricts(),restricts);
  ASSERT_EQ(new_course->getCreditHours(),"3");
  ASSERT_EQ(new_course->plansNreqs.size(),2);
  ASSERT_EQ(new_course->getSkillsLearnt(), skills);
};



// Unit Tests - Trie
class test_Trie : public ::testing::Test{
protected:
  // this function runs before every TEST_F function
  void SetUp() override {}
};


TEST_F(test_Trie, SetGetRoot) {
  Trie a = Trie();
  TrieNode* root_node= new TrieNode();
  a.setRoot(root_node);
  ASSERT_EQ(a.getRoot(), root_node);
};

TEST_F(test_Trie, readData) {
  Trie a = Trie();
  //string filename = "../static/test_cirt_data.csv"; not working
  //string filename = "code/static/test_cirt_data.csv";
  string filename = "../code/static/test_cirt_data.csv";
  vector<Course*> new_vector = a.readData(filename);
  ASSERT_EQ(new_vector.size(), 12);
};

TEST_F(test_Trie, createCourseFunction)
{
  Trie a = Trie();
  //string filename = "../static/test_cirt_data.csv"; not working
  //string filename = "code/static/test_cirt_data.csv";
  string filename = "../code/static/test_cirt_data.csv";
  vector<Course*> new_vector = a.readData(filename);
};

TEST_F(test_Trie, searchTrie)
{
  Trie a = Trie();
  TrieNode* root_node= new TrieNode();
  a.setRoot(root_node);

  string filename = "../code/static/test_cirt_data.csv";
  a.buildTrie(filename);
  a.searchTrie("CSCI-5253");
  ASSERT_EQ(a.searchTrie("CSCI-5253"), true);
};


TEST_F(test_Trie, insertNode)
{
  Trie a = Trie();
  TrieNode* root_node= new TrieNode();
  a.setRoot(root_node);
  
  string filename = "../code/static/test_cirt_data.csv";
  a.buildTrie(filename);
  bool answer = a.searchTrie("CSCI-5253");
  ASSERT_EQ(answer, true);

}; 

TEST_F(test_Trie, removeNode)
{
  Trie a = Trie();
  TrieNode* root_node= new TrieNode();
  a.setRoot(root_node);

  string filename = "../code/static/test_cirt_data.csv";
  a.buildTrie(filename);
  bool answer=true;
  a.removeNode("CSCI-5253");
  answer=a.searchTrie("CSCI-5253");
  ASSERT_EQ(answer, false); //lets us know it's removed successfully
}; 

TEST_F(test_Trie, buildTrie)
{
  Trie a = Trie();
  TrieNode* root_node= new TrieNode();
  a.setRoot(root_node);
  string filename = "../code/static/test_cirt_data.csv";
  a.buildTrie(filename);
  bool answer=a.searchTrie("CSCI-5253");
  ASSERT_EQ(answer,true);
};

TEST_F(test_Trie, SetGetNumWords)
{
  Trie a = Trie();
  TrieNode* root_node= new TrieNode();
  a.setRoot(root_node);

  string filename = "../code/static/test_cirt_data.csv";
  a.buildTrie(filename);
  int test_numWords=a.getNumWords();
  ASSERT_EQ(test_numWords,12);
};

TEST_F(test_Trie, helperFunctionTest_SwapCodeforPtr)
{
  Trie a = Trie();
  TrieNode* root_node= new TrieNode();
  a.setRoot(root_node);
  string filename = "../code/static/test_cirt_data.csv";
  a.buildTrie(filename);

  //test for nullptr
  Course* test = a.swapCodeforPtr("CSCI-5993");
  ASSERT_EQ(test,nullptr);

  //test for value
  Course* new_test = a.swapCodeforPtr("CSCI-5253");
  bool new_answer = false;
  if (new_test != nullptr)
  {
    new_answer=true;
  }
  ASSERT_EQ(new_answer, true);
}; 

TEST_F(test_Trie, autoComplete)
{
  Trie a = Trie();
  TrieNode* root_node= new TrieNode();
  a.setRoot(root_node);
  string filename = "../code/static/test_cirt_data.csv";
  a.buildTrie(filename);
  vector<Course*> autoCompleteSuggestions = a.startsWithPrefix("CSCI-5");
  cout << "AUTO-COMPLETE SUGGESTIONS FOR " << "CSCI-5" << endl;
  for (long unsigned int i=0;i<autoCompleteSuggestions.size();i++)
  {
    cout << autoCompleteSuggestions.at(i)->getCourseSubjectCode();
    cout << endl;
  }
  ASSERT_EQ(autoCompleteSuggestions.size(),11);

  //testing "CSCI-52" - 3 courses
  vector<Course*> autoCompleteSuggestionsThree = a.startsWithPrefix("CSCI-52");
  cout << "AUTO-COMPLETE SUGGESTIONS FOR " << "CSCI-52" << endl;
  for (long unsigned int i=0;i<autoCompleteSuggestionsThree.size();i++)
  {
    cout << autoCompleteSuggestionsThree.at(i)->getCourseSubjectCode();
    cout << endl;
  }
  ASSERT_EQ(autoCompleteSuggestionsThree.size(),3);

  //testing "A" prefix code, 1 course
  vector<Course*> autoCompleteSuggestionsOne = a.startsWithPrefix("A");
  cout << "AUTO-COMPLETE SUGGESTIONS FOR " << "A" << endl;
  for (long unsigned int i=0;i<autoCompleteSuggestionsOne.size();i++)
  {
    cout << autoCompleteSuggestionsOne.at(i)->getCourseSubjectCode();
    cout << endl;
  }
  ASSERT_EQ(autoCompleteSuggestionsOne.size(),1);
};

/*
TEST_F(test_Trie, output)
{
  trie a = trie();
  trieNode* root_node = new trieNode();
  a.setRoot(root_node);
  a.buildTrie();
  a.outputCourseData("CSCI-5253");
};

TEST_F(test_Trie, input)
{
  trie a = trie();
  trieNode* root_node = new trieNode();
  a.setRoot(root_node);
  a.buildTrie();

  ASSERT_EQ(a.userStatus,false);
  a.setUserStatus(true);
  ASSERT_EQ(a.userStatus,true);
  a.getUserInput();
};

*/