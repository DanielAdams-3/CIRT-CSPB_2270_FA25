# CIRT-CSPB_2270_FA25
-Repository for course projct for CSPB 2270, Fall 2025, Prof. Guinn, at CU Boulder. 
About the requirements
-This repository is for my course project for CSPB 2270 Data Structures in Fall 2025. 
# Project Summary
-Create a course information retrieval tool (CIRT), based on a trie (prefix tree) data structure.
The project will output course information based on a user- provided input string (course subject code)
## Project Goals - 
The goal is to create a rapid retrieval tool for pre-consolidated course information. CIRT
will use a trie data structure, allowing a user to quickly access a comprehensive set of
course information with one interface and limited interactions. The trie will store key-value
pairs, where the key is the course subject code (e.g., CSCI-5981) and the value stored at
the relevant terminating node will be a Course object containing the stored course
information. CIRT should quickly output the course information for the course matching the
user-provided subject code. If the course does not exist, the program will notify the user of
the failed search and give these reasons.
## About Tries (Prefix Trees)
A trie is a multi-pronged tree made up of nodes, each of which contains a string
character and points to as few as zero child nodes and may point to more than two child
nodes, unlike a binary tree whose nodes point to at most two child nodes. The traversal
path, like a HuƯman tree, represents the key to each key-value pair, formed by
concatenating the string characters, stored in each node on the path, except the leaf node
which does not contain a character. Instead, it stores the value (Course object). When a
new entry is added to the trie, new nodes are only created for the key’s string characters
that diƯer from the existing keys. When a key is removed, the trie only deletes the nodes
that are unique to the to-be-removed key. Each node will also contain metadata about the
number of courses in the node’s subtree and a list of those courses to aid in search and
insertion functions.

## CIRT Structure
Each Course object will contain strings for each course information item as well as a
map of key-value pairs of strings, representing the degree plans that the course applies to,
and the list of degree requirements that the course can satisfy for that degree plan.
Course information is not confidential, and subject codes are already required to be
unique (see exception below), suggesting a hash-based solution is not strictly necessary.
Search, CIRT’s primary task, has a computational complexity of O(N) where N is the
number of characters in the key. Since subject codes are limited to nine string characters
(see exception below), search will, in most cases, be quick.

## Limitations
A challenge in implementing the trie is the (rare) circumstance where multiple courses
share a course title. For example, Special Topics courses share a subject code but have
unique section-level titles. I plan to address this by adding Course object pointers to the
Special Topics node for each section. In initial implementation, CIRT will output all course
data for each Special Topics section upon request. Time permitting, I will ask the user for
input to isolate the desired section title and then output only the relevant section’s
information.
Time permitting, I will create a simple front-end, locally hosted web interface to
facilitate a better user experience and given my lack of experience, I anticipate this to be a
challenge. If I am unable to complete the interface by the due date, I will exclude it from the
submitted version and work on it after the class ends.
## Technical/Learning Hurdles
I need to learn how to implement a trie in C++, as this was not covered in a homework
assignment. I also need to learn how to implement file streams to read the pre-
consolidated course information from a .csv file, which may require finding a suitable C++
library. Finally, I need to learn how to create my own repository in GitHub and how to
structure the project’s files so they ‘build’ like our homework assignments. I will, as part of
this, need to build a few test cases to verify correct construction of the trie, Course objects,
and any related functions.
References & Resources
  zyBook CSPB 2270: Data Structures - 7.12 Tries
  zyBook CSPB 2270: C++ Refresher - 9.5, 9.6, 9.7 File input and output
  Wikipedia – Trie
  Geeks4Geeks – Trie Data Structure
