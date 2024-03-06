NAME = minishell
CFLAGS = -Wall -Werror -Wextra #-g
CC = cc
LIBFT = libft/libft.a
OBJS = $(SRCS:.c=.o)
SRCS = src/error_manager.c \
       src/error_utils.c \
       src/light_utils.c \
       src/comm_creat.c \
       src/libft_bis.c \
       src/skipper.c \
       src/tempo_utils.c \
       src/ft_itoa.c \
       src/export.c \
       src/export2.c \
       src/heredoc.c \
       src/in_and_out.c \
       src/prompt.c \
       src/main.c \
       src/arg_treat.c \
       src/arg_utils.c \
       src/char_treat.c \
       src/char_treat_bis.c \
       src/commands_to_exec.c \
       src/hd_exit.c \
       src/expansion_bis.c \
       src/expansion_exec.c \
       src/expansion_utils.c \
       src/input_parse.c \
       src/libft.c \
       src/libft_utils.c \
       src/paths_related.c \
       src/in_out_error.c \
       src/utils.c \
       src/init.c \
       src/deinit.c \
       src/expansion.c \
       src/solo_b_in.c \
       src/builtin.c \
       src/builtin2.c \
       src/env_b_in.c \
       src/signals.c \
       src/exec/funcs.c \
       src/exec/main.c \
       src/exec/resolve.c \
       src/exec/b_in.c \
       src/exec/deinit.c \
       src/exec/exec.c \
       src/exec/generate.c \
       src/exec/rand_file.c \
       src/exec/builtin/echo/main.c \
       src/exec/builtin/pwd/main.c \
       src/exec/builtin/env/main.c \
       src/exec/builtin/exit/main.c \
       src/exec/builtin/unset/main.c \
       src/exec/builtin/export/main.c \
       src/exec/builtin/cd/main.c

all: $(NAME)

$(LIBFT):
	make -C libft all

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
