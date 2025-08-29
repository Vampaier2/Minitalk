/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 10:28:11 by xalves            #+#    #+#             */
/*   Updated: 2025/08/29 11:31:46 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	print_and_reset(t_server *v)
{
	ft_printf("%s\n", v->str);
	free(v->str);
	v->str = NULL;
	v->bits_pos = 31;
	v->msg_len = 0;
}

static int	msg(t_server *v)
{
	if (!v->str)
	{
		v->str = malloc(v->msg_len + 1);
		if (!v->str)
			exit(1);
		v->message_pos = 0;
	}
	if (v->message_pos < v->msg_len)
		v->str[v->message_pos++] = v->current_char;
	v->current_char = 0;
	v->char_bit_index = 7;
	if (v->message_pos == v->msg_len)
	{
		v->str[v->message_pos] = '\0';
		print_and_reset(v);
		v->message_pos = 0;
		return (1);
	}
	return (0);
}

/// @brief
/// @param sig The signal number ex:(SIGUSR1, SIGUSR2)
/// @param info Pointer to the signal information (PID)
/// @param context A pointer to a structure (containing CPU states and more)
void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static t_server	v = {.current_char = 0, .bits_pos = 31, .msg_len = 0,
		.char_bit_index = 7};

	(void)context;
	if (sig == SIGINT)
	{
		printf("\nDetected Ctr+C (%d)\nStoping current Process.\n", sig);
		kill(info->si_pid, SIGINT);
	}
	if (v.bits_pos >= 0)
		v.msg_len |= ((sig == SIGUSR2) << v.bits_pos--);
	else
	{
		if (sig == SIGUSR2)
			v.current_char |= (1 << v.char_bit_index);
		if (v.char_bit_index-- == 0)
		{
			if (msg(&v))
			{
				kill(info->si_pid, SIGUSR2); // Reply to sender with SIGUSR2
				return ;
			}
		}
	}
	kill(info->si_pid, SIGUSR1);
}

/// @brief Executes handle_signal() when receives signal
/// @return nothing it runs until you stop the process( Ctrl + C )
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
	sigaction(SIGINT, &signal, NULL);
	while (1)
		pause();
}
