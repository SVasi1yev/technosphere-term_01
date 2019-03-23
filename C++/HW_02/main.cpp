#include <iostream>
#include <vector>
#include <string>
#include <map>

enum TokenType {
    TOK_NUM,
    TOK_PLUS,
    TOK_UN_MINUS,
    TOK_MINUS,
    TOK_TIMES,
    TOK_SLASH
};

struct Token {
    TokenType type;
    int64_t value;

    Token (TokenType type, int64_t value) 
        : type(type), value(value) {};
};

class Tokenizer {
    std::map<char, TokenType> tokenMap;
    char curChar;

    inline bool isSpace () { return curChar == ' '; }
    inline bool isEof () { return curChar == '\0'; }
    inline bool isMinus () { return curChar == '-'; }
    inline bool isNum1_9 () { 
        return (curChar >= '1') 
            && (curChar <= '9'); 
    }
    inline bool isNum0_9 () { 
        return (curChar >= '0') 
            && (curChar <= '9'); 
    }
    inline bool isOp () {
        return (curChar == '+') || (curChar == '-')
            || (curChar == '*') || (curChar == '/');
    }

public:
    std::vector<Token> tokens;

    Tokenizer () {
        tokenMap['+'] = TOK_PLUS;
        tokenMap['-'] = TOK_MINUS;
        tokenMap['*'] = TOK_TIMES;
        tokenMap['/'] = TOK_SLASH;
    }

    void fit (const char* exp) {
        bool finish = true;
        uint8_t state = 0;
        int64_t accNum = 0;
        tokens.clear();

        for (size_t i = 0; finish; i++) {
            curChar = exp[i];
            switch (state) {
                case 0:
                    if (isMinus()) {
                        tokens.push_back(Token(TOK_MINUS, 0));
                    } else if (isNum1_9()) {
                        accNum = curChar - '0';
                        state = 1;
                    } else if (!isSpace()) {
                        throw std::invalid_argument("Lex error");
                    }
                    break;

                case 1:
                    if (isNum0_9()) {
                        accNum = accNum * 10 + curChar - '0';
                    } else if (isEof()) {
                        tokens.push_back(Token(TOK_NUM, accNum));
                        finish = false;
                    } else if (isOp()) {
                        tokens.push_back(Token(TOK_NUM, accNum));
                        tokens.push_back(Token(tokenMap[curChar], 0));
                        state = 0;
                    } else if (isSpace()) {
                        tokens.push_back(Token(TOK_NUM, accNum));
                        state = 2;
                    } else {
                        throw std::invalid_argument("Lex error");
                    }
                    break;

                case 2:
                    if (isOp()) {
                        tokens.push_back(Token(tokenMap[curChar], 0));
                        state = 0;
                    } else if (!isSpace()) {
                        throw std::invalid_argument("Lex error");
                    }
                    break;

                default:
                    break;
            }
        }
    }
};

class Parser {
    
};

int main (int argc, char* argv[]) {
    Tokenizer t;
    t.fit(argv[1]);
    std::cout << "size = " << t.tokens.size() << "\n";
    for (size_t i = 0; i < t.tokens.size(); i++) {
        std::cout << t.tokens[i].type << "\n";
    }

    return 0;
}