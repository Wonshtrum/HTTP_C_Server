GCC = gcc -Wall -Wextra -Werror
GOO = $(GCC) -c
libs = -lpthread
srcdir = src/
bindir = bin/
SRC = $(wildcard $(srcdir)*.c)
HEAD = $(wildcard $(srcdir)*.h)
OBJ = $(subst $(srcdir), $(bindir), $(SRC:.c=.o))
PROG = server

all = $(PROG)

$(PROG) : $(OBJ)
	$(GCC) $^ $(libs) -o $@

$(bindir)%.o : $(srcdir)%.c
	$(GOO) $^ $(libs) -o $@

.PHONY : init
init :
	mkdir src bin

.PHONY : clean
clean :
	rm -rf $(bindir)*

.PHONY : run
run:
	./$(PROG)
