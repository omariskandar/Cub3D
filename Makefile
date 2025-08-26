NAME        = Cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

# Mandatory sources
MANDATORY_SRC = main.c \
	srcs/utils.c \
	srcs/init_game.c \
	srcs/texture_utils.c \
	srcs/game_loop.c \
	srcs/rendering.c \
	srcs/map_parser.c \
	srcs/map_utils.c \
	srcs/map_helpers.c \
	srcs/map_validation.c \
	srcs/map_validation_helpers.c \
	srcs/player_position.c \
	srcs/player_direction.c \
	srcs/texture_validation.c \
	srcs/color_validation.c \
	srcs/movement.c \
	srcs/raycasting.c \
	srcs/ray_utils.c \
	srcs/ray_helpers.c \
	srcs/ray_helpers_bg.c \
	srcs/ray_tex_helpers.c \
	srcs/door_tex_helpers.c \
	srcs/ray_calculation.c \
	srcs/mandatory_stubs.c \
	srcs/bonus_stubs.c \
	srcs/bonus_stubs2.c \
	srcs/doors_stubs.c

# Bonus sources (additional to mandatory)
BONUS_SRC = srcs/collision.c \
	srcs/minimap.c \
	srcs/minimap_utils.c \
	srcs/minimap_enemies_bonus.c \
	srcs/window_utils.c \
	srcs/doors_bonus.c \
	srcs/doors_anim_bonus.c \
	srcs/doors_anim_utils_bonus.c \
	srcs/floor_bonus.c \
	srcs/hud_bonus.c \
	srcs/hud_anim_bonus.c \
	srcs/hud_crosshair_bonus.c \
	srcs/mouse_bonus.c \
	srcs/pitch_bonus.c \
	srcs/sprites_bonus.c \
	srcs/health_bonus.c \
	srcs/medkit_bonus.c \
	srcs/ammo_bonus.c

# All sources for bonus (without stubs)
BONUS_ALL_SRC = $(MANDATORY_SRC) $(BONUS_SRC)
BONUS_ALL_SRC := $(filter-out srcs/mandatory_stubs.c, $(BONUS_ALL_SRC))
BONUS_ALL_SRC := $(filter-out srcs/bonus_stubs.c, $(BONUS_ALL_SRC))
BONUS_ALL_SRC := $(filter-out srcs/bonus_stubs2.c, $(BONUS_ALL_SRC))
BONUS_ALL_SRC := $(filter-out srcs/doors_stubs.c, $(BONUS_ALL_SRC))

# Object directories
OBJ_DIR     = obj
MANDATORY_OBJS = $(addprefix $(OBJ_DIR)/, $(MANDATORY_SRC:.c=.o))
BONUS_OBJS = $(addprefix $(OBJ_DIR)/, $(BONUS_ALL_SRC:.c=.o))

# Directories
MLX_DIR     = minilibx-linux
LIBFT_DIR   = ./libft
GNL_DIR     = ./get_next_line

# Libraries
MLX         = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
LIBFT       = $(LIBFT_DIR)/libft.a
GNL_OBJS    = $(GNL_DIR)/get_next_line.o $(GNL_DIR)/get_next_line_utils.o

# Includes
INCLUDES    = -I includes -I $(LIBFT_DIR) -I $(GNL_DIR) -I $(MLX_DIR)

# Build rules
all: $(NAME)

$(NAME): $(MANDATORY_OBJS)
	@make -C $(LIBFT_DIR) > /dev/null
	@make -C $(MLX_DIR) > /dev/null
	@make -C $(GNL_DIR) > /dev/null
	@$(CC) $(CFLAGS) $(MANDATORY_OBJS) $(GNL_OBJS) $(LIBFT) $(MLX) -o $(NAME)
	@echo "\033[1;32m[$(NAME)] mandatory created successfully.\033[0m"

bonus: $(BONUS_OBJS)
	@make -C $(LIBFT_DIR) > /dev/null
	@make -C $(MLX_DIR) > /dev/null
	@make -C $(GNL_DIR) > /dev/null
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(GNL_OBJS) $(LIBFT) $(MLX) -o $(NAME)
	@echo "\033[1;32m[$(NAME)] bonus created successfully.\033[0m"

# Create obj/ directory and compile .o files inside it
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ > /dev/null

clean:
	@make -C $(LIBFT_DIR) clean > /dev/null
	@make -C $(GNL_DIR) clean > /dev/null
	@rm -rf $(OBJ_DIR)
	@echo "\033[1;36m[$(NAME)] objects and obj/ directory removed.\033[0m"

fclean: clean
	@make -C $(LIBFT_DIR) fclean > /dev/null
	@make -C $(GNL_DIR) fclean > /dev/null
	@rm -f $(NAME)
	@echo "\033[1;31m[$(NAME)] executables removed.\033[0m"

re: fclean all
	@echo "\033[1;34m[$(NAME)] project rebuilt successfully.\033[0m"

# Leak check with valgrind
leaks:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

qleaks:
	valgrind -q --leak-check=full ./$(NAME)

# Norminette check (adjust the directory as needed)
norm:
	norminette $(MANDATORY_SRC) includes/ get_next_line/ libft/ | grep Error || true

norm_bonus:
	norminette $(BONUS_ALL_SRC) includes/ get_next_line/ libft/ | grep Error || true

.PHONY: all bonus clean fclean re leaks qleaks norm norm_bonus
