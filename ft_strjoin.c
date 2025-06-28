/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:22:22 by akoaik            #+#    #+#             */
/*   Updated: 2025/06/27 19:10:43 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static unsigned int	totl_len(const char *s1, const char *s2)
{
	return (ft_strlen(s1) + ft_strlen(s2));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*result;

	if (!s1 || !s2)
		return (0);
	result = (char *)malloc(totl_len(s1, s2) + 1);
	if (!result)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return (result);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*s1;
// 	char	*s2;
// 	char	*my_name;

// 	s1 = "Ali ";
// 	s2 = "Koaik";
// 	my_name = ft_strjoin(s1, s2);
// 	printf("%s", my_name);
// 	return (0);
// }