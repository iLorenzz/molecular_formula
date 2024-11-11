#ifndef MOLECULAR_FORMULA_HPP
#define MOLECULAR_FORMULA_HPP

#include <iostream>
#include <unordered_map>
#include <regex>
#include <string>
using namespace std;

const int TABLE_SIZE = 10;

struct Node{
    string molecule;    
    int molecular_weight;
    Node* next;
};

void insert(Node* hash_table[], string &molecule, int molecular_weight);
int create_hash(string &molecule);
int get_molecule_weight(string &formula);

#endif