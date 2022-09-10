#include <malloc.h>
#include <string.h>

typedef struct table {
  char *key;
  struct table *children;
  struct table *next;
} table_t;

table_t global_table;

void add_table_entry (table_t *table, const char *key) {
  table_t *node = table;

  while (strcmp(node->key, key) && node->next != NULL)
    {
      node = node->next;
    }

  if (!strcmp(node->key, key))
    {
      fprintf(stderr, "Found the slot");
    }
  else
    {
      fprintf(stderr, "Adding new entry to tail");
      table_t *table = malloc (sizeof (table_t));
      size_t key_size = sizeof (char) * sizeof (key);
      table->key = malloc (key_size);
      memcpy (table->key, key, key_size);
      node->next = table;
    }
}

table_t *
get_table_entry (table_t *table, char *key)
{
  do {
    fprintf(stderr, "table key: %s\n", table->key);
    if (!strcmp (table->key, key))
      {
        return table;
      }
  } while ((table = table->next) != NULL);

  return NULL;
}

void
init_table ()
{
  global_table.key = ""; // malloc(sizeof(char));
}

int
main (int argc, char *argv[])
{
  init_table ();
  const char *path = "/foo/bar";

  add_table_entry (&global_table, path);
  add_table_entry (&global_table, "lolz");

  table_t *t = get_table_entry (&global_table, "lolz");

  if (t == NULL)
    {
      fprintf (stderr, "Failure to find table key...");
    }
  else
    {
      fprintf (stderr, "Found: %s\n", t->key);
    }

  return 0;
}
