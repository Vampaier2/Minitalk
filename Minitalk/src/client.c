/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:18:40 by xalves            #+#    #+#             */
/*   Updated: 2025/08/21 16:29:53 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	size_t			m;
	size_t			i;
	unsigned char	*ptr_aux;

	m = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > (m / size))
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	ptr_aux = (unsigned char *)ptr;
	while (i < m)
	{
		ptr_aux[i] = 0;
		i++;
	}
	return (ptr_aux);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	new_str = ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < s1_len && s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len && s2[i])
	{
		new_str[s1_len + i] = s2[i];
		i++;
	}
	return (new_str);
}

char	*ft_strdup(const char *s)
{
	int		len;
	char	*dup_str;

	len = ft_strlen((char *)s);
	dup_str = malloc(sizeof(char) * (len + 1));
	if (!dup_str)
		return (NULL);
	len = 0;
	while (s[len])
	{
		dup_str[len] = s[len];
		len++;
	}
	dup_str[len] = '\0';
	return (dup_str);
}

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

int	main(int argc, char const **argv)
{
	pid_t	pid;
	int		asciis;
	char	binary[9];
	int		msg_len;
	int		i;
	int		j;
	char	*message;
	char	*tmp;

	i = 0;
	j = 7;
	pid = getpid();
	message = ft_strdup("");
	if (argc != 3)
	{
		ft_printerror("Not enought arguments ->%d", argc - 1);
	}
	else
	{
		if (ft_atoi(argv[1]) <= 0)
		{
			ft_printerror("Invalid PID -> %s\n", argv[1]);
			free(message);
			return (1);
		}

		ft_printf("Client PID: %d\n", pid);
		ft_printf("Enough arguments -> %d\n", argc - 1);
		msg_len = ft_strlen(argv[2]);
		ft_printf("Message lenght ->%d\n", msg_len);
		while (i != msg_len)
		{
			asciis = argv[2][i];
			ft_printf("ASCII -> %d\n", asciis);
			// Binary
			while (j >= 0)
			{
				binary[7 - j] = ((asciis >> j) & 1) + '0';
				j--;
			}
			binary[8] = '\0';
			ft_printf("Binary (8-bit) %d -> %s\n", argv[2][i], binary);
			// strjoin the binary to -> message
			tmp = ft_strjoin(message, binary);
			free(message);
			message = tmp;
			j = 7;
			i++;
		}
		ft_printf("The message in Binary is -> %s\n", message);
	}
	// Send signals to server
	i = 0;
	while (message[i])
	{
		if (message[i] == '0')
			kill(ft_atoi(argv[1]), SIGUSR1);
		else
			kill(ft_atoi(argv[1]), SIGUSR2);
		usleep(100); // allow time for server to process
		i++;
	}
	free(message);
	return (0);
}
