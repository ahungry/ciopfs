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
map_table (table_t *table, void (*fn)(char *c, int x))
{
  // First entry in each table is a dummy one we skip
  while ((table = table->next) != NULL)
    {
      fn (table->key, 9);
    }
}

void
add_table_children (table_t *parent, table_t *children)
{
  parent->children = children;
}

void
init_table (table_t *table)
{
  table->key = "";
  table->children = NULL; // malloc (sizeof (table_t));
  table->next = NULL; // malloc (sizeof (table_t));
}

table_t *
make_table ()
{
  table_t *table = malloc (sizeof (table_t));
  init_table (table);

  return table;
}

void
print_key (char *c, int x)
{
  fprintf (stderr, "\nThe key was: %s, x was: %d\n", c, x);
}

int
main (int argc, char *argv[])
{
  init_table (&global_table);

  table_t *files = make_table ();
  table_t *paths = &global_table;

  add_table_entry (files, "hello");
  add_table_entry (files, "BuBBles");

  map_table (files, &print_key);

  add_table_entry (paths, "/");
  add_table_children (paths, files);

  table_t *t = get_table_entry ((&global_table)->children, "hello");

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
