/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:18:40 by xalves            #+#    #+#             */
/*   Updated: 2025/09/02 12:02:25 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	ft_atoi(const char *nptr)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * res);
}

void	recieved(int sig)
{
	if (sig == SIGUSR2)
	{
		ft_printf("Message was received by server\n");
		exit(0);
	}
}

static void	send_str(char chr, int pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((chr >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i--;
		usleep(1500);
	}
}

static void	send_len(char *str, int pid)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 31;
	while (i >= 0)
	{
		if ((len >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i--;
		usleep(1500);
	}
}

/* AあЖ€😊🐴 */
int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	signal(SIGUSR1, recieved);
	signal(SIGUSR2, recieved);
	if (argc != 3)
	{
		ft_printerror("Invalid number of arguments\n");
		return (0);
	}
	pid = ft_atoi(argv[1]);
	if (pid < 1 || kill(pid, 0) == -1)
		return (ft_printerror("Invalid PID\n"), 1);
	send_len(argv[2], pid);
	i = 0;
	if (!argv[2][i])
	{
		send_str('\0', pid);
	}
	else
	{
		while (argv[2][i])
			send_str(argv[2][i++], pid);
	}

	while (1)
		pause();
}
