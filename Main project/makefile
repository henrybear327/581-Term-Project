#don't forget the test.o after -o to produce the name of the whole file
main: main.o linkedList.o queue.o getInput.o dataType.o utility.o
	clang-3.5 -o main main.o linkedList.o queue.o getInput.o utility.o

linkedList.o: linkedList.h linkedList.c dataType.h
	clang-format-3.5 -i -style=LLVM  linkedList.h && astyle --style=linux linkedList.h
	clang-format-3.5 -i -style=LLVM  linkedList.c && astyle --style=linux linkedList.c
	clang-3.5 -c -Wall -Wextra linkedList.h linkedList.c

queue.o: queue.h queue.c dataType.h
	clang-format-3.5 -i -style=LLVM  queue.h && astyle --style=linux queue.h
	clang-format-3.5 -i -style=LLVM  queue.c && astyle --style=linux queue.c
	clang-3.5 -c -Wall -Wextra queue.h queue.c

getInput.o: getInput.h getInput.c dataType.h
	clang-format-3.5 -i -style=LLVM  getInput.h && astyle --style=linux getInput.h
	clang-format-3.5 -i -style=LLVM  getInput.c && astyle --style=linux getInput.c
	clang-3.5 -c -Wall -Wextra getInput.h getInput.c

dataType.o: dataType.h
	clang-format-3.5 -i -style=LLVM  dataType.h && astyle --style=linux dataType.h
	clang-3.5 -c -Wall -Wextra dataType.h

utility.o: utility.h utility.c
	clang-format-3.5 -i -style=LLVM  utility.h && astyle --style=linux utility.h
	clang-format-3.5 -i -style=LLVM  utility.c && astyle --style=linux utility.c
	clang-3.5 -c -Wall -Wextra utility.h utility.c

#just the header is enough
main.o: main.c linkedList.h queue.h getInput.h dataType.h utility.h
	clang-format-3.5 -i -style=LLVM  main.c && astyle --style=linux main.c
	clang-3.5 -c -Wall -Wextra main.c linkedList.h queue.h getInput.h dataType.h utility.h

#https://www.gnu.org/software/make/manual/html_node/Cleanup.html
.PHONY: clean
clean:
	-rm *.o *.c.orig *.h.gch *.h.orig