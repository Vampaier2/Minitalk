/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:26:19 by xalves            #+#    #+#             */
/*   Updated: 2025/08/07 15:36:21 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char	get_hex_char(int tmp, int up_or_low)
{
	if (tmp < 10)
		return (tmp + 48);
	if (up_or_low == 1)
		return (tmp + 55);
	return (tmp + 87);
}

int	ft_handle_hex(unsigned int arg, int fd, int up_or_low)
{
	char	hex_digits[16];
	int		i;
	int		count;
	int		tmp;

	i = 0;
	tmp = 0;
	count = 0;
	if (arg == 0)
		return (ft_putchar_fd('0', fd), 1);
	while (arg != 0)
	{
		tmp = arg % 16;
		hex_digits[i] = get_hex_char(tmp, up_or_low);
		i++;
		count++;
		arg /= 16;
	}
	while (--i >= 0)
		ft_putchar_fd(hex_digits[i], fd);
	return (count);
}
