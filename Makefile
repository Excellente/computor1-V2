CC		= clang++
CFLAGS	= -std=c++11
EXE		= computor
INC 	= ./include/
SRC 	= main.cpp computor.cpp term.cpp
SRCDIR 	= ./src/
SRCS 	= $(addprefix $(SRCDIR), $(SRC))

all:
	$(CC) $(CFLAGS) $(SRCS) -I $(INC) -o $(EXE)

clean:
	rm -f $(EXE)

re: clean all
