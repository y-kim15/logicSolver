#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "table_io.h"
#include <string.h>

int main(int argc, char* const args[]){  
  if(check_input(argc, args, ONE_IN)){
        char* str = rm_space(args[S_ARG]);
        char* ptr="";
	int num = (int)strtol(args[F_ARG], &ptr, 10);
	int len = (int)strlen(str);
	if(!check_form(str,num)||(int)strlen(ptr)){
	  printf("Invalid input\n");
	  exit(2);
	}
        int total = (int)pow(2,num);
        Table* t = make_table(total);
        get_comb(t, str, num);
  
        print_head(num,str); // str
        print_table(t, num,len);
        free_table(t);
	free(str);
    }
    else printf("Invalid input\n");


}
