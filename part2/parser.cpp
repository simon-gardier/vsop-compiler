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
#line 49 "parser.y"

    #include "driver.hpp"

#line 50 "parser.cpp"


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

#line 13 "parser.y"
namespace VSOP {
#line 143 "parser.cpp"

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
        value.YY_MOVE_OR_COPY< VSOP::ClassAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
      case symbol_kind::S_expr: // expr
        value.YY_MOVE_OR_COPY< VSOP::ExprAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field: // field
        value.YY_MOVE_OR_COPY< VSOP::FieldAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formal: // formal
        value.YY_MOVE_OR_COPY< VSOP::FormalAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_method: // method
        value.YY_MOVE_OR_COPY< VSOP::MethodAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.YY_MOVE_OR_COPY< VSOP::ProgramAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTEGER_LITERAL: // INTEGER_LITERAL
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_TYPE_IDENTIFIER: // TYPE_IDENTIFIER
      case symbol_kind::S_OBJECT_IDENTIFIER: // OBJECT_IDENTIFIER
      case symbol_kind::S_type: // type
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_class_list: // class_list
        value.YY_MOVE_OR_COPY< std::vector<VSOP::ClassAst*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
      case symbol_kind::S_args: // args
        value.YY_MOVE_OR_COPY< std::vector<VSOP::ExprAst*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_list: // field_list
        value.YY_MOVE_OR_COPY< std::vector<VSOP::FieldAst*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formals: // formals
      case symbol_kind::S_formal_list: // formal_list
        value.YY_MOVE_OR_COPY< std::vector<VSOP::FormalAst*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_method_list: // method_list
        value.YY_MOVE_OR_COPY< std::vector<VSOP::MethodAst*> > (YY_MOVE (that.value));
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
        value.move< VSOP::ClassAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
      case symbol_kind::S_expr: // expr
        value.move< VSOP::ExprAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field: // field
        value.move< VSOP::FieldAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formal: // formal
        value.move< VSOP::FormalAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_method: // method
        value.move< VSOP::MethodAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< VSOP::ProgramAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTEGER_LITERAL: // INTEGER_LITERAL
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_TYPE_IDENTIFIER: // TYPE_IDENTIFIER
      case symbol_kind::S_OBJECT_IDENTIFIER: // OBJECT_IDENTIFIER
      case symbol_kind::S_type: // type
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_class_list: // class_list
        value.move< std::vector<VSOP::ClassAst*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
      case symbol_kind::S_args: // args
        value.move< std::vector<VSOP::ExprAst*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_list: // field_list
        value.move< std::vector<VSOP::FieldAst*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formals: // formals
      case symbol_kind::S_formal_list: // formal_list
        value.move< std::vector<VSOP::FormalAst*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_method_list: // method_list
        value.move< std::vector<VSOP::MethodAst*> > (YY_MOVE (that.value));
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
        value.copy< VSOP::ClassAst* > (that.value);
        break;

      case symbol_kind::S_block: // block
      case symbol_kind::S_expr: // expr
        value.copy< VSOP::ExprAst* > (that.value);
        break;

      case symbol_kind::S_field: // field
        value.copy< VSOP::FieldAst* > (that.value);
        break;

      case symbol_kind::S_formal: // formal
        value.copy< VSOP::FormalAst* > (that.value);
        break;

      case symbol_kind::S_method: // method
        value.copy< VSOP::MethodAst* > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.copy< VSOP::ProgramAst* > (that.value);
        break;

      case symbol_kind::S_INTEGER_LITERAL: // INTEGER_LITERAL
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_TYPE_IDENTIFIER: // TYPE_IDENTIFIER
      case symbol_kind::S_OBJECT_IDENTIFIER: // OBJECT_IDENTIFIER
      case symbol_kind::S_type: // type
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_class_list: // class_list
        value.copy< std::vector<VSOP::ClassAst*> > (that.value);
        break;

      case symbol_kind::S_expr_list: // expr_list
      case symbol_kind::S_args: // args
        value.copy< std::vector<VSOP::ExprAst*> > (that.value);
        break;

      case symbol_kind::S_field_list: // field_list
        value.copy< std::vector<VSOP::FieldAst*> > (that.value);
        break;

      case symbol_kind::S_formals: // formals
      case symbol_kind::S_formal_list: // formal_list
        value.copy< std::vector<VSOP::FormalAst*> > (that.value);
        break;

      case symbol_kind::S_method_list: // method_list
        value.copy< std::vector<VSOP::MethodAst*> > (that.value);
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
        value.move< VSOP::ClassAst* > (that.value);
        break;

      case symbol_kind::S_block: // block
      case symbol_kind::S_expr: // expr
        value.move< VSOP::ExprAst* > (that.value);
        break;

      case symbol_kind::S_field: // field
        value.move< VSOP::FieldAst* > (that.value);
        break;

      case symbol_kind::S_formal: // formal
        value.move< VSOP::FormalAst* > (that.value);
        break;

      case symbol_kind::S_method: // method
        value.move< VSOP::MethodAst* > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.move< VSOP::ProgramAst* > (that.value);
        break;

      case symbol_kind::S_INTEGER_LITERAL: // INTEGER_LITERAL
        value.move< int > (that.value);
        break;

      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_TYPE_IDENTIFIER: // TYPE_IDENTIFIER
      case symbol_kind::S_OBJECT_IDENTIFIER: // OBJECT_IDENTIFIER
      case symbol_kind::S_type: // type
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_class_list: // class_list
        value.move< std::vector<VSOP::ClassAst*> > (that.value);
        break;

      case symbol_kind::S_expr_list: // expr_list
      case symbol_kind::S_args: // args
        value.move< std::vector<VSOP::ExprAst*> > (that.value);
        break;

      case symbol_kind::S_field_list: // field_list
        value.move< std::vector<VSOP::FieldAst*> > (that.value);
        break;

      case symbol_kind::S_formals: // formals
      case symbol_kind::S_formal_list: // formal_list
        value.move< std::vector<VSOP::FormalAst*> > (that.value);
        break;

      case symbol_kind::S_method_list: // method_list
        value.move< std::vector<VSOP::MethodAst*> > (that.value);
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
        yylhs.value.emplace< VSOP::ClassAst* > ();
        break;

      case symbol_kind::S_block: // block
      case symbol_kind::S_expr: // expr
        yylhs.value.emplace< VSOP::ExprAst* > ();
        break;

      case symbol_kind::S_field: // field
        yylhs.value.emplace< VSOP::FieldAst* > ();
        break;

      case symbol_kind::S_formal: // formal
        yylhs.value.emplace< VSOP::FormalAst* > ();
        break;

      case symbol_kind::S_method: // method
        yylhs.value.emplace< VSOP::MethodAst* > ();
        break;

      case symbol_kind::S_program: // program
        yylhs.value.emplace< VSOP::ProgramAst* > ();
        break;

      case symbol_kind::S_INTEGER_LITERAL: // INTEGER_LITERAL
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_TYPE_IDENTIFIER: // TYPE_IDENTIFIER
      case symbol_kind::S_OBJECT_IDENTIFIER: // OBJECT_IDENTIFIER
      case symbol_kind::S_type: // type
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_class_list: // class_list
        yylhs.value.emplace< std::vector<VSOP::ClassAst*> > ();
        break;

      case symbol_kind::S_expr_list: // expr_list
      case symbol_kind::S_args: // args
        yylhs.value.emplace< std::vector<VSOP::ExprAst*> > ();
        break;

      case symbol_kind::S_field_list: // field_list
        yylhs.value.emplace< std::vector<VSOP::FieldAst*> > ();
        break;

      case symbol_kind::S_formals: // formals
      case symbol_kind::S_formal_list: // formal_list
        yylhs.value.emplace< std::vector<VSOP::FormalAst*> > ();
        break;

      case symbol_kind::S_method_list: // method_list
        yylhs.value.emplace< std::vector<VSOP::MethodAst*> > ();
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
  case 2: // program: class_list
#line 128 "parser.y"
        {
            yylhs.value.as < VSOP::ProgramAst* > () = new ProgramAst();
            yylhs.value.as < VSOP::ProgramAst* > ()->classes = yystack_[0].value.as < std::vector<VSOP::ClassAst*> > ();
            driver.programAst.reset(yylhs.value.as < VSOP::ProgramAst* > ());
        }
#line 831 "parser.cpp"
    break;

  case 3: // class_list: class
#line 137 "parser.y"
        {
            yylhs.value.as < std::vector<VSOP::ClassAst*> > () = std::vector<ClassAst*>();
            yylhs.value.as < std::vector<VSOP::ClassAst*> > ().push_back(yystack_[0].value.as < VSOP::ClassAst* > ());
        }
#line 840 "parser.cpp"
    break;

  case 4: // class_list: class_list class
#line 142 "parser.y"
        {
            yylhs.value.as < std::vector<VSOP::ClassAst*> > () = yystack_[1].value.as < std::vector<VSOP::ClassAst*> > ();
            yylhs.value.as < std::vector<VSOP::ClassAst*> > ().push_back(yystack_[0].value.as < VSOP::ClassAst* > ());
        }
#line 849 "parser.cpp"
    break;

  case 5: // class: "class" TYPE_IDENTIFIER "{" field_list method_list "}"
#line 151 "parser.y"
        {
            yylhs.value.as < VSOP::ClassAst* > () = new ClassAst(yystack_[4].value.as < std::string > ());
            yylhs.value.as < VSOP::ClassAst* > ()->fields = yystack_[2].value.as < std::vector<VSOP::FieldAst*> > ();
            yylhs.value.as < VSOP::ClassAst* > ()->methods = yystack_[1].value.as < std::vector<VSOP::MethodAst*> > ();
        }
#line 859 "parser.cpp"
    break;

  case 6: // class: "class" TYPE_IDENTIFIER "extends" TYPE_IDENTIFIER "{" field_list method_list "}"
#line 157 "parser.y"
        {
            yylhs.value.as < VSOP::ClassAst* > () = new ClassAst(yystack_[6].value.as < std::string > (), yystack_[4].value.as < std::string > ());
            yylhs.value.as < VSOP::ClassAst* > ()->fields = yystack_[2].value.as < std::vector<VSOP::FieldAst*> > ();
            yylhs.value.as < VSOP::ClassAst* > ()->methods = yystack_[1].value.as < std::vector<VSOP::MethodAst*> > ();
        }
#line 869 "parser.cpp"
    break;

  case 7: // field_list: %empty
#line 166 "parser.y"
        {
            yylhs.value.as < std::vector<VSOP::FieldAst*> > () = std::vector<FieldAst*>();
        }
#line 877 "parser.cpp"
    break;

  case 8: // field_list: field_list field
#line 170 "parser.y"
        {
            yylhs.value.as < std::vector<VSOP::FieldAst*> > () = yystack_[1].value.as < std::vector<VSOP::FieldAst*> > ();
            yylhs.value.as < std::vector<VSOP::FieldAst*> > ().push_back(yystack_[0].value.as < VSOP::FieldAst* > ());
        }
#line 886 "parser.cpp"
    break;

  case 9: // method_list: %empty
#line 178 "parser.y"
        {
            yylhs.value.as < std::vector<VSOP::MethodAst*> > () = std::vector<MethodAst*>();
        }
#line 894 "parser.cpp"
    break;

  case 10: // method_list: method_list method
#line 182 "parser.y"
        {
            yylhs.value.as < std::vector<VSOP::MethodAst*> > () = yystack_[1].value.as < std::vector<VSOP::MethodAst*> > ();
            yylhs.value.as < std::vector<VSOP::MethodAst*> > ().push_back(yystack_[0].value.as < VSOP::MethodAst* > ());
        }
#line 903 "parser.cpp"
    break;

  case 11: // field: OBJECT_IDENTIFIER ":" type ";"
#line 191 "parser.y"
        {
            yylhs.value.as < VSOP::FieldAst* > () = new FieldAst(yystack_[3].value.as < std::string > (), yystack_[1].value.as < std::string > ());
        }
#line 911 "parser.cpp"
    break;

  case 12: // field: OBJECT_IDENTIFIER ":" type "<-" expr ";"
#line 195 "parser.y"
        {
            yylhs.value.as < VSOP::FieldAst* > () = new FieldAst(yystack_[5].value.as < std::string > (), yystack_[3].value.as < std::string > (), yystack_[1].value.as < VSOP::ExprAst* > ());
        }
#line 919 "parser.cpp"
    break;

  case 13: // method: OBJECT_IDENTIFIER "(" formals ")" ":" type block
#line 203 "parser.y"
        {
            yylhs.value.as < VSOP::MethodAst* > () = new MethodAst(yystack_[6].value.as < std::string > (), yystack_[1].value.as < std::string > (), yystack_[0].value.as < VSOP::ExprAst* > ());
            yylhs.value.as < VSOP::MethodAst* > ()->formals = yystack_[4].value.as < std::vector<VSOP::FormalAst*> > ();
        }
#line 928 "parser.cpp"
    break;

  case 14: // formals: %empty
#line 212 "parser.y"
        {
            yylhs.value.as < std::vector<VSOP::FormalAst*> > () = std::vector<FormalAst*>();
        }
#line 936 "parser.cpp"
    break;

  case 15: // formals: formal_list
#line 216 "parser.y"
        {
            yylhs.value.as < std::vector<VSOP::FormalAst*> > () = yystack_[0].value.as < std::vector<VSOP::FormalAst*> > ();
        }
#line 944 "parser.cpp"
    break;

  case 16: // formal_list: formal
#line 223 "parser.y"
        {
            yylhs.value.as < std::vector<VSOP::FormalAst*> > () = std::vector<FormalAst*>();
            yylhs.value.as < std::vector<VSOP::FormalAst*> > ().push_back(yystack_[0].value.as < VSOP::FormalAst* > ());
        }
#line 953 "parser.cpp"
    break;

  case 17: // formal_list: formal_list "," formal
#line 228 "parser.y"
        {
            yylhs.value.as < std::vector<VSOP::FormalAst*> > () = yystack_[2].value.as < std::vector<VSOP::FormalAst*> > ();
            yylhs.value.as < std::vector<VSOP::FormalAst*> > ().push_back(yystack_[0].value.as < VSOP::FormalAst* > ());
        }
#line 962 "parser.cpp"
    break;

  case 18: // formal: OBJECT_IDENTIFIER ":" type
#line 236 "parser.y"
        {
            yylhs.value.as < VSOP::FormalAst* > () = new FormalAst(yystack_[2].value.as < std::string > (), yystack_[0].value.as < std::string > ());
        }
#line 970 "parser.cpp"
    break;

  case 19: // type: TYPE_IDENTIFIER
#line 244 "parser.y"
        {
            yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > ();
        }
#line 978 "parser.cpp"
    break;

  case 20: // type: "int32"
#line 248 "parser.y"
        {
            yylhs.value.as < std::string > () = "int32";
        }
#line 986 "parser.cpp"
    break;

  case 21: // type: "bool"
#line 252 "parser.y"
        {
            yylhs.value.as < std::string > () = "bool";
        }
#line 994 "parser.cpp"
    break;

  case 22: // type: "string"
#line 256 "parser.y"
        {
            yylhs.value.as < std::string > () = "string";
        }
#line 1002 "parser.cpp"
    break;

  case 23: // type: "unit"
#line 260 "parser.y"
        {
            yylhs.value.as < std::string > () = "unit";
        }
#line 1010 "parser.cpp"
    break;

  case 24: // block: "{" expr_list "}"
#line 268 "parser.y"
        {
            BlockExprAst* block = new BlockExprAst();
            block->expressions = yystack_[1].value.as < std::vector<VSOP::ExprAst*> > ();
            yylhs.value.as < VSOP::ExprAst* > () = block;
        }
#line 1020 "parser.cpp"
    break;

  case 25: // expr_list: expr
#line 277 "parser.y"
        {
            yylhs.value.as < std::vector<VSOP::ExprAst*> > () = std::vector<ExprAst*>();
            yylhs.value.as < std::vector<VSOP::ExprAst*> > ().push_back(yystack_[0].value.as < VSOP::ExprAst* > ());
        }
#line 1029 "parser.cpp"
    break;

  case 26: // expr_list: expr_list ";" expr
#line 282 "parser.y"
        {
            yylhs.value.as < std::vector<VSOP::ExprAst*> > () = yystack_[2].value.as < std::vector<VSOP::ExprAst*> > ();
            yylhs.value.as < std::vector<VSOP::ExprAst*> > ().push_back(yystack_[0].value.as < VSOP::ExprAst* > ());
        }
#line 1038 "parser.cpp"
    break;

  case 27: // expr: "if" expr "then" expr
#line 291 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new IfExprAst(yystack_[2].value.as < VSOP::ExprAst* > (), yystack_[0].value.as < VSOP::ExprAst* > ());
        }
#line 1046 "parser.cpp"
    break;

  case 28: // expr: "if" expr "then" expr "else" expr
#line 295 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new IfExprAst(yystack_[4].value.as < VSOP::ExprAst* > (), yystack_[2].value.as < VSOP::ExprAst* > (), yystack_[0].value.as < VSOP::ExprAst* > ());
        }
#line 1054 "parser.cpp"
    break;

  case 29: // expr: "while" expr "do" expr
#line 299 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new WhileExprAst(yystack_[2].value.as < VSOP::ExprAst* > (), yystack_[0].value.as < VSOP::ExprAst* > ());
        }
#line 1062 "parser.cpp"
    break;

  case 30: // expr: "let" OBJECT_IDENTIFIER ":" type "in" expr
#line 303 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new LetExprAst(yystack_[4].value.as < std::string > (), yystack_[2].value.as < std::string > (), nullptr, yystack_[0].value.as < VSOP::ExprAst* > ());
        }
#line 1070 "parser.cpp"
    break;

  case 31: // expr: "let" OBJECT_IDENTIFIER ":" type "<-" expr "in" expr
#line 307 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new LetExprAst(yystack_[6].value.as < std::string > (), yystack_[4].value.as < std::string > (), yystack_[2].value.as < VSOP::ExprAst* > (), yystack_[0].value.as < VSOP::ExprAst* > ());
        }
#line 1078 "parser.cpp"
    break;

  case 32: // expr: OBJECT_IDENTIFIER "<-" expr
#line 311 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new AssignExprAst(yystack_[2].value.as < std::string > (), yystack_[0].value.as < VSOP::ExprAst* > ());
        }
#line 1086 "parser.cpp"
    break;

  case 33: // expr: "not" expr
#line 315 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new UnaryOpExprAst("not", yystack_[0].value.as < VSOP::ExprAst* > ());
        }
#line 1094 "parser.cpp"
    break;

  case 34: // expr: "-" expr
#line 319 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new UnaryOpExprAst("-", yystack_[0].value.as < VSOP::ExprAst* > ());
        }
#line 1102 "parser.cpp"
    break;

  case 35: // expr: "isnull" expr
#line 323 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new UnaryOpExprAst("isnull", yystack_[0].value.as < VSOP::ExprAst* > ());
        }
#line 1110 "parser.cpp"
    break;

  case 36: // expr: expr "=" expr
#line 327 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new BinaryOpExprAst("=", yystack_[2].value.as < VSOP::ExprAst* > (), yystack_[0].value.as < VSOP::ExprAst* > ());
        }
#line 1118 "parser.cpp"
    break;

  case 37: // expr: expr "<" expr
#line 331 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new BinaryOpExprAst("<", yystack_[2].value.as < VSOP::ExprAst* > (), yystack_[0].value.as < VSOP::ExprAst* > ());
        }
#line 1126 "parser.cpp"
    break;

  case 38: // expr: expr "<=" expr
#line 335 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new BinaryOpExprAst("<=", yystack_[2].value.as < VSOP::ExprAst* > (), yystack_[0].value.as < VSOP::ExprAst* > ());
        }
#line 1134 "parser.cpp"
    break;

  case 39: // expr: expr "+" expr
#line 339 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new BinaryOpExprAst("+", yystack_[2].value.as < VSOP::ExprAst* > (), yystack_[0].value.as < VSOP::ExprAst* > ());
        }
#line 1142 "parser.cpp"
    break;

  case 40: // expr: expr "-" expr
#line 343 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new BinaryOpExprAst("-", yystack_[2].value.as < VSOP::ExprAst* > (), yystack_[0].value.as < VSOP::ExprAst* > ());
        }
#line 1150 "parser.cpp"
    break;

  case 41: // expr: expr "*" expr
#line 347 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new BinaryOpExprAst("*", yystack_[2].value.as < VSOP::ExprAst* > (), yystack_[0].value.as < VSOP::ExprAst* > ());
        }
#line 1158 "parser.cpp"
    break;

  case 42: // expr: expr "/" expr
#line 351 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new BinaryOpExprAst("/", yystack_[2].value.as < VSOP::ExprAst* > (), yystack_[0].value.as < VSOP::ExprAst* > ());
        }
#line 1166 "parser.cpp"
    break;

  case 43: // expr: expr "^" expr
#line 355 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new BinaryOpExprAst("^", yystack_[2].value.as < VSOP::ExprAst* > (), yystack_[0].value.as < VSOP::ExprAst* > ());
        }
#line 1174 "parser.cpp"
    break;

  case 44: // expr: expr "and" expr
#line 359 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new BinaryOpExprAst("and", yystack_[2].value.as < VSOP::ExprAst* > (), yystack_[0].value.as < VSOP::ExprAst* > ());
        }
#line 1182 "parser.cpp"
    break;

  case 45: // expr: OBJECT_IDENTIFIER "(" args ")"
#line 363 "parser.y"
        {
            CallExprAst* call = new CallExprAst(new SelfExprAst(), yystack_[3].value.as < std::string > ());
            call->arguments = yystack_[1].value.as < std::vector<VSOP::ExprAst*> > ();
            yylhs.value.as < VSOP::ExprAst* > () = call;
        }
#line 1192 "parser.cpp"
    break;

  case 46: // expr: expr "." OBJECT_IDENTIFIER "(" args ")"
#line 369 "parser.y"
        {
            CallExprAst* call = new CallExprAst(yystack_[5].value.as < VSOP::ExprAst* > (), yystack_[3].value.as < std::string > ());
            call->arguments = yystack_[1].value.as < std::vector<VSOP::ExprAst*> > ();
            yylhs.value.as < VSOP::ExprAst* > () = call;
        }
#line 1202 "parser.cpp"
    break;

  case 47: // expr: "new" TYPE_IDENTIFIER
#line 375 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new NewExprAst(yystack_[0].value.as < std::string > ());
        }
#line 1210 "parser.cpp"
    break;

  case 48: // expr: OBJECT_IDENTIFIER
#line 379 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new ObjectIdExprAst(yystack_[0].value.as < std::string > ());
        }
#line 1218 "parser.cpp"
    break;

  case 49: // expr: "self"
#line 383 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new SelfExprAst();
        }
#line 1226 "parser.cpp"
    break;

  case 50: // expr: INTEGER_LITERAL
#line 387 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new IntegerLiteralExprAst(yystack_[0].value.as < int > ());
        }
#line 1234 "parser.cpp"
    break;

  case 51: // expr: STRING_LITERAL
#line 391 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new StringLiteralExprAst(yystack_[0].value.as < std::string > ());
        }
#line 1242 "parser.cpp"
    break;

  case 52: // expr: "true"
#line 395 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new BooleanLiteralExprAst(true);
        }
#line 1250 "parser.cpp"
    break;

  case 53: // expr: "false"
#line 399 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new BooleanLiteralExprAst(false);
        }
#line 1258 "parser.cpp"
    break;

  case 54: // expr: "(" ")"
#line 403 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = new UnitExprAst();
        }
#line 1266 "parser.cpp"
    break;

  case 55: // expr: "(" expr ")"
#line 407 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = yystack_[1].value.as < VSOP::ExprAst* > ();
        }
#line 1274 "parser.cpp"
    break;

  case 56: // expr: block
#line 411 "parser.y"
        {
            yylhs.value.as < VSOP::ExprAst* > () = yystack_[0].value.as < VSOP::ExprAst* > ();
        }
#line 1282 "parser.cpp"
    break;

  case 57: // args: %empty
#line 419 "parser.y"
        {
            yylhs.value.as < std::vector<VSOP::ExprAst*> > () = std::vector<ExprAst*>();
        }
#line 1290 "parser.cpp"
    break;

  case 58: // args: expr_list
#line 423 "parser.y"
        {
            yylhs.value.as < std::vector<VSOP::ExprAst*> > () = yystack_[0].value.as < std::vector<VSOP::ExprAst*> > ();
        }
#line 1298 "parser.cpp"
    break;


#line 1302 "parser.cpp"

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
        std::string msg = YY_("syntax error");
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

#if YYDEBUG || 0
  const char *
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0





  const signed char Parser::yypact_ninf_ = -52;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
      -8,    19,     6,    -8,   -52,    -3,   -52,   -52,   -52,    23,
      39,    43,    40,     1,   -52,   -52,    -4,    44,   -52,   -52,
      39,   -52,   -52,   -52,   -52,   -52,    -7,    46,    17,   -52,
     100,    45,    48,    41,   -52,   -52,   -52,   -52,    -1,   100,
      59,   100,   -52,   100,   100,    49,    55,   100,   -52,   -52,
     100,   -52,   189,    -4,    53,    46,   100,   100,     7,   200,
     -52,   149,    51,   102,    51,    56,   -52,    51,   175,   -52,
     100,   100,   100,   100,   100,    65,   100,   100,   100,   100,
     -52,    -4,   -52,    60,    63,   200,   -52,   100,   -52,   100,
      -4,   100,    15,    15,    18,    18,    18,    66,   211,   211,
     211,   220,    69,   -52,   200,   160,   -20,   200,   100,   -52,
     100,   100,   100,    67,   200,   130,   200,   -52,   100,   200
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     0,     0,     2,     3,     0,     1,     4,     7,     0,
       9,     0,     0,     0,     8,     7,     0,     0,     5,    10,
       9,    19,    21,    20,    22,    23,     0,    14,     0,    11,
       0,     0,     0,    15,    16,     6,    50,    51,    48,     0,
       0,     0,    53,     0,     0,     0,     0,     0,    49,    52,
       0,    56,     0,     0,     0,     0,    57,     0,     0,    25,
      54,     0,    34,     0,    35,     0,    47,    33,     0,    12,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      18,     0,    17,    58,     0,    32,    24,     0,    55,     0,
       0,     0,    39,    40,    41,    42,    43,     0,    36,    37,
      38,    44,     0,    45,    26,    27,     0,    29,    57,    13,
       0,     0,     0,     0,    28,     0,    30,    46,     0,    31
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -52,   -52,   -52,    75,    64,    71,   -52,   -52,   -52,   -52,
      28,   -51,   -18,    47,   -30,   -23
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     2,     3,     4,    10,    13,    14,    19,    32,    33,
      34,    26,    51,    83,    59,    84
  };

  const signed char
  Parser::yytable_[] =
  {
      52,    21,    80,   111,     8,    29,     6,    17,    56,    18,
      61,    62,   112,    63,    64,    86,    30,    67,     1,    87,
      68,    22,    57,    17,     5,    35,     9,    85,    11,    23,
     102,    72,    73,    74,    75,    24,    74,    75,    25,   106,
      92,    93,    94,    95,    96,    12,    98,    99,   100,   101,
      15,    16,    31,    27,    55,    65,    53,   104,    54,   105,
      66,   107,    36,    37,    81,    38,    39,    90,    40,    60,
      75,    97,    87,   103,    41,   108,    39,   117,     7,    20,
     114,   115,   116,    82,   109,   113,    58,     0,   119,    42,
      43,    28,     0,    44,    45,    46,    47,    48,     0,     0,
      49,     0,    50,    36,    37,     0,    38,    39,     0,    40,
       0,     0,     0,     0,     0,    41,    70,    71,    72,    73,
      74,    75,    76,    77,    78,     0,    79,     0,     0,     0,
      42,    43,     0,     0,    44,    45,    46,    47,    48,     0,
       0,    49,    89,    50,    70,    71,    72,    73,    74,    75,
      76,    77,    78,     0,    79,     0,     0,     0,     0,    88,
       0,     0,   118,    70,    71,    72,    73,    74,    75,    76,
      77,    78,     0,    79,    70,    71,    72,    73,    74,    75,
      76,    77,    78,     0,    79,     0,     0,     0,   110,    70,
      71,    72,    73,    74,    75,    76,    77,    78,     0,    79,
       0,    69,    91,    70,    71,    72,    73,    74,    75,    76,
      77,    78,     0,    79,    70,    71,    72,    73,    74,    75,
      76,    77,    78,     0,    79,    70,    71,    72,    73,    74,
      75,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    77,    78
  };

  const signed char
  Parser::yycheck_[] =
  {
      30,     5,    53,    23,     7,    12,     0,     6,     9,     8,
      40,    41,    32,    43,    44,     8,    23,    47,    26,    12,
      50,    25,    23,     6,     5,     8,    29,    57,     5,    33,
      81,    16,    17,    18,    19,    39,    18,    19,    42,    90,
      70,    71,    72,    73,    74,     6,    76,    77,    78,    79,
       7,    11,     6,     9,    13,     6,    11,    87,    10,    89,
       5,    91,     3,     4,    11,     6,     7,    11,     9,    10,
      19,     6,    12,    10,    15,     9,     7,    10,     3,    15,
     110,   111,   112,    55,   102,   108,    39,    -1,   118,    30,
      31,    20,    -1,    34,    35,    36,    37,    38,    -1,    -1,
      41,    -1,    43,     3,     4,    -1,     6,     7,    -1,     9,
      -1,    -1,    -1,    -1,    -1,    15,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    24,    -1,    -1,    -1,
      30,    31,    -1,    -1,    34,    35,    36,    37,    38,    -1,
      -1,    41,    40,    43,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    -1,    -1,    -1,    -1,    10,
      -1,    -1,    32,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    -1,    -1,    -1,    28,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      -1,    12,    27,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    14,    15,    16,    17,    18,    19,
      20,    21,    22
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    26,    48,    49,    50,     5,     0,    50,     7,    29,
      51,     5,     6,    52,    53,     7,    11,     6,     8,    54,
      51,     5,    25,    33,    39,    42,    58,     9,    52,    12,
      23,     6,    55,    56,    57,     8,     3,     4,     6,     7,
       9,    15,    30,    31,    34,    35,    36,    37,    38,    41,
      43,    59,    61,    11,    10,    13,     9,    23,    60,    61,
      10,    61,    61,    61,    61,     6,     5,    61,    61,    12,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    24,
      58,    11,    57,    60,    62,    61,     8,    12,    10,    40,
      11,    27,    61,    61,    61,    61,    61,     6,    61,    61,
      61,    61,    58,    10,    61,    61,    58,    61,     9,    59,
      28,    23,    32,    62,    61,    61,    61,    10,    32,    61
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    47,    48,    49,    49,    50,    50,    51,    51,    52,
      52,    53,    53,    54,    55,    55,    56,    56,    57,    58,
      58,    58,    58,    58,    59,    60,    60,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    62,    62
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     6,     8,     0,     2,     0,
       2,     4,     6,     7,     0,     1,     1,     3,     3,     1,
       1,     1,     1,     1,     3,     1,     3,     4,     6,     4,
       6,     8,     3,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     6,     2,     1,     1,
       1,     1,     1,     1,     2,     3,     1,     0,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "INTEGER_LITERAL",
  "STRING_LITERAL", "TYPE_IDENTIFIER", "OBJECT_IDENTIFIER", "\"{\"",
  "\"}\"", "\"(\"", "\")\"", "\":\"", "\";\"", "\",\"", "\"+\"", "\"-\"",
  "\"*\"", "\"/\"", "\"^\"", "\".\"", "\"=\"", "\"<\"", "\"<=\"", "\"<-\"",
  "\"and\"", "\"bool\"", "\"class\"", "\"do\"", "\"else\"", "\"extends\"",
  "\"false\"", "\"if\"", "\"in\"", "\"int32\"", "\"isnull\"", "\"let\"",
  "\"new\"", "\"not\"", "\"self\"", "\"string\"", "\"then\"", "\"true\"",
  "\"unit\"", "\"while\"", "UMINUS", "UNOT", "UISNULL", "$accept",
  "program", "class_list", "class", "field_list", "method_list", "field",
  "method", "formals", "formal_list", "formal", "type", "block",
  "expr_list", "expr", "args", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   127,   127,   136,   141,   150,   156,   166,   169,   178,
     181,   190,   194,   202,   212,   215,   222,   227,   235,   243,
     247,   251,   255,   259,   267,   276,   281,   290,   294,   298,
     302,   306,   310,   314,   318,   322,   326,   330,   334,   338,
     342,   346,   350,   354,   358,   362,   368,   374,   378,   382,
     386,   390,   394,   398,   402,   406,   410,   419,   422
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


#line 13 "parser.y"
} // VSOP
#line 1706 "parser.cpp"

#line 428 "parser.y"


// User code
void VSOP::Parser::error(const location_type& l, const std::string& m)
{
    const position &pos = l.begin;

    std::cerr   << *(pos.filename) << ":"
                << pos.line << ":" 
                << pos.column << ": "
                << m
                << std::endl;
}
