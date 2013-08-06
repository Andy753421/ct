#define _GNU_SOURCE
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <printf.h>

/* Misc */
void ct_print_header(const char *content_type, const char *charset)
{
	if (!content_type) content_type = "text/html";
	if (!charset)      charset      = "UTF-8";
	printf("Content-Type: %s; charset=%s\n\n",
			content_type, charset);
}

/* Environment */
const gchar *ct_get_path_info(void)
{
	return g_getenv("PATH_INFO") ?: "";
}

const gchar *ct_get_query_string(void)
{
	return g_getenv("QUERY_STRING") ?: "";
}

const GHashTable *ct_get_query(void)
{
	const gchar *query_string = g_getenv("QUERY_STRING");
	GHashTable *query = g_hash_table_new(g_str_hash, g_str_equal);
	if (query_string) {
		gchar **vars = g_strsplit(query_string, "&", -1);
		for (int i = 0; vars[i]; i++) {
			gchar **parts = g_strsplit(vars[i], "=", 2);
			gchar *lhs = parts[0]             ? parts[0] : "";
			gchar *rhs = parts[0] && parts[1] ? parts[1] : "";
			g_hash_table_insert(query, lhs, rhs);
			g_free(parts); // keep lhs/rhs
		}
		g_strfreev(vars);
	}
	return query;
}

/* Markup escaping */
static int printf_markup(FILE *stream,
		const struct printf_info *info,
		const void *const *args)
{
	int len = 0;
	const char *str = *(const char **)args[0];
	for (int i = 0; str[i]; i++)
		switch (str[i]) {
		case '"':  len += fputs("&#39;",  stream); break;
		case '\'': len += fputs("&quot;", stream); break;
		case '&':  len += fputs("&amp;",  stream); break;
		case '<':  len += fputs("&lt;",   stream); break;
		case '>':  len += fputs("&gt;",   stream); break;
		default:   len += fputc(str[i],   stream); break;
		}
	return len;
}

static int printf_markup_arginfo(const struct printf_info *info,
		size_t n, int *argtypes, int *size)
{
	argtypes[0] = PA_STRING;
	return 1;
}

void ct_use_escape()
{
	register_printf_specifier('M', printf_markup, printf_markup_arginfo);
}

#ifdef TEST
int main(void)
{
	ct_use_escape();
	printf("%M\n", "<Hello, World>");
	printf("%M\n", "<Hello, World>");
	printf("%M\n", "<Hello, World>");
	return 0;
}
#endif
