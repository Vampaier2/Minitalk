/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:26:29 by xalves            #+#    #+#             */
/*   Updated: 2025/08/18 14:18:59 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	detect_conversion(char c, va_list arg)
{
	if (c == 'c')
		return (ft_putchar_fd(va_arg(arg, int), 1));
	if (c == 's')
		return (ft_putstr_fd(va_arg(arg, char *), 1));
	if (c == 'p')
		return (ft_handle_point(va_arg(arg, unsigned long), 1));
	if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(arg, int), 1));
	if (c == 'u')
		return (ft_putdecimal_int(va_arg(arg, unsigned int), 1));
	if (c == 'x')
		return (ft_handle_hex(va_arg(arg, int), 1, 0));
	if (c == 'X')
		return (ft_handle_hex(va_arg(arg, int), 1, 1));
	if (c == '%')
		return (ft_putchar_fd('%', 1));
	return (-1);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	arg;
	int		count;

	count = 0;
	i = 0;
	if (!str || write(1, 0, 0) == -1)
		return (-1);
	va_start(arg, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			if (!str[i + 1])
				return (va_end(arg), -1);
			count += detect_conversion(str[i + 1], arg);
			i += 2;
		}
		else
		{
			count += ft_putchar_fd(str[i], 1);
			i++;
		}
	}
	return (va_end(arg), count);
}
