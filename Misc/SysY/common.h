/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BREAK = 258,
    COMMENT = 259,
    CONST = 260,
    CONTINUE = 261,
    ELSE = 262,
    IF = 263,
    INT = 264,
    RETURN = 265,
    VOID = 266,
    WHILE = 267,
    INTCONST = 268,
    IDENTIFIER = 269,
    OP_L_AND = 270,
    OP_L_OR = 271,
    OP_N_LE = 272,
    OP_N_GE = 273,
    OP_N_EQ = 274,
    OP_N_NE = 275,
    ERROR = 276,
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

#ifndef COMMON
#define COMMON

// extern YYSTYPE yylval;
YYSTYPE yylval;

typedef struct
{
    int type;
    int val;
} element;

#endif