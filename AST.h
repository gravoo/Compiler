#ifndef AST_H
#define AST_H
#include<stdio.h>
#include<string.h>
#include<math.h>
#include <stdlib.h>
extern struct symbol_node *sym_table2;

struct ast_node 
{
  int node_type;
	
  struct ast_node * left;

  struct ast_node * right;
};
typedef struct ast_node ast_node;

struct symbol_node
{
	char * name;

	char * value;

	int type;
	
	int adres;
	
	struct ast_node * function;
	
	struct symbol_node *next; 
};

typedef struct symbol_node symbol_node;

struct ast_assignment_node // for assignment expressions
{
  int node_type;

  struct symbol_node * symbol;

  struct ast_node * value;
};
struct ast_number_node // for constant floating-point numbers
{
  int node_type;

  char *value;
};
struct ast_symbol_reference_node // for symbol references
{
  int node_type;

struct symbol_node * symbol;
};
struct ast_put_node
{
  int node_type;

 char * value;
};
struct ast_relational_node // for relational operators
{
  int node_type;

 int opr;

  struct ast_node * left;

  struct ast_node * right;
};

struct ast_equality_node // for equality operators
{
  int node_type;

 int opr;

  struct ast_node * left;

  struct ast_node * right;
};
struct ast_if_node // for "if/else" statements
{
  int node_type;

  struct ast_node * condition;

  struct ast_node * if_branch;

  struct ast_node * else_branch;
};
struct ast_while_node // for "while" statements
{
  int node_type;

  struct ast_node * condition;

  struct ast_node * while_branch;
};

void *emalloc (size_t size);
struct ast_node * new_ast_node (int node_type, struct ast_node * left, struct ast_node * right);
struct ast_node * new_ast_number_node (char* value);
struct ast_node * new_ast_symbol_reference_node (struct symbol_node * symbol);
struct ast_node * new_ast_assignment_node (struct symbol_node * symbol,struct ast_node * value);
struct symbol_node * new_symbol_node (char *value);
struct symbol_node * find_symbol (symbol_node *ptr2);
struct symbol_node * allocate_symbol (symbol_node *ptr,int adres);
struct ast_node * new_ast_relational_node (int opr, struct ast_node * left, struct ast_node * right);
struct ast_node * new_ast_equality_node (int opr,struct ast_node * left,struct ast_node * right);
struct ast_node * new_ast_if_node (struct ast_node * condition,struct ast_node * if_branch,struct ast_node * else_branch);
struct ast_node *new_ast_while_node (struct ast_node * condition,struct ast_node * while_branch);
void free_ast_tree (struct ast_node * ast_tree);
#endif
