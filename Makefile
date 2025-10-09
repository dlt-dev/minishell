INC_DIR = header
LEXING_DIR = lexing
UTILS_DIR = utils

SRC_LEXING =$(LEXING_DIR)/lexing.c  $(LEXING_DIR)/utils_lexing.c
SRC_UTILS =$(UTILS_DIR)/free_exit.c  $(UTILS_DIR)/utils_lst.c  $(UTILS_DIR)/utils.c
SRC_MAIN = main.c

OBJ =$(SRC_LEXING:$(LEXING_DIR)/%.c=$(LEXING_DIR)/%.o) \
$(SRC_UTILS:$(UTILS_DIR)/%.c=$(UTILS_DIR)/%.o) \
$(SRC_MAIN:%.c=%.o)

NAME = minishell
CC = cc
FLAG_OBJ = -Wall -Wextra -Werror -g -c
FLAG_NAME = -o $(NAME)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAG_NAME) $(OBJ)

%.o: %.c
	$(CC) $(FLAG_OBJ) $< -I$(INC_DIR)

re:

clean:
	
fclean:

.PHONY: all re clean fclean 



