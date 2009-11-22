#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <printf.h>

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

int main(void)
{
	ct_use_escape();
	printf("%M\n", "<Hello, World>");
	printf("%M\n", "<Hello, World>");
	printf("%M\n", "<Hello, World>");
	return 0;
}
