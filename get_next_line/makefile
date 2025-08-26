# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/09 23:27:43 by oiskanda          #+#    #+#              #
#    Updated: 2025/06/09 23:28:29 by oiskanda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   := libgnl.a
CC     := cc
CFLAGS := -Wall -Wextra -Werror
SRCS   := get_next_line.c get_next_line_utils.c get_next_line_bonus.c get_next_line_utils_bonus.c
OBJS   := $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
.PHONY: all clean fclean re
