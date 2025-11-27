/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:59:40 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/27 13:01:44 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_itoa(int n)
{
	long	nb_cast;
	char	*p;
	int		len;

	nb_cast = (long)n;
	len = len_number(nb_cast);
	p = malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	p[len] = '\0';
	if (nb_cast == 0)
		p[0] = '0';
	if (nb_cast < 0)
	{
		nb_cast = -nb_cast;
		p[0] = '-';
	}
	while (nb_cast > 0)
	{
		p[len - 1] = (nb_cast % 10 + '0');
		nb_cast = nb_cast / 10;
		len--;
	}
	return (p);
}

int	ft_atoi(const char *s)
{
	int	result;
	int	i;
	int	signe;

	result = 0;
	i = 0;
	signe = 1;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
	{
		i++;
	}
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			signe = signe * -1;
		i++;
	}
	while (s[i] != '\0' && s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i] - '0');
		i++;
	}
	return (result * signe);
}

void	ft_free_tab(char **tab)
{
	int	i;

	if (tab)
	{
		i = 0;
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
	}
	free(tab);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	char	result;

	nb = (long)n;
	if (nb < 0)
	{
		nb = -nb;
		write(fd, "-", 1);
	}
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	if (nb < 10)
	{
		result = nb + '0';
		write(fd, &result, 1);
	}
}
