#ifndef CT_H
#define CT_H

/* Misc */
void ct_print_header(const char *content_type, const char *charset);

/* Environment */
const gchar *ct_get_query_string(void);

const gchar *ct_get_path_info(void);

const GHashTable *ct_get_query(void);

/* Markup escaping */
void ct_use_escape(void);

#endif
