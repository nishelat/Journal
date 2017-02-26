all: journal
	./journal

journal: journal.cpp 
	g++ -g journal.cpp -o journal