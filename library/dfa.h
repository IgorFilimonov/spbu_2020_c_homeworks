#ifndef SPBU_2020_C_HOMEWORKS_DFA_H
#define SPBU_2020_C_HOMEWORKS_DFA_H

#include <stdbool.h>

typedef struct DFA DFA;

typedef struct DFAState DFAState;

DFA* createDFA(DFAState* initialState);

DFAState* createDFAState(bool isFinal);

void addTransition(DFAState* firstState, DFAState* secondState, char symbol);

bool isStringCorrect(char* string, DFA* dfa);

void destroyDFA(DFA* dfa);

void destroyDFAState(DFAState* dfaState);

#endif //SPBU_2020_C_HOMEWORKS_DFA_H
