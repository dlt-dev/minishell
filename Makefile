
#Dossier de compilation
INC_DIR = Header
SRC_DIR = Src/
UTILS_DIR = Src/Utils
OBJ_DIR = objs
BIN_DIR = $(HOME)/bin

#Source de compilation
SRC_SHELL = $(SRC_DIR)/Part0_init_var.c $(SRC_DIR)/Part1_Prompt.c \
$(SRC_DIR)/Part2_lexing.c $(SRC_DIR)/Part3_put_flag.c \
$(SRC_DIR)/main.c $(SRC_DIR)/PartX_free.c

SRC_UTILS = $(UTILS_DIR)/utils_libft1.c $(UTILS_DIR)/utils_va_lst.c \
$(UTILS_DIR)/utils_libft2.c $(UTILS_DIR)/utils_lst.c 

#Objet de compilation
OBJ = $(SRC_UTILS:$(UTILS_DIR)/%.c=$(OBJ_DIR)/%.o) \
$(SRC_SHELL:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#Nom de variable
NAME = minishell
CC = cc
FLAG_OBJ = -Wall -Wextra -Werror -g -c
FLAG_NAME = -o $(NAME)
RM = rm -rf
SCRIPT_SHELL = .minirc

#Couleur de compilation
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

install: $(BIN_DIR)/$(NAME)

$(BIN_DIR)/$(NAME): $(NAME)
	mkdir -p $(BIN_DIR)
	echo "export PATH=$(BIN_DIR):$$PATH" > $(BIN_DIR)/$(SCRIPT_SHELL)
	cp $(NAME) $(BIN_DIR)
	@echo "$(CYAN)				Creation du dossier bin dans le home"
	@echo "$(CYAN)				$(SCRIPT_SHELL) dans le bin pour sourcer le PATH"
	@echo "			Assurez vous que la variable PATH contienne le chemin \
	$(BIN_DIR)$(RESET)"
clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(BIN_DIR)
fclean: clean
	$(RM) $(NAME)
re: all

.PHONY: all perfect re clean fclean 



