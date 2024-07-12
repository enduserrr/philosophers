NAME	= philo
SRC_DIR	= src
OBJ_DIR = obj

SRCS	= $(addprefix $(SRC_DIR)/, actions.c init.c manage.c utils.c clean_exit.c) \
			$(addprefix $(SRC_DIR)/, main.c)
OBJ		= $(subst $(SRC_DIR), $(OBJ_DIR), $(SRCS:.c=.o))

INCS 	= -I incs
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

$(OBJ_DIR)/%.o :	$(SRC_DIR)/%.c
				@mkdir -p $(dir $@)
				@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)

clean:
			$(RM) $(OBJ)
			$(RM) -r $(OBJ_DIR)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
