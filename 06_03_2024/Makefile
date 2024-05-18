CC=g++
CFLAGS= -Wall -Wextra -Wpedantic -g
NAME =  paginator
CNAME = paginator.cpp
ONAME = paginator.o

objs:
		$(CC) $(CFLAGS) -c $(CNAME)

all: objs
		$(CC) $(CFLAGS) $(ONAME) -o $(NAME)

re: delete all

all_objs_delete:
		find . -type f -name '*.o' -exec rm {} +
executables_delete:
		find . -type f -executable -exec rm {} +

delete: all_objs_delete executables_delete