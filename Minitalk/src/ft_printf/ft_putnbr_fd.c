/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:26:55 by xalves            #+#    #+#             */
/*   Updated: 2025/08/05 10:22:13 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_putnbr_fd(int n, int fd)
{
	int	i;

	i = 0;
	if (fd < 0)
		return (ft_putstr_fd("(null)", fd));
	if (n == -2147483648)
	{
		i += ft_putchar_fd('-', fd);
		i += ft_putchar_fd('2', fd);
		n = 147483648;
	}
	if (n < 0)
	{
		i += ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
	{
		i += ft_putnbr_fd(n / 10, fd);
	}
	i += ft_putchar_fd(n % 10 + '0', fd);
	return (i);
}
