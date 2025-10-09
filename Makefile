INC_DIR = header
LEXING_DIR = lexing
UTILS_DIR = utils
OBJ_DIR = objs

SRC_LEXING =$(LEXING_DIR)/lexing.c  $(LEXING_DIR)/utils_lexing.c
SRC_UTILS =$(UTILS_DIR)/free_exit.c  $(UTILS_DIR)/utils_lst.c  $(UTILS_DIR)/utils.c
SRC_MAIN = main.c

OBJ =$(SRC_LEXING:$(LEXING_DIR)/%.c=$(OBJ_DIR)/%.o) \
$(SRC_UTILS:$(UTILS_DIR)/%.c=$(OBJ_DIR)/%.o) \
$(SRC_MAIN:%.c=$(OBJ_DIR)/%.o)

NAME = minishell
CC = cc
FLAG_OBJ = -Wall -Wextra -Werror -g -c
FLAG_NAME = -o $(NAME)

RM = rm -rf


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAG_NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(LEXING_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAG_OBJ) $< -I$(INC_DIR) -o $@

$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c
	mkdir -p $(OBJ_DIR)
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



