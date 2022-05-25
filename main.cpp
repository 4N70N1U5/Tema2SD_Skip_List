//
//  main.cpp
//  Skip List
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

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
        fin >> opt;

        switch (opt) {
            case 1:
                fin >> x;
                sl.insert_node(x);
                break;

            case 2:
                fin >> x;
                sl.delete_node(x);
                break;

            case 3:
                fin >> x;
                fout << sl.find_value(x) << '\n';
                break;

            case 4:
                fin >> x;
                fout << sl.find_greatest(x) << '\n';
                break;

            case 5:
                fin >> x;
                fout << sl.find_least(x) << '\n';
                break;

            case 6:
                fin >> x >> y;
                sl.print_interval(fout, x, y);
                break;

            case 7:
                sl.print_list(fout);
                break;

            default:
                break;
        }
    }
    
    return 0;
}
