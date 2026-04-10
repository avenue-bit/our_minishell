/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:25:25 by esezalor          #+#    #+#             */
/*   Updated: 2026/04/10 19:15:25 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_UTILS_H
# define LIBFT_UTILS_H

# include <limits.h>
# include <stdarg.h>
# include <stddef.h>

// Keep in Alphabetical Order
long	ft_atol(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
int		ft_printf(const char *__format, ...);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(const char *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_itoa(int n);

#endif