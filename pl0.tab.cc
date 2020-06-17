// A Bison parser, made by GNU Bison 3.5.0.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2019 Free Software Foundation, Inc.

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

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.



// First part of user prologue.
#line 2 "pl0.y"

#include <iostream>
#include <typeinfo>
#include "lexer.h"
YYSTYPE* yylval;
int yylex(YYSTYPE*);
YYSTYPE result;

#include "pl0_process.h"


#line 52 "pl0.tab.cc"




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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
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

namespace yy {
#line 183 "pl0.tab.cc"




  /// A Bison parser.
  class parser
  {
  public:
#ifndef YYSTYPE
    /// Symbol semantic values.
    typedef int semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m)
        : std::runtime_error (m)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        TOK_div = 258,
        TOK_mod = 259,
        TOK_and = 260,
        TOK_or = 261,
        TOK_not = 262,
        TOK_to = 263,
        TOK_downto = 264,
        TOK_with = 265,
        TOK_do = 266,
        TOK_begin = 267,
        TOK_end = 268,
        TOK_if = 269,
        TOK_then = 270,
        TOK_else = 271,
        TOK_case = 272,
        TOK_of = 273,
        TOK_while = 274,
        TOK_repeat = 275,
        TOK_until = 276,
        TOK_for = 277,
        TOK_array = 278,
        TOK_const = 279,
        TOK_procedure = 280,
        TOK_var = 281,
        TOK_function = 282,
        TOK_goto = 283,
        TOK_call = 284,
        TOK_break = 285,
        TOK_SEMI = 286,
        TOK_POINTER = 287,
        TOK_PLUS = 288,
        TOK_MINUS = 289,
        TOK_LPAREN = 290,
        TOK_RPAREN = 291,
        TOK_EQUAL = 292,
        TOK_COLON = 293,
        TOK_COMMA = 294,
        TOK_ASSIGN = 295,
        TOK_NOT_EQUAL = 296,
        TOK_LT = 297,
        TOK_LE = 298,
        TOK_GE = 299,
        TOK_GT = 300,
        TOK_AT = 301,
        TOK_LBRACK = 302,
        TOK_RBRACK = 303,
        TOK_LBRACK2 = 304,
        TOK_RBRACK2 = 305,
        TOK_DOT = 306,
        TOK_STAR = 307,
        TOK_SLASH = 308,
        TOK_MOD2 = 309,
        TOK_AND = 310,
        TOK_OR = 311,
        TOK_DOTDOT = 312,
        TOK_IDENTIFIER = 313,
        TOK_NUM_INT = 314,
        TOK_NUM_REAL = 315,
        TOK_STRING = 316,
        TOK_UNKNOWN = 317,
        TOK_EOF = 318,
        TOK_typename_pointer = 319
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef signed char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get ().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that);
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);
      /// Constructor for valueless symbols.
      basic_symbol (typename Base::kind_type t);

      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    YY_RVREF (semantic_type) v);

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
      {
        Base::clear ();
      }

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_type (by_type&& that);
#endif

      /// Copy constructor.
      by_type (const by_type& that);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const YY_NOEXCEPT;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_type>
    {};

    /// Build a parser object.
    parser ();
    virtual ~parser ();

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
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);



  private:
    /// This class is not copyable.
    parser (const parser&);
    parser& operator= (const parser&);

    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

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

    static const short yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    /// In theory \a t should be a token_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static token_number_type yytranslate_ (int t);

    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const short yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const unsigned char yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    // symbol of state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
    static const signed char yyr1_[];

    // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
    static const signed char yyr2_[];


#if YYDEBUG
    /// For a symbol, its name in clear.
    static const char* const yytname_[];

    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const unsigned char yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
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

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const YY_NOEXCEPT;

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
      typedef typename S::reverse_iterator iterator;
      typedef typename S::const_reverse_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

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

      std::ptrdiff_t
      ssize () const YY_NOEXCEPT
      {
        return std::ptrdiff_t (size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.rbegin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.rend ();
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
      stack (const stack&);
      stack& operator= (const stack&);
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

    /// Some specific tokens.
    static const token_number_type yy_error_token_ = 1;
    static const token_number_type yy_undef_token_ = 2;

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 499,     ///< Last index in yytable_.
      yynnts_ = 40,  ///< Number of nonterminal symbols.
      yyfinal_ = 7, ///< Termination state number.
      yyntokens_ = 65  ///< Number of tokens.
    };


  };


} // yy
#line 741 "pl0.tab.cc"









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
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 820 "pl0.tab.cc"


  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value (std::move (that.value))
  {}
#endif

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v)
    : Base (t)
    , value (YY_MOVE (v))
  {}

  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
  }

  // by_type.
  parser::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
  parser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  parser::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  parser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }


  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value))
  {
    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

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

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.type = yytranslate_ (yylex (&yyla.value));
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

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
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
    yypush_ ("Shifting", static_cast<state_type> (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
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
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 98 "pl0.y"
                            {/*puts("program: subprogram DOT EOF");*/ yyprocess_program_0("program", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); result = yylhs.value; YYACCEPT;}
#line 1257 "pl0.tab.cc"
    break;

  case 3:
#line 99 "pl0.y"
                                                           {/*puts("subprogram: opt_const_decl opt_val_decl opt_proc_decl stmt");*/ yyprocess_subprogram_0("subprogram", yylhs.value, {yystack_[3].value, yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1263 "pl0.tab.cc"
    break;

  case 4:
#line 101 "pl0.y"
                {/*puts("opt_const_decl: ");*/ yyprocess_opt_const_decl_0("opt_const_decl", yylhs.value, {}); }
#line 1269 "pl0.tab.cc"
    break;

  case 5:
#line 102 "pl0.y"
                        {/*puts("opt_const_decl: const const_decl SEMI");*/ yyprocess_opt_const_decl_1("opt_const_decl", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1275 "pl0.tab.cc"
    break;

  case 6:
#line 104 "pl0.y"
                                           {/*puts("const_decl: IDENTIFIER EQUAL const_literal");*/ yyprocess_const_decl_0("const_decl", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1281 "pl0.tab.cc"
    break;

  case 7:
#line 105 "pl0.y"
                                                  {/*puts("const_decl: IDENTIFIER EQUAL const_literal COMMA const_decl");*/ yyprocess_const_decl_1("const_decl", yylhs.value, {yystack_[4].value, yystack_[3].value, yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1287 "pl0.tab.cc"
    break;

  case 8:
#line 107 "pl0.y"
                       {/*puts("const_literal: NUM_INT");*/ yyprocess_const_literal_0("const_literal", yylhs.value, {yystack_[0].value}); }
#line 1293 "pl0.tab.cc"
    break;

  case 9:
#line 108 "pl0.y"
           {/*puts("const_literal: NUM_REAL");*/ yyprocess_const_literal_1("const_literal", yylhs.value, {yystack_[0].value}); }
#line 1299 "pl0.tab.cc"
    break;

  case 10:
#line 109 "pl0.y"
         {/*puts("const_literal: STRING");*/ yyprocess_const_literal_2("const_literal", yylhs.value, {yystack_[0].value}); }
#line 1305 "pl0.tab.cc"
    break;

  case 11:
#line 111 "pl0.y"
              {/*puts("opt_val_decl: ");*/ yyprocess_opt_val_decl_0("opt_val_decl", yylhs.value, {}); }
#line 1311 "pl0.tab.cc"
    break;

  case 12:
#line 112 "pl0.y"
                 {/*puts("opt_val_decl: var_name_decls");*/ yyprocess_opt_val_decl_1("opt_val_decl", yylhs.value, {yystack_[0].value}); }
#line 1317 "pl0.tab.cc"
    break;

  case 13:
#line 114 "pl0.y"
                              {/*puts("var_name_decls: var_name_decl");*/ yyprocess_var_name_decls_0("var_name_decls", yylhs.value, {yystack_[0].value}); }
#line 1323 "pl0.tab.cc"
    break;

  case 14:
#line 115 "pl0.y"
                               {/*puts("var_name_decls: var_name_decl var_name_decls");*/ yyprocess_var_name_decls_1("var_name_decls", yylhs.value, {yystack_[1].value, yystack_[0].value}); }
#line 1329 "pl0.tab.cc"
    break;

  case 15:
#line 117 "pl0.y"
                                                     {/*puts("var_name_decl: var var_name_list COLON typename SEMI");*/ yyprocess_var_name_decl_0("var_name_decl", yylhs.value, {yystack_[4].value, yystack_[3].value, yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1335 "pl0.tab.cc"
    break;

  case 16:
#line 119 "pl0.y"
                          {/*puts("var_name_list: IDENTIFIER");*/ yyprocess_var_name_list_0("var_name_list", yylhs.value, {yystack_[0].value}); }
#line 1341 "pl0.tab.cc"
    break;

  case 17:
#line 120 "pl0.y"
                                 {/*puts("var_name_list: IDENTIFIER COMMA var_name_list");*/ yyprocess_var_name_list_1("var_name_list", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1347 "pl0.tab.cc"
    break;

  case 18:
#line 122 "pl0.y"
                     {/*puts("typename: IDENTIFIER");*/ yyprocess_typename_0("typename", yylhs.value, {yystack_[0].value}); }
#line 1353 "pl0.tab.cc"
    break;

  case 19:
#line 123 "pl0.y"
                                          {/*puts("typename: POINTER typename");*/ yyprocess_typename_1("typename", yylhs.value, {yystack_[1].value, yystack_[0].value}); }
#line 1359 "pl0.tab.cc"
    break;

  case 20:
#line 124 "pl0.y"
                                       {/*puts("typename: LPAREN opt_param_decl RPAREN opt_ret");*/ yyprocess_typename_2("typename", yylhs.value, {yystack_[3].value, yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1365 "pl0.tab.cc"
    break;

  case 21:
#line 125 "pl0.y"
                                                {/*puts("typename: typename LBRACK NUM_INT DOTDOT NUM_INT RBRACK");*/ yyprocess_typename_3("typename", yylhs.value, {yystack_[5].value, yystack_[4].value, yystack_[3].value, yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1371 "pl0.tab.cc"
    break;

  case 22:
#line 126 "pl0.y"
                         {/*puts("typename: LPAREN typename RPAREN");*/ yyprocess_typename_4("typename", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1377 "pl0.tab.cc"
    break;

  case 23:
#line 128 "pl0.y"
         {/*puts("opt_ret: ");*/ yyprocess_opt_ret_0("opt_ret", yylhs.value, {}); }
#line 1383 "pl0.tab.cc"
    break;

  case 24:
#line 129 "pl0.y"
                 {/*puts("opt_ret: COLON typename");*/ yyprocess_opt_ret_1("opt_ret", yylhs.value, {yystack_[1].value, yystack_[0].value}); }
#line 1389 "pl0.tab.cc"
    break;

  case 25:
#line 131 "pl0.y"
               {/*puts("opt_proc_decl: ");*/ yyprocess_opt_proc_decl_0("opt_proc_decl", yylhs.value, {}); }
#line 1395 "pl0.tab.cc"
    break;

  case 26:
#line 132 "pl0.y"
             {/*puts("opt_proc_decl: proc_decls");*/ yyprocess_opt_proc_decl_1("opt_proc_decl", yylhs.value, {yystack_[0].value}); }
#line 1401 "pl0.tab.cc"
    break;

  case 27:
#line 134 "pl0.y"
                      {/*puts("proc_decls: proc_decl");*/ yyprocess_proc_decls_0("proc_decls", yylhs.value, {yystack_[0].value}); }
#line 1407 "pl0.tab.cc"
    break;

  case 28:
#line 135 "pl0.y"
            {/*puts("proc_decls: func_decl");*/ yyprocess_proc_decls_1("proc_decls", yylhs.value, {yystack_[0].value}); }
#line 1413 "pl0.tab.cc"
    break;

  case 29:
#line 136 "pl0.y"
                       {/*puts("proc_decls: proc_decl proc_decls");*/ yyprocess_proc_decls_2("proc_decls", yylhs.value, {yystack_[1].value, yystack_[0].value}); }
#line 1419 "pl0.tab.cc"
    break;

  case 30:
#line 137 "pl0.y"
                       {/*puts("proc_decls: func_decl proc_decls");*/ yyprocess_proc_decls_3("proc_decls", yylhs.value, {yystack_[1].value, yystack_[0].value}); }
#line 1425 "pl0.tab.cc"
    break;

  case 31:
#line 139 "pl0.y"
                                {/*puts("func_decl: func_head subprogram");*/ yyprocess_func_decl_0("func_decl", yylhs.value, {yystack_[1].value, yystack_[0].value}); }
#line 1431 "pl0.tab.cc"
    break;

  case 32:
#line 141 "pl0.y"
                                                                           {/*puts("func_head: function IDENTIFIER LPAREN opt_param_decl RPAREN COLON typename");*/ yyprocess_func_head_0("func_head", yylhs.value, {yystack_[6].value, yystack_[5].value, yystack_[4].value, yystack_[3].value, yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1437 "pl0.tab.cc"
    break;

  case 33:
#line 142 "pl0.y"
                                                   {/*puts("func_head: function IDENTIFIER LPAREN opt_param_decl RPAREN");*/ yyprocess_func_head_1("func_head", yylhs.value, {yystack_[4].value, yystack_[3].value, yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1443 "pl0.tab.cc"
    break;

  case 34:
#line 144 "pl0.y"
                                {/*puts("proc_decl: proc_head subprogram");*/ yyprocess_proc_decl_0("proc_decl", yylhs.value, {yystack_[1].value, yystack_[0].value}); }
#line 1449 "pl0.tab.cc"
    break;

  case 35:
#line 146 "pl0.y"
                                {/*puts("proc_head: procedure IDENTIFIER");*/ yyprocess_proc_head_0("proc_head", yylhs.value, {yystack_[1].value, yystack_[0].value}); }
#line 1455 "pl0.tab.cc"
    break;

  case 36:
#line 148 "pl0.y"
                {/*puts("opt_param_decl: ");*/ yyprocess_opt_param_decl_0("opt_param_decl", yylhs.value, {}); }
#line 1461 "pl0.tab.cc"
    break;

  case 37:
#line 149 "pl0.y"
             {/*puts("opt_param_decl: param_decl");*/ yyprocess_opt_param_decl_1("opt_param_decl", yylhs.value, {yystack_[0].value}); }
#line 1467 "pl0.tab.cc"
    break;

  case 38:
#line 151 "pl0.y"
                                      {/*puts("param_decl: IDENTIFIER COLON typename");*/ yyprocess_param_decl_0("param_decl", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1473 "pl0.tab.cc"
    break;

  case 39:
#line 152 "pl0.y"
                 {/*puts("param_decl: COLON typename");*/ yyprocess_param_decl_1("param_decl", yylhs.value, {yystack_[1].value, yystack_[0].value}); }
#line 1479 "pl0.tab.cc"
    break;

  case 40:
#line 153 "pl0.y"
                                             {/*puts("param_decl: IDENTIFIER COLON typename COMMA param_decl");*/ yyprocess_param_decl_2("param_decl", yylhs.value, {yystack_[4].value, yystack_[3].value, yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1485 "pl0.tab.cc"
    break;

  case 41:
#line 154 "pl0.y"
                                  {/*puts("param_decl: COLON typename COMMA param_decl");*/ yyprocess_param_decl_3("param_decl", yylhs.value, {yystack_[3].value, yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1491 "pl0.tab.cc"
    break;

  case 42:
#line 156 "pl0.y"
                  {/*puts("stmt: assign_stmt");*/ yyprocess_stmt_0("stmt", yylhs.value, {yystack_[0].value}); }
#line 1497 "pl0.tab.cc"
    break;

  case 43:
#line 157 "pl0.y"
            {/*puts("stmt: cond_stmt");*/ yyprocess_stmt_1("stmt", yylhs.value, {yystack_[0].value}); }
#line 1503 "pl0.tab.cc"
    break;

  case 44:
#line 158 "pl0.y"
            {/*puts("stmt: loop_stmt");*/ yyprocess_stmt_2("stmt", yylhs.value, {yystack_[0].value}); }
#line 1509 "pl0.tab.cc"
    break;

  case 45:
#line 159 "pl0.y"
                 {/*puts("stmt: proc_call_stmt");*/ yyprocess_stmt_3("stmt", yylhs.value, {yystack_[0].value}); }
#line 1515 "pl0.tab.cc"
    break;

  case 46:
#line 160 "pl0.y"
             {/*puts("stmt: compl_stmt");*/ yyprocess_stmt_4("stmt", yylhs.value, {yystack_[0].value}); }
#line 1521 "pl0.tab.cc"
    break;

  case 47:
#line 161 "pl0.y"
            {/*puts("stmt: expr_stmt");*/ yyprocess_stmt_5("stmt", yylhs.value, {yystack_[0].value}); }
#line 1527 "pl0.tab.cc"
    break;

  case 48:
#line 162 "pl0.y"
             {/*puts("stmt: empty_stmt");*/ yyprocess_stmt_6("stmt", yylhs.value, {yystack_[0].value}); }
#line 1533 "pl0.tab.cc"
    break;

  case 49:
#line 163 "pl0.y"
             {/*puts("stmt: break_stmt");*/ yyprocess_stmt_7("stmt", yylhs.value, {yystack_[0].value}); }
#line 1539 "pl0.tab.cc"
    break;

  case 50:
#line 165 "pl0.y"
                                   {/*puts("assign_stmt: expr ASSIGN expr SEMI");*/ yyprocess_assign_stmt_0("assign_stmt", yylhs.value, {yystack_[3].value, yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1545 "pl0.tab.cc"
    break;

  case 51:
#line 167 "pl0.y"
                                {/*puts("compl_stmt: begin opt_stmts end");*/ yyprocess_compl_stmt_0("compl_stmt", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1551 "pl0.tab.cc"
    break;

  case 52:
#line 169 "pl0.y"
           {/*puts("opt_stmts: ");*/ yyprocess_opt_stmts_0("opt_stmts", yylhs.value, {}); }
#line 1557 "pl0.tab.cc"
    break;

  case 53:
#line 170 "pl0.y"
        {/*puts("opt_stmts: stmts");*/ yyprocess_opt_stmts_1("opt_stmts", yylhs.value, {yystack_[0].value}); }
#line 1563 "pl0.tab.cc"
    break;

  case 54:
#line 172 "pl0.y"
            {/*puts("stmts: stmt");*/ yyprocess_stmts_0("stmts", yylhs.value, {yystack_[0].value}); }
#line 1569 "pl0.tab.cc"
    break;

  case 55:
#line 173 "pl0.y"
             {/*puts("stmts: stmt stmts");*/ yyprocess_stmts_1("stmts", yylhs.value, {yystack_[1].value, yystack_[0].value}); }
#line 1575 "pl0.tab.cc"
    break;

  case 56:
#line 175 "pl0.y"
                     {/*puts("expr_stmt: expr SEMI");*/ yyprocess_expr_stmt_0("expr_stmt", yylhs.value, {yystack_[1].value, yystack_[0].value}); }
#line 1581 "pl0.tab.cc"
    break;

  case 57:
#line 177 "pl0.y"
                  {/*puts("expr: simple_expr");*/ yyprocess_expr_0("expr", yylhs.value, {yystack_[0].value}); }
#line 1587 "pl0.tab.cc"
    break;

  case 58:
#line 178 "pl0.y"
                 {/*puts("expr: expr PLUS expr");*/ yyprocess_expr_1("expr", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1593 "pl0.tab.cc"
    break;

  case 59:
#line 179 "pl0.y"
                  {/*puts("expr: expr MINUS expr");*/ yyprocess_expr_2("expr", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1599 "pl0.tab.cc"
    break;

  case 60:
#line 180 "pl0.y"
                 {/*puts("expr: expr STAR expr");*/ yyprocess_expr_3("expr", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1605 "pl0.tab.cc"
    break;

  case 61:
#line 181 "pl0.y"
                  {/*puts("expr: expr SLASH expr");*/ yyprocess_expr_4("expr", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1611 "pl0.tab.cc"
    break;

  case 62:
#line 182 "pl0.y"
                {/*puts("expr: expr div expr");*/ yyprocess_expr_5("expr", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1617 "pl0.tab.cc"
    break;

  case 63:
#line 183 "pl0.y"
                 {/*puts("expr: expr MOD2 expr");*/ yyprocess_expr_6("expr", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1623 "pl0.tab.cc"
    break;

  case 64:
#line 184 "pl0.y"
                {/*puts("expr: expr and expr");*/ yyprocess_expr_7("expr", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1629 "pl0.tab.cc"
    break;

  case 65:
#line 185 "pl0.y"
               {/*puts("expr: expr or expr");*/ yyprocess_expr_8("expr", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1635 "pl0.tab.cc"
    break;

  case 66:
#line 186 "pl0.y"
                  {/*puts("expr: expr EQUAL expr");*/ yyprocess_expr_9("expr", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1641 "pl0.tab.cc"
    break;

  case 67:
#line 187 "pl0.y"
                      {/*puts("expr: expr NOT_EQUAL expr");*/ yyprocess_expr_10("expr", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1647 "pl0.tab.cc"
    break;

  case 68:
#line 188 "pl0.y"
               {/*puts("expr: expr LE expr");*/ yyprocess_expr_11("expr", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1653 "pl0.tab.cc"
    break;

  case 69:
#line 189 "pl0.y"
               {/*puts("expr: expr GE expr");*/ yyprocess_expr_12("expr", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1659 "pl0.tab.cc"
    break;

  case 70:
#line 190 "pl0.y"
               {/*puts("expr: expr LT expr");*/ yyprocess_expr_13("expr", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1665 "pl0.tab.cc"
    break;

  case 71:
#line 191 "pl0.y"
               {/*puts("expr: expr GT expr");*/ yyprocess_expr_14("expr", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1671 "pl0.tab.cc"
    break;

  case 72:
#line 193 "pl0.y"
                        {/*puts("simple_expr: naive_expr");*/ yyprocess_simple_expr_0("simple_expr", yylhs.value, {yystack_[0].value}); }
#line 1677 "pl0.tab.cc"
    break;

  case 73:
#line 194 "pl0.y"
                  {/*puts("simple_expr: not simple_expr");*/ yyprocess_simple_expr_1("simple_expr", yylhs.value, {yystack_[1].value, yystack_[0].value}); }
#line 1683 "pl0.tab.cc"
    break;

  case 74:
#line 195 "pl0.y"
                      {/*puts("simple_expr: POINTER simple_expr");*/ yyprocess_simple_expr_2("simple_expr", yylhs.value, {yystack_[1].value, yystack_[0].value}); }
#line 1689 "pl0.tab.cc"
    break;

  case 75:
#line 196 "pl0.y"
            {/*puts("simple_expr: PLUS expr");*/ yyprocess_simple_expr_3("simple_expr", yylhs.value, {yystack_[1].value, yystack_[0].value}); }
#line 1695 "pl0.tab.cc"
    break;

  case 76:
#line 197 "pl0.y"
             {/*puts("simple_expr: MINUS expr");*/ yyprocess_simple_expr_4("simple_expr", yylhs.value, {yystack_[1].value, yystack_[0].value}); }
#line 1701 "pl0.tab.cc"
    break;

  case 77:
#line 198 "pl0.y"
          {/*puts("simple_expr: AT expr");*/ yyprocess_simple_expr_5("simple_expr", yylhs.value, {yystack_[1].value, yystack_[0].value}); }
#line 1707 "pl0.tab.cc"
    break;

  case 78:
#line 200 "pl0.y"
                      {/*puts("naive_expr: atom_expr");*/ yyprocess_naive_expr_0("naive_expr", yylhs.value, {yystack_[0].value}); }
#line 1713 "pl0.tab.cc"
    break;

  case 79:
#line 201 "pl0.y"
                                          {/*puts("naive_expr: naive_expr LPAREN opt_param_list RPAREN");*/ yyprocess_naive_expr_1("naive_expr", yylhs.value, {yystack_[3].value, yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1719 "pl0.tab.cc"
    break;

  case 80:
#line 202 "pl0.y"
                                {/*puts("naive_expr: naive_expr LBRACK expr RBRACK");*/ yyprocess_naive_expr_2("naive_expr", yylhs.value, {yystack_[3].value, yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1725 "pl0.tab.cc"
    break;

  case 81:
#line 204 "pl0.y"
                         {/*puts("atom_expr: const_literal");*/ yyprocess_atom_expr_0("atom_expr", yylhs.value, {yystack_[0].value}); }
#line 1731 "pl0.tab.cc"
    break;

  case 82:
#line 205 "pl0.y"
                     {/*puts("atom_expr: LPAREN expr RPAREN");*/ yyprocess_atom_expr_1("atom_expr", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1737 "pl0.tab.cc"
    break;

  case 83:
#line 206 "pl0.y"
             {/*puts("atom_expr: IDENTIFIER");*/ yyprocess_atom_expr_2("atom_expr", yylhs.value, {yystack_[0].value}); }
#line 1743 "pl0.tab.cc"
    break;

  case 84:
#line 208 "pl0.y"
                {/*puts("opt_param_list: ");*/ yyprocess_opt_param_list_0("opt_param_list", yylhs.value, {}); }
#line 1749 "pl0.tab.cc"
    break;

  case 85:
#line 209 "pl0.y"
             {/*puts("opt_param_list: param_list");*/ yyprocess_opt_param_list_1("opt_param_list", yylhs.value, {yystack_[0].value}); }
#line 1755 "pl0.tab.cc"
    break;

  case 86:
#line 211 "pl0.y"
                 {/*puts("param_list: expr");*/ yyprocess_param_list_0("param_list", yylhs.value, {yystack_[0].value}); }
#line 1761 "pl0.tab.cc"
    break;

  case 87:
#line 212 "pl0.y"
                        {/*puts("param_list: expr COMMA param_list");*/ yyprocess_param_list_1("param_list", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1767 "pl0.tab.cc"
    break;

  case 88:
#line 214 "pl0.y"
                             {/*puts("cond_stmt: if expr then stmt");*/ yyprocess_cond_stmt_0("cond_stmt", yylhs.value, {yystack_[3].value, yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1773 "pl0.tab.cc"
    break;

  case 89:
#line 215 "pl0.y"
                              {/*puts("cond_stmt: if expr then stmt else stmt");*/ yyprocess_cond_stmt_1("cond_stmt", yylhs.value, {yystack_[5].value, yystack_[4].value, yystack_[3].value, yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1779 "pl0.tab.cc"
    break;

  case 90:
#line 217 "pl0.y"
                                     {/*puts("proc_call_stmt: call IDENTIFIER SEMI");*/ yyprocess_proc_call_stmt_0("proc_call_stmt", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1785 "pl0.tab.cc"
    break;

  case 91:
#line 219 "pl0.y"
                      {/*puts("loop_stmt: while_stmt");*/ yyprocess_loop_stmt_0("loop_stmt", yylhs.value, {yystack_[0].value}); }
#line 1791 "pl0.tab.cc"
    break;

  case 92:
#line 220 "pl0.y"
           {/*puts("loop_stmt: for_stmt");*/ yyprocess_loop_stmt_1("loop_stmt", yylhs.value, {yystack_[0].value}); }
#line 1797 "pl0.tab.cc"
    break;

  case 93:
#line 221 "pl0.y"
              {/*puts("loop_stmt: repeat_stmt");*/ yyprocess_loop_stmt_2("loop_stmt", yylhs.value, {yystack_[0].value}); }
#line 1803 "pl0.tab.cc"
    break;

  case 94:
#line 223 "pl0.y"
                                              {/*puts("repeat_stmt: repeat opt_stmts until expr SEMI");*/ yyprocess_repeat_stmt_0("repeat_stmt", yylhs.value, {yystack_[4].value, yystack_[3].value, yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1809 "pl0.tab.cc"
    break;

  case 95:
#line 225 "pl0.y"
                               {/*puts("while_stmt: while expr do stmt");*/ yyprocess_while_stmt_0("while_stmt", yylhs.value, {yystack_[3].value, yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1815 "pl0.tab.cc"
    break;

  case 96:
#line 227 "pl0.y"
                                                     {/*puts("for_stmt: for IDENTIFIER ASSIGN expr to expr do stmt");*/ yyprocess_for_stmt_0("for_stmt", yylhs.value, {yystack_[7].value, yystack_[6].value, yystack_[5].value, yystack_[4].value, yystack_[3].value, yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1821 "pl0.tab.cc"
    break;

  case 97:
#line 228 "pl0.y"
                                                 {/*puts("for_stmt: for IDENTIFIER ASSIGN expr downto expr do stmt");*/ yyprocess_for_stmt_1("for_stmt", yylhs.value, {yystack_[7].value, yystack_[6].value, yystack_[5].value, yystack_[4].value, yystack_[3].value, yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1827 "pl0.tab.cc"
    break;

  case 98:
#line 230 "pl0.y"
                 {/*puts("empty_stmt: SEMI");*/ yyprocess_empty_stmt_0("empty_stmt", yylhs.value, {yystack_[0].value}); }
#line 1833 "pl0.tab.cc"
    break;

  case 99:
#line 232 "pl0.y"
                       {/*puts("break_stmt: break SEMI");*/ yyprocess_break_stmt_0("break_stmt", yylhs.value, {yystack_[1].value, yystack_[0].value}); }
#line 1839 "pl0.tab.cc"
    break;

  case 100:
#line 233 "pl0.y"
                     {/*puts("break_stmt: break NUM_INT SEMI");*/ yyprocess_break_stmt_1("break_stmt", yylhs.value, {yystack_[2].value, yystack_[1].value, yystack_[0].value}); }
#line 1845 "pl0.tab.cc"
    break;


#line 1849 "pl0.tab.cc"

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
      YY_STACK_PRINT ();

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
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
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
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = static_cast<state_type> (yyn);
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
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const short parser::yypact_ninf_ = -146;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
      -3,   -34,    38,    -9,    19,     9,    26,  -146,    -2,    21,
      16,  -146,    19,   -12,  -146,  -146,    41,    43,    25,    28,
      82,  -146,    16,    -3,    16,    -3,  -146,  -146,  -146,  -146,
      45,    21,   -18,  -146,    50,    86,    82,    86,    86,    82,
      30,    32,   -25,  -146,    86,    86,    86,    86,    86,  -146,
    -146,  -146,  -146,  -146,  -146,   119,  -146,   -17,  -146,  -146,
    -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,
    -146,   -34,  -146,   -18,   -19,  -146,   -24,   -30,  -146,    82,
      74,  -146,   185,   229,    77,    55,    68,  -146,    72,  -146,
      24,    24,   243,  -146,    86,    86,    86,  -146,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,  -146,  -146,   -18,    69,   -21,    73,  -146,  -146,
      49,    69,    87,  -146,  -146,    82,    82,    86,    86,  -146,
    -146,  -146,  -146,   445,   445,    24,    24,     2,   286,     2,
       2,     2,     2,     2,  -146,  -146,  -146,   308,    91,  -146,
     330,   -14,   -18,  -146,    92,    53,    93,   113,  -146,   363,
     171,  -146,    86,  -146,  -146,   -30,   -10,   -18,  -146,    75,
     -18,    82,  -146,    86,    86,  -146,  -146,   -30,    88,    85,
      88,  -146,   387,   431,  -146,  -146,    82,    82,  -146,  -146
  };

  const signed char
  parser::yydefact_[] =
  {
       4,     0,     0,     0,    11,     0,     0,     1,     0,     0,
      25,    12,    13,     0,     5,     2,    16,     0,     0,     0,
       0,    26,    28,     4,    27,     4,    14,     8,     9,    10,
       6,     0,     0,    35,     0,     0,    52,     0,     0,    52,
       0,     0,     0,    98,     0,     0,     0,     0,     0,    83,
      81,     3,    42,    46,    47,     0,    57,    72,    78,    43,
      45,    44,    93,    91,    92,    48,    49,    30,    31,    29,
      34,     0,    17,     0,    36,    18,     0,    36,    73,    54,
       0,    53,     0,     0,     0,     0,     0,    99,     0,    74,
      75,    76,     0,    77,     0,     0,     0,    56,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      84,     0,     7,    19,     0,    18,     0,     0,    37,    15,
       0,     0,     0,    55,    51,     0,     0,     0,     0,    90,
     100,    82,    62,    64,    65,    58,    59,    66,     0,    67,
      70,    68,    69,    71,    60,    61,    63,    86,     0,    85,
       0,    39,     0,    22,    23,     0,    33,    88,    95,     0,
       0,    50,     0,    79,    80,     0,    38,     0,    20,     0,
       0,     0,    94,     0,     0,    87,    41,     0,    24,     0,
      32,    89,     0,     0,    40,    21,     0,     0,    96,    97
  };

  const short
  parser::yypgoto_[] =
  {
    -146,  -146,    27,  -146,    65,   126,  -146,   136,  -146,   118,
     -70,  -146,  -146,    29,  -146,  -146,  -146,  -146,    78,  -145,
     -20,  -146,  -146,   115,    79,  -146,   -36,   -13,  -146,  -146,
    -146,    -5,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     2,     3,     4,     6,    50,    10,    11,    12,    17,
      76,   168,    20,    21,    22,    23,    24,    25,   117,   118,
      79,    52,    53,    80,    81,    54,    55,    56,    57,    58,
     148,   149,    59,    60,    61,    62,    63,    64,    65,    66
  };

  const unsigned char
  parser::yytable_[] =
  {
      51,    82,    83,   113,   116,    94,    87,   119,   114,    90,
      91,    92,    93,    73,    73,   153,    74,    74,   110,   114,
     176,     1,    78,   120,     5,   165,   120,    94,   121,   177,
     111,    89,   184,   120,    88,    98,    99,   120,     7,   115,
      75,    18,     8,    19,   151,     9,    13,    27,    28,    29,
      68,    67,    70,    69,   107,   108,   109,    14,   132,   133,
     134,    15,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   150,   107,   108,   109,    16,
      31,    32,   166,    33,    71,    77,    34,   124,    85,    35,
      86,   159,   160,    35,    36,   128,    37,   178,   127,   129,
     180,    38,    39,   130,    40,   157,   158,   152,   155,   154,
     169,    41,    42,    43,    44,    45,    46,    47,    44,    45,
      46,    47,    94,   156,    95,    96,   147,   163,    48,   171,
     167,   170,    48,   185,   179,   120,   112,   182,   183,    30,
      49,    27,    28,    29,    49,    27,    28,    29,    26,    72,
      97,   181,    98,    99,    84,   122,   100,   175,   123,   101,
     102,   103,   104,   105,   106,     0,   188,   189,     0,     0,
       0,   107,   108,   109,    94,     0,    95,    96,     0,   173,
     174,     0,     0,     0,     0,     0,     0,     0,    94,     0,
      95,    96,     0,     0,     0,     0,     0,     0,     0,     0,
     125,     0,     0,     0,    98,    99,     0,     0,   100,     0,
       0,     0,   102,   103,   104,   105,   106,     0,    98,    99,
       0,     0,   100,   107,   108,   109,   102,   103,   104,   105,
     106,     0,    94,     0,    95,    96,     0,   107,   108,   109,
     126,     0,     0,     0,     0,     0,    94,     0,    95,    96,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    98,    99,     0,     0,   100,     0,     0,     0,
     102,   103,   104,   105,   106,     0,    98,    99,     0,   131,
     100,   107,   108,   109,   102,   103,   104,   105,   106,    94,
       0,    95,    96,     0,     0,   107,   108,   109,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    94,     0,    95,    96,     0,     0,   161,     0,    98,
      99,     0,     0,   100,     0,     0,     0,   102,   103,   104,
     105,   106,     0,    94,     0,    95,    96,     0,   107,   108,
     109,    98,    99,     0,     0,   100,     0,   162,     0,   102,
     103,   104,   105,   106,     0,     0,     0,     0,     0,     0,
     107,   108,   109,    98,    99,     0,    94,   100,    95,    96,
       0,   102,   103,   104,   105,   106,     0,     0,   164,     0,
       0,     0,   107,   108,   109,     0,     0,     0,     0,     0,
      94,     0,    95,    96,   172,     0,    98,    99,   186,     0,
     100,     0,     0,     0,   102,   103,   104,   105,   106,     0,
       0,     0,     0,     0,     0,   107,   108,   109,     0,     0,
      98,    99,     0,     0,   100,     0,     0,     0,   102,   103,
     104,   105,   106,     0,    94,     0,    95,    96,     0,   107,
     108,   109,   187,     0,     0,     0,     0,     0,    94,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    98,    99,     0,     0,   100,     0,
       0,     0,   102,   103,   104,   105,   106,     0,    98,    99,
       0,     0,   100,   107,   108,   109,   102,   103,   104,   105,
     106,     0,     0,     0,     0,     0,     0,   107,   108,   109
  };

  const short
  parser::yycheck_[] =
  {
      20,    37,    38,    73,    74,     3,    31,    31,    38,    45,
      46,    47,    48,    32,    32,    36,    35,    35,    35,    38,
     165,    24,    35,    47,    58,    39,    47,     3,    58,    39,
      47,    44,   177,    47,    59,    33,    34,    47,     0,    58,
      58,    25,    51,    27,   114,    26,    37,    59,    60,    61,
      23,    22,    25,    24,    52,    53,    54,    31,    94,    95,
      96,    63,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,    52,    53,    54,    58,
      39,    38,   152,    58,    39,    35,    58,    13,    58,     7,
      58,   127,   128,     7,    12,    40,    14,   167,    21,    31,
     170,    19,    20,    31,    22,   125,   126,    38,    59,    36,
      57,    29,    30,    31,    32,    33,    34,    35,    32,    33,
      34,    35,     3,    36,     5,     6,   162,    36,    46,    16,
      38,    38,    46,    48,    59,    47,    71,   173,   174,    13,
      58,    59,    60,    61,    58,    59,    60,    61,    12,    31,
      31,   171,    33,    34,    39,    77,    37,   162,    79,    40,
      41,    42,    43,    44,    45,    -1,   186,   187,    -1,    -1,
      -1,    52,    53,    54,     3,    -1,     5,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,
       5,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      15,    -1,    -1,    -1,    33,    34,    -1,    -1,    37,    -1,
      -1,    -1,    41,    42,    43,    44,    45,    -1,    33,    34,
      -1,    -1,    37,    52,    53,    54,    41,    42,    43,    44,
      45,    -1,     3,    -1,     5,     6,    -1,    52,    53,    54,
      11,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    -1,    -1,    37,    -1,    -1,    -1,
      41,    42,    43,    44,    45,    -1,    33,    34,    -1,    36,
      37,    52,    53,    54,    41,    42,    43,    44,    45,     3,
      -1,     5,     6,    -1,    -1,    52,    53,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    -1,     5,     6,    -1,    -1,    31,    -1,    33,
      34,    -1,    -1,    37,    -1,    -1,    -1,    41,    42,    43,
      44,    45,    -1,     3,    -1,     5,     6,    -1,    52,    53,
      54,    33,    34,    -1,    -1,    37,    -1,    39,    -1,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    53,    54,    33,    34,    -1,     3,    37,     5,     6,
      -1,    41,    42,    43,    44,    45,    -1,    -1,    48,    -1,
      -1,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,
       3,    -1,     5,     6,    31,    -1,    33,    34,    11,    -1,
      37,    -1,    -1,    -1,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,    -1,
      33,    34,    -1,    -1,    37,    -1,    -1,    -1,    41,    42,
      43,    44,    45,    -1,     3,    -1,     5,     6,    -1,    52,
      53,    54,    11,    -1,    -1,    -1,    -1,    -1,     3,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    37,    -1,
      -1,    -1,    41,    42,    43,    44,    45,    -1,    33,    34,
      -1,    -1,    37,    52,    53,    54,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54
  };

  const signed char
  parser::yystos_[] =
  {
       0,    24,    66,    67,    68,    58,    69,     0,    51,    26,
      71,    72,    73,    37,    31,    63,    58,    74,    25,    27,
      77,    78,    79,    80,    81,    82,    72,    59,    60,    61,
      70,    39,    38,    58,    58,     7,    12,    14,    19,    20,
      22,    29,    30,    31,    32,    33,    34,    35,    46,    58,
      70,    85,    86,    87,    90,    91,    92,    93,    94,    97,
      98,    99,   100,   101,   102,   103,   104,    78,    67,    78,
      67,    39,    74,    32,    35,    58,    75,    35,    92,    85,
      88,    89,    91,    91,    88,    58,    58,    31,    59,    92,
      91,    91,    91,    91,     3,     5,     6,    31,    33,    34,
      37,    40,    41,    42,    43,    44,    45,    52,    53,    54,
      35,    47,    69,    75,    38,    58,    75,    83,    84,    31,
      47,    58,    83,    89,    13,    15,    11,    21,    40,    31,
      31,    36,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    95,    96,
      91,    75,    38,    36,    36,    59,    36,    85,    85,    91,
      91,    31,    39,    36,    48,    39,    75,    38,    76,    57,
      38,    16,    31,     8,     9,    96,    84,    39,    75,    59,
      75,    85,    91,    91,    84,    48,    11,    11,    85,    85
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    65,    66,    67,    68,    68,    69,    69,    70,    70,
      70,    71,    71,    72,    72,    73,    74,    74,    75,    75,
      75,    75,    75,    76,    76,    77,    77,    78,    78,    78,
      78,    79,    80,    80,    81,    82,    83,    83,    84,    84,
      84,    84,    85,    85,    85,    85,    85,    85,    85,    85,
      86,    87,    88,    88,    89,    89,    90,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    92,    92,    92,    92,    92,    92,    93,    93,
      93,    94,    94,    94,    95,    95,    96,    96,    97,    97,
      98,    99,    99,    99,   100,   101,   102,   102,   103,   104,
     104
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     3,     4,     0,     3,     3,     5,     1,     1,
       1,     0,     1,     1,     2,     5,     1,     3,     1,     2,
       4,     6,     3,     0,     2,     0,     1,     1,     1,     2,
       2,     2,     7,     5,     2,     2,     0,     1,     3,     2,
       5,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     3,     0,     1,     1,     2,     2,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     2,     2,     2,     2,     2,     1,     4,
       4,     1,     3,     1,     0,     1,     1,     3,     4,     6,
       3,     1,     1,     1,     5,     4,     8,     8,     1,     2,
       3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "$end", "error", "$undefined", "div", "mod", "and", "or", "not", "to",
  "downto", "with", "do", "begin", "end", "if", "then", "else", "case",
  "of", "while", "repeat", "until", "for", "array", "const", "procedure",
  "var", "function", "goto", "call", "break", "SEMI", "POINTER", "PLUS",
  "MINUS", "LPAREN", "RPAREN", "EQUAL", "COLON", "COMMA", "ASSIGN",
  "NOT_EQUAL", "LT", "LE", "GE", "GT", "AT", "LBRACK", "RBRACK", "LBRACK2",
  "RBRACK2", "DOT", "STAR", "SLASH", "MOD2", "AND", "OR", "DOTDOT",
  "IDENTIFIER", "NUM_INT", "NUM_REAL", "STRING", "UNKNOWN", "EOF",
  "typename_pointer", "$accept", "program", "subprogram", "opt_const_decl",
  "const_decl", "const_literal", "opt_val_decl", "var_name_decls",
  "var_name_decl", "var_name_list", "typename", "opt_ret", "opt_proc_decl",
  "proc_decls", "func_decl", "func_head", "proc_decl", "proc_head",
  "opt_param_decl", "param_decl", "stmt", "assign_stmt", "compl_stmt",
  "opt_stmts", "stmts", "expr_stmt", "expr", "simple_expr", "naive_expr",
  "atom_expr", "opt_param_list", "param_list", "cond_stmt",
  "proc_call_stmt", "loop_stmt", "repeat_stmt", "while_stmt", "for_stmt",
  "empty_stmt", "break_stmt", YY_NULLPTR
  };


  const unsigned char
  parser::yyrline_[] =
  {
       0,    98,    98,    99,   101,   102,   104,   105,   107,   108,
     109,   111,   112,   114,   115,   117,   119,   120,   122,   123,
     124,   125,   126,   128,   129,   131,   132,   134,   135,   136,
     137,   139,   141,   142,   144,   146,   148,   149,   151,   152,
     153,   154,   156,   157,   158,   159,   160,   161,   162,   163,
     165,   167,   169,   170,   172,   173,   175,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   193,   194,   195,   196,   197,   198,   200,   201,
     202,   204,   205,   206,   208,   209,   211,   212,   214,   215,
     217,   219,   220,   221,   223,   225,   227,   228,   230,   232,
     233
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
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

  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
    };
    const int user_token_number_max_ = 319;

    if (t <= 0)
      return yyeof_;
    else if (t <= user_token_number_max_)
      return translate_table[t];
    else
      return yy_undef_token_;
  }

} // yy
#line 2387 "pl0.tab.cc"

#line 236 "pl0.y"



#include "lex.yy.cc"

int yylex(YYSTYPE* yylval)
{
  ::yylval = yylval;
  static FlexLexer *lexer = new yyFlexLexer;
  int ret = lexer->yylex();
  // std::cout << typeid(**yylval).name() << std::endl;
  return ret;
}

namespace yy
{
  // Report an error to the user.
  auto parser::error (const std::string& msg) -> void
  {
    std::cerr << '(' << linum << ", " << column << ") " << msg << '\n';
  }
}

void naive(YYSTYPE, char*);

int main(int argc, char **argv)
{
	try 
	{
		yy::parser parse;
		int ret = parse();

		if (result != nullptr)
		{
			// std::cerr << html_header << result->toJSON() << html_footer << std::endl;
			naive(result, argv[1]);
		}
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
}

