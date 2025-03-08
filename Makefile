#Project Name
NAME = philo

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread #-fsanitize=thread

# Header file
HEADERS = philo.h

# Source files
SRCS = main.c utils.c lib.c lib_helper.c init.c action.c monitor.c init_philosopher.c pickup_fork.c

# Object files
OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Dependency files
DEPS = $(OBJS:.o=.d)

# Rules
all: $(OBJ_DIR) $(NAME)

# Create object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compile object files
$(OBJ_DIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INC) -MMD -MP -c $< -o $@

# Link program
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Include generated dependency files
-include $(DEPS)

# Clean object files
clean:
	rm -rf $(OBJ_DIR)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Remake everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re obj