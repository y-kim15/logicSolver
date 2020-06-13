all: ttable ttable2  

table_io.o: table_io.c table_io.h
	gcc -c table_io.c -std=c99 -Wall -Wextra -g

ttable_io2.o: ttable_io2.c table_io.h ttable_io2.h
	gcc -c ttable2_io.c -std=c99 -Wall -Wextra -g

ttable.o: ttable.c table_io.h
	gcc -c ttable.c -std=c99 -Wall -Wextra -g

ttable2.o: ttable2.c table_io.h ttable2_io.h
	gcc -c ttable2.c -std=c99 -Wall -Wextra -g

ttable: ttable.o table_io.o
	gcc ttable.o table_io.o -lm -o ttable -g

ttable2: ttable2.o table_io.o ttable2_io.o
	gcc ttable2.o table_io.o ttable2_io.o -lm -o ttable2 -g

clean:
	rm -f *.o
	rm -f ttable
	rm -f ttable2
	rm -f *.c~
	rm -f *.h~

