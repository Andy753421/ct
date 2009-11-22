#include <glib.h>
#include <glib/gstdio.h>
#include "html.h"

void resize(gchar *orig, gchar *thumb)
{
	gchar *argv[] = {"convert", "-resize", "200x200", orig, thumb, NULL};
	/* god damn glib */
	g_spawn_sync(NULL, argv, NULL, G_SPAWN_SEARCH_PATH,
		NULL, NULL, NULL, NULL, NULL, NULL);
}

GList *gen_thumbs(GList *images)
{
	if (!g_file_test("thumbs", G_FILE_TEST_EXISTS))
		g_mkdir("thumbs", 0644);
	if (!g_file_test("images", G_FILE_TEST_EXISTS))
		g_mkdir("images", 0644);
	for (GList *cur = images; cur; cur = cur->next) {
		gchar *name = cur->data;
		gchar *thumb = g_strconcat("thumbs/", name, NULL);
		gchar *image = g_strconcat("images/", name, NULL);
		if (!g_file_test(thumb, G_FILE_TEST_EXISTS))
			resize(image, thumb);
		g_free(thumb);
		g_free(image);
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
	return images;
}

int main()
{
	header();
	g_print("\n");

	const gchar *query_string = g_getenv("QUERY_STRING");
	if (query_string == NULL)
		frame_index();
	else if (g_str_equal(query_string, "noframe"))
		frame_nav(TRUE, gen_thumbs(read_dir("images")));
	else if (g_str_equal(query_string, "nav"))
		frame_nav(FALSE, gen_thumbs(read_dir("images")));
	else if (g_str_equal(query_string, "head"))
		frame_head();
	else if (g_str_equal(query_string, "content"))
		frame_content();
	else
		frame_index();
}
