#include <iostream>
#include "omp.h"
using namespace std;

int main(int argc, char** argv)
{
    unsigned w_num = 0;
    if (argc < 2)
    {
        cout << "Please input some text" << endl;
        return 1;
    }
    char*       input_text = argv[1];
    char        new_symbol, previous_symbol;
    unsigned    i = 1;
    previous_symbol = new_symbol = input_text[0];
    while (new_symbol != '\0')
    {
        new_symbol = input_text[i];
        if (not(previous_symbol == ' ' or previous_symbol == '\t' or previous_symbol == '\n') and
            (new_symbol == ' ' or new_symbol == '\t' or new_symbol == '\n' or new_symbol == '\0'))
        {
            w_num++;
        }
        previous_symbol = new_symbol;
        i++;
    }
    cout << "Number of words:" << w_num << endl;
    return 0;
}