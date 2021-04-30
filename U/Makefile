SRC		= main.c input.c libft_utills.c keys.c keys2.c check_for_exit.c

OBJS	= $(SRC:.c=.o)

NAME	= terminal

CC		= gcc

RM		= rm -f

CFLAGS	=  -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -ltermcap

clean:
			$(RM) $(OBJS) $(BOBJS) $(DOBJS)

fclean:		clean
			$(RM) $(NAME)
re:			fclean all

.PHONY:		all clean fclean re
