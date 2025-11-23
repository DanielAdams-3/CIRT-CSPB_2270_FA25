
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
  for (long unsigned int i=0;i<new_vector.size();i++)
  {
    Course* course=new_vector.at(i);
    cout << course->getCourseSubjectCode() << endl;
    cout << "Course Title" << endl;
    cout << course->getCourseTitle() << endl;
    cout << "Course Description" << endl;
    cout << course->getCourseDescription() << endl;
    cout << "Course Notes: " << endl;
    cout << course->getCourseNotes() << endl;
    cout << "Credit Hours: " << endl;
    cout << course->getCreditHours() << endl;
    cout << "Registration Restrictions: " << endl;
    cout << course->getRegRestricts() << endl;
    cout << "FIXME - PLANSnREQS" << endl;
    //missing skills learnt
  }
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
  ASSERT_EQ(answer, true); //lets us know it is successfully added

}; 

TEST_F(test_Trie, removeNode)
{
  trie a = trie();
  trieNode* root_node= new trieNode();
  a.setRoot(root_node);

  a.buildTrie(); //RESOLVED -- error here, out of range for vector somehow? is vector not declared? - out of range, with '0'
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

  //REFLECTION mistake - buildTrie already builds based on the data we read in.

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
  //FIRST VAL = "C"
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
  //ASSERT_EQ(new_course->skillsLearnt,""); //from 3. Skills Learnt;
  ASSERT_EQ(new_course->plansNreqs.size(),0); //from Daniel's brain
  ASSERT_EQ(new_course->courseHours,"");
};

//https://www.geeksforgeeks.org/cpp/traversing-a-map-or-unordered_map-in-cpp-stl/
//https://en.cppreference.com/w/cpp/container/map/begin.html
TEST_F(test_Course, GetSetfunctions) {
  Course* new_course = new Course();

  string title="Datacenter Scale Computing";
  string description="This is a course description.";
  string notes="Section 002: restricted to ROBO students.";
  string subjectCode="CSCI-5253";
  string restricts="Restricted to grad students only.";
  string degreeplans="CSEN-MS: Electives, Bin 3; CSEN-MSCPS: Electives, Bin 3";
  string credithrs="3";
  new_course->setCourseInfo(title, description, notes, subjectCode,restricts,degreeplans,credithrs);
  ASSERT_EQ(new_course->getCourseTitle(),title);
  ASSERT_EQ(new_course->getCourseDescription(),description);
  ASSERT_EQ(new_course->getCourseNotes(),notes);
  ASSERT_EQ(new_course->getCourseSubjectCode(),subjectCode);
  ASSERT_EQ(new_course->getRegRestricts(),restricts);
  ASSERT_EQ(new_course->getCreditHours(),"3");
  ASSERT_EQ(new_course->plansNreqs.size(),2);
  //need one for skills
};

/*
TEST_F(test_Graph, Graph_NodeGetDiscoInfo) {
  Node* n(new Node("some node"));
  n->color = GRAY;
  n->discovery_time = 10;
  n->completion_time = 18;
  n->rank = 4;
  int c, dt, ct, r;
  n->getDiscoveryInformation(c, dt, ct, r);
  ASSERT_EQ(c, GRAY);
  add_points_to_grade(2);
  ASSERT_EQ(dt, 10);
  add_points_to_grade(2);
  ASSERT_EQ(ct, 18);
  add_points_to_grade(2);
  ASSERT_EQ(r, 4);
  add_points_to_grade(2);
}

TEST_F(test_Graph, Graph_TestIfNodeIsSpanningTreeAncestor) {
  Node* a(new Node("a"));
  Node* b(new Node("b"));
  Node* c(new Node("c"));
  Node* e(new Node("e"));
  a->predecessor = NULL;
  b->predecessor = a;
  c->predecessor = a;
  e->predecessor = c;

  ASSERT_EQ(a->isAncestor(c), false);
  add_points_to_grade(2);
  ASSERT_EQ(c->isAncestor(a), true);
  add_points_to_grade(2);
  ASSERT_EQ(e->isAncestor(a), true);
  add_points_to_grade(2);
  ASSERT_EQ(e->isAncestor(b), false);
  add_points_to_grade(2);
}

TEST_F(test_Graph, Graph_SetSpanningTreePredecessor) {
  Node* a(new Node("a"));
  Node* c(new Node("c"));
  Node* e(new Node("e"));
  c->setPredecessor(a);
  e->setPredecessor(c);

  ASSERT_EQ(c->predecessor, a);
  add_points_to_grade(5);
  ASSERT_EQ(e->predecessor, c);
  add_points_to_grade(5);
}

TEST_F(test_Graph, Graph_DepthFirstSeartchNoTrarget) {
  Graph* g = mkgraph();
  g->clear();
  ASSERT_EQ(g->clock, 0);
  add_points_to_grade(2);
  Node* a = find(g, "a");
  ASSERT_TRUE(a); // sanity check my find function, "a" shouldn't be null
  add_points_to_grade(2);
  g->dfs(a);
  ASSERT_GT(g->clock, 0); // clock should increment beyond zero
  add_points_to_grade(2);
  ASSERT_EQ(a->color, BLACK); // start node should be fully explored
  add_points_to_grade(2);
  ASSERT_EQ(a->discovery_time, 0); // start node discovered at t=0
  add_points_to_grade(2);
  ASSERT_EQ(a->completion_time, 13); // should finish at exactly t=13
  add_points_to_grade(2);
  int c, dt, ft, r;
  for (auto it = g->nodes.begin(); it != g->nodes.end(); ++it) {
    Node* n(*it);
    ASSERT_TRUE(n);
    n->getDiscoveryInformation(c, dt, ft, r);
    ASSERT_EQ(c, BLACK); // all nodes should be fully explored
    add_points_to_grade(0.25);
    ASSERT_GE(dt, 0); // discovered between 0 and 6 inclusive;
    add_points_to_grade(0.25);
    ASSERT_LE(dt, 6);
    add_points_to_grade(0.25);
    ASSERT_GE(ft, 7); // finish time between 7 and 13 inclusive
    add_points_to_grade(0.25);
    ASSERT_LE(ft, 13);
    add_points_to_grade(0.5);
  }
  Node* f = find(g, "f");
  Node* d = find(g, "d");
  ASSERT_EQ(f->predecessor, d);
  add_points_to_grade(1);
}

TEST_F(test_Graph, Graph_DepthFirstSeartchEdgeTypes) {
  Graph* g = mkgraph();
  g->clear();
  ASSERT_EQ(g->clock, 0);
  add_points_to_grade(1);
  Node* a = find(g, "a");
  ASSERT_TRUE(a); // sanity check my find function
  add_points_to_grade(1);
  g->dfs(a); // run the DFS

  // declare vars to count number of each kind of edge
  int numFwd = 0;
  int numTree = 0;
  int numBack = 0;
  int numCross = 0;
  for (auto it = g->edges.begin(); it != g->edges.end(); ++it) {
    Edge* e(*it);
    ASSERT_TRUE(e);
    add_points_to_grade(1);
    if (e->getType() == FORWARD_EDGE) {
      numFwd++;
    } else if (e->getType() == TREE_EDGE) {
      numTree++;
    } else if (e->getType() == BACK_EDGE) {
      numBack++;
    } else if (e->getType() == CROSS_EDGE) {
      numCross++;
    }
  }

  // The classification of edges depends on traversal order & can't be
  // predicted at write-time, so test sums and inequalities instead.
  ASSERT_EQ(numTree + numFwd + numBack + numCross, 12);
  add_points_to_grade(1);
  ASSERT_GE(numTree, 6);
  add_points_to_grade(1);
  ASSERT_GT(numFwd, 0);
  add_points_to_grade(1);
  ASSERT_GT(numBack, 0);
  add_points_to_grade(1);
  ASSERT_EQ(numCross, 0);
  add_points_to_grade(1);
}

TEST_F(test_Graph, Graph_BreadthFirstSearch) {
  Graph* graph = mkgraph();
  graph->clear();
  Node* a = find(graph, "a");
  Node* b = find(graph, "b");
  Node* c = find(graph, "c");
  Node* d = find(graph, "d");
  Node* e = find(graph, "e");
  Node* f = find(graph, "f");
  Node* g = find(graph, "g");
  int color, dt, ft, rank;

  graph->bfs(a);
  a->getDiscoveryInformation(color, dt, ft, rank);
  ASSERT_EQ(rank, 0);
  add_points_to_grade(2);
  b->getDiscoveryInformation(color, dt, ft, rank);
  ASSERT_EQ(rank, 1);
  add_points_to_grade(2);
  c->getDiscoveryInformation(color, dt, ft, rank);
  ASSERT_EQ(rank, 1);
  add_points_to_grade(2);
  e->getDiscoveryInformation(color, dt, ft, rank);
  ASSERT_EQ(rank, 1);
  add_points_to_grade(2);
  d->getDiscoveryInformation(color, dt, ft, rank);
  ASSERT_EQ(rank, 2);
  add_points_to_grade(2);
  g->getDiscoveryInformation(color, dt, ft, rank);
  ASSERT_EQ(rank, 2);
  add_points_to_grade(2);
  f->getDiscoveryInformation(color, dt, ft, rank);
  ASSERT_EQ(rank, 3);
  add_points_to_grade(2);
}

TEST_F(test_Graph, Graph_BreadthFirstSearchWithTarget) {
  int color, dt, ft, rank;
  {
    Graph* graph = mkgraph();
    graph->clear();
    Node* c = find(graph, "c");
    Node* f = find(graph, "f");
    graph->bfs(c, f);
    f->getDiscoveryInformation(color, dt, ft, rank);
    ASSERT_EQ(rank, 2);
    add_points_to_grade(5);
  }
  {
    Graph* graph = mkgraph();
    graph->clear();
    Node* b = find(graph, "b");
    Node* c = find(graph, "c");
    graph->bfs(c, b);
    b->getDiscoveryInformation(color, dt, ft, rank);
    ASSERT_EQ(rank, 3); // rank is 3 if graph is directed
    add_points_to_grade(5);
  }
  {
    Graph* graph = mkgraph();
    graph->setDirected(false);
    graph->clear();
    Node* b = find(graph, "b");
    Node* c = find(graph, "c");
    graph->bfs(c, b);
    b->getDiscoveryInformation(color, dt, ft, rank);
    ASSERT_EQ(rank, 1); // rank is 1 if graph is undirected
    add_points_to_grade(5);
  }
}

// ---------------------------------------------------------------- Helpers ---






trie* buildTrieToTest() {
  // make a trie with wonky metadata. it is intended test clear().
  Graph* g(new Graph());
  g->clock = 42;

  Node* a(new Node("a"));
  a->color = GRAY;
  a->discovery_time = 1;
  a->completion_time = 4;
  a->rank = 0;
  Node* b(new Node("b"));
  b->color = BLACK;
  b->discovery_time = 2;
  b->completion_time = 5;
  b->rank = 1;
  Node* c(new Node("c"));
  c->color = WHITE;
  c->discovery_time = 3;
  c->completion_time = 6;
  c->rank = -1;

  Edge* ab(new Edge(a, b));
  ab->type = TREE_EDGE;
  Edge* bc(new Edge(b, c));
  bc->type = CROSS_EDGE;
  Edge* ac(new Edge(a, c));
  bc->type = BACK_EDGE;

  a->predecessor = NULL;
  b->predecessor = a;
  c->predecessor = b;

  g->addNode(a);
  g->addNode(b);
  g->addNode(c);
  g->addEdge(ab);
  g->addEdge(bc);
  g->addEdge(ac);

  return g;
}

Graph* mkgraph() {
  Graph* ret(new Graph());
  Node* a(new Node("a"));
  Node* b(new Node("b"));
  Node* c(new Node("c"));
  Node* d(new Node("d"));
  Node* e(new Node("e"));
  Node* f(new Node("f"));
  Node* g(new Node("g"));

  Edge* ab(new Edge(a, b));
  Edge* ac(new Edge(a, c));
  Edge* bc(new Edge(b, c));
  Edge* ae(new Edge(a, e));
  Edge* ce(new Edge(c, e));
  Edge* cd(new Edge(c, d));
  Edge* dg(new Edge(d, g));
  Edge* eg(new Edge(e, g));
  Edge* df(new Edge(d, f));
  Edge* fb(new Edge(f, b));
  // if graph is undirected, these could cause trouble. see that it doesn't
  Edge* gd(new Edge(g, d));
  Edge* ge(new Edge(g, e));

  ret->addNode(a);
  ret->addNode(b);
  ret->addNode(c);
  ret->addNode(d);
  ret->addNode(e);
  ret->addNode(f);
  ret->addNode(g);

  ret->addEdge(ab);
  ret->addEdge(ac);
  ret->addEdge(bc);
  ret->addEdge(ae);
  ret->addEdge(ce);
  ret->addEdge(cd);
  ret->addEdge(dg);
  ret->addEdge(eg);
  ret->addEdge(df);
  ret->addEdge(fb);
  ret->addEdge(gd);
  ret->addEdge(ge);

  ret->setDirected(true);

  return ret;
}

Node* find(Graph* graph, string label) {
  for (auto it = graph->nodes.begin(); it != graph->nodes.end(); ++it) {
    Node* n = *it;
    if (n->data == label) {
      return n;
    }
  }
  return NULL;
}
*/