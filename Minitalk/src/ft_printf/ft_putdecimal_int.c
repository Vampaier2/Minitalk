/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdecimal_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:26:49 by xalves            #+#    #+#             */
/*   Updated: 2025/08/05 10:22:11 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_putdecimal_int(unsigned int arg, int fd)
{
	int	i;

	i = 0;
	if (arg >= 10)
		i += ft_putdecimal_int(arg / 10, fd);
	i += ft_putchar_fd(arg % 10 + '0', fd);
	return (i);
}
