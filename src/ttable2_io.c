#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "table_io.h"
#include "ttable2_io.h"

int check_op(char op){
  switch(op){
    case '(': return LEFT;
    case ')': return RIGHT;
    case '-': return OP_NOT;
    case '=': return OP_EQUAL;
    case '>': return OP_IMPLY;
    case '&': return OP_AND;
    case '#': return OP_XOR;
    case '|': return OP_OR;
  }
  return -1;
}

char get_op(int value){
  switch(value){
  case LEFT: return '(';
  case RIGHT: return ')';
  case OP_NOT: return '-';
  case OP_EQUAL: return '=';
  case OP_IMPLY: return '>';
  case OP_AND: return '&';
  case OP_XOR: return '#';
  case OP_OR: return '|';
  }
  return '\0';
}

char* shunting(char* str){
  int i=0, j=0;
  int num[MAX_SIZE];
  int* pt = num;
  Stack s;
  s.a = pt;
  s.n=0;
 
  char new_str[strlen(str)+1];
  int len = strlen(str);
  while(i < len){
    if(!isalpha(str[i])&&!isdigit(str[i])){
      int prec = check_op(str[i]);
      if(s.n==0)push(&s,prec); 
      else{
	int prec2 = top(&s);
	if(prec == LEFT){ 
	  push(&s,prec);
	}
	else if(prec == RIGHT){//if it is )
	  while(top(&s)!=LEFT){//pop operators until (
	    int v = pop(&s);
	    char op = get_op(v);
	    new_str[j++] = op;
	    if(s.n == 0){//case where ( doesn't exist
	      printf("Invalid input\n");
	      exit(1);
	    }
	  }
	  s.n--; //discard (
	 }
	 else if(prec <= prec2){
	   int v = pop(&s);
	   char op = get_op(v);
	  new_str[j++]= op;
	  push(&s,prec);
	 }
	else{
	  push(&s,prec);
	}
      }
    }
    else{
      new_str[j++] = str[i];
    }
    i++;
  }
  while(s.n > 0){
    int v = pop(&s);
    char op = get_op(v);
    new_str[j++] = op;
  }
  new_str[j]='\0';
  char* res = malloc(sizeof(char)*strlen(new_str));
  strcpy(res,new_str);
  return res;
}

// n is number of comb of input, len is the length of formula
void print_query(Table* t2, int n, int len,  int* result1){
  int size = t2->n;
  int** inputs = t2->in;
  int** str = t2->str;
  int* res = t2->res;
  for(int i=0; i<size; i++){
    // when the query is true
    if(result1[i]){
      for(int j=0; j<n; j++){
	printf("%d ", inputs[i][j]);
      }
      printf(": ");
      
      for(int j=0; j<len; j++){
	if(str[i][j] == -1) printf(" ");
	else printf("%i", str[i][j]);
      }
      printf(" :%4d\n", res[i]);
    }
  }
}


//extension - checks the results of the two formula and check if they are equivalent
int check_equi(Table* t1, Table* t2){
  int i;
  if(t1->n != t2->n) return INVALID;
  int* res1 = t1->res;
  int* res2 = t2->res;
  for(i=0; i < t1->n; i++){
    if(res1[i] != res2[i]) return INVALID;
  }
  return VALID;
}

//main will be whether or not this is default or extension - if it is for main
// that will only accept postfix, even if infix is correct it will still reject the input
char* get_postfix(char* str, int var, int main){
  char* new_str = rm_space(str);
  int num = (int)strlen(new_str);
  if(check_form(new_str, var)){
    return new_str;
  }
  else{
    if(main){
      printf("Invalid input\n");
      exit(1);
    }
    char* post = shunting(new_str);
    free(new_str);
    num = (int)strlen(post);
    if(check_form(post, var)){
      return post;
    }
    else{
      printf("Invalid input\n");
      exit(1);
    }
  }
  return NULL;
}

//f1 -ps, f2 -pt: 1 is true 0 is false, for f3, 0 is none, 1 is db 2 is ce
//n is no of flags, f1 for -st f2 pt, f3 for -dbs or -ce (check equivalence)
void find_flags(int argc, char* const args[], int* n, int* f1, int* f2, int* f3){
  int i=1;//exclude first ./ttable2
  while(i < argc){
    if(argc == ONE_IN) break; //main default - n and one input
    if(strcmp(args[i], "-ps")==0){
      *f1 = 1;
      (*n)++;
    }
    else if(strcmp(args[i], "-pt")==0){
      *f2 = 1;
      (*n)++;
    }
    else if(strcmp(args[i], "-dbs")==0){
      if((*f3)){
	printf("Invalid input\n");
	exit(1);
      }
      else {
	*f3 =1;
	(*n)++;
      }
    }
      else if(strcmp(args[i],"-ce")==0){
	if((*f3)){
	  printf("Invalid input.\n");
	  exit(1);
	}
	else{
	  *f3 = 2;
	  (*n)++;
	}
      }
      else break; //if no flags found check other inputs
      i++;
  }
}

int check(int argc, char* const args[], int n, int f1, int f2, int f3){
  if(argc == ONE_IN && n) return INVALID;
  //else if(!n || n > 2) return INVALID;
  else if(argc == ONE_IN +1 && ((n > 1|| n < 1)|| (f1&&f2) || f3))return INVALID;
  else if(argc == TWO_IN +1 && (n >= 3 || n < 1)) return INVALID;
  else if(argc == TWO_IN +1 && n==1 && (f1||f2)) return INVALID;
  else if(argc == TWO_IN+1 && n==2 && (f3 && (f1||f2))) return INVALID;
  else if(argc == TWO_IN+2 && ((n>2||n<2)|| (f1&&f2) || (f3==1&&(f1||f2))) ) return INVALID;
  else if(argc == TWO_IN+3 && ((n>3||n<3) || !(f1&&f2&&(f3==2)))) return INVALID; 
  else if(argc > TWO_IN+3|| argc < ONE_IN) return INVALID;
  
  char* ptr;
  //index of no_var
  int no_indx = n+1;
  int var = (int)strtol(args[no_indx], &ptr, 10);
  if(var > MAX || var <= 0 || (int)strlen(ptr)) return INVALID;

  return VALID;
}

int result_exist(int* res, int size){
  int i;
  for(i =0; i<size; i++){
    if(res[i]) return VALID;
  }
  return INVALID;
}
 
  

void print_two(Table* t1, Table* t2, char* str, char* str2, int num, int* flags){
  int len2 = (int)strlen(str2);
  if(flags[2] == 1){ //if flag is -dbs
    print_head(num,str2);
    print_query(t2,num,len2,t1->res);
  }
  else if(flags[2] == 2){ //if flag is -ce
    if(strcmp(str,str2)==0) printf("Two formulae are equal.\n");
    
    else if(check_equi(t1,t2)) printf("Two formulae are equivalent\n");
    else{
      if(flags[1]){ //if flag is -pt
	if(result_exist(t2->res, t2->n)){
	  printf("\n");
	  print_head(num,str2);
	  print_true(t2,num,len2);
	}
      }
      else{
	printf("\n");
	print_head(num,str2);
	print_table(t2,num,len2);
      }
      
      if(flags[0]) check_result(t2);
      printf("\nTwo formulae are not equivalent\n");
    }
  }
}


void print_true(Table* t, int n, int len){
    int size = t->n;
    int** inputs = t->in;
    int** str = t->str;
    int* result = t->res;
    int exist = 0;
    for(int i=0; i<size; i++){
        if(result[i]){
            for(int j=0; j<n; j++){
                printf("%d ", inputs[i][j]);
            }
            exist =1;
            printf(": ");
	    for(int j=0; j<len; j++){
	      if(str[i][j] == -1) printf(" ");
	      else printf("%i", str[i][j]);
	    }
            printf(" :%4d\n", result[i]);
        }
    }
    if(!exist){
        printf("No true exists - no solution\n");
    }

}
