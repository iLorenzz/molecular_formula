#include "molecular_formula.hpp"

int get_molecule_weight(string &formula){
    unordered_map<char, int> weight_table = {
        {'H', 1},
        {'C', 12},
        {'O', 16},
        {'S', 32}
    };
    
    int total_weight = 0;
    
    regex element_regex("([A-Z][a-z]?)([0-9]*)");
    auto it = sregex_iterator(formula.begin(), formula.end(), element_regex);
    auto end = sregex_iterator();
    
    while(it != end){
        smatch match = *it;
        string element = match[1];
        int quantidade = (match[2].length() == 0) ? 1 : stoi(match[2]);
        
        total_weight += weight_table[element[0]] * quantidade;
        ++it;
    }
    
    return total_weight;
}

int create_hash(string &molecule){
    int hash = 0;
    
    for(char bits : molecule){
        hash += bits;
    }
    
    return hash % TABLE_SIZE;
}

void insert(Node* hash_table[], string &molecule){
    int hash_value = create_hash(molecule);
    int molecular_weight = get_molecule_weight(molecule);
    
    Node* new_node = new Node{molecule, molecular_weight, nullptr};
    
    if(hash_table[hash_value] == nullptr)
        hash_table[hash_value] = new_node;
    else{
        Node* temp = hash_table[hash_value];
        
        while(temp->next != nullptr){
            if(temp->molecular_weight == molecular_weight){
                temp->molecule = molecule;
                delete new_node;
                return;
            }
            
            temp = temp->next;
        }
        
        temp->next = new_node;
    }    
}

int search(Node* hash_table[], string &molecule){
    int hash_value = create_hash(molecule);
    
    Node* temp = hash_table[hash_value];
    while(temp != nullptr){
        if(temp->molecule == molecule)
            return temp->molecular_weight;
            
        temp = temp->next;
    }
    
    return -1;
}

int main(){
    string hidrogen = "O2";
    
    Node* hash_table[TABLE_SIZE] = {nullptr};
    insert(hash_table, hidrogen);
    int weight = search(hash_table, hidrogen);
    
    cout << weight << endl;    
    return 0;
}

