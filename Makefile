INC_DIR = Header
LEXING_DIR = Src/Part1_lexing
UTILS_DIR = Src/Utils
OBJ_DIR = objs

SRC_LEXING =$(LEXING_DIR)/lexing.c  $(LEXING_DIR)/utils_lexing.c
SRC_UTILS =$(UTILS_DIR)/free_exit.c  $(UTILS_DIR)/utils_lst.c  $(UTILS_DIR)/utils.c
SRC_MAIN = main.c

OBJ =$(SRC_LEXING:$(LEXING_DIR)/%.c=$(OBJ_DIR)/%.o) \
$(SRC_UTILS:$(UTILS_DIR)/%.c=$(OBJ_DIR)/%.o) \
$(SRC_MAIN:%.c=$(OBJ_DIR)/%.o)

LIB = -l

NAME = minishell
CC = cc
FLAG_OBJ = -Wall -Wextra -Werror -g -c
FLAG_NAME = -o $(NAME)
RM = rm -rf

RED = \033[31;1;3m
GREEN = \033[32;1;3m
YEL = \033[33;1;3m
CYAN = \033[36;1;3m
RESET = \033[0m
MESSAGE = Compilation de

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(YEL)the nature elements is linking !$(RESET)"
	$(CC) $(FLAG_NAME) $(OBJ) -lreadline
	@echo "$(YEL)You found a shell on the beach ! Open it !$(RESET)"

$(OBJ_DIR)/%.o: $(LEXING_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	@echo "$(GREEN)$(MESSAGE) $< $(RESET)"
	$(CC) $(FLAG_OBJ) $< -I$(INC_DIR) -o $@

$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	@echo "$(GREEN)$(MESSAGE) $< $(RESET)"
	$(CC) $(FLAG_OBJ) $< -I$(INC_DIR) -o $@

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAG_OBJ) $< -I$(INC_DIR) -o $@

clean:
	$(RM) $(OBJ_DIR)
fclean: clean
	$(RM) $(NAME)
re: all

.PHONY: all re clean fclean 



