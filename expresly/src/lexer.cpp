#include "expresly/lexer.h"

#include <cctype>
#include <iostream>

namespace expresly {
  Lexer::Token Lexer::next() noexcept {
    while (std::isspace(peek())) get();

    switch (peek()) {
    case '\0':
      return Token(Token::Type::End, m_beg, 1);
    default:
      return atom(Token::Type::Unexpected);
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
      return identifier();
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return number();
    case '(':
      return atom(Token::Type::LeftParen);
    case ')':
      return atom(Token::Type::RightParen);
    case '[':
      return atom(Token::Type::LeftSquare);
    case ']':
      return atom(Token::Type::RightSquare);
    case '{':
      return atom(Token::Type::LeftCurly);
    case '}':
      return atom(Token::Type::RightCurly);
    case '<':
      return atom(Token::Type::LessThan);
    case '>':
      return atom(Token::Type::GreaterThan);
    case '=':
      return atom(Token::Type::Equal);
    case '+':
      return atom(Token::Type::Plus);
    case '-':
      return atom(Token::Type::Minus);
    case '*':
      return atom(Token::Type::Asterisk);
    case '/':
      return slash_or_comment();
    case '#':
      return atom(Token::Type::Hash);
    case '.':
      return atom(Token::Type::Dot);
    case ',':
      return atom(Token::Type::Comma);
    case ':':
      return atom(Token::Type::Colon);
    case ';':
      return atom(Token::Type::Semicolon);
    case '\'':
      return atom(Token::Type::SingleQuote);
    case '"':
      return atom(Token::Type::DoubleQuote);
    case '|':
      return atom(Token::Type::Pipe);
    }
  }

  Lexer::Token Lexer::identifier() noexcept {
    const char* start = m_beg;
    get();
    while (std::isalnum(peek())) get();
    return Lexer::Token(Lexer::Token::Type::Identifier, start, m_beg);
  }

  Lexer::Token Lexer::number() noexcept {
    const char* start = m_beg;
    get();
    while (std::isdigit(peek())) get();
    return Lexer::Token(Lexer::Token::Type::Number, start, m_beg);
  }

  Lexer::Token Lexer::slash_or_comment() noexcept {
    const char* start = m_beg;
    get();
    if (peek() == '/') {
      get();
      start = m_beg;
      while (peek() != '\0') {
        if (get() == '\n') {
          return Lexer::Token(Lexer::Token::Type::Comment, start,
            std::distance(start, m_beg) - 1);
        }
      }
      return Lexer::Token(Lexer::Token::Type::Unexpected, m_beg, 1);
    }
    else {
      return Lexer::Token(Lexer::Token::Type::Slash, start, 1);
    }
  }

  Lexer::Token Lexer::atom(Token::Type type) noexcept { return Lexer::Token(type, m_beg++, 1); }

  std::ostream& operator<<(std::ostream& os, const Lexer::Token::Type& type) {
    static const char* const names[]{
      "Number",      "Identifier",  "LeftParen",  "RightParen", "LeftSquare",
      "RightSquare", "LeftCurly",   "RightCurly", "LessThan",   "GreaterThan",
      "Equal",       "Plus",        "Minus",      "Asterisk",   "Slash",
      "Hash",        "Dot",         "Comma",      "Colon",      "Semicolon",
      "SingleQuote", "DoubleQuote", "Comment",    "Pipe",       "End",
      "Unexpected",
    };
    return os << names[static_cast<int>(type)];
  }
}