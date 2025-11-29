#ifndef TRIE_SERVER_H__
#define TRIE_SERVER_H__

#pragma once
#include <string>
#include <vector>
#include "Trie.h"

// Forward declare Trie so we don't depend on the student's full header here.
// The real Trie type must be defined in "Trie.h" with at least:
//   bool contains(const std::string& word);
// If you want autocomplete, also provide something like:
//   std::vector<std::string> autocomplete(const std::string& prefix, std::size_t max_results) const;
//class trie;

// Start an HTTP server that exposes a Trie via simple HTTP endpoints that
// return plain text (no JSON libraries required).
// This call blocks the current thread until the server is stopped.
void start_trie_server(Trie& dict);

#endif //TRIE_SERVER_H__