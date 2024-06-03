# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kschelvi <kschelvi@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/06/03 14:14:29 by kschelvi      #+#    #+#                  #
#    Updated: 2024/06/03 15:35:50 by kschelvi      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = lexer

CFLAGS = -Wall -Wextra -Werror

SRC = main.c \
		lexer.c
OBJ = $(SRC:%.c=%.o)

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	@if [ -d "libft" ]; then \
		echo "$(RED)libft already exists$(RESET)"; \
	else \
		echo "$(GREEN)Cloning libft...$(RESET)"; \
		git clone https://github.com/KrijnS8/libft.git; \
	fi
	@echo "$(GREEN)Compiling libft...$(RESET)"
	@cd $(LIBFT_PATH) && $(MAKE)

clean:
	$(RM) -rf $(OBJ)
	if [ -d "libft" ]; then \
		cd libft && $(MAKE) clean; \
	fi

fclean: clean
	$(RM) -rf $(NAME)
	if [ -d "libft" ]; then \
		$(RM) -rf $(LIBFT_PATH); \
	fi

re: fclean all

.PHONY: all clean fclean re