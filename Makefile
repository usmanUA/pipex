flags = -Wall -Wextra -Werror
LIBFT = libft.a
NAME = pipex
# B_NAME = checker
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

FILES = pipex.c \
		check_input.c \
		save_args.c \
		exec_cmds.c \
		errors.c \
		path.c \

# B_FILES = checker_bonus.c \
# 		  checker_utils_bonus.c \
# 		  check_input.c \
# 		  create_stack.c \
# 		  int_array.c \
# 		  instructions.c \
# 		  instructions_utils.c \
# 		  free_mem.c \
# 		  get_next_line/get_next_line.c \
# 		  get_next_line/get_next_line_utils.c

OBJS = $(FILES:.c=.o)

# B_OBJS = $(B_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@[ -f $(NAME) ] || (echo "$(GREEN)Creating The Executable:   $(NAME)$(RESET)" && cc $(OBJS) libft/$(LIBFT) -o $(NAME))
	
%.o: %.c
	@[ -f $@ ] || (echo "$(GREEN)Creating Object File: $@$(RESET)" && cc $(flags) -c $< -o $@)
	
# bonus: $(B_OBJS) $(LIBFT)
# 	@[ -f $(B_NAME) ] || (echo "$(GREEN)Creating The Executable:   $(B_NAME)$(RESET)" && cc $(B_OBJS) libft/$(LIBFT) -o $(B_NAME))

$(LIBFT):
	@$(MAKE) -C libft

clean:
	@echo "$(RED)Cleaning Object Files for libft and push_swap$(RESET)"
	@$(MAKE) -C libft clean
	@rm -rf $(OBJS) $(B_OBJS)

fclean: clean
	@echo "$(RED)Removing   $(LIBFT) and $(NAME)$(RESET)"
	@rm -rf libft/$(LIBFT)
	@rm -rf $(NAME) $(B_NAME)

re: fclean all

.PHONY: all clean fclean re
