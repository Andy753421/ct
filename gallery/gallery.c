#include <glib.h>
#include <glib/gstdio.h>
#include <ct.h>
#include "html.h"

void resize(gchar *orig, gchar *thumb, gchar *size)
{
	gchar *argv[] = {"convert", "-resize", size, orig, thumb, NULL};
	/* god damn glib */
	g_spawn_sync(NULL, argv, NULL, G_SPAWN_SEARCH_PATH,
		NULL, NULL, NULL, NULL, NULL, NULL);
}

GList *gen_thumbs(GList *images)
{
	if (!g_file_test("large", G_FILE_TEST_EXISTS)) g_mkdir("large", 0775);
	if (!g_file_test("small", G_FILE_TEST_EXISTS)) g_mkdir("small", 0775);
	if (!g_file_test("thumb", G_FILE_TEST_EXISTS)) g_mkdir("thumb", 0775);
	for (GList *cur = images; cur; cur = cur->next) {
		gchar *name = cur->data;
		gchar *large = g_build_filename("large", name, NULL);
		gchar *small = g_build_filename("small", name, NULL);
		gchar *thumb = g_build_filename("thumb", name, NULL);
		if (!g_file_test(thumb, G_FILE_TEST_EXISTS)) {
			resize(large, thumb, "200x200");
			resize(large, small, "800x800");
		}
		g_free(large);
		g_free(small);
		g_free(thumb);
	}
	return images;
}

GList *read_dir(gchar *dirname)
{
	GDir *dir = g_dir_open(dirname, 0, NULL);
	const gchar *name = NULL;
	GList *images = NULL;
	while ((name = g_dir_read_name(dir)))
		images = g_list_prepend(images, g_strdup(name));
	images = g_list_sort(images, (GCompareFunc)g_strcmp0);
	return images;
}

int main()
{
	ct_print_header("text/html", NULL);

	const gchar *path  = ct_get_path_info();
	const gchar *query = ct_get_query_string();

	GList *thumbs = gen_thumbs(read_dir("large"));

	if (!path || g_str_equal(path, "/"))
		frame_index();
	else if (g_str_equal(path, "/head"))
		frame_head();
	else if (g_str_equal(path, "/nav"))
		frame_nav(FALSE, thumbs);
	else if (g_str_equal(path, "/noframe"))
		frame_nav(TRUE, thumbs);
	else if (g_str_equal(path, "/show_small"))
		frame_show("small", "show_large", query);
	else if (g_str_equal(path, "/show_large"))
		frame_show("large", "show_small", query);
}
