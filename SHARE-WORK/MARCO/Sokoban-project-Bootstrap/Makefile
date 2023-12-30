

#####################################
SRC = ./display_popup.c  ./my_popup.c

OBJ = $(SRC:.c=.o)

CFLAGS += -Werror -Wextra -I./include
#####################################



NAME = my_popup

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) -lncurses

all:     $(NAME)

######################################

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:     fclean all


.PHONY: all clean fclean re




