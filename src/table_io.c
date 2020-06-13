#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "table_io.h"

Table* make_table(int size){
    Table* t = malloc(sizeof(Table));
    t->n = size;
    int** inputs = malloc(sizeof(int*)*size);
    int** str = malloc(sizeof(int*)*size);
    int* result = malloc(sizeof(int)*size);
    t->in = inputs;
    t->str = str;
    t->res = result;
    t->pos = 0;
    return t;
}
//for both, int len is the strlen of the input formula
void print_table(Table* t, int n, int len){
    int size = t->n;
    int** inputs = t->in;
    int** str = t->str;
    int* result = t->res;
    for(int i=0; i<size; i++){
        for(int j=0; j<n; j++){
            printf("%d ", inputs[i][j]);
        }
	printf(": ");
	
	for(int j=0; j<len; j++){
	  if(str[i][j] == -1) printf(" ");
	  else printf("%i", str[i][j]);
	}
        printf(" :%4d\n", result[i]);
    }
}

void free_table(Table* t){
    free(t->in);
    free(t->str);
    free(t->res);
    free(t);
}

void push(Stack* s, int v){
  int n = s->n;
  s->a[n]=v;
  s->n++;

}

int pop(Stack* s){
    s->n--;
    int n = s->n;
    return s->a[n];
}

int top(Stack* s){
  int n = s->n;
  return s->a[n-1];
}

int do_oper(char c, int a, int b){
    switch(c){
        case '|': return a|b;
        case '&': return a&b;
        case '#': return a^b;//xor(a,b)
        case '>': return imply(a,b);
        case '=': return a==b;
    }
    return INVALID;
}

int negate(int a){
  if(a == 1) return INVALID;
  else return VALID;
}


//for every input, computes values and print/ return int* with values?
void compute(Table* t, int v, char* str){//if we want to store every line and print in calling func
    int i =0;
    int result = 0;
    Stack s;
    int st[MAX_SIZE];
    int* pt = st;
    s.a = pt;
    s.n = 0;
    
    int* input = t->in[v];
    int len = (int)strlen(str);
    int res[len];
    char* ptr=NULL;
    
    while(str[i] != '\0'){
        if(isalpha(str[i])||isdigit(str[i])){
            if(isalpha(str[i])){
              int value = str[i] - 'a';
              
	      push(&s,input[value]);
	      result = input[value];
            }//if variable
            else{
	      int value = (int)strtol(&str[i], &ptr,10);
	      push(&s,value);
	      result = value;
            }
            res[i]=-1;
        }
        else{
            if(str[i] == ' ') continue;
            else if(str[i]=='-'){
	      
	      result = negate(pop(&s));
	      push(&s,result);
	      
	    }//~ for bit negate
            else{
	      int b = pop(&s);
	      int a = pop(&s);
                result = do_oper(str[i], a,b);
		push(&s,result);
            }
	    res[i] = result;
        }

        i++;
    }
    int* new_str = malloc(sizeof(int)*len);
    memcpy(new_str, res, sizeof(int)*len);
    t->str[v] = new_str;
    t->res[v] = result;
    if(result) t->pos++;
}




void get_bin(Table* t, int v, int n){
  //printf("int value is %i and no of var is %d\n", v,n);//use arg v as the index of the fields in t
    int i = n-1;
    int row = v;
    int r[n];
    while(i >= 0){
        r[i] = v%2;
	i--;
        v /= 2;    }
    int* new_r = malloc(sizeof(int)*n);
    memcpy(new_r, r, sizeof(int)*n);
    t->in[row] = new_r;
}

// get every possible combination of binary as input and pass it to compute()
void get_comb(Table* t, char* str, int n){
    // n is number of variables from args[0]
     //total no of comb
  int total = (int)pow(2.0,n);
  int v = total;
  while(total > 0){
    get_bin(t, v-total, n);
    compute(t, v-total, str);
    total--;
  }
}

//ttt, tff, ftt, fft
int imply(int a, int b){
  if((a!=b)&!b) return INVALID;
  else return VALID;

}


int valid_op(char op){
  switch(op){
    case ' ': return VALID;
    case '-': return VALID;
    case '=': return VALID;
    case '>': return VALID;
    case '&': return VALID;
    case '#': return VALID;
    case '|': return VALID;
    
  }
  return INVALID;
} 

char* rm_space(char* str){
  int i=0;
  int j=0;
  char new_str[strlen(str)+1];
  int len = strlen(str);
  while(i < len){
    if(str[i]==' '){
      i++;
      continue;
    }
    else new_str[j++] = str[i++];
  }
  new_str[j]='\0';
  char* str_pass = malloc(sizeof(char)*(strlen(new_str)+1));
  strcpy(str_pass,new_str);
  str_pass[j] = '\0';
  return str_pass;
}


      
int check_form(char* str,int var){
  int num_var = 0; // counts overall no of oper
  int i=0;
 
  while(str[i]!= '\0'){ 
    //if it's not var, " ", or operator
    if(!isalpha(str[i])&&!isdigit(str[i])){
      if(!valid_op(str[i])) return INVALID;
    
      if(str[i]==' '){
	i++;
	continue;
      } 
      if(str[i]=='-'){
	if(num_var < 1) return INVALID;
      }
      else { 
	//for other operators
	if(num_var < 2) return INVALID;
	
	else  num_var--;
      }
    }
    else{
      
      if(isalpha(str[i])){
	int n = str[i] - 'a';
	//if formula contains var that is undefined, eg d when num var is 3 (a,b,c only)
	if(n > var-1) return INVALID;
      }
      else{
	// only accept 0,1
	if(str[i] > '2') return INVALID;
      }
      num_var++;
      
    }
     i++;
  }
  if(num_var != 1)  return INVALID;
  
   return VALID;
}
  
//check command line input and reject if wrong formula
int check_input(int argc, char* const args[], int num_arg){
  char* ptr;
  if(argc < num_arg || argc > num_arg) return INVALID;
  int var = (int)strtol(args[F_ARG],&ptr, 10);
  if(var > MAX || var <= 0) return INVALID;
  return VALID;
}

void print_head(int num, char* str){
    char c = 'a';
    int i=0;
    while(i < num){
      printf("%c ", c);
      c++;
      i++;
    }
    printf(": %s : Result\n",str);
    int length = 2*num+(int)strlen(str)+12;//for pretty print of a table
    for(i=0; i < length-1; i++){
      printf("=");
    }
    printf("\n");
}

void check_result(Table* t){
    int num = t->pos;
    if(num == t->n) printf("valid(tautology)\n");
    else if(num > 0 && num < t->n) printf("satisfiable|invalid\n");
    else printf("unsatisfiable\n");
}

