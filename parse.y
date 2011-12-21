%{
#define YYSTYPE char *
#include <stdio.h>
#include <glib.h>
extern FILE *yyin;
int yylex(void);
void yyerror(gpointer node, char const *s);
extern int yylineno;
static const char *name;
static GList *code;
static GList *data;
%}
%error-verbose
%parse-param {gpointer root};
%token START END DATA FMT OUT
%%

input : all | all input ;

all   : data | code | print ;

data  : DATA {
	static int i = 0;
	data = g_list_prepend(data, g_strdup_printf(
		"#line %d \"%s\"\n"
		"static char data%d[] = \"%s\";\n",
		yylineno, name, i, g_strescape($1, "")));
	code = g_list_prepend(code, g_strdup_printf(
		"#line %d \"%s\"\n"
		"fwrite(data%d, sizeof(data%d)-1, 1, stdout);\n",
		yylineno, name, i, i));
	i++;
};

code  : START DATA END {
	code = g_list_prepend(code, g_strdup_printf("%s\n", $2));
};

print : START FMT DATA END {
	code = g_list_prepend(code, g_strdup_printf("printf(%s);\n", $3));
};

print : START OUT DATA END {
	code = g_list_prepend(code, g_strdup_printf("printf(\"%%s\", %s);\n", $3));
};

%%
gpointer parse(FILE *input, const char *_name,
		GList **_data, GList **_code)
{
	yyin = input;
	name = _name;
	yyparse(NULL);
	*_data = data;
	*_code = code;
	return NULL;
}
void yyerror(gpointer root, char const *s)
{
	g_error("[%s]\n", s);
}
