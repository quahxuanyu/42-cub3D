
# Program file name
CUB3D = cub3D
NAME = $(CUB3D)

# Directories
SRCDIR = src/
OBJDIR = objs/

# Parsing directory
PARDIR = $(SRCDIR)parsing/

# Source files
SRC_FILES = main.c \
            player.c \
            $(PARDIR)checking.c

SRCS = $(addprefix $(SRCDIR), $(SRC_FILES))
OBJS = $(addprefix $(OBJDIR), $(notdir $(SRCS:.c=.o)))

# Compiler and compilation flags
CC = gcc
#CFLAGS = -Werror -Wextra -Wall -g3 #-fsanitize=address

# Minilibx
MLX_PATH = minilibx-linux/
MLX_NAME = libmlx.a
MLX = $(MLX_PATH)$(MLX_NAME)

# Libft
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

# Include directories
INCLUDES = -I includes/ -I $(MLX_PATH) -I $(LIBFT_PATH) -I $(PARDIR)

# Linker flags
LDFLAGS = -L $(MLX_PATH) -lmlx -L $(LIBFT_PATH) -lft -lm -lbsd -lX11 -lXext

# Build the program
all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(INCLUDES) -c $< -o $@

$(OBJDIR)%.o: $(PARDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(INCLUDES) -c $< -o $@

$(MLX):
	$(MAKE) -C $(MLX_PATH)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

clean:
	$(MAKE) -C $(MLX_PATH) clean
	$(MAKE) -C $(LIBFT_PATH) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(MLX_PATH) clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

# norm :
# 	norminette ./includes
# 	norminette ./libft
# 	norminette ./src

valgrind :
	valgrind --leak-check=full ./cub3D

.PHONY: all re clean fclean