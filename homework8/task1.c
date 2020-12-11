#include "../library/commonUtils/arrayOperations.h"
#include "../library/dfa.h"
#include <stdio.h>
#include <stdlib.h>

DFA* initializeDFA()
{
    DFAState* initialState = createDFAState(false);
    DFAState* plusState = createDFAState(false);
    DFAState* minusState = createDFAState(false);
    DFAState* numberState = createDFAState(true);
    DFAState* dotState = createDFAState(false);

    DFA* dfa = createDFA(initialState);
    addTransition(initialState, plusState, '+');
    addTransition(initialState, minusState, '-');
    addTransition(numberState, initialState, 'E');
    addTransition(numberState, dotState, '.');
    for (int i = '0'; i <= '9'; ++i) {
        addTransition(initialState, numberState, (char)(i));
        addTransition(plusState, numberState, (char)(i));
        addTransition(minusState, numberState, (char)(i));
        addTransition(numberState, numberState, (char)(i));
        addTransition(dotState, initialState, (char)(i));
    }

    return dfa;
}

int main()
{
    printf("Enter the string:\n");
    char* string = readString();

    DFA* dfa = initializeDFA();

    if (isStringCorrect(string, dfa))
        printf("This is a real number");
    else
        printf("This isn't a real number");

    destroyDFA(dfa);
    free(string);
    return 0;
}
