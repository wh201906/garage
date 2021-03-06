#include <vector>
#include <stack>
#include "common.h"

using namespace std;

enum SymbolType
{
    TERMINAL = 0,
    UNTERMINAL,
    END,
    UNDEFINED
};

// row: E, e, T, t, F, A, M
// column: +, -, *, /, i, (, ), $
// reversed order for pushing into stack
char analyzeTable[7][8][20] = {
    {"", "", "", "", "eT", "eT", "", ""},
    {"eTA", "eTA", "", "", "", "", "#", "#"},
    {"", "", "", "", "tF", "tF", "", ""},
    {"#", "#", "tFM", "tFM", "", "", "#", "#"},
    {"", "", "", "", "i", ")E(", "", ""},
    {"+", "-", "", "", "", "", "", ""},
    {"", "", "*", "/", "", "", "", ""}};

extern vector<element> elementList; // input series
// vector<element> elementList; // test only
stack<int> downStack;

int Down_tr(int symbol)
{
    if (symbol == 'E' || symbol == '+')
        return 0;
    else if (symbol == 'e' || symbol == '-')
        return 1;
    else if (symbol == 'T' || symbol == '*')
        return 2;
    else if (symbol == 't' || symbol == '/')
        return 3;
    else if (symbol == 'F' || symbol == 'i' || symbol == IDENTIFIER)
        return 4;
    else if (symbol == 'A' || symbol == '(')
        return 5;
    else if (symbol == 'M' || symbol == ')')
        return 6;
    else if (symbol == '$')
        return 7;
}

SymbolType Down_check(int symbol)
{
    if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == 'i' || symbol == IDENTIFIER || symbol == '(' || symbol == ')')
        return TERMINAL;
    else if (symbol == 'E' || symbol == 'e' || symbol == 'T' || symbol == 't' || symbol == 'F' || symbol == 'A' || symbol == 'M')
        return UNTERMINAL;
    else if (symbol == '$')
        return END;
    else
        return UNDEFINED;
}

bool Down_Start()
{
    int currTop;
    int i, ptr = 0, flag = 0, tmp;
    SymbolType type;
    int x, y;
    elementList.push_back({'$', 0}); // end symbol
    downStack.push('$');             // end symbol
    downStack.push('E');             // start symbol
    while ((currTop = downStack.top()) != '$')
    {
        downStack.pop();
        flag = 0;
        x = Down_tr(currTop);
        y = Down_tr(elementList[ptr].type);
        // error check
        type = Down_check(elementList[ptr].type);
        if (type != END && type != TERMINAL)
        {
            printf("Error: unexpected symbol in elementList(result of scanner)\n");
            return false;
        }
        type = Down_check(currTop);
        if (type == TERMINAL)
        {
            if (currTop == elementList[ptr].type)
            {
                ptr++;
                continue;
            }
            else if (currTop == 'i' && elementList[ptr].type == IDENTIFIER)
            {
                ptr++;
                continue;
            }
            else
            {
                printf("Error: Error\n");
                return false;
            }
        }
        else if (type != UNTERMINAL)
        {
            printf("Error: unexpected symbol in downStack\n");
            return false;
        }
        if (analyzeTable[x][y][0] == '\0')
        {
            printf("Error: invalid syntax\n");
            return false;
        }
        // X->#
        printf("Using: %d, %c, %s\n", currTop, currTop, analyzeTable[x][y]);
        if (analyzeTable[x][y][0] == '#')
        {
            continue; // do nothing, skipped
        }
        // normal
        for (i = 0; analyzeTable[x][y][i] != '\0'; i++)
            downStack.push(analyzeTable[x][y][i]);
    }
    if (elementList[ptr].type != '$')
        return false;
    else
        return true;
}

// int main() // test only
// {
//     elementList.push_back(element({'i', 0}));
//     elementList.push_back(element({'+', 0}));
//     elementList.push_back(element({'i', 0}));
//     elementList.push_back(element({'*', 0}));
//     elementList.push_back(element({'i', 0}));
//     if(Down_Start())
//         printf("valid expression\n");
//     return 0;
// }