/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esezalor <esezalor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:53:44 by jille             #+#    #+#             */
/*   Updated: 2026/03/17 18:53:52 by esezalor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_utils.h"
#include <stdarg.h>

static int	f_printstr(char *cs, char c, int check_cs)
{
	int	len;

	if (check_cs)
		if (!cs && c == 0)
			return (write(1, "(null)", 6), 6);
	if ((!cs && c > 0) || (!cs && c < 0) || (!cs && c == 0))
		return (write(1, &c, 1), 1);
	len = 0;
	while (*cs)
	{
		write(1, cs, 1);
		cs++;
		len++;
	}
	return (len);
}

static int	f_baselen(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		j = i + 1;
		while (base[j])
			if (base[i] == base[j++])
				return (0);
		i++;
	}
	return (i);
}

static int	f_putnbrbase(long long nbr, char *base, char conv, int len)
{
	long long	num;
	int			baselen;

	baselen = f_baselen(base);
	if (baselen < 2)
		return (0);
	num = nbr;
	if ((conv == 'd' || conv == 'i' || conv == 'u') && num < 0)
	{
		write(1, "-", 1);
		num *= -1;
		len++;
	}
	else if (conv == 'p' && nbr == 0)
	{
		len += f_printstr("(nil)", 0, 1);
		return (len);
	}
	else if (conv == 'p' && len == 0)
		len += f_printstr("0x", 0, 1);
	if (num > (baselen - 1))
		len = f_putnbrbase(num / baselen, base, conv, len);
	write(1, &base[num % baselen], 1);
	return (len + 1);
}

static int	f_check_input(const char conv, va_list arglist, int len)
{
	char	*base10;
	char	*lhex;
	char	*uhex;

	base10 = "0123456789";
	lhex = "0123456789abcdef";
	uhex = "0123456789ABCDEF";
	if (conv == 'c')
		len += f_printstr(NULL, (char)va_arg(arglist, int), 0);
	else if (conv == 's')
		len += f_printstr(va_arg(arglist, char *), 0, 1);
	else if (conv == 'p')
		len += f_putnbrbase(va_arg(arglist, long), lhex, conv, 0);
	else if (conv == 'd' || conv == 'i')
		len += f_putnbrbase(va_arg(arglist, int), base10, conv, 0);
	else if (conv == 'u')
		len += f_putnbrbase(va_arg(arglist, unsigned), base10, conv, 0);
	else if (conv == 'x')
		len += f_putnbrbase(va_arg(arglist, unsigned), lhex, conv, 0);
	else if (conv == 'X')
		len += f_putnbrbase(va_arg(arglist, unsigned), uhex, conv, 0);
	else if (conv == '%')
		len += f_printstr(NULL, '%', 0);
	return (len);
}

int	ft_printf(const char *__format, ...)
{
	va_list	arglist;
	int		slen;
	int		i;
	char	*convers;

	if (!__format)
		return (-1);
	i = 0;
	slen = 0;
	convers = "cspdiuxX%";
	va_start(arglist, __format);
	while (__format[i])
	{
		if (__format[i] == '%' && ft_strchr(convers, __format[i + 1]))
			slen += f_check_input(__format[++i], arglist, 0);
		else
		{
			if (__format[i] == '%' && !ft_strchr(convers, __format[i + 1]))
				return (-1);
			slen += f_printstr(NULL, __format[i], 0);
		}
		i++;
	}
	va_end(arglist);
	return (slen);
}

// #include <stdio.h>
// #include <limits.h>
// int	main(void)
// {
// 	char b[] = "ab";
// 	printf("\n%i\n", ft_printf("%% 372"));
// 	printf("\n%i\n", printf("%% 372"));
// }

// int	main(void)
// {
// 	int	i;
// 	int j;
// 	unsigned int	u;
// 	unsigned long int	ft;
// 	unsigned long int	*ptr;
// 	char	*test = NULL;

// 	ft = 42;
// 	ptr = &ft;
// 	u = 2150505050;

// 	ft_printf("\n\n%s\n", "-----Testing %-----");
// 	i = ft_printf("% ");
// 	ft_printf("%d\n", i);
// 	j = printf("% ");
// 	printf("%d\n", j);
// 	ft_printf("\n\n%s\n", "-----Testing chars-----");
// 	i = ft_printf(":%c:%c:%c:%c:%c:%c:%c:\n", 0, 9, 32, 65, 122, 127, 128);
// 	ft_printf("%d\n", i);
// 	j = printf(":%c:%c:%c:%c:%c:%c:%c:\n", 0, 9, 32, 65, 122, 127, 128);
// 	printf("%d\n", j);
// 	ft_printf("\n\n%s\n", "-----Testing strings-----");
// 	i = ft_printf(":%s:\n", test);
// 	ft_printf("%d\n", i);
// 	j = printf(":%s:\n", test);
// 	printf("%d\n", j);
// 	i = ft_printf(":%s:\n", "");
// 	ft_printf("%d\n", i);
// 	j = printf(":%s:\n", "");
// 	printf("%d\n", j);
// 	i = ft_printf(":%s:\n", "		I want to finish printf123#+!.");
// 	ft_printf("%d\n", i);
// 	j = printf(":%s:\n", "		I want to finish printf123#+!.");
// 	printf("%d\n", j);
// 	ft_printf("\n\n%s\n", "-----Testing decimal numbers-----");
// 	i = ft_printf(":%i:%i:%i:\n", 0, INT_MAX, INT_MIN);
// 	ft_printf("%d\n", i);
// 	j = printf(":%i:%i:%i:\n",  0, INT_MAX, INT_MIN);
// 	printf("%d\n", j);
// 	i = ft_printf(":%d:%d:%d:\n",  0, INT_MAX, INT_MIN);
// 	ft_printf("%d\n", i);
// 	j = printf(":%d:%d:%d:\n",  0, INT_MAX, INT_MIN);
// 	printf("%d\n", j);
// 	ft_printf("\n\n%s\n", "-----Testing %-----");
// 	i = ft_printf(":50%% & 100%%:\n");
// 	ft_printf("%d\n", i);
// 	j = printf(":50%% & 100%%:\n");
// 	printf("%d\n", j);
// 	ft_printf("\n\n%s\n", "-----Testing unsigned int-----");
// 	i = ft_printf(":%u:%u:%u:\n", 0, INT_MAX, -1);
// 	ft_printf("%d\n", i);
// 	j = printf(":%u:%u:%u:\n", 0, INT_MAX, -1);
// 	printf("%d\n", j);
// 	ft_printf("\n\n%s\n", "-----Testing HEX-----");
// 	i = ft_printf(":%x:%x:%x:\n", 0, INT_MAX, INT_MIN);
// 	ft_printf("%d\n", i);
// 	j = printf(":%x:%x:%x:\n", 0, INT_MAX, INT_MIN);
// 	printf("%d\n", j);
// 	i = ft_printf(":%X:%X:%X:\n", 0, INT_MAX, INT_MIN);
// 	ft_printf("%d\n", i);
// 	j = printf(":%X:%X:%X:\n", 0, INT_MAX, INT_MIN);
// 	printf("%d\n", j);
// 	ft_printf("\n\n%s\n", "-----Testing PTR-----");
// 	ft_printf("%p\n", ptr);
// 	printf("%p\n", ptr);
// 	i = ft_printf("%p\n", NULL);
// 	ft_printf("%d\n", i);
// 	j = printf("%p\n", NULL);
// 	printf("%d\n", j);
// 	return (0);
// }

/*
get rid of this undefined behaviour after eval:

		if (__format[i] == '%' && !ft_strchr(convers, __format[i + 1]))
				return (-1);
*/