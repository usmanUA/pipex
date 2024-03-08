flags = -Wall -Wextra -Werror
LIBFTPRINTF = libftprintf.a
NAME = pipex
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

FILES = pipex.c \
		check_input.c \
		exec_cmds.c \
		errors.c \
		path.c \
		pipex_utils.c \

B_FILES = pipex_bonus.c \
		  exec_cmds_bonus.c \
		  check_input.c \
		  errors.c \
		  path.c \
		  pipex_utils.c \
		  get_next_line/get_next_line.c \
		  get_next_line/get_next_line_utils.c

OBJS = $(FILES:.c=.o)

B_OBJS = $(B_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFTPRINTF)
	@(echo "$(GREEN)Creating The Executable:   $(NAME)$(RESET)" && cc $(OBJS) ft_printf/$(LIBFTPRINTF) -o $(NAME))
	
%.o: %.c
	@(echo "$(GREEN)Creating Object File: $@$(RESET)" && cc $(flags) -c $< -o $@)
	
bonus: $(B_OBJS) $(LIBFTPRINTF)
	@(echo "$(GREEN)Creating The Executable:   $(NAME)$(RESET)" && cc $(B_OBJS) ft_printf/$(LIBFTPRINTF) -o $(NAME))

$(LIBFTPRINTF):
	@$(MAKE) -C ft_printf

clean:
	@echo "$(RED)Cleaning Object Files for ft_printf and push_swap$(RESET)"
	@$(MAKE) -C ft_printf clean
	@rm -rf $(OBJS) $(B_OBJS)

fclean: clean
	@echo "$(RED)Removing   $(LIBFTPRINTF) and $(NAME)$(RESET)"
	@rm -rf ft_printf/$(LIBFTPRINTF)
	@rm -rf $(NAME) $(B_NAME)

re: fclean all

.PHONY: all clean fclean re
