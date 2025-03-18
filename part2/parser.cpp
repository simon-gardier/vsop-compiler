// A Bison parser, made by GNU Bison 3.7.5.

// Skeleton implementation for Bison LALR(1) parsers in C++

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.hpp"


// Unqualified %code blocks.
#line 55 "parser.y"

    #include "driver.hpp"

    using namespace std;

#line 52 "parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 19 "parser.y"
namespace VSOP {
#line 145 "parser.cpp"

  /// Build a parser object.
  Parser::Parser (VSOP::Driver &driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_class: // class
        value.YY_MOVE_OR_COPY< ClassAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_49_class_body: // class-body
        value.YY_MOVE_OR_COPY< ClassBody > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_if: // if
      case symbol_kind::S_while: // while
      case symbol_kind::S_let: // let
      case symbol_kind::S_63_object_assign: // object-assign
      case symbol_kind::S_unop: // unop
      case symbol_kind::S_binop: // binop
      case symbol_kind::S_call: // call
      case symbol_kind::S_new: // new
        value.YY_MOVE_OR_COPY< ExprAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.YY_MOVE_OR_COPY< ExprBlockAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_literal: // literal
        value.YY_MOVE_OR_COPY< ExprLiteralAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field: // field
        value.YY_MOVE_OR_COPY< FieldAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formal: // formal
        value.YY_MOVE_OR_COPY< FormalAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_method: // method
        value.YY_MOVE_OR_COPY< MethodAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTEGER_LIT: // "integer-literal"
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TYPE_ID: // "type-identifier"
      case symbol_kind::S_OBJECT_ID: // "object-identifier"
      case symbol_kind::S_STRING_LIT: // "string-literal"
      case symbol_kind::S_ERROR: // "error"
      case symbol_kind::S_type: // type
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_classes: // classes
        value.YY_MOVE_OR_COPY< std::vector<ClassAst*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_exprs: // exprs
      case symbol_kind::S_58_args_optional: // args-optional
      case symbol_kind::S_args: // args
        value.YY_MOVE_OR_COPY< std::vector<ExprAst*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formals: // formals
        value.YY_MOVE_OR_COPY< std::vector<FormalAst*> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_class: // class
        value.move< ClassAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_49_class_body: // class-body
        value.move< ClassBody > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_if: // if
      case symbol_kind::S_while: // while
      case symbol_kind::S_let: // let
      case symbol_kind::S_63_object_assign: // object-assign
      case symbol_kind::S_unop: // unop
      case symbol_kind::S_binop: // binop
      case symbol_kind::S_call: // call
      case symbol_kind::S_new: // new
        value.move< ExprAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.move< ExprBlockAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_literal: // literal
        value.move< ExprLiteralAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field: // field
        value.move< FieldAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formal: // formal
        value.move< FormalAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_method: // method
        value.move< MethodAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTEGER_LIT: // "integer-literal"
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TYPE_ID: // "type-identifier"
      case symbol_kind::S_OBJECT_ID: // "object-identifier"
      case symbol_kind::S_STRING_LIT: // "string-literal"
      case symbol_kind::S_ERROR: // "error"
      case symbol_kind::S_type: // type
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_classes: // classes
        value.move< std::vector<ClassAst*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_exprs: // exprs
      case symbol_kind::S_58_args_optional: // args-optional
      case symbol_kind::S_args: // args
        value.move< std::vector<ExprAst*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formals: // formals
        value.move< std::vector<FormalAst*> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_class: // class
        value.copy< ClassAst* > (that.value);
        break;

      case symbol_kind::S_49_class_body: // class-body
        value.copy< ClassBody > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_if: // if
      case symbol_kind::S_while: // while
      case symbol_kind::S_let: // let
      case symbol_kind::S_63_object_assign: // object-assign
      case symbol_kind::S_unop: // unop
      case symbol_kind::S_binop: // binop
      case symbol_kind::S_call: // call
      case symbol_kind::S_new: // new
        value.copy< ExprAst* > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.copy< ExprBlockAst* > (that.value);
        break;

      case symbol_kind::S_literal: // literal
        value.copy< ExprLiteralAst* > (that.value);
        break;

      case symbol_kind::S_field: // field
        value.copy< FieldAst* > (that.value);
        break;

      case symbol_kind::S_formal: // formal
        value.copy< FormalAst* > (that.value);
        break;

      case symbol_kind::S_method: // method
        value.copy< MethodAst* > (that.value);
        break;

      case symbol_kind::S_INTEGER_LIT: // "integer-literal"
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_TYPE_ID: // "type-identifier"
      case symbol_kind::S_OBJECT_ID: // "object-identifier"
      case symbol_kind::S_STRING_LIT: // "string-literal"
      case symbol_kind::S_ERROR: // "error"
      case symbol_kind::S_type: // type
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_classes: // classes
        value.copy< std::vector<ClassAst*> > (that.value);
        break;

      case symbol_kind::S_exprs: // exprs
      case symbol_kind::S_58_args_optional: // args-optional
      case symbol_kind::S_args: // args
        value.copy< std::vector<ExprAst*> > (that.value);
        break;

      case symbol_kind::S_formals: // formals
        value.copy< std::vector<FormalAst*> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_class: // class
        value.move< ClassAst* > (that.value);
        break;

      case symbol_kind::S_49_class_body: // class-body
        value.move< ClassBody > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_if: // if
      case symbol_kind::S_while: // while
      case symbol_kind::S_let: // let
      case symbol_kind::S_63_object_assign: // object-assign
      case symbol_kind::S_unop: // unop
      case symbol_kind::S_binop: // binop
      case symbol_kind::S_call: // call
      case symbol_kind::S_new: // new
        value.move< ExprAst* > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.move< ExprBlockAst* > (that.value);
        break;

      case symbol_kind::S_literal: // literal
        value.move< ExprLiteralAst* > (that.value);
        break;

      case symbol_kind::S_field: // field
        value.move< FieldAst* > (that.value);
        break;

      case symbol_kind::S_formal: // formal
        value.move< FormalAst* > (that.value);
        break;

      case symbol_kind::S_method: // method
        value.move< MethodAst* > (that.value);
        break;

      case symbol_kind::S_INTEGER_LIT: // "integer-literal"
        value.move< int > (that.value);
        break;

      case symbol_kind::S_TYPE_ID: // "type-identifier"
      case symbol_kind::S_OBJECT_ID: // "object-identifier"
      case symbol_kind::S_STRING_LIT: // "string-literal"
      case symbol_kind::S_ERROR: // "error"
      case symbol_kind::S_type: // type
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_classes: // classes
        value.move< std::vector<ClassAst*> > (that.value);
        break;

      case symbol_kind::S_exprs: // exprs
      case symbol_kind::S_58_args_optional: // args-optional
      case symbol_kind::S_args: // args
        value.move< std::vector<ExprAst*> > (that.value);
        break;

      case symbol_kind::S_formals: // formals
        value.move< std::vector<FormalAst*> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_class: // class
        yylhs.value.emplace< ClassAst* > ();
        break;

      case symbol_kind::S_49_class_body: // class-body
        yylhs.value.emplace< ClassBody > ();
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_if: // if
      case symbol_kind::S_while: // while
      case symbol_kind::S_let: // let
      case symbol_kind::S_63_object_assign: // object-assign
      case symbol_kind::S_unop: // unop
      case symbol_kind::S_binop: // binop
      case symbol_kind::S_call: // call
      case symbol_kind::S_new: // new
        yylhs.value.emplace< ExprAst* > ();
        break;

      case symbol_kind::S_block: // block
        yylhs.value.emplace< ExprBlockAst* > ();
        break;

      case symbol_kind::S_literal: // literal
        yylhs.value.emplace< ExprLiteralAst* > ();
        break;

      case symbol_kind::S_field: // field
        yylhs.value.emplace< FieldAst* > ();
        break;

      case symbol_kind::S_formal: // formal
        yylhs.value.emplace< FormalAst* > ();
        break;

      case symbol_kind::S_method: // method
        yylhs.value.emplace< MethodAst* > ();
        break;

      case symbol_kind::S_INTEGER_LIT: // "integer-literal"
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_TYPE_ID: // "type-identifier"
      case symbol_kind::S_OBJECT_ID: // "object-identifier"
      case symbol_kind::S_STRING_LIT: // "string-literal"
      case symbol_kind::S_ERROR: // "error"
      case symbol_kind::S_type: // type
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_classes: // classes
        yylhs.value.emplace< std::vector<ClassAst*> > ();
        break;

      case symbol_kind::S_exprs: // exprs
      case symbol_kind::S_58_args_optional: // args-optional
      case symbol_kind::S_args: // args
        yylhs.value.emplace< std::vector<ExprAst*> > ();
        break;

      case symbol_kind::S_formals: // formals
        yylhs.value.emplace< std::vector<FormalAst*> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: classes
#line 148 "parser.y"
            { driver.programAst = std::make_unique<ProgramAst>(yystack_[0].location.begin.line, yystack_[0].location.begin.column, yystack_[0].value.as < std::vector<ClassAst*> > ()); }
#line 869 "parser.cpp"
    break;

  case 3: // classes: class
#line 151 "parser.y"
                    { yylhs.value.as < std::vector<ClassAst*> > ().push_back(yystack_[0].value.as < ClassAst* > ()); }
#line 875 "parser.cpp"
    break;

  case 4: // classes: classes class
#line 152 "parser.y"
                    { yystack_[1].value.as < std::vector<ClassAst*> > ().push_back(yystack_[0].value.as < ClassAst* > ()); yylhs.value.as < std::vector<ClassAst*> > () = yystack_[1].value.as < std::vector<ClassAst*> > (); }
#line 881 "parser.cpp"
    break;

  case 5: // class: "class" "type-identifier" "{" class-body "}"
#line 155 "parser.y"
                                           { yylhs.value.as < ClassAst* > () = new ClassAst(yystack_[4].location.begin.line, yystack_[4].location.begin.column, yystack_[3].value.as < std::string > (), "Object", yystack_[1].value.as < ClassBody > ().fields, yystack_[1].value.as < ClassBody > ().methods); }
#line 887 "parser.cpp"
    break;

  case 6: // class: "class" "type-identifier" "extends" "type-identifier" "{" class-body "}"
#line 156 "parser.y"
                                                             { yylhs.value.as < ClassAst* > () = new ClassAst(yystack_[6].location.begin.line, yystack_[6].location.begin.column, yystack_[5].value.as < std::string > (), yystack_[3].value.as < std::string > (), yystack_[1].value.as < ClassBody > ().fields, yystack_[1].value.as < ClassBody > ().methods); }
#line 893 "parser.cpp"
    break;

  case 7: // class-body: %empty
#line 159 "parser.y"
                        {}
#line 899 "parser.cpp"
    break;

  case 8: // class-body: class-body field
#line 160 "parser.y"
                        { yystack_[1].value.as < ClassBody > ().fields.push_back(yystack_[0].value.as < FieldAst* > ()); yylhs.value.as < ClassBody > () = yystack_[1].value.as < ClassBody > (); }
#line 905 "parser.cpp"
    break;

  case 9: // class-body: class-body method
#line 161 "parser.y"
                        { yystack_[1].value.as < ClassBody > ().methods.push_back(yystack_[0].value.as < MethodAst* > ()); yylhs.value.as < ClassBody > () = yystack_[1].value.as < ClassBody > (); }
#line 911 "parser.cpp"
    break;

  case 10: // field: "object-identifier" ":" type ";"
#line 164 "parser.y"
                                   { yylhs.value.as < FieldAst* > () = new FieldAst(yystack_[3].location.begin.line, yystack_[3].location.begin.column, yystack_[3].value.as < std::string > (), yystack_[1].value.as < std::string > ()); }
#line 917 "parser.cpp"
    break;

  case 11: // field: "object-identifier" ":" type "<-" expr ";"
#line 165 "parser.y"
                                                 { yylhs.value.as < FieldAst* > () = new FieldAst(yystack_[5].location.begin.line, yystack_[5].location.begin.column, yystack_[5].value.as < std::string > (), yystack_[3].value.as < std::string > (), yystack_[1].value.as < ExprAst* > ()); }
#line 923 "parser.cpp"
    break;

  case 12: // method: "object-identifier" "(" formals ")" ":" type block
#line 168 "parser.y"
                                                 { yylhs.value.as < MethodAst* > () = new MethodAst(yystack_[6].location.begin.line, yystack_[6].location.begin.column, yystack_[6].value.as < std::string > (), yystack_[4].value.as < std::vector<FormalAst*> > (), yystack_[1].value.as < std::string > (), yystack_[0].value.as < ExprBlockAst* > ()); }
#line 929 "parser.cpp"
    break;

  case 13: // type: "int32"
#line 171 "parser.y"
               { yylhs.value.as < std::string > () = "int32"; }
#line 935 "parser.cpp"
    break;

  case 14: // type: "bool"
#line 172 "parser.y"
               { yylhs.value.as < std::string > () = "bool"; }
#line 941 "parser.cpp"
    break;

  case 15: // type: "string"
#line 173 "parser.y"
               { yylhs.value.as < std::string > () = "string"; }
#line 947 "parser.cpp"
    break;

  case 16: // type: "unit"
#line 174 "parser.y"
               { yylhs.value.as < std::string > () = "unit"; }
#line 953 "parser.cpp"
    break;

  case 17: // type: "type-identifier"
#line 175 "parser.y"
               { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 959 "parser.cpp"
    break;

  case 18: // formals: %empty
#line 178 "parser.y"
                           {}
#line 965 "parser.cpp"
    break;

  case 19: // formals: formal
#line 179 "parser.y"
                           { yylhs.value.as < std::vector<FormalAst*> > ().push_back(yystack_[0].value.as < FormalAst* > ()); }
#line 971 "parser.cpp"
    break;

  case 20: // formals: formals "," formal
#line 180 "parser.y"
                           { yystack_[2].value.as < std::vector<FormalAst*> > ().push_back(yystack_[0].value.as < FormalAst* > ()); yylhs.value.as < std::vector<FormalAst*> > () = yystack_[2].value.as < std::vector<FormalAst*> > (); }
#line 977 "parser.cpp"
    break;

  case 21: // formal: "object-identifier" ":" type
#line 183 "parser.y"
                         { yylhs.value.as < FormalAst* > () = new FormalAst(yystack_[2].location.begin.line, yystack_[2].location.begin.column, yystack_[2].value.as < std::string > (), yystack_[0].value.as < std::string > ()); }
#line 983 "parser.cpp"
    break;

  case 22: // block: "{" exprs "}"
#line 186 "parser.y"
                        { yylhs.value.as < ExprBlockAst* > () = new ExprBlockAst(yystack_[2].location.begin.line, yystack_[2].location.begin.column, yystack_[1].value.as < std::vector<ExprAst*> > ()); }
#line 989 "parser.cpp"
    break;

  case 23: // exprs: expr
#line 189 "parser.y"
                           { yylhs.value.as < std::vector<ExprAst*> > ().push_back(yystack_[0].value.as < ExprAst* > ()); }
#line 995 "parser.cpp"
    break;

  case 24: // exprs: exprs ";" expr
#line 190 "parser.y"
                           { yystack_[2].value.as < std::vector<ExprAst*> > ().push_back(yystack_[0].value.as < ExprAst* > ()); yylhs.value.as < std::vector<ExprAst*> > () = yystack_[2].value.as < std::vector<ExprAst*> > (); }
#line 1001 "parser.cpp"
    break;

  case 25: // expr: if
#line 193 "parser.y"
    { yylhs.value.as < ExprAst* > () = yystack_[0].value.as < ExprAst* > (); }
#line 1007 "parser.cpp"
    break;

  case 26: // expr: while
#line 194 "parser.y"
      { yylhs.value.as < ExprAst* > () = yystack_[0].value.as < ExprAst* > (); }
#line 1013 "parser.cpp"
    break;

  case 27: // expr: let
#line 195 "parser.y"
      { yylhs.value.as < ExprAst* > () = yystack_[0].value.as < ExprAst* > (); }
#line 1019 "parser.cpp"
    break;

  case 28: // expr: object-assign
#line 196 "parser.y"
      { yylhs.value.as < ExprAst* > () = yystack_[0].value.as < ExprAst* > (); }
#line 1025 "parser.cpp"
    break;

  case 29: // expr: unop
#line 197 "parser.y"
      { yylhs.value.as < ExprAst* > () = yystack_[0].value.as < ExprAst* > (); }
#line 1031 "parser.cpp"
    break;

  case 30: // expr: binop
#line 198 "parser.y"
      { yylhs.value.as < ExprAst* > () = yystack_[0].value.as < ExprAst* > (); }
#line 1037 "parser.cpp"
    break;

  case 31: // expr: call
#line 199 "parser.y"
      { yylhs.value.as < ExprAst* > () = yystack_[0].value.as < ExprAst* > (); }
#line 1043 "parser.cpp"
    break;

  case 32: // expr: new
#line 200 "parser.y"
                        { yylhs.value.as < ExprAst* > () = yystack_[0].value.as < ExprAst* > (); }
#line 1049 "parser.cpp"
    break;

  case 33: // expr: "self"
#line 203 "parser.y"
                        { yylhs.value.as < ExprAst* > () = new ExprObjectIdAst(yystack_[0].location.begin.line, yystack_[0].location.begin.column, "self"); }
#line 1055 "parser.cpp"
    break;

  case 34: // expr: "object-identifier"
#line 204 "parser.y"
                        { yylhs.value.as < ExprAst* > () = new ExprObjectIdAst(yystack_[0].location.begin.line, yystack_[0].location.begin.column, yystack_[0].value.as < std::string > ()); }
#line 1061 "parser.cpp"
    break;

  case 35: // expr: literal
#line 205 "parser.y"
                        { yylhs.value.as < ExprAst* > () = yystack_[0].value.as < ExprLiteralAst* > (); }
#line 1067 "parser.cpp"
    break;

  case 36: // expr: "(" ")"
#line 206 "parser.y"
                        { yylhs.value.as < ExprAst* > () = new ExprLiteralAst(yystack_[1].location.begin.line, yystack_[1].location.begin.column, "()", "unit"); }
#line 1073 "parser.cpp"
    break;

  case 37: // expr: "(" expr ")"
#line 207 "parser.y"
                        { yylhs.value.as < ExprAst* > () = yystack_[1].value.as < ExprAst* > (); }
#line 1079 "parser.cpp"
    break;

  case 38: // expr: block
#line 210 "parser.y"
                      { yylhs.value.as < ExprAst* > () = yystack_[0].value.as < ExprBlockAst* > (); }
#line 1085 "parser.cpp"
    break;

  case 39: // args-optional: %empty
#line 213 "parser.y"
           {}
#line 1091 "parser.cpp"
    break;

  case 40: // args-optional: args
#line 214 "parser.y"
           { yylhs.value.as < std::vector<ExprAst*> > () = yystack_[0].value.as < std::vector<ExprAst*> > (); }
#line 1097 "parser.cpp"
    break;

  case 41: // args: expr
#line 217 "parser.y"
                      { yylhs.value.as < std::vector<ExprAst*> > ().push_back(yystack_[0].value.as < ExprAst* > ()); }
#line 1103 "parser.cpp"
    break;

  case 42: // args: args "," expr
#line 218 "parser.y"
                      { yystack_[2].value.as < std::vector<ExprAst*> > ().push_back(yystack_[0].value.as < ExprAst* > ()); yylhs.value.as < std::vector<ExprAst*> > () = yystack_[2].value.as < std::vector<ExprAst*> > (); }
#line 1109 "parser.cpp"
    break;

  case 43: // if: "if" expr "then" expr
#line 221 "parser.y"
                      { yylhs.value.as < ExprAst* > () = new ExprIfAst(yystack_[3].location.begin.line, yystack_[3].location.begin.column, yystack_[2].value.as < ExprAst* > (), yystack_[0].value.as < ExprAst* > ()); }
#line 1115 "parser.cpp"
    break;

  case 44: // if: "if" expr "then" expr "else" expr
#line 222 "parser.y"
                                  { yylhs.value.as < ExprAst* > () = new ExprIfAst(yystack_[5].location.begin.line, yystack_[5].location.begin.column, yystack_[4].value.as < ExprAst* > (), yystack_[2].value.as < ExprAst* > (), yystack_[0].value.as < ExprAst* > ()); }
#line 1121 "parser.cpp"
    break;

  case 45: // while: "while" expr "do" expr
#line 225 "parser.y"
                       { yylhs.value.as < ExprAst* > () = new ExprWhileAst(yystack_[3].location.begin.line, yystack_[3].location.begin.column, yystack_[2].value.as < ExprAst* > (), yystack_[0].value.as < ExprAst* > ()); }
#line 1127 "parser.cpp"
    break;

  case 46: // let: "let" "object-identifier" ":" type "in" expr
#line 228 "parser.y"
                                     { yylhs.value.as < ExprAst* > () = new ExprLetAst(yystack_[5].location.begin.line, yystack_[5].location.begin.column, yystack_[4].value.as < std::string > (), yystack_[2].value.as < std::string > (), yystack_[0].value.as < ExprAst* > ()); }
#line 1133 "parser.cpp"
    break;

  case 47: // let: "let" "object-identifier" ":" type "<-" expr "in" expr
#line 229 "parser.y"
                                                   { yylhs.value.as < ExprAst* > () = new ExprLetAst(yystack_[7].location.begin.line, yystack_[7].location.begin.column, yystack_[6].value.as < std::string > (), yystack_[4].value.as < std::string > (), yystack_[2].value.as < ExprAst* > (), yystack_[0].value.as < ExprAst* > ()); }
#line 1139 "parser.cpp"
    break;

  case 48: // object-assign: "object-identifier" "<-" expr
#line 232 "parser.y"
                          { yylhs.value.as < ExprAst* > () = new ExprAssignAst(yystack_[2].location.begin.line, yystack_[2].location.begin.column, yystack_[2].value.as < std::string > (), yystack_[0].value.as < ExprAst* > ()); }
#line 1145 "parser.cpp"
    break;

  case 49: // unop: "not" expr
#line 235 "parser.y"
                  { yylhs.value.as < ExprAst* > () = new ExprUnopAst(yystack_[1].location.begin.line, yystack_[1].location.begin.column, "not", yystack_[0].value.as < ExprAst* > ()); }
#line 1151 "parser.cpp"
    break;

  case 50: // unop: "-" expr
#line 236 "parser.y"
                  { yylhs.value.as < ExprAst* > () = new ExprUnopAst(yystack_[1].location.begin.line, yystack_[1].location.begin.column, "-", yystack_[0].value.as < ExprAst* > ()); }
#line 1157 "parser.cpp"
    break;

  case 51: // unop: "isnull" expr
#line 237 "parser.y"
                  { yylhs.value.as < ExprAst* > () = new ExprUnopAst(yystack_[1].location.begin.line, yystack_[1].location.begin.column, "isnull", yystack_[0].value.as < ExprAst* > ()); }
#line 1163 "parser.cpp"
    break;

  case 52: // binop: expr "+" expr
#line 240 "parser.y"
                                              { yylhs.value.as < ExprAst* > () = new ExprBinopAst(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "+", yystack_[2].value.as < ExprAst* > (), yystack_[0].value.as < ExprAst* > ()); }
#line 1169 "parser.cpp"
    break;

  case 53: // binop: expr "=" expr
#line 241 "parser.y"
                                              { yylhs.value.as < ExprAst* > () = new ExprBinopAst(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "=", yystack_[2].value.as < ExprAst* > (), yystack_[0].value.as < ExprAst* > ()); }
#line 1175 "parser.cpp"
    break;

  case 54: // binop: expr "<" expr
#line 242 "parser.y"
                                              { yylhs.value.as < ExprAst* > () = new ExprBinopAst(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "<", yystack_[2].value.as < ExprAst* > (), yystack_[0].value.as < ExprAst* > ()); }
#line 1181 "parser.cpp"
    break;

  case 55: // binop: expr "<=" expr
#line 243 "parser.y"
                                              { yylhs.value.as < ExprAst* > () = new ExprBinopAst(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "<=", yystack_[2].value.as < ExprAst* > (), yystack_[0].value.as < ExprAst* > ()); }
#line 1187 "parser.cpp"
    break;

  case 56: // binop: expr "-" expr
#line 244 "parser.y"
                                              { yylhs.value.as < ExprAst* > () = new ExprBinopAst(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "-", yystack_[2].value.as < ExprAst* > (), yystack_[0].value.as < ExprAst* > ()); }
#line 1193 "parser.cpp"
    break;

  case 57: // binop: expr "*" expr
#line 245 "parser.y"
                                              { yylhs.value.as < ExprAst* > () = new ExprBinopAst(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "*", yystack_[2].value.as < ExprAst* > (), yystack_[0].value.as < ExprAst* > ()); }
#line 1199 "parser.cpp"
    break;

  case 58: // binop: expr "/" expr
#line 246 "parser.y"
                                              { yylhs.value.as < ExprAst* > () = new ExprBinopAst(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "/", yystack_[2].value.as < ExprAst* > (), yystack_[0].value.as < ExprAst* > ()); }
#line 1205 "parser.cpp"
    break;

  case 59: // binop: expr "^" expr
#line 247 "parser.y"
                                              { yylhs.value.as < ExprAst* > () = new ExprBinopAst(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "^", yystack_[2].value.as < ExprAst* > (), yystack_[0].value.as < ExprAst* > ()); }
#line 1211 "parser.cpp"
    break;

  case 60: // binop: expr "and" expr
#line 248 "parser.y"
                                              { yylhs.value.as < ExprAst* > () = new ExprBinopAst(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "and", yystack_[2].value.as < ExprAst* > (), yystack_[0].value.as < ExprAst* > ()); }
#line 1217 "parser.cpp"
    break;

  case 61: // call: "object-identifier" "(" args-optional ")"
#line 251 "parser.y"
                                                 { yylhs.value.as < ExprAst* > () = new ExprCallAst(yystack_[3].location.begin.line, yystack_[3].location.begin.column, new ExprObjectIdAst(yystack_[3].location.begin.line, yystack_[3].location.begin.column, "self"), yystack_[3].value.as < std::string > (), yystack_[1].value.as < std::vector<ExprAst*> > ()); }
#line 1223 "parser.cpp"
    break;

  case 62: // call: expr "." "object-identifier" "(" args-optional ")"
#line 252 "parser.y"
                                                 { yylhs.value.as < ExprAst* > () = new ExprCallAst(yystack_[5].location.begin.line, yystack_[5].location.begin.column, yystack_[5].value.as < ExprAst* > (), yystack_[3].value.as < std::string > (), yystack_[1].value.as < std::vector<ExprAst*> > ()); }
#line 1229 "parser.cpp"
    break;

  case 63: // new: "new" "type-identifier"
#line 255 "parser.y"
                { yylhs.value.as < ExprAst* > () = new ExprNewAst(yystack_[1].location.begin.line, yystack_[1].location.begin.column, yystack_[0].value.as < std::string > ()); }
#line 1235 "parser.cpp"
    break;

  case 64: // literal: "integer-literal"
#line 258 "parser.y"
                 { yylhs.value.as < ExprLiteralAst* > () = new ExprLiteralAst(yystack_[0].location.begin.line, yystack_[0].location.begin.column, std::to_string(yystack_[0].value.as < int > ()), "int32"); }
#line 1241 "parser.cpp"
    break;

  case 65: // literal: "string-literal"
#line 259 "parser.y"
                 { yylhs.value.as < ExprLiteralAst* > () = new ExprLiteralAst(yystack_[0].location.begin.line, yystack_[0].location.begin.column, yystack_[0].value.as < std::string > (), "string"); }
#line 1247 "parser.cpp"
    break;

  case 66: // literal: "true"
#line 260 "parser.y"
                 { yylhs.value.as < ExprLiteralAst* > () = new ExprLiteralAst(yystack_[0].location.begin.line, yystack_[0].location.begin.column, "true", "bool"); }
#line 1253 "parser.cpp"
    break;

  case 67: // literal: "false"
#line 261 "parser.y"
                 { yylhs.value.as < ExprLiteralAst* > () = new ExprLiteralAst(yystack_[0].location.begin.line, yystack_[0].location.begin.column, "false", "bool"); }
#line 1259 "parser.cpp"
    break;


#line 1263 "parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }



  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -35;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
      12,    -5,    38,    12,   -35,     7,   -35,   -35,   -35,     1,
      -2,    41,   -35,    53,   -35,   -35,   -35,    14,    35,    -1,
      43,     5,   -35,   -35,   -35,   -35,   -35,   -35,    17,   -35,
      35,    55,    14,   -35,    98,   -35,    35,   -35,    98,    63,
      98,   -35,    98,    98,    22,    27,    98,   -35,   -35,    98,
       8,   -35,   -35,   -35,   181,   -35,   -35,   -35,   -35,   -35,
     -35,   -35,   -35,   -35,    68,    25,   192,   -35,   100,    64,
       6,    16,    65,   -35,   203,   167,    98,    98,   -35,    98,
      98,    98,    98,    98,    39,    98,    98,    98,    98,   -35,
     -35,    98,   -35,    98,    35,    98,   192,    76,    77,   192,
      64,    64,    16,    16,    16,    82,   212,   212,   212,   203,
     192,   152,     9,   192,   -35,    98,    98,    98,    98,    98,
     192,    85,   192,   133,   192,   -35,    98,   192
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     0,     0,     2,     3,     0,     1,     4,     7,     0,
       0,     0,     5,     0,     8,     9,     7,    18,     0,     0,
       0,     0,    19,    14,    13,    15,    16,    17,     0,     6,
       0,     0,     0,    10,     0,    21,     0,    20,     0,     0,
       0,    67,     0,     0,     0,     0,     0,    33,    66,     0,
      34,    65,    64,    38,     0,    25,    26,    27,    28,    29,
      30,    31,    32,    35,     0,     0,    23,    36,     0,    50,
       0,    51,     0,    63,    49,     0,    39,     0,    11,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    12,
      22,     0,    37,     0,     0,     0,    41,     0,    40,    48,
      52,    56,    57,    58,    59,     0,    53,    54,    55,    60,
      24,    43,     0,    45,    61,     0,    39,     0,     0,     0,
      42,     0,    44,     0,    46,    62,     0,    47
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -35,   -35,   -35,    95,    72,   -35,   -35,   -29,   -35,    67,
      44,   -35,   -34,     3,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,   -35,   -35,   -35
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     2,     3,     4,    10,    14,    15,    28,    21,    22,
      53,    65,    96,    97,    98,    55,    56,    57,    58,    59,
      60,    61,    62,    63
  };

  const signed char
  Parser::yytable_[] =
  {
      54,    35,    12,    29,    66,    68,    69,    64,    70,    71,
       8,    31,    74,    76,    32,    75,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    33,    88,    77,   118,    90,
      83,    84,     9,    91,     1,     5,    34,   119,     6,    13,
      13,    11,    93,    99,    16,   100,   101,   102,   103,   104,
      30,   106,   107,   108,   109,    20,    23,   110,    17,   111,
      18,   113,    36,    72,    24,   112,    38,    73,    39,    67,
      25,    38,    94,    26,    40,    27,    81,    82,    83,    84,
     105,   120,   114,   122,   123,   124,   115,   116,    19,    41,
      42,   125,   127,    43,    44,    45,    46,    47,     7,    37,
      48,    38,    49,    39,    50,    51,    92,    52,    89,    40,
      79,    80,    81,    82,    83,    84,    85,    86,    87,   121,
      88,     0,     0,     0,    41,    42,     0,     0,    43,    44,
      45,    46,    47,     0,     0,    48,     0,    49,     0,    50,
      51,     0,    52,    79,    80,    81,    82,    83,    84,    85,
      86,    87,     0,    88,     0,     0,     0,     0,     0,     0,
       0,   126,    79,    80,    81,    82,    83,    84,    85,    86,
      87,     0,    88,     0,     0,     0,   117,    79,    80,    81,
      82,    83,    84,    85,    86,    87,     0,    88,     0,    78,
      95,    79,    80,    81,    82,    83,    84,    85,    86,    87,
       0,    88,    79,    80,    81,    82,    83,    84,    85,    86,
      87,     0,    88,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    79,    80,    81,    82,    83,    84,    -1,    -1,
      -1
  };

  const signed char
  Parser::yycheck_[] =
  {
      34,    30,     4,     4,    38,    39,    40,    36,    42,    43,
       3,     6,    46,     5,     9,    49,    10,    11,    12,    13,
      14,    15,    16,    17,    18,     8,    20,    19,    19,     4,
      14,    15,    25,     8,    22,    40,    19,    28,     0,    41,
      41,    40,    36,    77,     3,    79,    80,    81,    82,    83,
       7,    85,    86,    87,    88,    41,    21,    91,     5,    93,
       7,    95,     7,    41,    29,    94,     3,    40,     5,     6,
      35,     3,     7,    38,    11,    40,    12,    13,    14,    15,
      41,   115,     6,   117,   118,   119,     9,     5,    16,    26,
      27,     6,   126,    30,    31,    32,    33,    34,     3,    32,
      37,     3,    39,     5,    41,    42,     6,    44,    64,    11,
      10,    11,    12,    13,    14,    15,    16,    17,    18,   116,
      20,    -1,    -1,    -1,    26,    27,    -1,    -1,    30,    31,
      32,    33,    34,    -1,    -1,    37,    -1,    39,    -1,    41,
      42,    -1,    44,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    -1,    20,    -1,    -1,    -1,    24,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    -1,    20,    -1,     8,
      23,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      -1,    20,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    -1,    20,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    10,    11,    12,    13,    14,    15,    16,    17,
      18
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    22,    46,    47,    48,    40,     0,    48,     3,    25,
      49,    40,     4,    41,    50,    51,     3,     5,     7,    49,
      41,    53,    54,    21,    29,    35,    38,    40,    52,     4,
       7,     6,     9,     8,    19,    52,     7,    54,     3,     5,
      11,    26,    27,    30,    31,    32,    33,    34,    37,    39,
      41,    42,    44,    55,    57,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    52,    56,    57,     6,    57,    57,
      57,    57,    41,    40,    57,    57,     5,    19,     8,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    20,    55,
       4,     8,     6,    36,     7,    23,    57,    58,    59,    57,
      57,    57,    57,    57,    57,    41,    57,    57,    57,    57,
      57,    57,    52,    57,     6,     9,     5,    24,    19,    28,
      57,    58,    57,    57,    57,     6,    28,    57
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    45,    46,    47,    47,    48,    48,    49,    49,    49,
      50,    50,    51,    52,    52,    52,    52,    52,    53,    53,
      53,    54,    55,    56,    56,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    58,
      58,    59,    59,    60,    60,    61,    62,    62,    63,    64,
      64,    64,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    66,    66,    67,    68,    68,    68,    68
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     5,     7,     0,     2,     2,
       4,     6,     7,     1,     1,     1,     1,     1,     0,     1,
       3,     3,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     1,     0,
       1,     1,     3,     4,     6,     4,     6,     8,     3,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     4,     6,     2,     1,     1,     1,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"{\"", "\"}\"",
  "\"(\"", "\")\"", "\":\"", "\";\"", "\",\"", "\"+\"", "\"-\"", "\"*\"",
  "\"/\"", "\"^\"", "\".\"", "\"=\"", "\"<\"", "\"<=\"", "\"<-\"",
  "\"and\"", "\"bool\"", "\"class\"", "\"do\"", "\"else\"", "\"extends\"",
  "\"false\"", "\"if\"", "\"in\"", "\"int32\"", "\"isnull\"", "\"let\"",
  "\"new\"", "\"not\"", "\"self\"", "\"string\"", "\"then\"", "\"true\"",
  "\"unit\"", "\"while\"", "\"type-identifier\"", "\"object-identifier\"",
  "\"string-literal\"", "\"error\"", "\"integer-literal\"", "$accept",
  "program", "classes", "class", "class-body", "field", "method", "type",
  "formals", "formal", "block", "exprs", "expr", "args-optional", "args",
  "if", "while", "let", "object-assign", "unop", "binop", "call", "new",
  "literal", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   148,   148,   151,   152,   155,   156,   159,   160,   161,
     164,   165,   168,   171,   172,   173,   174,   175,   178,   179,
     180,   183,   186,   189,   190,   193,   194,   195,   196,   197,
     198,   199,   200,   203,   204,   205,   206,   207,   210,   213,
     214,   217,   218,   221,   222,   225,   228,   229,   232,   235,
     236,   237,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   251,   252,   255,   258,   259,   260,   261
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 19 "parser.y"
} // VSOP
#line 1834 "parser.cpp"

#line 264 "parser.y"

// User code
void VSOP::Parser::error(const location_type& l, const std::string& m)
{
    const position &pos = l.begin;

    cerr << *(pos.filename) << ":"
         << pos.line << ":" 
         << pos.column << ": "
         << m
         << endl;
}
