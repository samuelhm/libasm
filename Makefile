CC		= gcc
ASM		= nasm
AR		= ar
FLAGS_C	= -Wall -Wextra -Werror
FLAGS_ASM= -f elf64

NAME	= libasm.a
SRC_ASM	= ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s
OBJ_ASM	= $(SRC_ASM:.s=.o)
SRC_C	= main.c
EXEC	= programa

.PHONY: all clean fclean re

all: $(EXEC)

$(NAME): $(OBJ_ASM)
	$(AR) rcs $(NAME) $(OBJ_ASM)

%.o: %.s
	$(ASM) $(FLAGS_ASM) $< -o $@

$(OBJ_ASM): $(SRC_ASM)

$(EXEC): $(NAME) $(SRC_C)
	$(CC) $(FLAGS_C) $(SRC_C) -L. -lasm -o $(EXEC)

clean:
	rm -f $(OBJ_ASM)

fclean: clean
	rm -f $(NAME) $(EXEC)

re: fclean all
