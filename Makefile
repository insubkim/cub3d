
# ---------------------------------- NAME ------------------------------------ #

NAME = cub3d

# ------------------------------- DIRECTORIES -------------------------------- #

LIBFT_DIR	= library/libft/
MLX_DIR		= library/mlx/
HDRS_DIR	= headers/
SRCS_DIR	= sources/
OBJS_DIR	= objects/

# ---------------------------------- FILES ----------------------------------- #

LIBS = $(LIBFT_DIR)libft.a
MLX = $(MLX_DIR)libmlx.a 
INCLUDE = -I $(HDRS_DIR) -I $(MLX_DIR) -I $(LIBFT_DIR)
SRCS = $(wildcard $(SRCS_DIR)*.c)
OBJS += $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))

# -------------------------------- COMPILATE --------------------------------- #

CC		= cc
CFLAGS	= -g
# -Wall -Werror -Wextra
RM		= rm -rf
MD		= mkdir -p 

# --------------------------------- RULES ------------------------------------ #

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c 
	$(MD) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -g -c $< -o $@

all:
	make -C $(MLX_DIR)
	make bonus -C $(LIBFT_DIR)
	make $(NAME)

$(NAME): $(OBJS) $(HDRS_DIR)
	cc -L./$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit $(OBJS) $(LIBS) -g -o $(NAME)
# cc -Lmlx -lmlx -framework OpenGL -framework AppKit $(OBJS) $(LIBS) -o $(NAME)


clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS_DIR)

fclean:
	make clean
	make clean -C $(MLX_DIR)
	$(RM) $(LIBS) $(NAME) 
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY:		all clean fclean re