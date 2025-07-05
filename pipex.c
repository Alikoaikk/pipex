/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:49:04 by akoaik            #+#    #+#             */
/*   Updated: 2025/07/05 17:30:30 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "pipex.h"

void	exec_cmd(char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	if (!args || !args[0] || args[0][0] == '\0')
	{
		write(2, "command not found\n", 18);
		free_strs(args);
		exit(127);
	}
	cmd_path = get_cmd_path(args[0], envp);
	if (!cmd_path)
	{
		write(2, "command not found\n", 18);
		free_strs(args);
		exit(127);
	}
	execve(cmd_path, args, envp);
	perror(cmd_path);
	free_strs(args);
	free(cmd_path);
	exit(127);
}

int	child1(char *cmd, int infile, int *pipefd, char **envp)
{
	if (dup2(infile, 0) < 0)
		error_exit("dup2 infile read error", 1);
	if (dup2(pipefd[1], 1) < 0)
		error_exit("dup2 pipe write error", 1);
	close(pipefd[0]);
	exec_cmd(cmd, envp);
	return (1);
}

int	child2(char **argv, int outfile, int *pipefd, char **envp)
{
	if (dup2(pipefd[0], 0) < 0)
		error_exit("dup2 pipe read", 1);
	outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile < 0)
		error_exit("outfile could not be created", 1);
	if (dup2(outfile, 1) < 0)
		error_exit("dup2 outfile", 1);
	close(pipefd[1]);
	exec_cmd(argv[3], envp);
	return (1);
}

int	handle_main_errors(int argc, char **argv, int *infile)
{
	if (argc != 5)
		error_exit("Use this format: ./pipex infile cmd1 cmd2 outfile", 1);
	*infile = open(argv[1], O_RDONLY);
	if (*infile < 0)
	{
		perror(argv[1]);
		*infile = open("/dev/null", O_RDONLY);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_var	var;
	int		exit_code;

	handle_main_errors(argc, argv, &var.infile);
	if (pipe(var.pipefd) < 0)
		error_exit("pipe failed", 1);
	var.pid1 = fork();
	if (var.pid1 == 0)
		child1(argv[2], var.infile, var.pipefd, envp);
	var.pid2 = fork();
	if (var.pid2 == 0)
		child2(argv, var.outfile, var.pipefd, envp);
	close(var.pipefd[0]);
	close(var.pipefd[1]);
	waitpid(var.pid1, NULL, 0);
	waitpid(var.pid2, &var.status, 0);
	exit_code = (var.status >> 8);
	return (exit_code);
}
