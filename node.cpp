//
//  node.cpp
//  Skip List
//

#include "node.hpp"

#include <iostream>
#include <utility>

node::node()
{
    this->void_list = true;
    this->next = nullptr;
    this->prev = nullptr;
    this->above = nullptr;
    this->below = nullptr;
}

node* node::insert_node(int x, bool& lowest_value)
{
    lowest_value = false;
    
    if (this->void_list)
    {
        lowest_value = true;
        this->void_list = false;
        this->value = x;
        return this;
    }
    
    if (this->value == x)
        return this;
    
    node* new_node = new node();
    
    if (this->value > x)
    {
        lowest_value = true;
        
        new_node->value = this->value;
        
        this->value = x;
        
        new_node->prev = this;
        new_node->next = this->next;
        
        if (this->next != nullptr)
            this->next->prev = new_node;
        
        this->next = new_node;
        
        return new_node;
    }
    
    new_node->value = x;
    
    node* prev_node = this;
    
    while (prev_node->next != nullptr)
        if (prev_node->next->value >= x)
            break;
        else
            prev_node = prev_node->next;
    
    if (prev_node->next != nullptr)
        if (prev_node->next->value == x)
            return prev_node->next;

    new_node->next = prev_node->next;
    new_node->prev = prev_node;
    
    if (prev_node->next != nullptr)
        prev_node->next->prev = new_node;
    
    prev_node->next = new_node;
    
    return new_node;
}

void node::propagate_deletion()
{
    node* curr_node = this;

    while (curr_node != nullptr)
    {
        if (curr_node->prev == nullptr && curr_node->next == nullptr)
        {
            void_list = true;
        }

        if (curr_node->prev == nullptr && curr_node->next != nullptr)
        {
            std::swap(curr_node->value, curr_node->next->value);
            curr_node = curr_node->next;
        }

        if (curr_node->prev != nullptr && curr_node->next == nullptr)
        {
            curr_node->prev->next = nullptr;
        }

        if (curr_node->prev != nullptr && curr_node->next != nullptr)
        {
            curr_node->prev->next = curr_node->next;
            curr_node->next->prev = curr_node->prev;
        }
        
        curr_node = curr_node->below;

        delete curr_node->above;
    }
}

bool node::delete_node(int x)
{
    node* curr_node = this;

    while (curr_node->next != nullptr)
        if (curr_node->next->value < x)
            curr_node = curr_node->next;
        else
            break;

    bool go_down = false;
    
    if (curr_node->next == nullptr)
        go_down = true;
    else if (curr_node->next->value > x)
        go_down = true;
    
    if (curr_node->value < x && go_down)
    {
        if (curr_node->below != nullptr)
            return curr_node->below->delete_node(x);
        else
            return false;
    }
    
    if (curr_node->next->value == x)
    {
        curr_node = curr_node->next;
        
        if (curr_node->prev == nullptr && curr_node->next == nullptr)
        {
            void_list = true;
        }

        if (curr_node->prev == nullptr && curr_node->next != nullptr)
        {
            std::swap(curr_node->value, curr_node->next->value);
            curr_node = curr_node->next;
        }

        if (curr_node->prev != nullptr && curr_node->next == nullptr)
        {
            curr_node->prev->next = nullptr;
        }

        if (curr_node->prev != nullptr && curr_node->next != nullptr)
        {
            curr_node->prev->next = curr_node->next;
            curr_node->next->prev = curr_node->prev;
        }

        curr_node->below->propagate_deletion();

        delete curr_node;

        return true;
    }

    return false;
}

bool node::find_value(int x)
{
    node* curr_node = this;
    
    if (x == curr_node->value)
        return curr_node->value;

    while (curr_node->next != nullptr)
        if (curr_node->next->value < x)
            curr_node = curr_node->next;
        else
            break;

    bool go_down = false;
    
    if (curr_node->next == nullptr)
        go_down = true;
    else if (curr_node->next->value > x)
        go_down = true;
    
    if (curr_node->value < x && go_down)
    {
        if (curr_node->below != nullptr)
            return curr_node->below->find_value(x);
        else
            return false;
    }

    if (curr_node->next->value == x)
        return true;
    
    return false;
}

node* node::find_greatest(int x)
{
    node* curr_node = this;
    
    if (x < curr_node->value)
        return curr_node;

    while (curr_node->next != nullptr)
        if (curr_node->next->value < x)
            curr_node = curr_node->next;
        else
            break;

    bool go_down = false;
    
    if (curr_node->next == nullptr)
        go_down = true;
    else if (curr_node->next->value > x)
        go_down = true;
    
    if (curr_node->value < x && go_down)
        if (curr_node->below != nullptr)
            return curr_node->below->find_greatest(x);
    
    return curr_node;
}

int node::find_least(int x)
{
    node* curr_node = this;
    
    while (curr_node->below != nullptr)
    {
        while (curr_node->next != nullptr)
            if (curr_node->value > x)
                break;
            else
                curr_node = curr_node->next;
        
        curr_node = curr_node->below;
    }

    if (curr_node->value < x)
    {
        while (curr_node != nullptr)
        {
            if (curr_node->value >= x)
                break;
            else
                curr_node = curr_node->next;
        }
    }
    else
    {
        while (curr_node->prev != nullptr)
        if (curr_node->prev->value < x)
            break;
        else
            curr_node = curr_node->prev;
    }
    
    return curr_node->value;
}

void node::print_list(std::ostream& out)
{
    node* curr_node = this;
    
    if (void_list)
        return;
    
    while (curr_node != nullptr) {
        out << curr_node->value << ' ';
        curr_node = curr_node->next;
    }
    
    out << '\n';
}
