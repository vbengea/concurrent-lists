CC = cc

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

CFLAGS = -Wall -Wextra -Werror -pthread
SRC_DIR = src
INCL_DIR = incl
OBJ_DIR = obj
BIN_DIR = bin

NAME = $(BIN_DIR)/c_test

SRCS = $(SRC_DIR)/main.c \
		$(SRC_DIR)/generate_random_number.c \
		$(SRC_DIR)/list_utils.c \
		$(SRC_DIR)/sort_list.c \
		$(SRC_DIR)/cleanup.c \
		$(SRC_DIR)/routine.c \
		$(SRC_DIR)/init_data.c \
		$(SRC_DIR)/parse_args.c \
		$(SRC_DIR)/init_join_threads.c \
		$(SRC_DIR)/sort_and_print.c

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
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "${GREEN}C_TEST Compiled${NC}"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "${RED}Objects removed${NC}"

fclean: clean
	@rm -rf $(NAME) $(OBJ_DIR) $(BIN_DIR)
	@echo "${RED}Objects and executable removed${NC}"

test: $(NAME)
	@cd testing && chmod +x invalid_input.sh leaks.sh order.sh race_conditions.sh
	@cd testing && ./invalid_input.sh && ./leaks.sh && ./order.sh && ./race_conditions.sh

test-tsan: CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread -g
test-tsan: fclean
	@echo "${GREEN}Compiling with ThreadSanitizer...${NC}"
	@$(MAKE) --no-print-directory NAME=$(BIN_DIR)/c_test_tsan
	@echo "${GREEN}Running ThreadSanitizer tests...${NC}"
	@$(BIN_DIR)/c_test_tsan 4 100 > /dev/null 2>&1 && echo "${GREEN}✓ ThreadSanitizer: No issues detected${NC}" || echo "${RED}✗ ThreadSanitizer: Issues found${NC}"
	@$(BIN_DIR)/c_test_tsan 10 50 > /dev/null 2>&1 && echo "${GREEN}✓ ThreadSanitizer: No issues detected${NC}" || echo "${RED}✗ ThreadSanitizer: Issues found${NC}"
	@rm -f $(BIN_DIR)/c_test_tsan

re: fclean all

.PHONY: all clean fclean re test test-tsan