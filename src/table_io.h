enum E {INVALID, VALID, MAX_SIZE = 10, MAX = 26};
enum Arg {F_ARG=1, S_ARG, T_ARG, FO_ARG};//first and second argument for input, third for second string
//fourth for whether to print only true or all results - 1 as true or 0 as all

#define ONE_IN 3 //main
#define TWO_IN 4 //extension - allow two input string or one input string and one to denote whether to print all or only true

typedef struct
{
  int* a;//stack
  int n;//size of stack
} Stack;

typedef struct
{
  int** in; //inputs
  int** str;//results of subexpressions
  int* res;//overall results
  int n;//total number of inputs
  int pos;//total number of true results
} Table;

//creates a pointer to a table which will contain all the data
//size argument provides the number of rows
Table* make_table(int size);

//prints out the result table, n is number of var
void print_table(Table* t, int n, int len);

//frees block of memory allocated for table struct
void free_table(Table* t);

//pushes the value v onto the stack s
void push(Stack* s, int v);

//pop a value off the stack
int pop();

//return the value at the top of the stack
int top();

//do operation 
int do_oper(char c, int a, int b);

//check if valid operator symbol is used
int valid_op(char op);

//gets input formula and returns new string with any spaces removed
char* rm_space(char* str);

//checking the validity of input formula, part of checking input
int check_form(char* str, int var);

//checks command line arguments if the inputs are valid
int check_input(int argc, char* const args[], int num_arg);

//evaluates and stores binary input variables at field in at vth row
//n is the number of variables
void get_bin(Table* t, int v, int n);

//gets inputs stored at vth row of field 'in' of table t and evaluates according to the
//algebra in str, stores the results vth row in field 'str'
//the final result at index v in field 'res'
void compute(Table* t, int (v), char *str);

//receives pointer to an empty table, input formula in str and no.of variables
//in 'total', calls get_bin to store inputs, then calls compute to calculate iteratively
void get_comb(Table* t, char* str, int n);

//method to evaluate imply logic
int imply(int a, int b);

//negate operator
int negate(int a);

//receives input values, an integer and a string
//to print out the heading of the results table
void print_head(int num, char* str);







