#include <stdlib.h> /* malloc. */
#include <string.h> /* strlen. */

/* Data type for links in the chain of symbols.  */
struct symrec
{
  char *name;  /* nazwa */
  int type;    /* typ czyli zmienna z id->1 czy stała wpisana w kod->2  czy przyszla z GET->0*/
  char *value;	
  
  int adres;		/*kolejny adress */
 
  struct symrec *next;  /* link field */
};
typedef struct symrec symrec;

/* The symbol table: a chain of 'struct symrec'.  */
extern symrec *sym_table;

symrec *
putsym (char const *sym_name, int sym_type,int adres)
{
  symrec *ptr = (symrec *) malloc (sizeof (symrec));
  ptr->name = (char *) malloc (strlen (sym_name) + 1);
  strcpy (ptr->name,sym_name);
  ptr->type = sym_type;
  ptr->value = 0; /* Set value to 0 even if fctn.  */
  ptr->next = (struct symrec *)sym_table;
  sym_table = ptr;
  ptr->adres=adres;
  return ptr;
}
symrec *
getsym (char const *sym_name)
{
  symrec *ptr;
  for (ptr = sym_table; ptr != (symrec *) 0;
       ptr = (symrec *)ptr->next)
    if (strcmp (ptr->name, sym_name) == 0)
      return ptr;
  return 0;
}

