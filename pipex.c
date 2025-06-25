/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:49:04 by akoaik            #+#    #+#             */
/*   Updated: 2025/06/26 00:50:26 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	cmd_path = get_cmd_path(args[0], envp);
	if (!cmd_path)
	{
		perror("command not found");
		free_strs(args);
		exit(127);
	}
	execve(cmd_path, args, envp);
	perror("execve");
	free_strs(args);
	exit(1);
}

int	child1(char *cmd, int infile, int *pipefd, char **envp)
{
	if (dup2(infile, STDIN_FILENO) < 0)
		error_exit("dup2 infile");
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		error_exit("dup2 pipe write");
	close(pipefd[0]);
	exec_cmd(cmd, envp);
	return (1);
}

int	child2(char *cmd, int outfile, int *pipefd, char **envp)
{
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		error_exit("dup2 pipe read");
	if (dup2(outfile, STDOUT_FILENO) < 0)
		error_exit("dup2 outfile");
	close(pipefd[1]);
	exec_cmd(cmd, envp);
	return (1);
}

int	handle_main_errors(int argc, char **argv, int *infile, int *outfile)
{
	if (argc != 5)
		error_exit("Usage: ./pipex infile cmd1 cmd2 outfile");
	*infile = open(argv[1], O_RDONLY);
	if (*infile < 0)
		error_exit("infile");
	*outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*outfile < 0)
		error_exit("outfile");
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	handle_main_errors(argc, argv, &infile, &outfile);
	if (pipe(pipefd) < 0)
		error_exit("pipe");
	pid1 = fork();
	if (pid1 == 0)
		child1(argv[2], infile, pipefd, envp);
	pid2 = fork();
	if (pid2 == 0)
		child2(argv[3], outfile, pipefd, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
