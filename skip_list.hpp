//
//  skip_list.hpp
//  Skip List
//

#ifndef skip_list_hpp
#define skip_list_hpp

#include <iostream>
#include <vector>

#include "node.hpp"

class skip_list
{
public:
    skip_list();
    void insert_node(int);
    bool delete_node(int);
    void print_list(std::ostream&);
    bool find_value(int);
    int find_greatest(int);
    int find_least(int);
    void print_interval(std::ostream&, int, int);

private:
    std::vector<node*> levels;
};

#endif /* skip_list_hpp */
