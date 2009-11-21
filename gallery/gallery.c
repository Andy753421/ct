#include <glib.h>
#include "html.h"

const gchar *query_string;

void ct_init()
{
	query_string = g_getenv("QUERY_STRING");
}

GList *read_dir(gchar *dirname)
{
	GDir *dir = g_dir_open(dirname, 0, NULL);
	const gchar *name = NULL;
	GList *images = NULL;
	while ((name = g_dir_read_name(dir)))
		images = g_list_prepend(images, (gchar*)name);
	g_dir_close(dir);
	return images;
}

int main()
{
	ct_init();

	header();
	g_print("\n");

	if (query_string == NULL)
		frame_index();
	else if (g_str_equal(query_string, "noframe"))
		frame_nav(TRUE, read_dir("images"));
	else if (g_str_equal(query_string, "nav"))
		frame_nav(FALSE, read_dir("images"));
	else if (g_str_equal(query_string, "head"))
		frame_head();
	else if (g_str_equal(query_string, "content"))
		frame_content();
	else
		frame_index();
}
