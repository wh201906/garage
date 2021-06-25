/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BREAK = 258,
    CONST = 259,
    CONTINUE = 260,
    ELSE = 261,
    IF = 262,
    INT = 263,
    RETURN = 264,
    VOID = 265,
    WHILE = 266,
    INTCONST = 267,
    IDENTIFIER = 268,
    OP_L_AND = 269,
    OP_L_OR = 270,
    OP_N_LE = 271,
    OP_N_GE = 272,
    OP_N_EQ = 273,
    OP_N_NE = 274
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


// extern YYSTYPE yylval;
YYSTYPE yylval;

typedef struct
{
    int type;
    int val;
} element;