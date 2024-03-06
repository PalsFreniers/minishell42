CC = cc
LD = ar
NAME = libft.a
SRCS = ft_arena.c \
      ft_complex_math.c \
      ft_complex.c \
      ft_isascii.c \
      ft_memcmp.c \
      ft_printf_special_handlers_p1.c \
      ft_putnbr_fd.c \
      ft_strdup.c \
      ft_strlcpy.c \
      ft_strprefix.c \
      ft_tolower.c \
      ft_atoi.c \
      ft_count.c \
      ft_isdigit.c \
      ft_memcpy.c \
      ft_printf_special_handlers_p2.c \
      ft_putstr_fd.c \
      ft_string.c \
      ft_strlen.c \
      ft_strrchr.c \
      ft_toupper.c \
      ft_bzero.c \
      ft_free.c \
      ft_isprint.c \
      ft_memmove.c \
      ft_printf_specials.c \
      ft_rand.c \
      ft_striteri.c \
      ft_strmapi.c \
      ft_strsufix.c \
      ft_calloc.c \
      ft_isalnum.c \
      ft_itoa.c \
      ft_memset.c \
      ft_putchar_fd.c \
      ft_split.c \
      ft_strjoin.c \
      ft_strncmp.c \
      ft_strtrim.c \
      ft_isalpha.c \
      ft_memchr.c \
      ft_printf.c \
      ft_putendl_fd.c \
      ft_strchr.c \
      ft_strlcat.c \
      ft_strnstr.c \
      ft_substr.c \
      ft_getenv.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -fpie
LDFLAGS = -rcs

all:$(NAME)

$(NAME): $(OBJS)
	@$(LD) $(LDFLAGS) $(NAME) $(OBJS) 
	@echo "libft compiled !!"

%.o : %.c
	$(CC) $(CFLAGS) $< -c -o $@

fclean: clean
	@rm -f $(NAME)
	@echo "libft fclean"

clean:
	@rm -f $(OBJS)
	@echo "libft clean"

re: fclean all

.PHONY: all fclean clean re
