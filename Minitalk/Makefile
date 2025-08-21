# Executable names
CLIENT_NAME = client
SERVER_NAME = server

# Source files
SRC_CLIENT = client.c
SRC_SERVER = server.c
SRC_FILES = $(SRC_CLIENT) $(SRC_SERVER)

# Paths
SRC_DIR = src
OBJ_DIR = obj
PRINTF_DIR = $(SRC_DIR)/ft_printf
PRINTF_LIB = $(PRINTF_DIR)/ft_printf.a

# Full paths
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Compiler
CC = cc
C_FLAGS = -Wall -Wextra -Werror -g
INCLUDES = -Iincludes -I$(PRINTF_DIR)

# Default rule
all: $(PRINTF_LIB) $(SERVER_NAME) $(CLIENT_NAME)

# Client and Server builds
$(CLIENT_NAME): $(SRC_DIR)/$(SRC_CLIENT) $(PRINTF_LIB)
	$(CC) $(C_FLAGS) $(INCLUDES) $(SRC_DIR)/$(SRC_CLIENT) $(PRINTF_LIB) -o $(CLIENT_NAME)

$(SERVER_NAME): $(SRC_DIR)/$(SRC_SERVER) $(PRINTF_LIB)
	$(CC) $(C_FLAGS) $(INCLUDES) $(SRC_DIR)/$(SRC_SERVER) $(PRINTF_LIB) -o $(SERVER_NAME)

# Object file build (not strictly needed for now)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@

# Build printf library
$(PRINTF_LIB):
	@$(MAKE) -C $(PRINTF_DIR)

# Cleaning
clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(CLIENT_NAME) $(SERVER_NAME)
	@$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all
