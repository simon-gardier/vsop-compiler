// A Bison parser, made by GNU Bison 3.7.5.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


/**
 ** \file parser.hpp
 ** Define the VSOP::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
// "%code requires" blocks.
#line 40 "parser.y"

    #include <string>
    #include <vector>
    #include <array>
    #include "ast.hpp"

    namespace VSOP
    {
        class Driver;
    }

#line 61 "parser.hpp"

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"
#include <typeinfo>
#ifndef YY_ASSERT
# include <cassert>
# define YY_ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

#line 19 "parser.y"
namespace VSOP {
#line 196 "parser.hpp"




  /// A Bison parser.
  class Parser
  {
  public:
#ifndef YYSTYPE
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class semantic_type
  {
  public:
    /// Type of *this.
    typedef semantic_type self_type;

    /// Empty construction.
    semantic_type () YY_NOEXCEPT
      : yybuffer_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    semantic_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      YY_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    semantic_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {
      YY_ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == *that.yytypeid_);
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    semantic_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // single-class
      char dummy1[sizeof (ClassAst*)];

      // members
      char dummy2[sizeof (ClassBody)];

      // single-expr
      // conditional
      // loop
      // variable-binding
      // assignment
      // unary-op
      // binary-op
      // method-call
      // object-creation
      char dummy3[sizeof (ExprAst*)];

      // code-block
      char dummy4[sizeof (ExprBlockAst*)];

      // constant
      char dummy5[sizeof (ExprLiteralAst*)];

      // field-decl
      char dummy6[sizeof (FieldAst*)];

      // single-param
      char dummy7[sizeof (FormalAst*)];

      // method-decl
      char dummy8[sizeof (MethodAst*)];

      // "integer-literal"
      char dummy9[sizeof (int)];

      // "type-identifier"
      // "object-identifier"
      // "string-literal"
      // "error"
      // type-spec
      char dummy10[sizeof (std::string)];

      // program
      // class-list
      char dummy11[sizeof (std::vector<ClassAst*>)];

      // expr-sequence
      // arg-list-opt
      // arg-list
      char dummy12[sizeof (std::vector<ExprAst*>)];

      // param-list
      char dummy13[sizeof (std::vector<FormalAst*>)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[size];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    YYEOF = 0,                     // "end of file"
    YYerror = 1,                   // error
    YYUNDEF = 2,                   // "invalid token"
    LBRACE = 3,                    // "{"
    RBRACE = 4,                    // "}"
    LPAR = 5,                      // "("
    RPAR = 6,                      // ")"
    COLON = 7,                     // ":"
    SEMICOLON = 8,                 // ";"
    COMMA = 9,                     // ","
    PLUS = 10,                     // "+"
    MINUS = 11,                    // "-"
    TIMES = 12,                    // "*"
    DIV = 13,                      // "/"
    POW = 14,                      // "^"
    DOT = 15,                      // "."
    EQUAL = 16,                    // "="
    LOWER = 17,                    // "<"
    LOWER_EQUAL = 18,              // "<="
    ASSIGN = 19,                   // "<-"
    AND = 20,                      // "and"
    BOOL = 21,                     // "bool"
    CLASS = 22,                    // "class"
    DO = 23,                       // "do"
    ELSE = 24,                     // "else"
    EXTENDS = 25,                  // "extends"
    FALSE = 26,                    // "false"
    IF = 27,                       // "if"
    IN = 28,                       // "in"
    INT32 = 29,                    // "int32"
    ISNULL = 30,                   // "isnull"
    LET = 31,                      // "let"
    NEW = 32,                      // "new"
    NOT = 33,                      // "not"
    SELF = 34,                     // "self"
    STRING = 35,                   // "string"
    THEN = 36,                     // "then"
    TRUE = 37,                     // "true"
    UNIT = 38,                     // "unit"
    WHILE = 39,                    // "while"
    TYPE_ID = 40,                  // "type-identifier"
    OBJECT_ID = 41,                // "object-identifier"
    STRING_LIT = 42,               // "string-literal"
    ERROR = 43,                    // "error"
    INTEGER_LIT = 44               // "integer-literal"
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::yytokentype token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 45, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_LBRACE = 3,                            // "{"
        S_RBRACE = 4,                            // "}"
        S_LPAR = 5,                              // "("
        S_RPAR = 6,                              // ")"
        S_COLON = 7,                             // ":"
        S_SEMICOLON = 8,                         // ";"
        S_COMMA = 9,                             // ","
        S_PLUS = 10,                             // "+"
        S_MINUS = 11,                            // "-"
        S_TIMES = 12,                            // "*"
        S_DIV = 13,                              // "/"
        S_POW = 14,                              // "^"
        S_DOT = 15,                              // "."
        S_EQUAL = 16,                            // "="
        S_LOWER = 17,                            // "<"
        S_LOWER_EQUAL = 18,                      // "<="
        S_ASSIGN = 19,                           // "<-"
        S_AND = 20,                              // "and"
        S_BOOL = 21,                             // "bool"
        S_CLASS = 22,                            // "class"
        S_DO = 23,                               // "do"
        S_ELSE = 24,                             // "else"
        S_EXTENDS = 25,                          // "extends"
        S_FALSE = 26,                            // "false"
        S_IF = 27,                               // "if"
        S_IN = 28,                               // "in"
        S_INT32 = 29,                            // "int32"
        S_ISNULL = 30,                           // "isnull"
        S_LET = 31,                              // "let"
        S_NEW = 32,                              // "new"
        S_NOT = 33,                              // "not"
        S_SELF = 34,                             // "self"
        S_STRING = 35,                           // "string"
        S_THEN = 36,                             // "then"
        S_TRUE = 37,                             // "true"
        S_UNIT = 38,                             // "unit"
        S_WHILE = 39,                            // "while"
        S_TYPE_ID = 40,                          // "type-identifier"
        S_OBJECT_ID = 41,                        // "object-identifier"
        S_STRING_LIT = 42,                       // "string-literal"
        S_ERROR = 43,                            // "error"
        S_INTEGER_LIT = 44,                      // "integer-literal"
        S_YYACCEPT = 45,                         // $accept
        S_program = 46,                          // program
        S_47_class_list = 47,                    // class-list
        S_48_single_class = 48,                  // single-class
        S_members = 49,                          // members
        S_50_field_decl = 50,                    // field-decl
        S_51_method_decl = 51,                   // method-decl
        S_52_type_spec = 52,                     // type-spec
        S_53_param_list = 53,                    // param-list
        S_54_single_param = 54,                  // single-param
        S_55_code_block = 55,                    // code-block
        S_56_expr_sequence = 56,                 // expr-sequence
        S_57_single_expr = 57,                   // single-expr
        S_58_arg_list_opt = 58,                  // arg-list-opt
        S_59_arg_list = 59,                      // arg-list
        S_conditional = 60,                      // conditional
        S_loop = 61,                             // loop
        S_62_variable_binding = 62,              // variable-binding
        S_assignment = 63,                       // assignment
        S_64_unary_op = 64,                      // unary-op
        S_65_binary_op = 65,                     // binary-op
        S_66_method_call = 66,                   // method-call
        S_67_object_creation = 67,               // object-creation
        S_constant = 68                          // constant
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_48_single_class: // single-class
        value.move< ClassAst* > (std::move (that.value));
        break;

      case symbol_kind::S_members: // members
        value.move< ClassBody > (std::move (that.value));
        break;

      case symbol_kind::S_57_single_expr: // single-expr
      case symbol_kind::S_conditional: // conditional
      case symbol_kind::S_loop: // loop
      case symbol_kind::S_62_variable_binding: // variable-binding
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_64_unary_op: // unary-op
      case symbol_kind::S_65_binary_op: // binary-op
      case symbol_kind::S_66_method_call: // method-call
      case symbol_kind::S_67_object_creation: // object-creation
        value.move< ExprAst* > (std::move (that.value));
        break;

      case symbol_kind::S_55_code_block: // code-block
        value.move< ExprBlockAst* > (std::move (that.value));
        break;

      case symbol_kind::S_constant: // constant
        value.move< ExprLiteralAst* > (std::move (that.value));
        break;

      case symbol_kind::S_50_field_decl: // field-decl
        value.move< FieldAst* > (std::move (that.value));
        break;

      case symbol_kind::S_54_single_param: // single-param
        value.move< FormalAst* > (std::move (that.value));
        break;

      case symbol_kind::S_51_method_decl: // method-decl
        value.move< MethodAst* > (std::move (that.value));
        break;

      case symbol_kind::S_INTEGER_LIT: // "integer-literal"
        value.move< int > (std::move (that.value));
        break;

      case symbol_kind::S_TYPE_ID: // "type-identifier"
      case symbol_kind::S_OBJECT_ID: // "object-identifier"
      case symbol_kind::S_STRING_LIT: // "string-literal"
      case symbol_kind::S_ERROR: // "error"
      case symbol_kind::S_52_type_spec: // type-spec
        value.move< std::string > (std::move (that.value));
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_47_class_list: // class-list
        value.move< std::vector<ClassAst*> > (std::move (that.value));
        break;

      case symbol_kind::S_56_expr_sequence: // expr-sequence
      case symbol_kind::S_58_arg_list_opt: // arg-list-opt
      case symbol_kind::S_59_arg_list: // arg-list
        value.move< std::vector<ExprAst*> > (std::move (that.value));
        break;

      case symbol_kind::S_53_param_list: // param-list
        value.move< std::vector<FormalAst*> > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ClassAst*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ClassAst*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ClassBody&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ClassBody& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ExprAst*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ExprAst*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ExprBlockAst*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ExprBlockAst*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ExprLiteralAst*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ExprLiteralAst*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, FieldAst*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const FieldAst*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, FormalAst*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const FormalAst*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, MethodAst*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const MethodAst*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ClassAst*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ClassAst*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ExprAst*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ExprAst*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<FormalAst*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<FormalAst*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_48_single_class: // single-class
        value.template destroy< ClassAst* > ();
        break;

      case symbol_kind::S_members: // members
        value.template destroy< ClassBody > ();
        break;

      case symbol_kind::S_57_single_expr: // single-expr
      case symbol_kind::S_conditional: // conditional
      case symbol_kind::S_loop: // loop
      case symbol_kind::S_62_variable_binding: // variable-binding
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_64_unary_op: // unary-op
      case symbol_kind::S_65_binary_op: // binary-op
      case symbol_kind::S_66_method_call: // method-call
      case symbol_kind::S_67_object_creation: // object-creation
        value.template destroy< ExprAst* > ();
        break;

      case symbol_kind::S_55_code_block: // code-block
        value.template destroy< ExprBlockAst* > ();
        break;

      case symbol_kind::S_constant: // constant
        value.template destroy< ExprLiteralAst* > ();
        break;

      case symbol_kind::S_50_field_decl: // field-decl
        value.template destroy< FieldAst* > ();
        break;

      case symbol_kind::S_54_single_param: // single-param
        value.template destroy< FormalAst* > ();
        break;

      case symbol_kind::S_51_method_decl: // method-decl
        value.template destroy< MethodAst* > ();
        break;

      case symbol_kind::S_INTEGER_LIT: // "integer-literal"
        value.template destroy< int > ();
        break;

      case symbol_kind::S_TYPE_ID: // "type-identifier"
      case symbol_kind::S_OBJECT_ID: // "object-identifier"
      case symbol_kind::S_STRING_LIT: // "string-literal"
      case symbol_kind::S_ERROR: // "error"
      case symbol_kind::S_52_type_spec: // type-spec
        value.template destroy< std::string > ();
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_47_class_list: // class-list
        value.template destroy< std::vector<ClassAst*> > ();
        break;

      case symbol_kind::S_56_expr_sequence: // expr-sequence
      case symbol_kind::S_58_arg_list_opt: // arg-list-opt
      case symbol_kind::S_59_arg_list: // arg-list
        value.template destroy< std::vector<ExprAst*> > ();
        break;

      case symbol_kind::S_53_param_list: // param-list
        value.template destroy< std::vector<FormalAst*> > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return Parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// Default constructor.
      by_kind ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that);
#endif

      /// Copy constructor.
      by_kind (const by_kind& that);

      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t);

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type(token_type (tok), std::move (l))
#else
      symbol_type (int tok, const location_type& l)
        : super_type(token_type (tok), l)
#endif
      {
        YY_ASSERT (tok == token::YYEOF
                   || (token::YYerror <= tok && tok <= token::WHILE));
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const int& v, const location_type& l)
        : super_type(token_type (tok), v, l)
#endif
      {
        YY_ASSERT (tok == token::INTEGER_LIT);
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type(token_type (tok), v, l)
#endif
      {
        YY_ASSERT ((token::TYPE_ID <= tok && tok <= token::ERROR));
      }
    };

    /// Build a parser object.
    Parser (VSOP::Driver &driver_yyarg);
    virtual ~Parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    Parser (const Parser&) = delete;
    /// Non copyable.
    Parser& operator= (const Parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYEOF (location_type l)
      {
        return symbol_type (token::YYEOF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYEOF (const location_type& l)
      {
        return symbol_type (token::YYEOF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror (location_type l)
      {
        return symbol_type (token::YYerror, std::move (l));
      }
#else
      static
      symbol_type
      make_YYerror (const location_type& l)
      {
        return symbol_type (token::YYerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF (location_type l)
      {
        return symbol_type (token::YYUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYUNDEF (const location_type& l)
      {
        return symbol_type (token::YYUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LBRACE (location_type l)
      {
        return symbol_type (token::LBRACE, std::move (l));
      }
#else
      static
      symbol_type
      make_LBRACE (const location_type& l)
      {
        return symbol_type (token::LBRACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RBRACE (location_type l)
      {
        return symbol_type (token::RBRACE, std::move (l));
      }
#else
      static
      symbol_type
      make_RBRACE (const location_type& l)
      {
        return symbol_type (token::RBRACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LPAR (location_type l)
      {
        return symbol_type (token::LPAR, std::move (l));
      }
#else
      static
      symbol_type
      make_LPAR (const location_type& l)
      {
        return symbol_type (token::LPAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RPAR (location_type l)
      {
        return symbol_type (token::RPAR, std::move (l));
      }
#else
      static
      symbol_type
      make_RPAR (const location_type& l)
      {
        return symbol_type (token::RPAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COLON (location_type l)
      {
        return symbol_type (token::COLON, std::move (l));
      }
#else
      static
      symbol_type
      make_COLON (const location_type& l)
      {
        return symbol_type (token::COLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEMICOLON (location_type l)
      {
        return symbol_type (token::SEMICOLON, std::move (l));
      }
#else
      static
      symbol_type
      make_SEMICOLON (const location_type& l)
      {
        return symbol_type (token::SEMICOLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA (location_type l)
      {
        return symbol_type (token::COMMA, std::move (l));
      }
#else
      static
      symbol_type
      make_COMMA (const location_type& l)
      {
        return symbol_type (token::COMMA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PLUS (location_type l)
      {
        return symbol_type (token::PLUS, std::move (l));
      }
#else
      static
      symbol_type
      make_PLUS (const location_type& l)
      {
        return symbol_type (token::PLUS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MINUS (location_type l)
      {
        return symbol_type (token::MINUS, std::move (l));
      }
#else
      static
      symbol_type
      make_MINUS (const location_type& l)
      {
        return symbol_type (token::MINUS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TIMES (location_type l)
      {
        return symbol_type (token::TIMES, std::move (l));
      }
#else
      static
      symbol_type
      make_TIMES (const location_type& l)
      {
        return symbol_type (token::TIMES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DIV (location_type l)
      {
        return symbol_type (token::DIV, std::move (l));
      }
#else
      static
      symbol_type
      make_DIV (const location_type& l)
      {
        return symbol_type (token::DIV, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_POW (location_type l)
      {
        return symbol_type (token::POW, std::move (l));
      }
#else
      static
      symbol_type
      make_POW (const location_type& l)
      {
        return symbol_type (token::POW, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOT (location_type l)
      {
        return symbol_type (token::DOT, std::move (l));
      }
#else
      static
      symbol_type
      make_DOT (const location_type& l)
      {
        return symbol_type (token::DOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQUAL (location_type l)
      {
        return symbol_type (token::EQUAL, std::move (l));
      }
#else
      static
      symbol_type
      make_EQUAL (const location_type& l)
      {
        return symbol_type (token::EQUAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LOWER (location_type l)
      {
        return symbol_type (token::LOWER, std::move (l));
      }
#else
      static
      symbol_type
      make_LOWER (const location_type& l)
      {
        return symbol_type (token::LOWER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LOWER_EQUAL (location_type l)
      {
        return symbol_type (token::LOWER_EQUAL, std::move (l));
      }
#else
      static
      symbol_type
      make_LOWER_EQUAL (const location_type& l)
      {
        return symbol_type (token::LOWER_EQUAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN (location_type l)
      {
        return symbol_type (token::ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_ASSIGN (const location_type& l)
      {
        return symbol_type (token::ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AND (location_type l)
      {
        return symbol_type (token::AND, std::move (l));
      }
#else
      static
      symbol_type
      make_AND (const location_type& l)
      {
        return symbol_type (token::AND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BOOL (location_type l)
      {
        return symbol_type (token::BOOL, std::move (l));
      }
#else
      static
      symbol_type
      make_BOOL (const location_type& l)
      {
        return symbol_type (token::BOOL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CLASS (location_type l)
      {
        return symbol_type (token::CLASS, std::move (l));
      }
#else
      static
      symbol_type
      make_CLASS (const location_type& l)
      {
        return symbol_type (token::CLASS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DO (location_type l)
      {
        return symbol_type (token::DO, std::move (l));
      }
#else
      static
      symbol_type
      make_DO (const location_type& l)
      {
        return symbol_type (token::DO, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSE (location_type l)
      {
        return symbol_type (token::ELSE, std::move (l));
      }
#else
      static
      symbol_type
      make_ELSE (const location_type& l)
      {
        return symbol_type (token::ELSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXTENDS (location_type l)
      {
        return symbol_type (token::EXTENDS, std::move (l));
      }
#else
      static
      symbol_type
      make_EXTENDS (const location_type& l)
      {
        return symbol_type (token::EXTENDS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FALSE (location_type l)
      {
        return symbol_type (token::FALSE, std::move (l));
      }
#else
      static
      symbol_type
      make_FALSE (const location_type& l)
      {
        return symbol_type (token::FALSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IF (location_type l)
      {
        return symbol_type (token::IF, std::move (l));
      }
#else
      static
      symbol_type
      make_IF (const location_type& l)
      {
        return symbol_type (token::IF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IN (location_type l)
      {
        return symbol_type (token::IN, std::move (l));
      }
#else
      static
      symbol_type
      make_IN (const location_type& l)
      {
        return symbol_type (token::IN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INT32 (location_type l)
      {
        return symbol_type (token::INT32, std::move (l));
      }
#else
      static
      symbol_type
      make_INT32 (const location_type& l)
      {
        return symbol_type (token::INT32, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ISNULL (location_type l)
      {
        return symbol_type (token::ISNULL, std::move (l));
      }
#else
      static
      symbol_type
      make_ISNULL (const location_type& l)
      {
        return symbol_type (token::ISNULL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LET (location_type l)
      {
        return symbol_type (token::LET, std::move (l));
      }
#else
      static
      symbol_type
      make_LET (const location_type& l)
      {
        return symbol_type (token::LET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NEW (location_type l)
      {
        return symbol_type (token::NEW, std::move (l));
      }
#else
      static
      symbol_type
      make_NEW (const location_type& l)
      {
        return symbol_type (token::NEW, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NOT (location_type l)
      {
        return symbol_type (token::NOT, std::move (l));
      }
#else
      static
      symbol_type
      make_NOT (const location_type& l)
      {
        return symbol_type (token::NOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SELF (location_type l)
      {
        return symbol_type (token::SELF, std::move (l));
      }
#else
      static
      symbol_type
      make_SELF (const location_type& l)
      {
        return symbol_type (token::SELF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRING (location_type l)
      {
        return symbol_type (token::STRING, std::move (l));
      }
#else
      static
      symbol_type
      make_STRING (const location_type& l)
      {
        return symbol_type (token::STRING, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_THEN (location_type l)
      {
        return symbol_type (token::THEN, std::move (l));
      }
#else
      static
      symbol_type
      make_THEN (const location_type& l)
      {
        return symbol_type (token::THEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TRUE (location_type l)
      {
        return symbol_type (token::TRUE, std::move (l));
      }
#else
      static
      symbol_type
      make_TRUE (const location_type& l)
      {
        return symbol_type (token::TRUE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNIT (location_type l)
      {
        return symbol_type (token::UNIT, std::move (l));
      }
#else
      static
      symbol_type
      make_UNIT (const location_type& l)
      {
        return symbol_type (token::UNIT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHILE (location_type l)
      {
        return symbol_type (token::WHILE, std::move (l));
      }
#else
      static
      symbol_type
      make_WHILE (const location_type& l)
      {
        return symbol_type (token::WHILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TYPE_ID (std::string v, location_type l)
      {
        return symbol_type (token::TYPE_ID, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TYPE_ID (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TYPE_ID, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OBJECT_ID (std::string v, location_type l)
      {
        return symbol_type (token::OBJECT_ID, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_OBJECT_ID (const std::string& v, const location_type& l)
      {
        return symbol_type (token::OBJECT_ID, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRING_LIT (std::string v, location_type l)
      {
        return symbol_type (token::STRING_LIT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_STRING_LIT (const std::string& v, const location_type& l)
      {
        return symbol_type (token::STRING_LIT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ERROR (std::string v, location_type l)
      {
        return symbol_type (token::ERROR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ERROR (const std::string& v, const location_type& l)
      {
        return symbol_type (token::ERROR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTEGER_LIT (int v, location_type l)
      {
        return symbol_type (token::INTEGER_LIT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_INTEGER_LIT (const int& v, const location_type& l)
      {
        return symbol_type (token::INTEGER_LIT, v, l);
      }
#endif


    class context
    {
    public:
      context (const Parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const Parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    Parser (const Parser&);
    /// Non copyable.
    Parser& operator= (const Parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef signed char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static symbol_kind_type yytranslate_ (int t);

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const signed char yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const signed char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const signed char yytable_[];

    static const signed char yycheck_[];

    // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    // symbol of state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
    static const signed char yyr1_[];

    // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yylast_ = 230,     ///< Last index in yytable_.
      yynnts_ = 24,  ///< Number of nonterminal symbols.
      yyfinal_ = 6 ///< Termination state number.
    };


    // User arguments.
    VSOP::Driver &driver;

  };

  inline
  Parser::symbol_kind_type
  Parser::yytranslate_ (int t)
  {
    return static_cast<symbol_kind_type> (t);
  }

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_48_single_class: // single-class
        value.copy< ClassAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_members: // members
        value.copy< ClassBody > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_57_single_expr: // single-expr
      case symbol_kind::S_conditional: // conditional
      case symbol_kind::S_loop: // loop
      case symbol_kind::S_62_variable_binding: // variable-binding
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_64_unary_op: // unary-op
      case symbol_kind::S_65_binary_op: // binary-op
      case symbol_kind::S_66_method_call: // method-call
      case symbol_kind::S_67_object_creation: // object-creation
        value.copy< ExprAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_55_code_block: // code-block
        value.copy< ExprBlockAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_constant: // constant
        value.copy< ExprLiteralAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_50_field_decl: // field-decl
        value.copy< FieldAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_54_single_param: // single-param
        value.copy< FormalAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_51_method_decl: // method-decl
        value.copy< MethodAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTEGER_LIT: // "integer-literal"
        value.copy< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TYPE_ID: // "type-identifier"
      case symbol_kind::S_OBJECT_ID: // "object-identifier"
      case symbol_kind::S_STRING_LIT: // "string-literal"
      case symbol_kind::S_ERROR: // "error"
      case symbol_kind::S_52_type_spec: // type-spec
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_47_class_list: // class-list
        value.copy< std::vector<ClassAst*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_56_expr_sequence: // expr-sequence
      case symbol_kind::S_58_arg_list_opt: // arg-list-opt
      case symbol_kind::S_59_arg_list: // arg-list
        value.copy< std::vector<ExprAst*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_53_param_list: // param-list
        value.copy< std::vector<FormalAst*> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_48_single_class: // single-class
        value.move< ClassAst* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_members: // members
        value.move< ClassBody > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_57_single_expr: // single-expr
      case symbol_kind::S_conditional: // conditional
      case symbol_kind::S_loop: // loop
      case symbol_kind::S_62_variable_binding: // variable-binding
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_64_unary_op: // unary-op
      case symbol_kind::S_65_binary_op: // binary-op
      case symbol_kind::S_66_method_call: // method-call
      case symbol_kind::S_67_object_creation: // object-creation
        value.move< ExprAst* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_55_code_block: // code-block
        value.move< ExprBlockAst* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_constant: // constant
        value.move< ExprLiteralAst* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_50_field_decl: // field-decl
        value.move< FieldAst* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_54_single_param: // single-param
        value.move< FormalAst* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_51_method_decl: // method-decl
        value.move< MethodAst* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_INTEGER_LIT: // "integer-literal"
        value.move< int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TYPE_ID: // "type-identifier"
      case symbol_kind::S_OBJECT_ID: // "object-identifier"
      case symbol_kind::S_STRING_LIT: // "string-literal"
      case symbol_kind::S_ERROR: // "error"
      case symbol_kind::S_52_type_spec: // type-spec
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_47_class_list: // class-list
        value.move< std::vector<ClassAst*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_56_expr_sequence: // expr-sequence
      case symbol_kind::S_58_arg_list_opt: // arg-list-opt
      case symbol_kind::S_59_arg_list: // arg-list
        value.move< std::vector<ExprAst*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_53_param_list: // param-list
        value.move< std::vector<FormalAst*> > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  inline
  Parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  Parser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  Parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  inline
  Parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  inline
  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

#line 19 "parser.y"
} // VSOP
#line 2463 "parser.hpp"




#endif // !YY_YY_PARSER_HPP_INCLUDED
