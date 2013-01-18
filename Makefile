CC=gcc
objs = btree.o hash.o mymalloc.o stack.o
dest = libmylibs.a
mylibs : $(objs)
			ar rcs $(dest) $(objs)

mymalloc.o : mymalloc.c mymalloc.h 
			cc -c mymalloc.c 
btree.o : btree.c btree.h mymalloc.h 
			cc -c btree.c 
hash.o : hash.c hash.h mymalloc.h 
			cc -c hash.c 
stack.o : stack.c stack.h mymalloc.h
			cc -c stack.c 
test : main
main:	test/main.c $(dest)
			cc -I. -L. test/main.c -lmylibs -o main

.PHONY : clean 
clean :
	rm $(objs)
	rm $(dest)

