
# ---------------------------------- NAME ------------------------------------ #

NAME = cub3D

# ------------------------------- DIRECTORIES -------------------------------- #

LIBFT_DIR	= library/libft/
MLX_DIR		= library/mlx/
HDRS_DIR	= mandatory/headers/
SRCS_DIR	= mandatory/sources/
OBJS_DIR	= objects/
BONUS_HDRS_DIR = bonus/headers/
BONUS_SRCS_DIR	= bonus/sources/
BONUS_OBJS_DIR	= objects/

# ---------------------------------- FILES ----------------------------------- #

LIBS = $(LIBFT_DIR)libft.a
MLX = $(MLX_DIR)libmlx.a 

INCLUDE = -I $(HDRS_DIR) -I $(MLX_DIR) -I $(LIBFT_DIR)
SRCS = $(wildcard $(SRCS_DIR)*.c)
OBJS += $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))

BONUS_INCLUDE = -I $(BONUS_HDRS_DIR) -I $(MLX_DIR) -I $(LIBFT_DIR)
BONUS_SRCS = $(wildcard $(BONUS_SRCS_DIR)*.c)
BONUS_OBJS += $(addprefix $(BONUS_OBJS_DIR), $(notdir $(BONUS_SRCS:.c=.o)))

# -------------------------------- COMPILATE --------------------------------- #

CC		= cc
CFLAGS	= -Wall -Werror -Wextra 
# -g -fsanitize=address
RM		= rm -rf
MD		= mkdir -p 

# --------------------------------- RULES ------------------------------------ #

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(HDRS_DIR)*.h
	$(MD) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(BONUS_OBJS_DIR)%.o : $(BONUS_SRCS_DIR)%.c $(BONUS_HDRS_DIR)*.h
	$(MD) $(dir $@)
	$(CC) $(CFLAGS) $(BONUS_INCLUDE) -c $< -o $@

all: $(NAME)

$(NAME): | MAKE_MAN

bonus: | MAKE_BONUS

MAKE_LIBS:
	touch MAKE_LIBS
	make -C $(MLX_DIR)
	make bonus -C $(LIBFT_DIR)

MAKE_MAN: MAKE_LIBS $(HDRS_DIR)*.h $(OBJS)
		touch MAKE_MAN
		rm -f MAKE_BONUS
		cc -L./$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit $(OBJS) $(LIBS) $(CFLAGS) -o $(NAME)
		
MAKE_BONUS: MAKE_LIBS $(BONUS_HDRS_DIR)*.h $(BONUS_OBJS) 
		touch MAKE_BONUS
		rm -f MAKE_MAN
		cc -L./$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit $(BONUS_OBJS) $(LIBS) $(CFLAGS) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS_DIR) $(BONUS_OBJS_DIR)
	$(RM) MAKE_MAN MAKE_BONUS MAKE_LIBS

fclean:
	make clean
	make clean -C $(MLX_DIR)
	$(RM) $(LIBS) $(NAME) 

re:
	make fclean
	make all

.PHONY:		all clean fclean re bonus