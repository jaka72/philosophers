BLU = \033[0;34m
WHT = \033[0m

NAME 			=	philo
FLAGS 			=	-Wall -Wextra -Werror
OBJ_DIR 		=	obj_dir
C_FILES_MAIN	=	main.c \
					init.c \
					start_philo.c \
					timer.c \
					utils.c \
					ft_atoi.c \
					free.c

OBJ_FILES	= $(patsubst %, $(OBJ_DIR)/%, $(C_FILES_MAIN:.c=.o))


all:	makedir $(NAME) $(MAKE_BONUS)
		@echo "$(BLU)\n --- MAKEFILE DONE ------------- \n$(WHT)"
		
makedir:
		@echo "$(BLU)\n --- START MAKEFILE ------------ \n$(WHT)"
		@echo "$(BLU)- Making obj_dir Directory $(WHT)"
		mkdir -p $(OBJ_DIR)/
		@echo "$(BLU)\n- Start making object files $(WHT)"

$(OBJ_DIR)/%.o: 	%.c
		@echo "$(BLU)  making .o file $(WHT)"
		gcc -g $(FLAGS) -c $< -o $@

$(NAME): $(OBJ_FILES)
		@echo "$(BLU)\n - Making Philosophers Executable --- $(WHT)"
#		gcc -fsanitize=thread -g $^ $(FLAGS) -pthread -o $(NAME)
		gcc -g $^ $(FLAGS) -pthread -o $(NAME)

re:		fclean all

clean:
		rm -rf $(OBJ_DIR)
		
fclean:	clean
		rm -f philo

.PHONY: fclean bonus clean re all
