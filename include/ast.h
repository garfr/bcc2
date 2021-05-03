#ifndef AST_H
#define AST_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "helper.h"
#include "symtable.h"

enum {
  BINOP_ADD,
  BINOP_SUB,
  BINOP_MUL,
  BINOP_DIV,
};

enum {
  EXPR_INT,
  EXPR_VAR,
  EXPR_BINOP,
  EXPR_DEC,
};

typedef struct Expr {
  int t;
  const uint8_t* start;
  size_t sz;

  union {
    struct {
      struct Expr* left;
      struct Expr* right;
      int op;
    } binop;
  } data;

} Expr;

enum {
  STMT_LET,
  STMT_EXPR,
};

typedef struct {
  int t;

  union {
    struct {
      const uint8_t* name;
      size_t sz;
      int mut;
      Expr* value; /* null if variable is not initialized on declaration */
    } let;

    Expr* expr;
  } data;
} Stmt;

typedef struct {
  Vector stmts; /* Stmt */
} Block;

typedef struct {
  MemPool pool; /* used to allocate structures that belong to this AST */
  Block block;
  Scope global;
} AST;

void ast_deinit(AST* ast);
void ast_init(AST* ast);
void ast_dump(FILE* file, AST* ast);
#endif