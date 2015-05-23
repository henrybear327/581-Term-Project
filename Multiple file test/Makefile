#The actions of the make utility is governed by a Makefile
#It describes	1. the source files that are needed to generate the “target”
#				2. how a “target” is to be generated

#When invoked, make automatically determines which files need to be recompiled and issues the commands needed to recompile them.

#A target is on a newline followed by a “:”

#Name the target clearly so people can guess what to expect easily
#A terget is followed by the files that the target is dependent on.

#The action is executed if there are no additional rules to satisfy for all .o files
test: main.o hello_world.o 
	#The action is always on a newline and must be indented with a TAB.
	#Anything here being executed will be printed out 
	clang-3.5 -o test.o main.o hello_world.o 

main.o: main.c hello_world.h hello_world.c
	clang-3.5 -c -Wall -Wextra main.c

hello_world.o: hello_world.h hello_world.c
	clang-3.5 -c -Wall -Wextra hello_world.c