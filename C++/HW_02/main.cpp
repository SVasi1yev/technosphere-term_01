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
    TOK_SLASH,
    TOK_END
};

struct Token {
    TokenType type;
    int64_t value;

    Token (TokenType type, int64_t value) 
        : type(type), value(value) {};
};

class Tokenizer {
    std::map<char, TokenType> tokenMap;
    std::vector<Token> tokens;
    char curChar;
    size_t tokensSize;

    inline bool isSpace () const { return curChar == ' '; }
    inline bool isEof () const { return curChar == '\0'; }
    inline bool isMinus () const { return curChar == '-'; }
    inline bool isNum0 () const { return curChar == '0'; }
    inline bool isNum1_9 () const { 
        return (curChar >= '1') 
            && (curChar <= '9'); 
    }
    inline bool isNum0_9 () const { 
        return (curChar >= '0') 
            && (curChar <= '9'); 
    }
    inline bool isOp () const {
        return (curChar == '+') || (curChar == '-')
            || (curChar == '*') || (curChar == '/');
    }

public:
    Tokenizer () {
        tokenMap['+'] = TOK_PLUS;
        tokenMap['-'] = TOK_MINUS;
        tokenMap['*'] = TOK_TIMES;
        tokenMap['/'] = TOK_SLASH;
    }

    Token getTokenAt (size_t i) const {
        return tokens[i];
    }

    void fit (const std::string& exp) {
        bool finish = true;
        uint8_t state = 0;
        int64_t accNum = 0;
        tokens.clear();

        for (size_t i = 0; finish; i++) {
            curChar = exp[i];
            switch (state) {
                case 0:
                    if (isMinus()) {
                        tokens.push_back(Token(TOK_UN_MINUS, 0));
                    } else if (isNum0()) {
                        tokens.push_back(Token(TOK_NUM, 0));
                        state = 2;
                    } else if (isNum1_9()) {
                        accNum = curChar - '0';
                        state = 1;
                    } else if (!isSpace()) {
                        throw std::invalid_argument("error");
                    }
                    break;

                case 1:
                    if (isNum0_9()) {
                        accNum = accNum * 10 + curChar - '0';
                    } else if (isEof()) {
                        tokens.push_back(Token(TOK_NUM, accNum));
                        tokens.push_back(Token(TOK_END, 0));
                        finish = false;
                    } else if (isOp()) {
                        tokens.push_back(Token(TOK_NUM, accNum));
                        tokens.push_back(Token(tokenMap[curChar], 0));
                        state = 0;
                    } else if (isSpace()) {
                        tokens.push_back(Token(TOK_NUM, accNum));
                        state = 2;
                    } else {
                        throw std::invalid_argument("error");
                    }
                    break;

                case 2:
                    if (isOp()) {
                        tokens.push_back(Token(tokenMap[curChar], 0));
                        state = 0;
                    } else if (isEof()) {
                        tokens.push_back(Token(TOK_END, 0));
                        finish = false;
                    } else if (!isSpace()) {
                        throw std::invalid_argument("error");
                    }
                    break;

                default:
                    break;
            }
        }
    }
};

class Parser {
    Tokenizer t;
    size_t pos;

    inline bool isAdd () const { return t.getTokenAt(pos).type == TOK_PLUS; }
    inline bool isSub () const { return t.getTokenAt(pos).type == TOK_MINUS; }
    inline bool isMul () const { return t.getTokenAt(pos).type == TOK_TIMES; }
    inline bool isDiv () const { return t.getTokenAt(pos).type == TOK_SLASH; }
    inline bool isUnMinus () const { return t.getTokenAt(pos).type == TOK_UN_MINUS; }
    inline bool isNum () const { return t.getTokenAt(pos).type == TOK_NUM; }
    inline bool isEnd () const { return t.getTokenAt(pos).type == TOK_END; }

    int64_t addSub () {
        int64_t acc = 0;
        acc = mulDiv();
        while (true) {
            if (isAdd()) {
                pos++;
                acc += mulDiv();
            } else if (isSub()) {
                pos++;
                acc -= mulDiv();
            } else if (isEnd()) {
                return acc;
            } else {
                throw std::invalid_argument("error");
            }
        }
    }

    int64_t mulDiv () {
        int64_t acc = 0;
        acc = num();
        while (true) {
            if (isMul()) {
                pos++;
                acc *= num();
            } else if (isDiv()) {
                pos++;
                int64_t temp = num ();
                if (temp == 0) {
                    throw std::invalid_argument("error");
                }
                acc /= temp;
            } else {
                return acc;       
            }
        }
    }

    int64_t num () {
        int8_t sign = 1;
        while (isUnMinus()) {
            sign *= -1;
            pos++;
        }
        if (isNum()) {
            return t.getTokenAt(pos++).value * sign;
        } else {
            throw std::invalid_argument("error");
        }
    }

public:
    std::string parse (const std::string& exp) {
        t.fit(exp);
        pos = 0;
        return std::to_string(addSub());
    }
};

int main (int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "error" << '\n';
        return 1;
    }
    Parser p;
    try {
        std::cout << p.parse(argv[1]) << '\n';
    } catch (std::invalid_argument e) {
        std::cout << e.what() << '\n';
        return 1;
    }

    return 0;
}