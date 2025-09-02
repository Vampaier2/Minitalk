NAME = ft_printf.a

SRC_DIR = .
OBJ_DIR = ../../obj/ft_printf

SRC_FILES =	ft_handle_hex.c \
			ft_handle_point.c \
			ft_printf.c \
			ft_printerror.c \
			ft_putchar_fd.c \
			ft_putdecimal_int.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

CC = cc
C_FLAGS = -Wall -Wextra -Werror
AR = ar rcs

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(C_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
