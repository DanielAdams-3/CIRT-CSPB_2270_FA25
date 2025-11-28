#include <iostream>
#include <fstream>
#include "../code/Course.h"
#include "../code/TrieNode.h"
#include "../code/Trie.h"

using namespace std;

int main(){
    
  Trie a = Trie();
  TrieNode* root_node = new TrieNode();
  a.setRoot(root_node);
  string filename = "./code/static/test_cirt_data.csv";
  a.buildTrie(filename);
  //a.getUserInput();

  return 0;
}
