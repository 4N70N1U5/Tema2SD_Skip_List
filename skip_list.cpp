//
//  skip_list.cpp
//  Skip List
//

#include "node.hpp"
#include "skip_list.hpp"

#include <iostream>

skip_list::skip_list()
{
    this->levels.push_back(new node());
}

void skip_list::insert_node(int value)
{
    bool lowest_value;
    
    node* base_node = levels[0]->insert_node(value, lowest_value);
    
    if (base_node == nullptr)
        return;
    
    if (lowest_value)
    {
        for (int i = 1; i < levels.size(); i++)
        {
            node* new_node = levels[i]->insert_node(value, lowest_value);
    
            new_node->below = base_node;
            base_node->above = new_node;
    
            base_node = new_node;
        }
    }
    else
    {
        int level = 1;
        
        while (rand() % 2)
        {
            if (level >= levels.size())
            {
                node* new_head = new node();
    
                new_head->value = levels[level - 1]->value;
    
                new_head->void_list = false;
    
                new_head->below = levels[level - 1];
                levels[level - 1]->above = new_head;
    
                levels.push_back(new_head);
            }
    
            node* new_node = levels[level]->insert_node(value, lowest_value);
    
            new_node->below = base_node;
            base_node->above = new_node;
    
            base_node = new_node;
    
            level++;
        }
    }
}

bool skip_list::delete_node(int value)
{   
    bool was_first, aux;
    bool del = levels[levels.size() - 1]->delete_node(value, was_first);

    if (was_first)
    {
        while (levels.size() > 1 && levels[levels.size() - 1]->void_list)
            levels.pop_back();

        for (int i = 0; i < levels.size(); i++)
            levels[i]->insert_node(levels[0]->value, aux);

    }

    return del;
}

void skip_list::print_list(std::ostream& out)
{
    for (int i = (int)this->levels.size() - 1; i >= 0; i--)
        levels[i]->print_list(out);
    
    out << '\n';
}

bool skip_list::find_value(int x)
{
    return levels[levels.size() - 1]->find_value(x);
}

int skip_list::find_greatest(int x)
{
    return levels[levels.size() - 1]->find_greatest(x)->value;
}

int skip_list::find_least(int x)
{
    return levels[levels.size() - 1]->find_least(x);
}

void skip_list::print_interval(std::ostream& out, int x, int y)
{
    node* start_node = levels[levels.size() - 1]->find_greatest(x);

    if (start_node->next == nullptr)
        return;
        
    if (start_node->value < x)
        start_node = start_node->next;
    
    while (start_node->below != nullptr)
        start_node = start_node->below;
    
    while (start_node != nullptr) {
        if (start_node->value > y)
            break;
        out << start_node->value << ' ';
        start_node = start_node->next;
    }
    
    out << '\n';
}
