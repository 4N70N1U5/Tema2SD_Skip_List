//
//  node.hpp
//  Skip List
//

#ifndef node_hpp
#define node_hpp

#include <iostream>

class node
{
public:
    node();
    node* insert_node(int, bool&);
    void propagate_deletion();
    bool delete_node(int, bool&);
    void print_list(std::ostream&);
    bool find_value(int);
    node* find_greatest(int);
    int find_least(int);
    
    int value, level;
    
    bool void_list;
    
    node* next;
    node* prev;
    node* above;
    node* below;
};

#endif /* node_hpp */
