#include <iostream>
#include <string>
#include "Trie.h"         // <-- student's trie header
#include "trie_server.h"   // declares start_trie_server()
#include "httplib.h"

int main() {
    trie::trie* dict= new trie();
    dict->buildTrie(); //we build and read it internally
    // Adjust this to however your Trie loads data.
    // For example:
    //   dict.load("words.txt");
    //   dict.loadFromFile("words.txt");
    // or manual inserts.
    //
    // Here we assume a member function: bool load(const std::string& filename);
    if (!dict->load()) {
        std::cerr << "Warning: could not load test_cirt_data.csv; "
                     "make sure it is in the same directory as the executable\n";
    }

    std::cout << "Starting trie HTTP server on http://localhost:8080\n";
    std::cout << "Open: http://localhost:8080/index.html\n";

    // Start the HTTP server (blocking call)
    start_trie_server(*dict); //is it thinking this is it? it's just...doing what we want...that's a function call

    return 0;
}
