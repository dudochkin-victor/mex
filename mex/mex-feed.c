/*
 * Mex - a media explorer
 *
 * Copyright © 2010, 2011 Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 2.1, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses>
 */

#include <string.h>
#include "mex-feed.h"
#include "mex-program.h"
#include "mex-model.h"

enum {
  PROP_0,
  PROP_SOURCE,
};

struct _MexFeedPrivate {
  char *source;

  GPtrArray *index_terms;
  GHashTable *index_to_programs; /* Maps index term to a GHashTable of
                                    MexPrograms that have that term */
  GHashTable *id_to_programs; /* Maps program ids to MexPrograms */
};

#define GET_PRIVATE(obj)                                                \
  (G_TYPE_INSTANCE_GET_PRIVATE ((obj), MEX_TYPE_FEED, MexFeedPrivate))

G_DEFINE_TYPE (MexFeed, mex_feed, MEX_TYPE_GENERIC_MODEL);

/*
 * GObject implementation
 */

static void
mex_feed_finalize (GObject *object)
{
  MexFeed *feed = (MexFeed *) object;
  MexFeedPrivate *priv = feed->priv;

  g_free (priv->source);
  priv->source = NULL;

  G_OBJECT_CLASS (mex_feed_parent_class)->finalize (object);
}

static void
mex_feed_dispose (GObject *object)
{
  G_OBJECT_CLASS (mex_feed_parent_class)->dispose (object);
}

static void
mex_feed_set_property (GObject      *object,
                       guint         prop_id,
                       const GValue *value,
                       GParamSpec   *pspec)
{
  MexFeed *feed = (MexFeed *) object;
  MexFeedPrivate *priv = feed->priv;

  switch (prop_id) {
  case PROP_SOURCE:
    g_free (priv->source);
    priv->source = g_value_dup_string (value);
    break;

  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    break;
  }
}

static void
mex_feed_get_property (GObject    *object,
                       guint       prop_id,
                       GValue     *value,
                       GParamSpec *pspec)
{
  MexFeed *feed = (MexFeed *) object;
  MexFeedPrivate *priv = feed->priv;

  switch (prop_id) {
  case PROP_SOURCE:
    g_value_set_string (value, priv->source);
    break;

  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    break;
  }
}

static void
index_program (MexFeed    *feed,
               MexProgram *program)
{
  MexFeedPrivate *priv = feed->priv;
  char *index_str = mex_program_get_index_str (program);
  char **idx_strs;
  int i;

  if (index_str == NULL) {
    return;
  }

  idx_strs = g_strsplit (index_str, " ", -1);

  /* Put each index item into the hashtable, and add its program to the
     bucket */
  for (i = 0; idx_strs[i]; i++) {
    GHashTable *bucket = NULL;

    bucket = g_hash_table_lookup (priv->index_to_programs, idx_strs[i]);
    if (bucket == NULL) {
      char *term;

      /* We use a hashtable so that we can eliminate duplicates easily. */
      bucket = g_hash_table_new (NULL, NULL);
      g_hash_table_insert (bucket, program, program);

      term = g_strdup (idx_strs[i]);
      g_hash_table_insert (priv->index_to_programs, term, bucket);

      /* Put the term into an array for searching later */
      g_ptr_array_add (priv->index_terms, term);
    } else {
      /* Check if the program is already in the bucket */
      if (g_hash_table_lookup (bucket, program) == NULL) {
        g_hash_table_insert (bucket, program, program);
      }

      /* The bucket is already in the hashtable so don't need to
         do anything else */
    }
  }

  g_free (index_str);
  g_strfreev (idx_strs);

  /* Add to id table */
  index_str = mex_program_get_id (program);

  if (index_str)
    g_hash_table_insert (priv->id_to_programs, index_str, program);
}

static void
mex_feed_add_content (MexGenericModel *model,
                      MexContent      *content)
{
  index_program ((MexFeed *) model, (MexProgram *) content);
}

static void
unindex_program (MexFeed    *feed,
                 MexProgram *program)
{
  MexFeedPrivate *priv = feed->priv;
  char *index_str = mex_program_get_index_str (program);
  char **idx_strs;
  int i;

  if (index_str == NULL) {
    return;
  }

  idx_strs = g_strsplit (index_str, " ", -1);
  g_free (index_str);

  /* Look for each index term in the index, and remove the program from
     its bucket */
  for (i = 0; idx_strs[i]; i++) {
    GHashTable *bucket = NULL;

    bucket = g_hash_table_lookup (priv->index_to_programs, idx_strs[i]);
    if (bucket) {
      /* Check if the program is already in the bucket and remove */
      if (g_hash_table_lookup (bucket, program)) {
        g_hash_table_remove (bucket, program);
      }

      if (g_hash_table_size (bucket) == 0) {
        /* Empty bucket, remove from the index */
        g_hash_table_remove (priv->index_to_programs, idx_strs[i]);
      }
    }
  }

  g_strfreev (idx_strs);

  /* Remove from id table */
  index_str = mex_program_get_id (program);

  if (index_str) {
    g_hash_table_remove (priv->id_to_programs, index_str);
    g_free (index_str);
  }
}

static void
mex_feed_remove_content (MexGenericModel *model,
                         MexContent      *content)
{
  MexFeed *feed = (MexFeed *) model;

  unindex_program (feed, (MexProgram *) content);
}

static void
mex_feed_clear (MexGenericModel *model)
{
  MexFeed *feed = (MexFeed *) model;
  MexFeedPrivate *priv = feed->priv;

  g_hash_table_remove_all (priv->index_to_programs);
  g_ptr_array_set_size (priv->index_terms, 0);
}

static void
mex_feed_class_init (MexFeedClass *klass)
{
  GObjectClass *o_class = (GObjectClass *) klass;
  MexGenericModelClass *m_class = (MexGenericModelClass *) klass;
  GParamSpec *pspec;

  o_class->dispose = mex_feed_dispose;
  o_class->finalize = mex_feed_finalize;
  o_class->set_property = mex_feed_set_property;
  o_class->get_property = mex_feed_get_property;

  m_class->add_content = mex_feed_add_content;
  m_class->remove_content = mex_feed_remove_content;
  m_class->clear = mex_feed_clear;

  g_type_class_add_private (klass, sizeof (MexFeedPrivate));

  pspec = g_param_spec_string ("source", "Source",
                               "The source of the feed", "",
                               G_PARAM_STATIC_STRINGS | G_PARAM_READWRITE);
  g_object_class_install_property (o_class, PROP_SOURCE, pspec);
}

static void
mex_feed_init (MexFeed *self)
{
  MexFeedPrivate *priv = GET_PRIVATE (self);

  self->priv = priv;

  priv->index_terms = g_ptr_array_new ();
  priv->index_to_programs = g_hash_table_new_full
    (g_str_hash, g_str_equal, g_free,
     (GDestroyNotify) g_hash_table_destroy);
  priv->id_to_programs = g_hash_table_new_full (g_str_hash,
                                                g_str_equal,
                                                g_free,
                                                NULL);
}

/**
 * mex_feed_new:
 * @title: String containing the title.
 * @source: String containing the source.
 *
 * Creates an empty #MexFeed.
 *
 * Return value: A #MexFeed
 */
MexFeed *
mex_feed_new (const char *title,
              const char *source)
{
  return g_object_new (MEX_TYPE_FEED,
                       "title", title,
                       "source", source,
                       NULL);
}

static void
or_add_to_feed (gpointer key,
                gpointer value,
                gpointer userdata)
{
  MexModel *model = (MexModel *) userdata;

  /* The key and value are the same, doesn't matter which we add */
  mex_model_add_content (model, (MexContent *) key);
}

struct _SearchPayload {
  MexModel *model;
  int term_count;
};

static void
and_add_to_feed (gpointer key,
                 gpointer value,
                 gpointer userdata)
{
  struct _SearchPayload *payload = (struct _SearchPayload *) userdata;

  /* @value is the number of terms that the program in @key was found
     related to. For AND operations the program needs to have been found
     related to all of the terms */
  if (GPOINTER_TO_INT (value) == payload->term_count) {
    mex_model_add_content (payload->model, (MexContent *) key);
  }
}

static GPtrArray *
get_full_search_terms (MexFeed     *feed,
                       const char **terms)
{
  MexFeedPrivate *priv = feed->priv;
  GPtrArray *results;
  int i;

  results = g_ptr_array_new ();

  for (i = 0; terms[i]; i++) {
    GPtrArray *t;
    int j;

    /* For each term in terms, we want to find all the search terms
       that it might match in the index */

    t = g_ptr_array_new ();
    g_ptr_array_add (results, t);

    for (j = 0; j < priv->index_terms->len; j++) {
      if (strstr (priv->index_terms->pdata[j], terms[i])) {
        g_ptr_array_add (t, priv->index_terms->pdata[j]);
      }
    }
  }

  return results;
}

static void
insert_into_hash (gpointer key,
                  gpointer value,
                  gpointer userdata)
{
  g_hash_table_insert ((GHashTable *) userdata, key, value);
}

static GHashTable *
get_programs_for_term (MexFeed   *feed,
                       GPtrArray *possible_terms)
{
  MexFeedPrivate *priv = feed->priv;
  GHashTable *results;
  int i;

  results = g_hash_table_new (NULL, NULL);

  for (i = 0; i < possible_terms->len; i++) {
    GHashTable *programs;

    programs = g_hash_table_lookup (priv->index_to_programs,
                                    possible_terms->pdata[i]);
    if (programs) {
      /* Just put all the items in programs into results, this
         will make them unique too */
      g_hash_table_foreach (programs, insert_into_hash, results);
    }
  }

  return results;
}

/**
 * mex_feed_search:
 * @feed: A #MexFeed
 * @search: A string array
 * @mode: The #MexFeedSearchMode
 * @results_feed: A #MexFeed to store the results of the search.
 *
 * Searches @feed for the terms found in @search and puts the results
 * into @results_feed;
 */
void
mex_feed_search (MexFeed            *feed,
                 const char        **search,
                 MexFeedSearchMode   mode,
                 MexModel           *results_model)
{
  MexFeedPrivate *priv;
  int i;
  GHashTable *count_hash = NULL;
  GPtrArray *terms;

  g_return_if_fail (MEX_IS_FEED (feed));
  g_return_if_fail (MEX_IS_MODEL (results_model));

  priv = feed->priv;

  terms = get_full_search_terms (feed, search);

  for (i = 0; i < terms->len; i++) {
    GPtrArray *possible_terms = terms->pdata[i];
    GHashTable *term_programs;

    term_programs = get_programs_for_term (feed, possible_terms);

    /* term_programs now contains all the programs that match
       the term in search[i] */

    if (mode == MEX_FEED_SEARCH_MODE_OR) {
      /* For OR mode we just need to add the programs to the feed */
      g_hash_table_foreach (term_programs, or_add_to_feed,
                            results_model);
    } else {
      GList *programs, *p;
      gpointer count_as_ptr;
      int count;

      /* For AND mode we need to count how many terms each program is
         found in */
      if (G_UNLIKELY (count_hash == NULL)) {
        count_hash = g_hash_table_new (NULL, NULL);
      }

      programs = g_hash_table_get_keys (term_programs);
      for (p = programs; p; p = p->next) {
        MexProgram *program = (MexProgram *) p->data;

        count_as_ptr = g_hash_table_lookup (count_hash, program);
        count = GPOINTER_TO_INT (count_as_ptr);
        count++;

        g_hash_table_insert (count_hash, program,
                             GINT_TO_POINTER (count));
      }
      g_list_free (programs);
    }

    g_ptr_array_free (possible_terms, TRUE);
    g_hash_table_destroy (term_programs);
  }

  if (count_hash) {
    struct _SearchPayload payload;

    payload.model = results_model;
    payload.term_count = i;

    g_hash_table_foreach (count_hash, and_add_to_feed, &payload);
    g_hash_table_destroy (count_hash);
  }

  g_ptr_array_free (terms, TRUE);
}

MexProgram *
mex_feed_lookup (MexFeed *feed, const char *id)
{
  MexFeedPrivate *priv;

  g_return_val_if_fail (MEX_IS_FEED (feed), NULL);
  g_return_val_if_fail (id != NULL, NULL);

  priv = feed->priv;

  return g_hash_table_lookup (priv->id_to_programs, id);
}
