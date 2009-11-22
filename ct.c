#include <stdio.h>
#include <glib.h>

#include "parse.h"

gpointer parse(FILE *input, GList **data, GList **code);

int main(int argc, char **argv)
{
        /* Parse arguments */
        int option_log_level = 7;
        GOptionEntry entries[] = {
                {"debug", 'd', 0, G_OPTION_ARG_INT,  &option_log_level,
                        "Change default log level", "[1-7]"},
                {NULL}
        };
        GOptionContext *context = g_option_context_new("infile");
        g_option_context_add_main_entries(context, entries, NULL);
        g_option_context_parse(context, &argc, &argv, NULL);

        FILE *input = stdin;
        for (int i = 1; i < argc; i++)
                if (g_str_has_suffix(argv[i], ".ct"))
                        input = fopen(argv[i], "r");

        /* Start compiling */
	GList *data = NULL;
	GList *code = NULL;
        parse(input, &data, &code);
	data = g_list_reverse(data);
	code = g_list_reverse(code);

        g_print("#include <stdio.h>\n");
	g_print("\n");
	for (GList *cur = data; cur; cur = cur->next)
		g_print("%s", cur->data);
        g_print("\n");
	for (GList *cur = code; cur; cur = cur->next)
		g_print("%s", cur->data);
}
