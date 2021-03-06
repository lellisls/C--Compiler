

/****************************************************/
/* File: symtab.h                                   */
/* Symbol table interface for the TINY compiler     */
/* (allows only one symbol table)                   */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/* Adapted by Gustavo O. Souza                      */
/****************************************************/
#include "globals.h"
#include <vector>
#include <string>

#ifndef _SYMTAB_H_
#define _SYMTAB_H_
/* the list of line numbers of the source 
 * code in which a variable is referenced
 */

typedef enum
{
  VARIABLE,
  VECTOR,
  FUNCTION
} IDType;

// typedef struct LineListRec
//    { int lineno;
//      struct LineListRec * next;
//    } * LineList;

/* The record in the bucket lists for
 * each variable, including name, 
 * assigned memory location, and
 * the list of line numbers in which
 * it appears in the source code
 */
class BucketListRec
{
public:
  std::string name;
  std::vector<int> lines;
  int memloc; /* memory location for variable */
  struct BucketListRec *next;
  std::string scope;
  IDType vtype;
  ExpType dtype;
};

typedef BucketListRec *BucketList;
/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
BucketList st_declare(std::string name, int lineno, int loc, IDType type, std::string scope);
BucketList st_declare_function(std::string name, int lineno, int loc, IDType type, ExpType eType, std::string escopo);
BucketList st_reference(BucketList l, int lineno);
/* Function st_find returns the memory reference 
   to the bucketlist of the variable or NULL if not found
 */
BucketList st_find(std::string name, std::string scope);
BucketList st_find_at_scope(std::string name, std::string escopo); //Used by code generator

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(FILE *listing);

#endif
