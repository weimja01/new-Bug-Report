all:
	g++ -pedantic-errors BugReport.cpp -g -o BugReport.o -c
	g++ -pedantic-errors main.cpp BugReport.o -g -o main

clean:
	rm -f *.o main