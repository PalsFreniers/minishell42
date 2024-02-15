# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dosokin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 11:11:05 by dosokin           #+#    #+#              #
#    Updated: 2024/02/13 14:51:15 by tdelage          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = error_manager.c \
       element_treat.c \
       command_creation.c \
       libft_bis.c \
       skipper.c \
       tempo_utils.c \
       ft_itoa.c \
       heredoc.c \
       in_and_out.c \
       main.c \
       arg_treat.c \
       arg_utils.c \
       char_treat.c \
       commands_to_exec.c \
       ft_split.c \
       input_parse.c \
       libft.c \
       paths_related.c \
       utils.c \
       exec/funcs.c \
       exec/main.c \
       exec/resolve.c \
       exec/builtin/echo/main.c \
       exec/builtin/pwd/main.c \
       exec/builtin/env/main.c \
       exec/builtin/exit/main.c
OBJS = $(SRCS:.c=.o)
HEADER = minishell.h
FLAGS = -Wall -Werror -Wextra -g
CC = cc

ifdef CHECK
	FLAGS += -fsanitize=address
endif

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) ../libft/libft.a -lreadline -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean : 
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all
