CC		= gcc
ASM		= nasm
AR		= ar
FLAGS_C	= -Wall -Wextra -Werror
FLAGS_ASM= -f elf64

NAME	= libasm.a
SRC_ASM	= program.s
OBJ_ASM	= program.o
SRC_C	= main.c
EXEC	= programa

.PHONY: all clean fclean re

all: $(EXEC)

$(NAME): $(OBJ_ASM)
	$(AR) rcs $(NAME) $(OBJ_ASM)

$(OBJ_ASM): $(SRC_ASM)
	$(ASM) $(FLAGS_ASM) $(SRC_ASM) -o $(OBJ_ASM)

$(EXEC): $(NAME) $(SRC_C)
	$(CC) $(FLAGS_C) $(SRC_C) -L. -lasm -o $(EXEC)

clean:
	rm -f $(OBJ_ASM)

fclean: clean
	rm -f $(NAME) $(EXEC)

re: fclean all
