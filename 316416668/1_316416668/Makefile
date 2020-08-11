all:prefix_table prefix_table_opt

prefix_table: prefix_table.o
	g++ -o prefix_table prefix_table.o

prefix_table_opt: prefix_table_opt.o
	g++ -o prefix_table_opt prefix_table_opt.o

prefix_table.o : prefix_table.cpp
	g++ -c prefix_table.cpp

prefix_table_opt.o : prefix_table_opt.cpp
	g++ -c prefix_table_opt.cpp

clean:
	rm -f *.o prefix_table_opt prefix_table