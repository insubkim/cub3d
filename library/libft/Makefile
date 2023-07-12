CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

SRCS_MAN = $(wildcard *_man.c)
SRCS_BONUS = $(wildcard *_bonus.c)
OBJS_MAN = $(SRCS_MAN:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

ifdef ADD_BONUS
		OBJECTS = $(OBJS_MAN) $(OBJS_BONUS)
else
		OBJECTS = $(OBJS_MAN)
endif

%o : %c
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJECTS)
		ar -crs $@ $(OBJECTS)

bonus :
		sleep 1
		make ADD_BONUS=1 
		make all

all : $(NAME)

clean :
		rm -rf $(OBJS_MAN) $(OBJS_BONUS)

fclean : clean
		rm -rf $(NAME)
re :
	make fclean 
	make all

.PHONY : all clean fclean re bonus
