# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/26 00:44:58 by akoaik            #+#    #+#              #
#    Updated: 2025/07/05 18:42:41 by akoaik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I includes
NAME    = pipex
LIBFT_DIR = libft
LIBFT_SRCS = $(LIBFT_DIR)/ft_split.c \
			 $(LIBFT_DIR)/ft_strjoin.c \
			 $(LIBFT_DIR)/ft_strncmp.c
SRCS    = pipex.c utils.c $(LIBFT_SRCS)
OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re