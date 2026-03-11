/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:25:25 by esezalor          #+#    #+#             */
/*   Updated: 2026/03/11 15:20:21 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_UTILS_H
# define LIBFT_UTILS_H

# include <limits.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

// Keep in Alphabetical Order
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	**ft_split(const char *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);


#endif