/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_point.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:02:44 by xalves            #+#    #+#             */
/*   Updated: 2025/08/05 10:22:06 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char	get_hex_char2(int tmp, int up_or_low)
{
	if (tmp < 10)
		return (tmp + 48);
	if (up_or_low == 1)
		return (tmp + 55);
	return (tmp + 87);
}

int	ft_handle_point(unsigned long arg, int fd)
{
	char		hex_digits[16];
	long long	i;
	int			count;
	long long	tmp;

	i = 0;
	tmp = 0;
	count = 0;
	if (arg == 0)
		return (ft_putstr_fd("(nil)", fd), 5);
	ft_putstr_fd("0x", 1);
	count = 2;
	while (arg != 0)
	{
		tmp = arg % 16;
		hex_digits[i] = get_hex_char2(tmp, 0);
		i++;
		count++;
		arg /= 16;
	}
	while (--i >= 0)
		ft_putchar_fd(hex_digits[i], fd);
	return (count);
}
