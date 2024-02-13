/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:11:06 by tdelage           #+#    #+#             */
/*   Updated: 2024/02/08 14:26:23 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include "enums.h"
# include "ft_printf.h"
# include "iodef.h"
# include "structs.h"
# include "types.h"

// ft_strings
struct s_string		ft_string_create(char *ptr, size_t len);
struct s_string		ft_string_from_cstr(char *str);

// ft_arena
struct s_arena		ft_arena_create(size_t size);
void				ft_arena_destroy(struct s_arena *arena);
void				*ft_arena_alloc(struct s_arena *arena, size_t size);

// ft_complex
struct s_complex	ft_complex_create(t_f64 real, t_f64 imag);
struct s_complex	ft_complex_add(struct s_complex a, struct s_complex b);
struct s_complex	ft_complex_sub(struct s_complex a, struct s_complex b);
struct s_complex	ft_complex_mul(struct s_complex a, struct s_complex b);
struct s_complex	ft_complex_div(struct s_complex a, struct s_complex b);

// ft_memory
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_free(enum e_freeable which, ...);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

// ft_chars
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

// ft_cstrings
size_t				ft_strlen(const char *s);
size_t				ft_strlenc(const char *s, char c);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t size);
int					ft_strequ(const char *s1, const char *s2);
char				*ft_strnstr(const char *str, const char *sub, size_t n);
char				*ft_strdup(const char *str);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
int					ft_strsufix(char *s, char *sufix);
int					ft_strprefix(char *s, char *prefix);
char				**ft_split(char const *str, char charset);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

// ft_convert
char				*ft_itoa(int n);
int					ft_atoi(const char *str);

// ft_output
int					ft_putchar_fd(char c, int fd);
int					ft_putstr_fd(char *str, int fd);
int					ft_putendl_fd(char *str, int fd);
int					ft_putnbr_fd(long long int nb, int fd, int radix, int up);
int					ft_putunbr_fd(unsigned long long int nb, int fd, int radix,
						int up);

// ft_rand
void				ft_srand(unsigned int seed);
int					ft_rand(int a, int b);

// ft_count
void				ft_count(char *str, char c, size_t *of, size_t *ofnt);
size_t				ft_countof(char *str, char c);
size_t				ft_countofnot(char *str, char c);

// ft_env
char				*ft_getenv(char *name, char **env);

#endif // LIBFT_H
