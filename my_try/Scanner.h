
// Scanner.h
#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>
#include <bits/stdc++.h>

using namespace std;

// Token types
enum class TokenType {
    
    
    // Single-character tokens.
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
    // One or two character tokens.
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,
    // Literals.
    IDENTIFIER, STRING, NUMBER,
    // Keywords.
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,
    FUNCTION, 
    EOF_TOKEN,

    UNKNOWN
};

// End of header guard
// Token structure
struct Token {
    TokenType type;
    std::string lexeme;
    int line;

    Token(TokenType t, const std::string& lex, int ln) : type(t), lexeme(lex), line(ln) {}
};

class Scanner {

public:
    Scanner(const std::string& sourceCode);
    std::vector<Token> scanTokens();
private:
    std::string source;
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;
    
    int line = 1;

    std::unordered_map<std::string, TokenType> keywords ;

    bool isAtEnd() ;

    char advance() ;

    char peek() ;

    char peekNext() ;

    void addToken(TokenType type, const std::string& lexeme) ;

    void addToken(TokenType type) ;

    bool match(char expected) ;

    void string() ;

    void number() ;

    void identifier() ;

    void scanToken() ;
};

#endif // SCANNER_H