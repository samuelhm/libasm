CC			= gcc
ASM			= nasm
AR			= ar
FLAGS_C		= -Wall -Wextra -Werror
FLAGS_ASM	= -f elf64

NAME		= libasm.a

SRC_ASM		= ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s
OBJ_ASM		= $(SRC_ASM:.s=.o)

SRC_ASM_BONUS	= ft_atoi_base_bonus.s ft_list_push_front_bonus.s ft_list_size_bonus.s \
			ft_list_sort_bonus.s ft_list_remove_if_bonus.s
OBJ_ASM_BONUS	= $(SRC_ASM_BONUS:.s=.o)

SRC_C		= main.c
SRC_C_BONUS	= main_bonus.c
EXEC		= programa
EXEC_BONUS	= programa_bonus

.PHONY: all clean fclean re bonus

all: $(EXEC)

$(NAME): $(OBJ_ASM)
	$(AR) rcs $(NAME) $(OBJ_ASM)

%.o: %.s
	$(ASM) $(FLAGS_ASM) $< -o $@

$(EXEC): $(NAME) $(SRC_C)
	$(CC) $(FLAGS_C) $(SRC_C) -L. -lasm -o $(EXEC)

bonus: $(OBJ_ASM_BONUS) $(NAME) $(SRC_C_BONUS)
	$(AR) rcs $(NAME) $(OBJ_ASM) $(OBJ_ASM_BONUS)
	$(CC) $(FLAGS_C) $(SRC_C_BONUS) -L. -lasm -o $(EXEC_BONUS)

clean:
	rm -f $(OBJ_ASM) $(OBJ_ASM_BONUS)

fclean: clean
	rm -f $(NAME) $(EXEC) $(EXEC_BONUS)

re: fclean all
