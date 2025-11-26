
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
  trieNode* a = new trieNode();
  trieNode* base = new trieNode();
  a->setLeafStatus(true);
  ASSERT_EQ(a->getLeafStatus(), true);
  ASSERT_EQ(base->getLeafStatus(), false);
};

TEST_F(test_TrieNode, SetGetDeleted) {
  trieNode* first = new trieNode();
  first->markDeletion(true);
  ASSERT_EQ(first->getDeleteStatus(), true);
};

TEST_F(test_TrieNode, SetGetPredecessor) {
  trieNode* second = new trieNode();
  trieNode* first = new trieNode();
  second->setPredecessor(first);
  ASSERT_EQ(second->getPredecessor(), first);
};

TEST_F(test_TrieNode, SetGetCoursePtr) {
  Course* csci_5525 = new Course();
  trieNode* new_node = new trieNode();
  new_node->setCoursePtr(csci_5525);
  ASSERT_EQ(new_node->getCoursePtr(), csci_5525);
};

TEST_F(test_TrieNode, descendantsVector) {
  trieNode* new_node = new trieNode();
  trieNode* parent_node = new trieNode();
  trieNode* child_node = new trieNode();
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
  trie a = trie();
  trieNode* new_root = new trieNode();
  a.setRoot(new_root);
  ASSERT_EQ(a.getRoot(), new_root);
};

TEST_F(test_Trie, readData) {
  trie a= trie();
  string file_name="../code/test_cirt_data.csv";
  vector<Course*> new_vector = a.readData(file_name);
  ASSERT_EQ(new_vector.size(), 5);
};

TEST_F(test_Trie, createCourseFunction)
{
  trie a = trie();
  string file_name="../code/test_cirt_data.csv";
  vector<Course*> new_vector = a.readData(file_name);
};

TEST_F(test_Trie, searchTrie)
{
  trie a = trie();
  trieNode* root_node= new trieNode();
  a.setRoot(root_node);

  //string file_name="../code/test_cirt_data.csv";
  a.buildTrie();
  a.searchTrie("CSCI-5253");
  ASSERT_EQ(a.searchTrie("CSCI-5253"), true);
};


TEST_F(test_Trie, insertNode)
{
  trie a = trie();
  trieNode* root_node= new trieNode();
  a.setRoot(root_node);

  a.buildTrie();
  bool answer = a.searchTrie("CSCI-5253");
  ASSERT_EQ(answer, true);

}; 

TEST_F(test_Trie, removeNode)
{
  trie a = trie();
  trieNode* root_node= new trieNode();
  a.setRoot(root_node);

  a.buildTrie();
  bool answer=true;
  a.removeNode("CSCI-5253");
  answer=a.searchTrie("CSCI-5253");
  ASSERT_EQ(answer, false); //lets us know it's removed successfully
}; 

TEST_F(test_Trie, buildTrie)
{
  trie a = trie();
  trieNode* root_node = new trieNode();
  a.setRoot(root_node);
  a.buildTrie();
  bool answer=a.searchTrie("CSCI-5253");
  ASSERT_EQ(answer,true);
};

TEST_F(test_Trie, SetGetNumWords)
{
  trie a = trie();
  trieNode* root_node = new trieNode();
  a.setRoot(root_node);

  a.buildTrie();
  int test_numWords=a.getNumWords();
  ASSERT_EQ(test_numWords,5);
};

TEST_F(test_Trie, helperFunctionTest_SwapCodeforPtr)
{
  trie a = trie();
  trieNode* root_node = new trieNode();
  a.setRoot(root_node);
  a.buildTrie();

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