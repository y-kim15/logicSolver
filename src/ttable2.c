#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "table_io.h"
#include "ttable2_io.h"


int main(int argc, char* const args[]){
  
  int n=0,f1=0, f2=0, f3=0;
  find_flags(argc,args,&n,&f1,&f2,&f3);
  if(check(argc,args,n,f1,f2,f3)){
    int n_indx = n+1;//index of n
    int no_str = argc-n_indx-1;//number of input strings
    int str_indx = n_indx+1;//index of first input string
    char* ptr;
    int num = (int)strtol(args[n_indx], &ptr, 10);
    char* str = rm_space(args[str_indx]);
    if(f1||f2||no_str == 2) {
      str = get_postfix(args[str_indx],num, INVALID);
    }
    int len = (int)strlen(str);
     if(!check_form(str,num)){
      printf("Invalid input\n");
      exit(2);
    }
    int total = (int)pow(2,num);
    Table* t1 = make_table(total);
    
    get_comb(t1, str, num);

    if(no_str > 0 && f3 != 1){
      if(f2){
	if(result_exist(t1->res, t1->n)){
	  print_head(num,str);
	  print_true(t1,num,len);
	}
	else printf("No solution\n");
      }
      else{
	print_head(num,str);
	print_table(t1,num,len);
      }
      if(f1) check_result(t1);
    }

    if(no_str ==2){
      char* str2 = get_postfix(args[str_indx+1],num, INVALID);
      len = (int)strlen(str);
      Table* t2 = make_table(total);
      get_comb(t2,str2,num);

      int flags[3] = {f1,f2,f3};
      int* ptr = flags;
      print_two(t1,t2, str, str2,num, ptr);
      	
      free_table(t2);
      free(str2);
      
    }
    
    free_table(t1);
    free(str);
  }
  else{
    printf("Invalid input\n");
  }
}




  
  
  
  

  
