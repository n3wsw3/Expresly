#pragma once

#include <string_view>
#include <string>
#include <iostream>

namespace expresly
{
  class Lexer
  {
  public:
    class Token
    {
    public:
      enum class Type
      {
        Number,
        Identifier,
        LeftParen,
        RightParen,
        LeftSquare,
        RightSquare,
        LeftCurly,
        RightCurly,
        LessThan,
        GreaterThan,
        Equal,
        Plus,
        Minus,
        Asterisk,
        Slash,
        Hash,
        Dot,
        Comma,
        Colon,
        Semicolon,
        SingleQuote,
        DoubleQuote,
        Comment,
        Pipe,
        End,
        Unexpected,
      };
      Token(Type type) noexcept : m_type{ type } {}
      Token(Type type, const char* beg, std::size_t len) noexcept : m_type{ type }, m_lexeme(beg, len) {}
      Token(Type type, const char* beg, const char* end) noexcept : m_type{ type }, m_lexeme(beg, std::distance(beg, end)) {}

      Type type() const noexcept { return m_type; }
      bool is(Type type) const noexcept { return m_type == type; }
      bool is_one_of(Type t1, Type t2) const noexcept { return is(t1) || is(t2); }

      template <typename... Ts>
      bool is_one_of(Type t1, Type t2, Ts... ts) const noexcept {
        return is(t1) || is_one_of(t2, ts...);
      }

      std::string_view lexeme() const noexcept { return m_lexeme; }

      void lexeme(std::string_view lexeme) noexcept {
        m_lexeme = std::move(lexeme);
      }

      friend std::ostream& operator<<(std::ostream& os, const Type& type);

    private:
      Type m_type{};
      std::string_view m_lexeme{};
    };

  public:
    Lexer(const char* beg) noexcept : m_beg{ beg } {}

    Lexer::Token next() noexcept;

  private:
    Lexer::Token identifier() noexcept;
    Lexer::Token number() noexcept;
    Lexer::Token slash_or_comment() noexcept;
    Lexer::Token atom(Lexer::Token::Type) noexcept;
    // Token number()

    char peek() const noexcept { return *m_beg; }
    char get() noexcept { return *m_beg++; }

    const char* m_beg = nullptr;
  };
  
}
