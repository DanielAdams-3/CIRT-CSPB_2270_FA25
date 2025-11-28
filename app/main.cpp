#include <iostream>
#include <fstream>
#include "../code/Course.h"
#include "../code/TrieNode.h"
#include "../code/Trie.h"

using namespace std;

int main(){
    
  trie a = trie();
  trieNode* root_node = new trieNode();
  a.setRoot(root_node);
  a.buildTrie();
  //a.getUserInput();

  return 0;
}
