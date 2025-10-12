INC_DIR = Header
SRC_DIR = Src/
UTILS_DIR = Src/Utils
OBJ_DIR = objs

SRC_SHELL = $(SRC_DIR)/Part0_Prompt.c $(SRC_DIR)/Part1_lexing.c $(SRC_DIR)/main.c
SRC_UTILS =$(UTILS_DIR)/free_exit.c $(UTILS_DIR)/utils_libft1.c \
$(UTILS_DIR)/utils_libft2.c $(UTILS_DIR)/utils_lst.c 

OBJ = $(SRC_UTILS:$(UTILS_DIR)/%.c=$(OBJ_DIR)/%.o) \
$(SRC_SHELL:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = minishell
CC = cc
FLAG_OBJ = -Wall -Wextra -Werror -g -c
FLAG_NAME = -o $(NAME)
RM = rm -rf

RED = \033[31;1;3m
GREEN = \033[32;1;3m
YEL = \033[33;1;3m
CYAN = \033[36;1;3m
RESET = \033[m
MESSAGE = Compilation de

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(YEL)the nature elements is linking !$(RESET)"
	$(CC) $(FLAG_NAME) $(OBJ) -lreadline
	@echo "$(YEL)You found a shell on the beach ! Open it !$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	@echo "$(GREEN)$(MESSAGE) $< $(RESET)"
	$(CC) $(FLAG_OBJ) $< -I$(INC_DIR) -o $@


$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	@echo "$(GREEN)$(MESSAGE) $< $(RESET)"
	$(CC) $(FLAG_OBJ) $< -I$(INC_DIR) -o $@

clean:
	$(RM) $(OBJ_DIR)
fclean: clean
	$(RM) $(NAME)
re: all

.PHONY: all re clean fclean 



