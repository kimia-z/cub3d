# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rshaheen <rshaheen@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2025/01/15 12:10:13 by rshaheen      #+#    #+#                  #
#    Updated: 2025/03/25 12:59:37 by rshaheen      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFT = ./libft/libft.a

MLXLIB = MLX42/build/libmlx42.a

LIBMLX = ./MLX42

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

FLAGSMLX = -ldl -lglfw -pthread -lm

OBJ_DIR = obj

SOURCE = src/main.c\
		src/error_msg.c\
		src/clean.c\
			src/parsing/check_file_ext.c\
			src/parsing/init.c\
			src/parsing/assign_input.c\
			src/parsing/parse_color.c\
			src/parsing/parse_player.c\
			src/parsing/parse_file.c\
			src/parsing/validate_map_line.c\
			src/parsing/parse_texture_color.c\
			src/parsing/validate_game_config.c\
			src/parsing/validate_store_map2d.c\
			src/execution/execution.c\
			src/execution/hook.c\
			src/execution/ray_casting.c\
			src/execution/init.c\
			src/execution/render.c\
			src/execution/utils.c

OBJECTS = $(SOURCE:%.c=$(OBJ_DIR)/%.o)

all: $(LIBMLX) $(MLXLIB) $(NAME)

$(LIBMLX):
	git clone https://github.com/codam-coding-college/MLX42.git && \
	cd MLX42 && \
	cmake -B build && \
	cmake --build build -j4

$(MLXLIB):
	@cmake $(LIBMLX) -DDEBUG=1 -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(LIBFT):
	@$(MAKE) -C ./libft

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "Object directory Created"
	
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(MLXLIB) $(OBJ_DIR) $(OBJECTS)
	@cc $(CFLAGS) $(FLAGSMLX) $(OBJECTS) $(LIBFT) $(MLXLIB) -o $(NAME)
	@echo "CUB3D CREATED"

clean: 
	@echo "REMOVING OBJECT FILES"
	@$(MAKE) clean -C ./libft
	@rm -rf $(OBJ_DIR)
	@echo "OBJECT FILES REMOVED"

fclean: clean
	@echo "REMOVING CUB3D"
	@$(MAKE) fclean -C ./libft
	@rm -f $(NAME)
	@rm -rf $(LIBMLX)/build
	@rm -rf ./MLX42
	@echo "CUB3D REMOVED"

re: fclean all

.PHONY: all clean fclean re info