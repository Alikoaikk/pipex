/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:31:35 by akoaik            #+#    #+#             */
/*   Updated: 2025/06/26 00:07:00 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0 ;
	while (i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		if (s1[i] == '\0')
			break ;
		i++;
	}
	return (0);
}

// #include <stdio.h>

// int main(int argc, char *argv[])
// {
//     const char *str1 = argv[1];
//     const char *str2 = argv[2];
//     unsigned int n = 5;

//     int result = ft_strncmp(str1, str2, n);

//     printf("ft_strncmp result: %d\n", result);

//     return 0;
// }