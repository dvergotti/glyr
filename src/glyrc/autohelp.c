#include <string.h>
#include "autohelp.h"

#include "../../lib/stringlib.h"

/* Copied from lib/stringlib.c - more details there */
gsize levenshtein_strcmp(const gchar * s, const gchar * t)
{
 	 /* Get strlen */
    int n = (s) ? strlen(s)+1 : 0;
    int m = (t) ? strlen(t)+1 : 0;

    /* Nothing to compute really */
    if (n == 0) return m;
    if (m == 0) return n;

    /* String matrix */
    int d[n][m];
    int i,j;

    /* Init first row|column to 0...n|m */
    for (i = 0; i < n; i++) d[i][0] = i;
    for (j = 0; j < m; j++) d[0][j] = j;

    for (i = 1; i < n; i++)
    {
        /* Current char in string s */
        char cats = s[i-1];

        for (j = 1; j < m; j++)
        {
            /* Do -1 only once */
            int jm1 = j-1,
                im1 = i-1;

            /* a = above cell, b = left cell, c = left above cell */
            int a = d[im1][j] + 1,
                b = d[i][jm1] + 1,
                c = d[im1][jm1] + (t[jm1] != cats);

            /* Now compute the minimum of a,b,c and set MIN(a,b,c) to cell d[i][j] */
 				d[i][j] = (a < b) ? MIN(a,c) : MIN(b,c);
        }
    }

    /* The result is stored in the very right down cell */
    return d[n-1][m-1];
}

/* ------------------------------------------------------------- */

gsize levenshtein_strcasecmp(const gchar * string, const gchar * other)
{
    gsize diff = 100;
    if(string != NULL && other != NULL)
	 {
				/* Lowercase UTF8 string might have more or less bytes! */
				gchar * lower_string = g_ascii_strdown(string,-1);
				gchar * lower_other  = g_ascii_strdown(other, -1);

				if(lower_string && lower_other)
				{
						  diff = levenshtein_strcmp(lower_string, lower_other);
				}

				/* Free 'em */
				g_free(lower_string);
				g_free(lower_other);
	 }
	 return diff;
}

/* ------------------------------------------------------------- */

void suggest_other_getter(GlyrQuery * query, gchar * wrong_input)
{
		  if(query->verbosity <= 0)
		  {
					 return;
		  }

		  GlyrFetcherInfo * fetcher = glyr_get_plugin_info();
		  if(fetcher != NULL)
		  {
					 gboolean did_you_mean_printed = FALSE;
					 GlyrFetcherInfo * it = fetcher;
					 while(it != NULL)
					 {
						if(levenshtein_strcasecmp(wrong_input,it->name) < 5)
						{
							if(did_you_mean_printed == FALSE)
							{
								g_print("\nDid you mean this?\n");
								did_you_mean_printed = TRUE;
							}
							g_print(" - %s\n",it->name);
						}		
						it = it->next;
					 }
					 glyr_free_plugin_info(fetcher);
		  }
}

/*-----------------------------------------*/

void suggest_other_provider(GlyrQuery * query, gchar * wrong_input)
{
		  if(query->verbosity <= 0)
		  {
					 return;
		  }

		  GlyrFetcherInfo * fetcher = glyr_get_plugin_info();
		  GlyrFetcherInfo * it = fetcher;
		  while(it != NULL)
		  {
				  if(it->type == query->type)
				  {
						  break;
				  }

				  it = it->next;
		  }

		  if(it != NULL && wrong_input)
		  {
				gboolean did_you_mean_printed = FALSE;
				GlyrSourceInfo * head = it->head;
				GHashTable * key_table = g_hash_table_new(g_direct_hash,g_direct_equal);
				while(head != NULL)
				{
					gsize offset = 0;
					gsize length = strlen(wrong_input);
					gchar *token = NULL;
					while((token = get_next_word(wrong_input,GLYR_DEFAULT_FROM_ARGUMENT_DELIM,&offset,length)) != NULL)
					{	
						if(levenshtein_strcasecmp(token,head->name) < 5 &&
						   g_hash_table_lookup(key_table,head->name) == NULL)
						{
							if(did_you_mean_printed == FALSE)
							{
								g_print("\nDid you mean this?\n");
								did_you_mean_printed = TRUE;
							}
							g_print(" - %s\n",head->name);
							g_hash_table_insert(key_table,head->name,head);
						}
						g_free(token);
					}
					head = head->next;	
				}
				g_hash_table_destroy(key_table);
		  }		
		  glyr_free_plugin_info(fetcher);
}

/*-----------------------------------------*/
