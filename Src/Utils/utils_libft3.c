/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:59:40 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/24 18:16:59 by jdelattr         ###   ########.fr       */
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
	p = malloc(sizeof(char) * (len +1));
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
