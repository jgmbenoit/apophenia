//db.h		Copyright (c) 2005--2007 by Ben Klemens.  Licensed under the modified GNU GPL v2; see COPYING and COPYING2.  
#ifndef apop_db_included
#define apop_db_included
#include "types.h"
#include "variadic.h"
#include "asst.h"
#include <gsl/gsl_matrix.h>
#define ERRCHECK {if (err!=NULL) {printf("%s\n",err);  return 0;}}

#undef __BEGIN_DECLS    /* extern "C" stuff cut 'n' pasted from the GSL. */
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif
__BEGIN_DECLS

//From the GNU's vasprintf suite:
extern int asprintf (char **result, const char *format, ...);

APOP_VAR_DECLARE int apop_table_exists(char *name, char remove);

void apop_db_rng_init(int seed);

int apop_db_open(char *filename);
APOP_VAR_DECLARE int apop_db_close(char vacuum);

int apop_query(const char *q, ...) __attribute__ ((format (printf,1,2)));
gsl_matrix * apop_query_to_matrix(const char * fmt, ...) __attribute__ ((format (printf,1,2)));
apop_data * apop_query_to_text(const char * fmt, ...) __attribute__ ((format (printf,1,2)));
apop_data * apop_query_to_data(const char * fmt, ...) __attribute__ ((format (printf,1,2)));
apop_data * apop_query_to_mixed_data(const char *typelist, const char * fmt, ...) __attribute__ ((format (printf,2,3)));
gsl_vector * apop_query_to_vector(const char * fmt, ...) __attribute__ ((format (printf,1,2)));
double apop_query_to_float(const char * fmt, ...) __attribute__ ((format (printf,1,2)));
int apop_system(const char *fmt, ...) __attribute__ ((format (printf,1,2)));

int apop_matrix_to_db(gsl_matrix *data,char *tabname, char **headers);
int apop_data_to_db(apop_data *set, char *tabname);

APOP_VAR_DECLARE void apop_db_merge(char *db_file, char inout);
APOP_VAR_DECLARE void apop_db_merge_table(char *db_file, char *tabname, char inout);

double apop_db_t_test(char * tab1, char *col1, char *tab2, char *col2);
double apop_db_paired_t_test(char * tab1, char *col1, char *col2);

__END_DECLS
#endif
