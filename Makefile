# Directories
SRCDIR = src/
OBJDIR = objs/
SRC_FILES = main.c \
			player.c

SRCS = $(addprefix $(SRCDIR), $(SRC_FILES))
OBJS = $(addprefix $(OBJDIR), $(notdir $(SRCS:.c=.o)))

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

MINILIBX = minilibx-linux/
MINILIBX_LIBRARY = -L$(MINILIBX) -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

# FLAGS = -Wall -Wextra -Werror
FLAGS = 

CUB3D = cub3D
NAME = $(CUB3D)

# Rules
all: $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(FLAGS) -I/usr/include -I mlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	make -C $(MINILIBX)
	$(CC) $(OBJS) $(LIBFT) $(MINILIBX_LIBRARY) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH) all

clean:
	make -C $(LIBFT_PATH) fclean
	make clean -C $(MINILIBX) 
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft