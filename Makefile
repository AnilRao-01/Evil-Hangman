CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o my_string.o generic_vector.o avl.o
TEST = my_string.o  unit_test.o test_def.o

string_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
my_string.o: my_string.h my_string.c Status.h
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o
generic_vector.o: generic_vector.c 
	$(CC) $(CFLAGS) -c generic_vector.c -o generic_vector.o
avl.o: avl.c avl.h
	$(CC) $(CFLAGS) -c avl.c -o avl.o

unit_test: $(TEST)
	$(CC) $(CFLAGS) -o unit_test $(TEST)
unit_test.o: unit_test.c unit_test.h
	$(CC) $(CFLAGS) -c unit_test.c -o unit_test.o
test_def.o: unit_test.h test_def.c
	$(CC) $(CFLAGS) -c test_def.c -o test_def.o

clean_string_driver:
	rm string_driver $(OBJECTS) 
clean_unit_test:
	rm unit_test $(TEST)
