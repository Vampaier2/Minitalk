/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:18:40 by xalves            #+#    #+#             */
/*   Updated: 2025/08/21 16:52:45 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	handle_signal(int sig)
{
	if (sig == SIGUSR1)
		write(1, "0", 1);
	else if (sig == SIGUSR2)
		write(1, "1", 1);
}

int	main(void)
{
	pid_t	pid;
	struct sigaction sa;

	pid = getpid();
	printf("Server PID: %d\n", pid);

	sa.sa_handler = &handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	while (1)
		pause(); // Wait for signal
}
