/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:47:18 by akoaik            #+#    #+#             */
/*   Updated: 2025/07/05 17:18:37 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>

typedef struct variables
{
	int		infile;
	int		outfile;
	int		pipefd[2];
	int		pid1;
	int		pid2;
	int		status;
}	t_var;

void	error_exit(const char *msg, int exit_code);
char	*get_cmd_path(char *cmd, char **envp);
void	exec_cmd(char *cmd, char **envp);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
void	free_strs(char **strs);
size_t	ft_strlen(const char *s);

#endif
