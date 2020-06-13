enum Precedence{
  OP_OR=4, OP_XOR, OP_AND, OP_IMPLY, OP_EQUAL, OP_NOT, 
};

enum Paren{NONE=1, LEFT, RIGHT};

//***EXTENSION
//extension - identifies the property of the formula - valid - tautology, invalid,

//satisfiable, unsatisfiable 
void check_result(Table* t);

//performs algorithm to get postfix notation rpn
char* shunting(char* str);

//gets char operator and returns relevant number denoting its precedence
int check_op(char op);

//gets the precedence value and return the character operator - undo check_op
char get_op(int value);

//print as database query
//from second table, which has n inputs and formula of length len and where
//the result of the first table is given
void print_query(Table* t2, int n, int len, int* result);

//check if the two formula are equivalent by comparing the results of the two
int check_equi(Table* t1, Table* t2);

//check input formula and do shunting by default to change correct infix notation
//given with formula str, number of variables var, and to be applied for the ttable
//functionality, check if main is 1 or 0. if 0 reject infix as invalid if 0 do shunting 
char* get_postfix(char* str, int var, int main);

//check the flags, go through the arguments and count number of flags, store
//-ps in f1, -pt in f2, -dbs or -ce in f3 ( 0 is none, 1 is -dbs and 2 is -ce)
void find_flags(int argc, char* const args[], int* n, int* f1, int* f2, int* f3);

//more robust checking of correct format the arguments are given
int check(int argc, char* const args[], int n, int f1, int f2, int f3);

//to print true, checks if any true solution exists
int result_exist(int* res, int size);

//prints out according to the flags where there are two input strings
void print_two(Table* t1, Table* t2, char* str, char* str2, int num, int* flags);

//extension - only prints true lines
void print_true(Table* t, int n, int len);
