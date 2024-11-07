# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: skoene <skoene@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2024/10/26 15:58:53 by skoene        #+#    #+#                  #
#    Updated: 2024/11/01 20:50:03 by skoene        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME     = philo
HEADER  = philosophers.h
CC       = cc
CFLAGS   = -Wall -Wextra -Werror -pthread -Iinclude -flto -O3 #-fsanitize=thread

# Color Codes
BABY_BLUE = \033[38;5;153m
NC        = \033[0m

SRCS = main.c init.c philo_routine.c philo_utils.c \
       routine_utils.c simulation_utils.c launch_simulation.c 

OBJDIR  = obj/
OBJS    = $(addprefix $(OBJDIR), $(SRCS:.c=.o))
TOTAL_SRC := $(words $(SRCS))

# Default target
all: ascii_art $(NAME)

# Rule to build the final executable
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "\n    $(BABY_BLUE)$(NAME) compiled successfully!$(NC)\n"

# Pattern rule to compile object files
$(OBJDIR)%.o: %.c | $(OBJDIR)
	@mkdir -p $(OBJDIR)
	@$(CC) -c $(CFLAGS) $< -o $@  # Compile first, then count
	@CURRENT_COUNT=`find $(OBJDIR) -type f -name '*.o' 2>/dev/null | wc -l`; \
	printf "\r    $(BABY_BLUE)[%d/$(TOTAL_SRC)] Compiling: %s$(NC)" "$$CURRENT_COUNT" "$(notdir $<)"

# Print ASCII art only once
ascii_art:
	@echo -n "\n$(BABY_BLUE)╹╹┳   ┓ •  ┓    ┓       ┏        ┳       ╹╹\n  ┃  ╋┣┓┓┏┓┃┏  ╋┣┓┏┓┏┓┏┓╋┏┓┏┓┏┓  ┃  ┏┓┏┳┓  \n  ┻  ┗┛┗┗┛┗┛┗  ┗┛┗┗ ┛ ┗ ┛┗┛┛ ┗   ┻  ┗┻┛┗┗ $(NC)                                          \n"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Clean object files
clean:
	@if [ -d "$(OBJDIR)" ] && find $(OBJDIR) -name '*.o' | grep -q .; then \
		echo "\n    $(BABY_BLUE)Cleaning object files...$(NC)"; \
		rm -rf $(OBJDIR); \
	else \
		echo "\n    $(BABY_BLUE)Nothing to clean$(NC)"; \
	fi

# Full clean: remove executable and object files
fclean: clean
	@if [ -f "$(NAME)" ]; then \
		echo "    $(BABY_BLUE)Removing executable $(NAME)...$(NC)"; \
		rm -f $(NAME); \
	else \
		echo "    $(BABY_BLUE)No executable to remove$(NC)"; \
	fi

# Rebuild everything from scratch
re: fclean all

.PHONY: all clean fclean re ascii_art