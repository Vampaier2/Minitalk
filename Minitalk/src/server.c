/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:18:40 by xalves            #+#    #+#             */
/*   Updated: 2025/08/27 18:03:03 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	print_reset(t_server *v)
{
	ft_printf("%s\n", v->str);
	free(v->str);
	v->str = NULL;
	v->bits_len = 31;
	v->len = 0;
}

static int	msg(t_server *v)
{
	if (!v->str)
	{
		v->str = malloc(v->len + 1);
		if (!v->str)
			exit (1);
		v->pos = 0;
	}
	if (v->pos < v->len)
		v->str[v->pos++] = v->c;
	v->c = 0;
	v->binary = 7;
	if (v->pos == v->len)
	{
		v->str[v->pos] = '\0';
		print_reset(v);
		v->pos = 0;
		return (1);
	}
	return (0);
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static t_server	v = {.c = 0, .bits_len = 31, .len = 0, .binary = 7};

	(void)context;
	if (v.bits_len >= 0)
		v.len |= ((sig == SIGUSR2) << v.bits_len--);
	else
	{
		if (sig == SIGUSR2)
			v.c |= (1 << v.binary);
		if (v.binary-- == 0)
		{
			if (msg(&v))
			{
				kill(info->si_pid, SIGUSR2);
				return ;
			}
		}
	}
	kill(info->si_pid, SIGUSR1);

}

int	main(void)
{
	pid_t				pid;
	struct sigaction	signal;

	signal.sa_sigaction = handle_signal;
	sigemptyset(&signal.sa_mask);
	signal.sa_flags = SA_SIGINFO;
	pid = getpid();
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &signal, NULL);
	sigaction(SIGUSR2, &signal, NULL);
	while (1)
		pause();
}
