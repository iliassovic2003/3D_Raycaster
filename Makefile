PURPLE    = \033[0;35m
BLUE      = \033[0;34m
GREEN     = \033[0;32m
RED       = \033[0;31m
YELLOW    = \033[0;33m
RESET     = \033[0m

CC = cc -Wall -Wextra -Werror
MLX_FLAG = -Lmlx -lmlx -lX11 -lXext -lm -g3

NAME = Cub3D

SRC = $(shell find . -name "*.c" ! -path "./mlx/*")
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)🔧 Compiling Into Something...$(RESET)"
	@$(CC) $(OBJ) -o $(NAME) $(MLX_FLAG)

clean:
	@echo "$(YELLOW)🧹 Cleaning the objects files...$(RESET)"
	@rm -rf $(OBJ)

fclean: clean
	@echo "$(RED)💫 finishing the cleaning...$(RESET)"
	@rm -rf $(NAME)

ilias: all clean

re: fclean all
