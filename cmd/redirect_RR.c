#include "../minishell.h"

extern t_ext g_var;

int	ft_redirect_RR(t_cmd *c)
{
	pid_t	pid;
	int		out;
	int		status;

	pid = fork();
	g_var.pid[g_var.pnum++] = pid;
	if (pid == 0)
	{
		out = open(c[1].cmd[0], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (out < 0)
		{
			printf("minishell: no such file or directory: %s\n", c[1].cmd[0]);
			return (1);
		}
		if (c[1].cmd[1])
		{
			close(out);
			return (1);
		}
		dup2(out, STDOUT_FILENO);
		run_cmd(c[0].cmd);
		close(out);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	return (SUCCESS);
}
