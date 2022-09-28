NAME			= pipex

CC				= gcc
CFLAG			= -Wall -Wextra -Werror
RM				= rm -f

SRC				= ./source/pipex.c ./source/pipe.c ./source/utils.c 
OBJS			= ${SRC:.c=.o}

SRC_BONUS		= source_bonus/*.c
OBJS_BONUS		= ${SRC_BONUS:.c=.o}

INC				= libft/libft.a
LIB_DIR			= ./libft


all: 		${NAME}

${NAME}:	$(OBJS)
			@make -C $(LIB_DIR)
			@$(CC) $(CFLAG) $(INC) $(SRC) -o $(NAME)

bonus:		bonus
			$(OBJS_BONUS)
			@make -C $(LIB_DIR)
			@$(CC) $(CFLAG) $(INC) $(SRC_BONUS) -o $(NAME)

clean:		
			$(RM) $(OBJS)
			@make clean -C $(LIB_DIR)

fclean:		fclean
			$(RM) $(NAME) $(OBJS)
			@make fclean -C $(LIB_DIR)

.PHONY:			all clean fclean re bonus