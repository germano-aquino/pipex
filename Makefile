# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 19:19:45 by grenato-          #+#    #+#              #
#    Updated: 2022/04/16 21:12:35 by grenato-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# define the C compiler
CC = clang
#CC = gcc

# define any compile-time flags
CFLAGS = -Wall -Wextra -Werror -g

# library flags
LDFLAGS = -L.

# name of the project
NAME = pipex

# bonus
BONUS = pipex_bonus

BONUS_INC = inc_bonus
BONUS_SRC = src_bonus
B_OBJ_DIR = obj_b
# name of include folder
INCLUDE = inc

# name of source folder
SRC_DIR = src

# name of libft folder
LIBFT_DIR = libft

UTILS_DIR = src/utils

LIBFT = libft/libft.a

HEADERS = -I/usr/include -I$(INCLUDE) -I$(LIBFT_DIR) -I$(BONUS_INC)

OBJ_DIR = obj

SOURCE_FILES = main.c check_params.c parse_args.c free.c
SOURCE_FILES += ft_split_with_quote.c exec_cmd.c

BONUS_FILES = main_bonus.c check_params_bonus.c parse_args_bonus.c
BONUS_FILES += free_bonus.c ft_split_with_quote_bonus.c exec_cmd_bonus.c

C_SOURCE = $(addprefix $(SRC_DIR)/, $(SOURCE_FILES))
B_SOURCE = $(addprefix $(BONUS_SRC)/, $(BONUS_FILES))

OBJ = $(C_SOURCE:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_B = $(B_SOURCE:$(BONUS_SRC)/%.c=$(B_OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CLFLAGS) $(HEADERS) -O3 -c $< -o $@

$(B_OBJ_DIR)/%.o: $(BONUS_SRC)/%.c
	$(CC) $(CLFLAGS) $(HEADERS) -O3 -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJ) $(PRINTF)
	$(CC) $(CFLAGS) $(HEADERS) $(OBJ) -o $(NAME) $(LIBFT) $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

bonus: $(B_OBJ_DIR) $(LIBFT) $(OBJ_B)
	$(CC) $(CFLAGS) $(HEADERS) $(OBJ_B) -o $(NAME) $(LIBFT) $(LDFLAGS)

$(B_OBJ_DIR):
	mkdir -p $(B_OBJ_DIR)

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_B)
	$(MAKE) -C ${LIBFT_DIR} clean

fclean: clean
	rm -rf ${NAME}
	$(MAKE) -C ${LIBFT_DIR} fclean

re: fclean all