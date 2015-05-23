#don't forget the test.o after -o to produce the name of the whole file
test: main.o linkedlist.o 
	clang-3.5 -o test.o main.o linkedlist.o

linkedlist.o: linkedlist.h linkedlist.c
	clang-format-3.5 -i -style=LLVM  linkedlist.c && astyle --style=linux linkedlist.c
	clang-format-3.5 -i -style=LLVM  linkedlist.h && astyle --style=linux linkedlist.h
	clang-3.5 -c -Wall -Wextra linkedlist.h linkedlist.c

main.o: main.c linkedlist.h linkedlist.c
	clang-format-3.5 -i -style=LLVM  main.c && astyle --style=linux main.c
	clang-3.5 -c -Wall -Wextra main.c