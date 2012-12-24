%{
#define YYSTYPE char *
#include <stdio.h>
#include <glib.h>
extern FILE *yyin;
extern int   yylineno;
int yylex(void);
void yyerror(gpointer node, char const *s);
static const char *name = NULL;
static GList *code = NULL;
static GList *data = NULL;
%}
%error-verbose
%parse-param {gpointer root};
%token START END DATA OUT FMT
%%

input : all | all input ;

all   : data | code | out | fmt ;

data  : DATA {
	static int i = 0;
	data = g_list_prepend(data, g_strdup_printf(
		"static char data%d[] = \"%s\";\n",
		i, g_strescape($1, "")));
	code = g_list_prepend(code, g_strdup_printf(
		"fwrite(data%d, sizeof(data%d)-1, 1, stdout);\n",
		i, i));
	i++;
};

code  : START DATA END {
	code = g_list_prepend(code, g_strdup_printf("#line %d \"%s\"\n", yylineno, name));
	code = g_list_prepend(code, g_strdup_printf("%s\n", $2));
};

out : START OUT DATA END {
	code = g_list_prepend(code, g_strdup_printf("printf(\"%%s\", %s);\n", $3));
};

fmt : START FMT DATA END {
	code = g_list_prepend(code, g_strdup_printf("printf(%s);\n", $3));
};

%%
gpointer parse(const char *_name, FILE *_input,
		GList **_data, GList **_code)
{
	name = _name;
	yyin = _input;
	yyparse(NULL);
	*_data = data;
	*_code = code;
	return NULL;
}
void yyerror(gpointer root, char const *s)
{
	g_error("[%s]\n", s);
}
