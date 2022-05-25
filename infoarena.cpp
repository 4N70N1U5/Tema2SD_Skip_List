#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>

std::ifstream fin("abce.in");
std::ofstream fout("abce.out");

class node
{
public:
    node();
    
    node* get_above();
    
    node* insert_node(int, bool&);
    void propagate_deletion();
    bool delete_node(int);
    void print_list();
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

node::node()
{
    this->void_list = true;
    this->next = NULL;
    this->prev = NULL;
    this->above = NULL;
    this->below = NULL;
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
        
        if (this->next != NULL)
            this->next->prev = new_node;
        
        this->next = new_node;
        
        return new_node;
    }
    
    new_node->value = x;
    
    node* prev_node = this;
    
    while (prev_node->next != NULL)
        if (prev_node->next->value >= x)
            break;
        else
            prev_node = prev_node->next;
    
    if (prev_node->next != NULL)
        if (prev_node->next->value == x)
            return prev_node->next;

    new_node->next = prev_node->next;
    new_node->prev = prev_node;
    
    if (prev_node->next != NULL)
        prev_node->next->prev = new_node;
    
    prev_node->next = new_node;
    
    return new_node;
}

void node::propagate_deletion()
{
    node* curr_node = this;

    while (curr_node != NULL)
    {
        if (curr_node->prev == NULL && curr_node->next == NULL)
        {
            void_list = true;
        }

        if (curr_node->prev == NULL && curr_node->next != NULL)
        {
            std::swap(curr_node->value, curr_node->next->value);
            curr_node = curr_node->next;
        }

        if (curr_node->prev != NULL && curr_node->next == NULL)
        {
            curr_node->prev->next = NULL;
        }

        if (curr_node->prev != NULL && curr_node->next != NULL)
        {
            curr_node->prev->next = curr_node->next;
            curr_node->next->prev = curr_node->prev;
        }
        
        curr_node = curr_node->below;

        // delete curr_node->above;
    }
}

bool node::delete_node(int x)
{
    node* curr_node = this;
    
    while (curr_node->next != NULL)
        if (curr_node->next->value < x)
            curr_node = curr_node->next;
        else
            break;

    bool go_down = false;
    
    if (curr_node->next == NULL)
        go_down = true;
    else if (curr_node->next->value > x)
        go_down = true;
    
    if (curr_node->value < x && go_down)
    {
        if (curr_node->below != NULL)
            return curr_node->below->delete_node(x);
        else
            return false;
    }
    
    if (curr_node->next->value == x)
    {
        curr_node = curr_node->next;
        
        if (curr_node->prev == NULL && curr_node->next == NULL)
        {
            void_list = true;
        }

        if (curr_node->prev == NULL && curr_node->next != NULL)
        {
            std::swap(curr_node->value, curr_node->next->value);
            curr_node = curr_node->next;
        }

        if (curr_node->prev != NULL && curr_node->next == NULL)
        {
            curr_node->prev->next = NULL;
        }

        if (curr_node->prev != NULL && curr_node->next != NULL)
        {
            curr_node->prev->next = curr_node->next;
            curr_node->next->prev = curr_node->prev;
        }

        curr_node->below->propagate_deletion();

        // delete curr_node;

        return true;
    }

    return false;
}

bool node::find_value(int x)
{
    node* curr_node = this;
    
    if (x == curr_node->value)
        return curr_node->value;

    while (curr_node->next != NULL)
        if (curr_node->next->value < x)
            curr_node = curr_node->next;
        else
            break;

    bool go_down = false;
    
    if (curr_node->next == NULL)
        go_down = true;
    else if (curr_node->next->value > x)
        go_down = true;
    
    if (curr_node->value < x && go_down)
    {
        if (curr_node->below != NULL)
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

    while (curr_node->next != NULL)
        if (curr_node->next->value < x)
            curr_node = curr_node->next;
        else
            break;

    bool go_down = false;
    
    if (curr_node->next == NULL)
        go_down = true;
    else if (curr_node->next->value > x)
        go_down = true;
    
    if (curr_node->value < x && go_down)
        if (curr_node->below != NULL)
            return curr_node->below->find_greatest(x);
    
    return curr_node;
}

int node::find_least(int x)
{
    node* curr_node = this;
    
    while (curr_node->below != NULL)
    {
        while (curr_node->next != NULL)
            if (curr_node->value > x)
                break;
            else
                curr_node = curr_node->next;
        
        curr_node = curr_node->below;
    }

    if (curr_node->value < x)
    {
        while (curr_node != NULL)
        {
            if (curr_node->value >= x)
                break;
            else
                curr_node = curr_node->next;
        }
    }
    else
    {
        while (curr_node->prev != NULL)
        if (curr_node->prev->value < x)
            break;
        else
            curr_node = curr_node->prev;
    }
    
    return curr_node->value;
}

void node::print_list()
{
    node* curr_node = this;
    
    if (void_list)
        return;
    
    while (curr_node != NULL) {
        fout << curr_node->value << ' ';
        
        curr_node = curr_node->next;
    }
    
    fout << '\n';
}

class skip_list
{
public:
    skip_list();
    
    void insert_node(int);
    bool delete_node(int);
    void print_list();
    bool find_value(int);
    int find_greatest(int);
    int find_least(int);
    void print_interval(int, int);

private:
    std::vector<node*> levels;
};

skip_list::skip_list()
{
    this->levels.push_back(new node());
}

void skip_list::insert_node(int value)
{
    bool lowest_value;
    
    node* base_node = levels[0]->insert_node(value, lowest_value);
    
    if (base_node == NULL)
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
    return levels[levels.size() - 1]->delete_node(value);
}

void skip_list::print_list()
{
    for (int i = (int)this->levels.size() - 1; i >= 0; i--)
        levels[i]->print_list();
    
    fout << '\n';
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

void skip_list::print_interval(int x, int y)
{
    node* start_node = levels[levels.size() - 1]->find_greatest(x);

    if (start_node->next == NULL)
        return;
        
    start_node = start_node->next;
    
    while (start_node->below != NULL)
        start_node = start_node->below;
    
    while (start_node != NULL) {
        if (start_node->value > y)
            break;
        fout << start_node->value << ' ';
        start_node = start_node->next;
    }
    
    fout << '\n';
}

int main() {
    srand(time(NULL));
    
    skip_list sl;
    
    int x, y, q, opt;

    fin >> q;

    for (int i = 1; i <= q; i++)
    {
        fin >> opt >> x;

        switch (opt) {
            case 1:
                sl.insert_node(x);
                break;

            case 2:
                sl.delete_node(x);
                break;

            case 3:
                fout << sl.find_value(x) << '\n';
                break;

            case 4:
                fout << sl.find_greatest(x) << '\n';
                break;

            case 5:
                fout << sl.find_least(x) << '\n';
                break;

            case 6:
                fin >> y;
                sl.print_interval(x, y);
                break;

            default:
                break;
        }
    }
    
    return 0;
}
