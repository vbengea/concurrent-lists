CC = cc

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src
INCL_DIR = incl
OBJ_DIR = obj
BIN_DIR = bin

NAME = $(BIN_DIR)/c_test

SRCS = $(SRC_DIR)/main.c \
		$(SRC_DIR)/generate_random_number.c \
		$(SRC_DIR)/list_utils.c \
		$(SRC_DIR)/sort_list.c

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(NAME): $(OBJS) | $(BIN_DIR)
	@$(CC) $(OBJS) -o $@
	@echo "${GREEN}C_TEST Compiled${NC}"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "${RED}Objects removed${NC}"

fclean: clean
	@rm -rf $(NAME) $(OBJ_DIR) $(BIN_DIR)
	@echo "${RED}Objects and executable removed${NC}"

re: fclean all

.PHONY: all clean fclean re