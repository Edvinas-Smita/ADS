l: zMain.o zFunc.o
	gcc zMain.o zFunkc.o -o l
	
zFunc.o: LongIntegerFUNc.c
	gcc -c LongIntegerFUNc.c -o zFunkc.o
	
zMain.o: LongIntegerMain.c
	gcc -c LongIntegerMain.c -o zMain.o -I.
	
clean:
	rm *.o
