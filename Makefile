# Define color codes
ORANGE = \033[38;5;214m
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

# Program file name
CUB3D = cub3D
NAME = $(CUB3D)

# Directories
SRCDIR = src/
OBJDIR = objs/
MAPDIR = maps/

# sub directory
PARDIR = $(SRCDIR)parsing/
INITDIR = $(SRCDIR)initialize/
RAYCASTDIR = $(SRCDIR)raycast/
PLAYERDIR = $(SRCDIR)player/

# Source files
SRC_FILES = main.c \
            render.c \
            texture.c \
            $(INITDIR)init.c \
            $(INITDIR)init_2.c \
            $(PARDIR)checking.c\
            $(PARDIR)checking_utils.c\
            $(PARDIR)check_map.c\
            $(PLAYERDIR)player.c\
            $(PLAYERDIR)player2.c\
            $(RAYCASTDIR)raycast.c\
            $(RAYCASTDIR)raycast_utils.c\

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
INCLUDES = -I includes/ -I $(MLX_PATH) -I $(LIBFT_PATH) -I $(PARDIR) -I $(INITDIR) -I $(PLAYERDIR) -I $(RAYCASTDIR) -I $(MAPDIR)

# Linker flags
LDFLAGS = -L $(MLX_PATH) -lmlx -L $(LIBFT_PATH) -lft -lm -lbsd -lX11 -lXext

# Build the program
all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo -e "\n\n\n$(YELLOW) -- DONE COMPILING CUB3D, LET'S BEGIN THE GAME NOW ! --$(RESET)"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)initialize
	@mkdir -p $(OBJDIR)raycast
	@mkdir -p $(OBJDIR)player
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)%.o: $(PARDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(INCLUDES) -c $< -o $@

$(OBJDIR)%.o: $(INITDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(INCLUDES) -c $< -o $@

$(OBJDIR)%.o: $(PLAYERDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(INCLUDES) -c $< -o $@

$(OBJDIR)%.o: $(RAYCASTDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(INCLUDES) -c $< -o $@

$(MLX):
	$(MAKE) -C $(MLX_PATH)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

clean:
	$(MAKE) -C $(MLX_PATH) clean
	$(MAKE) -C $(LIBFT_PATH) clean
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) -C $(MLX_PATH) clean
	rm -f $(NAME)
	rm -rf $(OBJDIR)

re: fclean all

# norm :
# 	norminette ./includes
# 	norminette ./libft
# 	norminette ./src

valgrind :
	valgrind --leak-check=full ./cub3D

.PHONY: all re clean fclean