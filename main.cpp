//
//  main.cpp
//  Skip List
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "skip_list.hpp"

std::ifstream fin("abce.in");
std::ofstream fout("abce.out");

int main() {
    srand(time(nullptr));
    
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
                sl.print_interval(fout, x, y);
                break;

            default:
                break;
        }
    }
    
    return 0;
}
