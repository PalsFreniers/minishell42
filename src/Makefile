NAME = minishell
SRCS = ft_itoa.c heredoc.c in_and_out.c main.c argument_treat.c char_treat.c commands_to_exec.c ft_split.c input_parse.c libft.c paths_related.c program_treat.c utils.c
OBJS = $(SRCS:.c=.o)
HEADER = minishell.h
FLAGS = -Wall -Werror -Wextra -g
CC = cc

ifdef CHECK
	FLAGS += -fsanitize=address
endif

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -lreadline -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean : 
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all