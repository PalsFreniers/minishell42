NAME = minishell
SRCS = error_manager.c \
       error_utils.c \
       light_utils.c \
       comm_creat.c \
       libft_bis.c \
       skipper.c \
       tempo_utils.c \
       ft_itoa.c \
       export.c \
       export2.c \
       heredoc.c \
       in_and_out.c \
       prompt.c \
       main.c \
       arg_treat.c \
       arg_utils.c \
       char_treat.c \
       char_treat_bis.c \
       commands_to_exec.c \
       hd_exit.c \
       expansion_bis.c \
       expansion_exec.c \
       expansion_utils.c \
       ft_split.c \
       input_parse.c \
       libft.c \
       libft_utils.c \
       paths_related.c \
       utils.c \
       init.c \
       deinit.c \
       expansion.c \
       solo_b_in.c \
       builtin.c \
       builtin2.c \
       env_b_in.c \
       signals.c \
       exec/funcs.c \
       exec/main.c \
       exec/resolve.c \
       exec/b_in.c \
       exec/deinit.c \
       exec/exec.c \
       exec/generate.c \
       exec/rand_file.c \
       exec/builtin/echo/main.c \
       exec/builtin/pwd/main.c \
       exec/builtin/env/main.c \
       exec/builtin/exit/main.c \
       exec/builtin/unset/main.c \
       exec/builtin/export/main.c \
       exec/builtin/cd/main.c
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

.PHONY: all clean fclean re
