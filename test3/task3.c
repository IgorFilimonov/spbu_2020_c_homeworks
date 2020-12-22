#include "../library/commonUtils/arrayOperations.h"
#include "../library/dfa.h"
#include <stdio.h>
#include <stdlib.h>

DFA* initializeDFA()
{
    DFAState* initialState = createDFAState(false);
    DFAState* userName = createDFAState(false);
    DFAState* atSign = createDFAState(false);
    DFAState* serverNamePart = createDFAState(false);
    DFAState* dotState = createDFAState(false);
    DFAState* finalState = createDFAState(true);

    DFA* dfa = createDFA(initialState);
    addTransition(initialState, userName, '.');
    addTransition(initialState, userName, '_');
    addTransition(initialState, userName, '%');
    addTransition(initialState, userName, '+');
    addTransition(initialState, userName, '-');
    addTransition(userName, userName, '.');
    addTransition(userName, userName, '_');
    addTransition(userName, userName, '%');
    addTransition(userName, userName, '+');
    addTransition(userName, userName, '-');
    addTransition(userName, atSign, '@');
    addTransition(atSign, serverNamePart, '-');
    addTransition(serverNamePart, serverNamePart, '-');
    addTransition(serverNamePart, dotState, '.');
    addTransition(dotState, serverNamePart, '-');
    addTransition(finalState, serverNamePart, '-');
    addTransition(finalState, dotState, '.');
    for (int i = 'A'; i <= 'Z'; ++i) {
        addTransition(initialState, userName, (char)(i));
        addTransition(userName, userName, (char)(i));
        addTransition(atSign, serverNamePart, (char)(i));
        addTransition(serverNamePart, serverNamePart, (char)(i));
        addTransition(dotState, finalState, (char)(i));
        addTransition(finalState, serverNamePart, (char)(i));
    }
    for (int i = '0'; i <= '9'; ++i) {
        addTransition(initialState, userName, (char)(i));
        addTransition(userName, userName, (char)(i));
        addTransition(atSign, serverNamePart, (char)(i));
        addTransition(serverNamePart, serverNamePart, (char)(i));
        addTransition(dotState, serverNamePart, (char)(i));
        addTransition(finalState, serverNamePart, (char)(i));
    }

    return dfa;
}

int main()
{
    printf("Enter a string:\n");
    char* string = readString();

    DFA* dfa = initializeDFA();

    if (isStringCorrect(string, dfa))
        printf("This string is valid");
    else
        printf("This string is invalid");

    free(string);
    destroyDFA(dfa);

    return 0;
}