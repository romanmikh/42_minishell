# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 12:57:25 by dmdemirk          #+#    #+#              #
#    Updated: 2024/09/06 11:50:43 by dmdemirk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
DEF_COLOR	=	\033[0;39m
GRAY		=	\033[0;90m
RED			=	\033[0;91m
GREEN		=	\033[0;92m
YELLOW		=	\033[0;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[0;96m
WHITE		=	\033[0;97m

# Program
NAME			=	minishell

# Comands
COMPILER		=	cc
DFLAGS			=	-g3 -gdwarf-2
CFLAGS			=	-Wall -Wextra -Werror $(DFLAGS)
AR			=	ar rcs
RM			=	rm -rf
MAKEFLAGS 		+= --silent

# Structure
LIB_DIR					=	./lib
LIBFT					=	$(LIB_DIR)/libft/libft.a
READLINE 				= -lreadline

SRC_DIR					=	./src
UTILS_DIR				= 	$(SRC_DIR)/utils
ENV_DIR					=	$(SRC_DIR)/env
SHELL_VAR_DIR			=	$(SRC_DIR)/shell_variables
APP_DIR					=	$(SRC_DIR)/app
COMMON_DIR				=	$(SRC_DIR)/common
PARSER_DIR				= 	$(SRC_DIR)/parser
PIPE_DIR				= 	$(SRC_DIR)/pipe
REDIRECTION_DIR			=	$(SRC_DIR)/redirection
BUILTINS_DIR			=	$(SRC_DIR)/builtins
EXECUTE_DIR				=	$(SRC_DIR)/execute
EXIT_STATUS_DIR			=	$(SRC_DIR)/exit_status
TEST_DIR				=	$(SRC_DIR)/test
SIGNALS_DIR				=	$(SRC_DIR)/signals

INCLUDES				=	-I./inc \
							-I $(LIB_DIR)/libft/inc \

TEST_INCLUDES			=	-I./inc \
							-I $(LIB_DIR)/libft/inc \
							-I $(TEST_DIR)

MAIN_SOURCE					=	$(wildcard $(SRC_DIR)/*.c)
APP_SOURCES					=	$(wildcard $(APP_DIR)/*.c)
ENV_SOURCES					=	$(wildcard $(ENV_DIR)/*.c)
ERRORS_SOURCES				=	$(wildcard $(ERRORS_DIR)/*.c)
SHELL_VAR_SOURCES			=	$(wildcard $(SHELL_VAR_DIR)/*.c)
COMMON_SOURCES				=	$(wildcard $(COMMON_DIR)/*.c)
UTILS_SOURCES				= 	$(wildcard $(UTILS_DIR)/*.c)
PARSER_SOURCES 				= 	$(wildcard $(PARSER_DIR)/*.c)
PIPE_SOURCES				=	$(wildcard $(PIPE_DIR)/*.c)
REDIRECTION_SOURCES			=	$(wildcard $(REDIRECTION_DIR)/*.c)
BUILTINS_SOURCES			=	$(wildcard $(BUILTINS_DIR)/*.c)
EXECUTE_SOURCES				=	$(wildcard $(EXECUTE_DIR)/*.c)
EXIT_STATUS_SOURCES			=	$(wildcard $(EXIT_STATUS_DIR)/*.c)
SIGNALS_SOURCES				=	$(wildcard $(SIGNALS_DIR)/*.c)

MAIN_TEST_SOURCE			=	$(wildcard $(TEST_DIR)/*.c)
ENV_TEST_SOURCES			=	$(wildcard $(TEST_DIR)/env/*.c)
PIPE_TEST_SOURCES			=	$(wildcard $(TEST_DIR)/pipe/*.c)

SOURCES					=	$(MAIN_SOURCE) \
							$(APP_SOURCES) \
							$(ENV_SOURCES) \
							$(ERRORS_SOURCES) \
							$(SHELL_VAR_SOURCES) \
							$(COMMON_SOURCES) \
							$(UTILS_SOURCES) \
							$(PARSER_SOURCES) \
							$(PIPE_SOURCES) \
							$(BUILTINS_SOURCES) \
							$(EXECUTE_SOURCES)	\
							$(EXIT_STATUS_SOURCES) \
							$(MAIN_TEST_SOURCE) \
							$(ENV_TEST_SOURCES) \
							$(PIPE_TEST_SOURCES) \
							$(REDIRECTION_SOURCES) \
							$(SIGNALS_SOURCES)
# Building
BUILD_DIR					=	./build
MAIN_OBJECT					=	$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/src/%.o, $(MAIN_SOURCE))
APP_OBJECTS					=	$(patsubst $(APP_DIR)/%.c, $(BUILD_DIR)/src/app/%.o, $(APP_SOURCES))
ENV_OBJECTS					=	$(patsubst $(ENV_DIR)/env/%.c, $(BUILD_DIR)/src/app/env/%.o, $(ENV_SOURCES))
EXIT_STATUS_OBJECTS			=	$(patsubst $(EXIT_STATUS_DIR)/%.c, $(BUILD_DIR)/src/exit_status/%.o, $(EXIT_STATUS_SOURCES))
SHELL_VAR_OBJECTS			=	$(patsubst $(SHELL_VAR_DIR)/%.c, $(BUILD_DIR)/src/shell_variables/%.o, $(SHELL_VAR_SOURCES))
COMMON_OBJECTS				=	$(patsubst $(COMMON_DIR)/%.c, $(BUILD_DIR)/common/app/%.o, $(COMMON_SOURCES))
UTILS_OBJECTS				=	$(patsubst $(UTILS_DIR)/%.c, $(BUILD_DIR)/utils/%.o, $(UTILS_SOURCES))
PARSER_OBJECTS				=	$(patsubst $(PARSER_DIR)/%.c, $(BUILD_DIR)/src/parser/%.o, $(PARSER_SOURCES))
PIPE_OBJECTS				=	$(patsubst $(PIPE_DIR)/%.c, $(BUILD_DIR)/src/pipe/%.o, $(PIPE_SOURCES))
REDIRECTION_OBJECTS			=	$(patsubst $(REDIRECTION_DIR)/%.c, $(BUILD_DIR)/src/redirection/%.o, $(REDIRECTION_SOURCES))
BUILTINS_OBJECTS			=	$(patsubst $(BUILTINS_DIR)/%.c, $(BUILD_DIR)/src/builtins/%.o, $(BUILTINS_SOURCES))
EXECUTE_OBJECTS				=	$(patsubst $(EXECUTE_DIR)/%.c, $(BUILD_DIR)/src/execute/%.o, $(EXECUTE_SOURCES))
SIGNALS_OBJECTS				=	$(patsubst $(SIGNALS_DIR)/%.c, $(BUILD_DIR)/src/signals/%.o, $(SIGNALS_SOURCES))
MAIN_TEST_OBJECT			=	$(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/src/test/%.o, $(MAIN_TEST_SOURCE))
ENV_TEST_OBJECTS			=	$(patsubst $(TEST_DIR)/env/%.c, $(BUILD_DIR)/src/test/env/%.o, $(ENV_TEST_SOURCES))
PIPE_TEST_OBJECTS			=	$(patsubst $(TEST_DIR)/pipe/%.c, $(BUILD_DIR)/src/test/pipe/%.o, $(PIPE_TEST_SOURCES))

OBJECTS					=	$(MAIN_OBJECT) \
							$(APP_OBJECTS) \
							$(ENV_OBJECTS) \
							$(ERRORS_OBJECTS) \
							$(SHELL_VAR_OBJECTS) \
							$(EXECUTE_OBJECTS) \
							$(EXIT_STATUS_OBJECTS) \
							$(COMMON_OBJECTS) \
							$(BUILTINS_OBJECTS) \
							$(UTILS_OBJECTS) \
							$(PARSER_OBJECTS) \
							$(PIPE_OBJECTS)	\
							$(REDIRECTION_OBJECTS) \
							$(SIGNALS_OBJECTS)
						
TEST_OBJECTS			=	$(APP_OBJECTS) \
							$(ENV_OBJECTS) \
							$(EXECUTE_OBJECTS) \
							$(COMMON_OBJECTS) \
							$(BUILTINS_OBJECTS) \
							$(UTILS_OBJECTS) \
							$(PARSER_OBJECTS) \
							$(PIPE_OBJECTS) \
							$(MAIN_TEST_OBJECT) \
							$(ENV_TEST_OBJECTS)	\
							$(PIPE_TEST_OBJECTS)

# Processing
all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@$(COMPILER) $(CFLAGS) $(OBJECTS) $(INCLUDES) $(LIBFT) -o $@ $(READLINE)
	@echo "$(GREEN)minishell compiled$(DEF_COLOR)"
	
$(BUILD_DIR)/src/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(COMPILER) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/src/env/%.o: $(ENV_DIR)/%.c
	@mkdir -p $(@D)
	@$(COMPILER) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/src/shell_variables/%.o: $(SHELL_VAR_DIR)/%.c
	@mkdir -p $(@D)
	@$(COMPILER) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/src/builtins/%.o: $(BUILTINS_DIR)/%.c
	@mkdir -p $(@D)
	@$(COMPILER) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/src/execute/%.o: $(EXECUTE_DIR)/%.c
	@mkdir -p $(@D)
	@$(COMPILER) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/src/exit_status/%.o: $(ERRORS_DIR)/%.c
	@mkdir -p $(@D)
	@$(COMPILER) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/utils/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(@D)
	@$(COMPILER) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/src/parser/%.o: $(PARSER_DIR)/%.c
	@mkdir -p $(@D)
	@$(COMPILER) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/src/pipe/%.o: $(PIPE_DIR)/%.c
	@mkdir -p $(@D)
	@$(COMPILER) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/src/redirection/%.o: $(REDIRECTION_DIR)/%.c
	@mkdir -p $(@D)
	@$(COMPILER) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/src/signals/%.o: $(SIGNALS_DIR)/%.c
	@mkdir -p $(@D)
	@$(COMPILER) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@cd $(LIB_DIR)/libft -s && make -s

bonus: $(NAME)
	@echo "$(CYAN)bonus $(YELLOW)features $(MAGENTA)enabled$(DEF_COLOR)"

clean:
	@$(RM) $(BUILD_DIR)
	@$(RM) valgrind-out.txt
	@cd $(LIB_DIR)/libft && make clean
	@echo "$(GRAY)files.o removed$(DEF_COLOR)"
	
fclean: clean
	@$(RM) $(NAME)*
	@rm -f test
	@cd $(LIB_DIR)/libft && make fclean
	@echo "$(RED)minishell removed$(DEF_COLOR)"

re: fclean
	@make

#	TESTS
$(BUILD_DIR)/test/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	@$(COMPILER) $(CFLAGS) $(TEST_INCLUDES) -c $< -o $@

$(BUILD_DIR)/test/env/%.o: $(TEST_DIR)/env/%.c
	@mkdir -p $(@D)
	@$(COMPILER) $(CFLAGS) $(TEST_INCLUDES) -c $< -o $@

$(BUILD_DIR)/test/pipe/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	@$(COMPILER) $(CFLAGS) $(TEST_INCLUDES) -c $< -o $@

test: $(TEST_OBJECTS) $(LIBFT)
	@$(COMPILER) $(CFLAGS) $(TEST_OBJECTS) $(TEST_INCLUDES) $(LIBFT) -o $@ $(READLINE)
	@echo "$(YELLOW)tests compiled$(DEF_COLOR)"
	@echo "$(YELLOW)--------------$(DEF_COLOR)"
	@echo "$(GRAY)running tests$(DEF_COLOR)"
	@./test

valgrind: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --suppressions=readline.supp --log-file=valgrind-out.txt ./minishell

.PHONY: all bonus clean fclean re test
