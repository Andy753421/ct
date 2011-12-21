#include <stdio.h>
#include <string.h>
#include <glib.h>

#include "parse.h"

gpointer parse(FILE *input, const char *name,
		GList **data, GList **code);

int main(int argc, char **argv)
{
	const char *name = "stdin";
        /* Parse arguments */
        char *option_output = NULL;
        GOptionEntry entries[] = {
                {"output", 'o', 0, G_OPTION_ARG_STRING,  &option_output,
                        "Output file", ""},
                {NULL}
        };
        GOptionContext *context = g_option_context_new("[template]");
        g_option_context_add_main_entries(context, entries, NULL);
        g_option_context_parse(context, &argc, &argv, NULL);

	/* Handle input and output */
	FILE *input = stdin;
	if (argv[1] && !g_str_equal(input, "-")) {
		name  = argv[1];
		input = fopen(argv[1], "r");
	}
	if (!input)
		g_error("invalid input file");

	FILE *output = stdout;
	if (option_output && !g_str_equal(option_output, "-"))
		output = fopen(option_output, "w");
	else if (input != stdin && option_output == NULL) {
		char *outf = g_strdup(argv[1]);
		outf[strlen(outf)-1] = '\0';
		output = fopen(outf, "w");
		g_free(outf);
	}
	if (!output)
		g_error("invalid output file");

	/* Start compiling */
	GList *data = NULL;
	GList *code = NULL;
	parse(input, name, &data, &code);
	data = g_list_reverse(data);
	code = g_list_reverse(code);

	fprintf(output, "#include <stdio.h>\n");
	fprintf(output, "\n");
	for (GList *cur = data; cur; cur = cur->next)
		fprintf(output, "%s", (gchar *)cur->data);
	fprintf(output, "\n");
	for (GList *cur = code; cur; cur = cur->next)
		fprintf(output, "%s", (gchar *)cur->data);

	fclose(input);
	fclose(output);
}
