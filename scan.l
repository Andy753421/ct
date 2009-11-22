%{
#define YYSTYPE char *
#include <glib.h>
#include "parse.h"
#define debug(arg) // g_message("scan: " arg, yytext);
%}
%option noyywrap
%option nounput
%option noinput
/* %option nodebug */
START [ \t]*<%
END   [ \t]*%>[ \t]*
DATA  ([^<\n]|<[^%])*\n*
CODE  [ \t\n]([^%\n]|%[^>])*\n*
%s IN FMT
%%
[[:space:]]*\n   { debug("NL    [%s]"); }
<INITIAL>{START} { debug("START [%s]"); yylval = g_strdup(yytext); BEGIN(IN);      return START; }
<INITIAL>{DATA}  { debug("DATA  [%s]"); yylval = g_strdup(yytext);                 return DATA;  }
<IN>{END}        { debug("END   [%s]"); yylval = g_strdup(yytext); BEGIN(INITIAL); return END;   }
<IN>=            { debug("OUT   [%s]"); yylval = g_strdup(yytext);                 return OUT;   }
<IN>{CODE}       { debug("CODE  [%s]"); yylval = g_strdup(yytext);                 return DATA;  }
%%
