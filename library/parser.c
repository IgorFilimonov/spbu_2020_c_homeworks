#include "dfa.h"
#include "parser.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

enum TokenType {
    number,
    operation
};

typedef struct Token {
    enum TokenType type;
    char* value;
} Token;

Token* createToken(enum TokenType type, char* value)
{
    Token* newToken = (Token*)malloc(sizeof(Token));
    newToken->type = type;
    newToken->value = value;
    return newToken;
}

void destroyToken(Token* token)
{
    free(token->value);
    free(token);
}

bool E(Token** tokens, int size, int* current);
bool T(Token** tokens, int size, int* current);
bool E1(Token** tokens, int size, int* current);
bool T1(Token** tokens, int size, int* current);

/*
 * E -> T E1
 * E1 -> + T E1 | - T E1 | eps
 * T -> num T1
 * T1 -> * num T1 | / num T1 | eps
 */

bool E(Token** tokens, int size, int* current)
{
    return T(tokens, size, current) && E1(tokens, size, current);
}

bool T(Token** tokens, int size, int* current)
{
    if (*current >= size)
        return true;
    int position = *current;
    if (tokens[*current]->type == number) {
        ++(*current);
        if (T1(tokens, size, current))
            return true;
        *current = position;
    }
    return false;
}

bool E1(Token** tokens, int size, int* current)
{
    if (*current >= size)
        return true;
    int position = *current;
    if (strcmp(tokens[*current]->value, "+") == 0 || strcmp(tokens[*current]->value, "-") == 0) {
        ++(*current);
        if (T(tokens, size, current) && E1(tokens, size, current))
            return true;
        *current = position;
    }
    return true;
}

bool T1(Token** tokens, int size, int* current)
{
    if (*current >= size)
        return true;
    int position = *current;
    if (strcmp(tokens[*current]->value, "*") == 0 || strcmp(tokens[*current]->value, "/") == 0) {
        ++(*current);
        if (tokens[*current]->type == number) {
            ++(*current);
            if (T1(tokens, size, current))
                return true;
        }
        *current = position;
    }
    return true;
}

Token** getTokens(char* string, int* countTokens, bool* isAllCorrect);

char* getTokenValue(char* string);

DFA* initializeDFA();

bool isOperation(char* string);

bool isCorrectForParser(char* string)
{
    int countTokens = 0;
    bool isAllCorrect = true;
    Token** tokens = getTokens(string, &countTokens, &isAllCorrect);

    bool result = false;
    if (isAllCorrect) {
        int current = 0;
        result = E(tokens, countTokens, &current) & (current == countTokens);
    }

    for (int i = 0; i < countTokens; ++i)
        destroyToken(tokens[i]);
    free(tokens);

    if (!isAllCorrect)
        return false;
    else
        return result;
}

Token** getTokens(char* string, int* countTokens, bool* isAllCorrect)
{
    Token** tokens = (Token**)calloc(strlen(string) / 2 + 1, sizeof(Token*));
    DFA* dfa = initializeDFA();
    int index = 0;
    while (index < strlen(string)) {
        char* tokenValue = getTokenValue(&string[index]);
        if (!isOperation(tokenValue)) {
            if (!isCorrectForDFA(tokenValue, dfa)) {
                *isAllCorrect = false;
                break;
            }
            tokens[*countTokens] = createToken(number, tokenValue);
        } else
            tokens[*countTokens] = createToken(operation, tokenValue);
        ++(*countTokens);
        index += strlen(tokenValue) + 1;
    }

    destroyDFA(dfa);
    return tokens;
}

char* getTokenValue(char* string)
{
    int nextSpaceIndex = strcspn(string, " ");
    int tokenValueSize = nextSpaceIndex + 1;
    char* tokenValue = (char*)malloc(tokenValueSize * sizeof(char));
    strncpy(tokenValue, string, tokenValueSize - 1);
    tokenValue[tokenValueSize - 1] = '\0';
    return tokenValue;
}

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
        addTransition(dotState, numberState, (char)(i));
    }

    return dfa;
}

bool isOperation(char* string)
{
    if (strcmp(string, "+") == 0)
        return true;
    if (strcmp(string, "-") == 0)
        return true;
    if (strcmp(string, "*") == 0)
        return true;
    if (strcmp(string, "/") == 0)
        return true;
    return false;
}
