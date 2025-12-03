#Nom du programme
NAME = minishell

#Library
LIBRARY = -lreadline

#Compilation : Compilateur et Flags
CC = cc
CC_FLAG = -Wall -Wextra -Werror -g -c
OPT_NAME = -o $(NAME)

#Compilation : Couleurs et message
RED = \033[31;1;3m
GREEN = \033[32;1;3m
YEL = \033[33;1;3m
CYAN = \033[36;1;3m
RESET = \033[m
MESSAGE = Compilation de

#Clean
RM = rm -rf

#Make install Rules
SCRIPT_SHELL = .minirc
BIN_DIR = $(HOME)/bin

#Dossier de compilation
SRC_DIR = Src
OBJ_DIR = objs
INC_DIR = Header

#Sous dossiers
SUBS_DIR = Utils Built_in Part0_Init Part1_Shell_mode Part2_Lexing Part3_Flags \
Part4_Expand Part5_Word_splitting Part6_Delete_quotes Part7_Cmd_struct \
PartX_Free Part8_Open_fd Part9_Execution PartZ_Signaux get_next_line

#Fichiers sources
	#Sources parties
	SRC_PART0 = Part0_init_var.c
	SRC_PART1 = Part1_Prompt.c interactive.c non_interactive.c
	SRC_PART2 = Part2_lexing.c
	SRC_PART3 = Part3_flags_main.c Part3_flag_word.c
	SRC_PART4 = Part4_1expand_main.c Part4_3expand_dollar.c Part4_2expand_quotes.c \
	Part4_expand_main_2.c
	SRC_PART5 = Part5_word_splitting_main.c Part5_countword_hdl_quotes.c Part5_word_splitting.c
	SRC_PART6 = Part6_delete_quotes.c Part6_delete_quotes_utils.c
	SRC_PART7 = Part7_cmd_struc.c Part7_main_tree_struct.c PartX_print_tree.c \
	Part7_redir_struct.c Part7_syntaxe_err.c
	SRC_PART8 = main_open_fd.c redir_heredoc.c type_of_heredoc.c
	SRC_PART9 = Part1_exec_main.c Part2_A_exec_built_in.c Part2_B_routine_simple_cmd.c \
	Part2_C_routine_pipe.c Part3_apply_redirection.c Part4_execve.c PartX_debug_exec.c \
	Part4_utils_execution.c Part5_waitpid.c
	SRC_PARTX = PartX_free.c
	SRC_PARTZ = signaux.c heredoc_sig.c
	SRC_MAIN  = main.c
#Sources utiles
	SRC_UTILS = utils_chunk_buffer.c utils_chunk_buffer2.c utils_lenght.c utils_libft1.c \
	utils_libft2.c utils_lst.c utils_lst2.c utils_print_lst.c utils_free.c \
	utils_libft3.c utils_error.c utils_exec1.c utils_exec2.c  utils_lst3.c utils_va_lst.c \
	utils_va_lst2.c utils_va_lst3.c
#Sources Built_in
	SRC_BUILTIN = built_in_cd.c built_in_cd2.c built_in_echo.c built_in_env.c \
	built_in_exit.c 	built_in_export1.c built_in_export2.c built_in_pwd.c built_in_unset.c 
#sources GNL
	SRC_GNL = get_next_line_utils.c get_next_line.c

#Tous les sources
	ALL_SRC=$(SRC_MAIN) \
	$(addprefix Utils/, $(SRC_UTILS)) \
	$(addprefix Part0_Init/, $(SRC_PART0)) \
	$(addprefix Part1_Shell_mode/, $(SRC_PART1)) \
	$(addprefix Part2_Lexing/, $(SRC_PART2)) \
	$(addprefix Part3_Flags/, $(SRC_PART3)) \
	$(addprefix Part4_Expand/, $(SRC_PART4)) \
	$(addprefix Part5_Word_splitting/, $(SRC_PART5)) \
	$(addprefix Part6_Delete_quotes/, $(SRC_PART6)) \
	$(addprefix Part7_Cmd_struct/, $(SRC_PART7)) \
	$(addprefix Part8_Open_fd/, $(SRC_PART8)) \
	$(addprefix Part9_Execution/, $(SRC_PART9)) \
	$(addprefix PartX_Free/, $(SRC_PARTX)) \
	$(addprefix PartZ_Signaux/, $(SRC_PARTZ)) \
	$(addprefix Built_in/, $(SRC_BUILTIN)) \
	$(addprefix get_next_line/, $(SRC_GNL))
OBJ = $(addprefix $(OBJ_DIR)/, $(ALL_SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(YEL)the nature elements is linking !$(RESET)"
	$(CC) $(OPT_NAME) $(OBJ) $(LIBRARY)
	@echo "$(YEL)You found a shell on the beach ! Open it !$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(GREEN)$(MESSAGE) $< $(RESET)"
	$(CC) $(CC_FLAG) $< -I$(INC_DIR) -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SUBS_DIR))

install: $(BIN_DIR)/$(NAME)

exec: $(NAME)
	valgrind -s --leak-check=full --show-leak-kinds=all --suppressions=readline.supp --track-fds=yes --trace-children=yes ./minishell

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

re:
	make fclean
	make all

.PHONY: all install re clean fclean 

#	SRC_PART8 = Part8_execution.c Part8_built_in.c Part8_heredoc.c Part8_open_redir.c \
#	Part8_exec_fork_one.c
