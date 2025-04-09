#include "Scanner.h"

Scanner::Scanner(const std::string& sourceCode) : source(sourceCode) {
    keywords = {
        {"if", TokenType::IF}, {"else", TokenType::ELSE},
        {"for", TokenType::FOR}, {"while", TokenType::WHILE},
        {"return", TokenType::RETURN}, {"var", TokenType::VAR},
        {"function", TokenType::FUNCTION} , {"and", TokenType::AND},
        {"class", TokenType::CLASS}, {"false", TokenType::FALSE},
        {"fun", TokenType::FUN}, {"nil", TokenType::NIL},
        {"or", TokenType::OR}, {"print", TokenType::PRINT},
        {"super", TokenType::SUPER}, {"this", TokenType::THIS},
        {"true", TokenType::TRUE}
    };
}

std::vector<Token> Scanner::scanTokens(){
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }

    tokens.emplace_back(TokenType::EOF_TOKEN, "", line);
    return tokens;
}


bool Scanner::isAtEnd() {
    return current >= (int) source.size();
}

char Scanner::advance() {
    return source[current++];
}

char Scanner::peek() {
    return isAtEnd() ? '\0' : source[current];
}

char Scanner::peekNext() {
    return (current + 1 < (int) source.size()) ? source[current + 1] : '\0';
}

void Scanner::addToken(TokenType type, const std::string& lexeme) {
    tokens.emplace_back(type, lexeme, line);
}

void Scanner::addToken(TokenType type) {
    addToken(type, source.substr(start, current - start));
}

bool Scanner::match(char expected) {
    if (isAtEnd() || source[current] != expected) return false;
    current++;
    return true;
}


void Scanner::string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }

    if (isAtEnd()) {
        std::cerr << "[Line " << line << "] Unterminated string." << std::endl;
        return;
    }

    advance(); // Closing "
    std::string value = source.substr(start + 1, current - start - 2);
    addToken(TokenType::STRING, value);
}

void Scanner::number() {
    while (isdigit(peek())) advance();

    if (peek() == '.' && isdigit(peekNext())) {
        advance();
        while (isdigit(peek())) advance();
    }

    addToken(TokenType::NUMBER);
}

void Scanner::identifier() {
    while (isalnum(peek()) || peek() == '_') advance();

    std::string text = source.substr(start, current - start);
    TokenType type = keywords.count(text) ? keywords[text] : TokenType::IDENTIFIER;
    addToken(type);
}

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case '+': addToken(TokenType::PLUS); break;
        case '-': addToken(TokenType::MINUS); break;
        case '*': addToken(TokenType::STAR); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '!': addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
        case '=': addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
        case '<': addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
        case '>': addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
        case '/':
            if (match('/')) {
                while (peek() != '\n' && !isAtEnd()) advance();
            } else {
                addToken(TokenType::SLASH);
            }
            break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '"': string(); break;
        case '\n': line++; break;
        case ' ': case '\r': case '\t': break; // Ignore whitespace
        default:
            if (isdigit(c)) {
                number();
            } else if (isalpha(c) || c == '_') {
                identifier();
            } else {
                addToken(TokenType::UNKNOWN);
            }
    }
}



