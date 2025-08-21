/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:09:58 by xalves            #+#    #+#             */
/*   Updated: 2025/08/20 16:14:47 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <limits.h>

int	ft_printf(const char *str, ...);

int	ft_putchar_fd(unsigned char c, int fd);

int	ft_putdecimal_int(unsigned int arg, int fd);

int	ft_putnbr_fd(int n, int fd);

int	ft_putstr_fd(char *s, int fd);

int	ft_handle_hex(unsigned int arg, int fd, int up_or_low);

int	ft_handle_point(unsigned long arg, int fd);

//------- print error
int	ft_printerror(const char *str, ...);

#endif
