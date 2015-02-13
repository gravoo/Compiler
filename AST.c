#include "AST.h"
struct ast_node *
new_ast_node (int node_type,
              struct ast_node * left,
              struct ast_node * right)
{
	struct ast_node * ast_node =
	emalloc (sizeof (struct ast_node));

	ast_node->node_type = node_type;

	ast_node->left = left;
	ast_node->right = right;

	return ast_node;
	}

struct ast_node *
new_ast_number_node (char* value)
{
  struct ast_number_node * ast_node =
    emalloc (sizeof (struct ast_number_node));
  ast_node->value = (char *) malloc (strlen (value) + 1);
  ast_node->node_type = 'N';

   strcpy ( ast_node->value,value);

  return (struct ast_node *) ast_node;
}
struct ast_node *
new_ast_symbol_reference_node (struct symbol_node * symbol)
{
  struct ast_symbol_reference_node * ast_node =
    emalloc (sizeof (struct ast_symbol_reference_node));

  ast_node->node_type = 'S';

  ast_node->symbol = symbol;

  return (struct ast_node *) ast_node;
}

struct ast_node *
new_ast_assignment_node (struct symbol_node * symbol,
                         struct ast_node * value)
{
  struct ast_assignment_node * ast_node =
    emalloc (sizeof (struct ast_assignment_node));

  ast_node->node_type = 'A';
  ast_node->symbol = symbol;
  ast_node->value = value;

  return (struct ast_node *) ast_node;
}
struct symbol_node * new_symbol_node (char *value)
{
	struct symbol_node * ast_node =
	(symbol_node*)malloc (sizeof (struct symbol_node));
	ast_node->name = (char *) malloc (strlen (value) + 1);
	strcpy ( ast_node->name,value);

return ast_node;
}

struct symbol_node * find_symbol (symbol_node *ptr2)
{
	symbol_node *ptr;
	for (ptr = sym_table2; ptr != (symbol_node *) 0;
		ptr = (symbol_node *)ptr->next)
	if (strcmp (ptr->name,ptr2-> name) == 0)
		return ptr;
	return NULL;
	
}
struct symbol_node * 
	allocate_symbol (symbol_node *ptr,int adres)
{
	ptr->value = 0; /* Set value to 0 even if fctn.  */
	ptr->next = (struct symbol_node *)sym_table2;
	ptr->adres=adres;
	ptr->type=0;
	sym_table2 = ptr;
  return ptr;
}
struct ast_node *
	new_ast_relational_node (int opr,
	 struct ast_node * left,
	 struct ast_node * right)
{
	struct ast_relational_node * ast_node =
	emalloc (sizeof (struct ast_relational_node));

	ast_node->node_type = 'R';

	ast_node->opr=opr;
	ast_node->left = left;
	ast_node->right = right;

  return (struct ast_node *) ast_node;
}

struct ast_node *
new_ast_equality_node (int opr,
	struct ast_node * left,
	struct ast_node * right)
{
		struct ast_equality_node * ast_node =
		emalloc (sizeof (struct ast_equality_node));

		ast_node->node_type = 'E';
		ast_node->opr=opr;
		ast_node->left = left;
		ast_node->right = right;

  return (struct ast_node *) ast_node;
}
struct ast_node *
new_ast_if_node (struct ast_node * condition,
	struct ast_node * if_branch,
	struct ast_node * else_branch)
	{
		struct ast_if_node * ast_node =
		emalloc (sizeof (struct ast_if_node));

		ast_node->node_type = 'I';

		ast_node->condition = condition;
		ast_node->if_branch = if_branch;
		ast_node->else_branch = else_branch;

		return (struct ast_node *) ast_node;
}
struct ast_node *
new_ast_while_node (struct ast_node * condition,
                    struct ast_node * while_branch)
{
  struct ast_while_node * ast_node =
    emalloc (sizeof (struct ast_while_node));

  ast_node->node_type = 'W';

  ast_node->condition = condition;
  ast_node->while_branch = while_branch;
  
  return (struct ast_node *) ast_node;
}
void
free_ast_tree (struct ast_node * ast_tree)
{
  if (!ast_tree) return;

  switch (ast_tree->node_type)
  {
    /* two sub trees */
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case 'L':
      free_ast_tree (ast_tree->right);

    /* one sub tree */
    case 'M':
    case 'G':
    case 'V':
      free_ast_tree (ast_tree->left);
    case 'P':
      free_ast_tree (ast_tree->right);

    /* no sub trees */
    case 'S':
    case 'N':
      break;

    case 'R':
      {
        struct ast_relational_node * node =
          (struct ast_relational_node *) ast_tree;

        free_ast_tree (node->left);

        free_ast_tree (node->right);
      }
      break;

    case 'E':
      {
        struct ast_equality_node * node =
          (struct ast_equality_node *) ast_tree;

        free_ast_tree (node->left);

        free_ast_tree (node->right);
      }
      break;

    case 'A':
      {
        struct ast_assignment_node * node =
          (struct ast_assignment_node *) ast_tree;

        free_ast_tree (node->value);
      }
      break;

    case 'I':
      {
        struct ast_if_node * node =
          (struct ast_if_node *) ast_tree;

        free_ast_tree (node->condition);

        if (node->if_branch)
        {
          free_ast_tree (node->if_branch);
        }

        if (node->else_branch)
        {
          free_ast_tree (node->else_branch);
        }
      }
      break;

    case 'W':
      {
        struct ast_while_node * node =
          (struct ast_while_node *) ast_tree;

        free_ast_tree (node->condition);

        if (node->while_branch)
        {
          free_ast_tree (node->while_branch);
        }
      }
      break;
   

    

    default:
	break;
  }

  free (ast_tree);
}
void *emalloc (size_t size)
{
	void * pointer=malloc(size);
	if(!pointer)
		printf("Error:malloc  poległ");
	return pointer;

}
