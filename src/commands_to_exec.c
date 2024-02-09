#include "minishell.h"

int	command_disection(char *command, t_com *comm)
{
	int	i;
	int last_heredoc_i;

	i = 0;
	comm->program = get_the_program(command, &i);
	if (!comm->program)
		return (-1);
	comm->arguments = get_the_arguments(command, &i, comm->program);
	if (!comm->arguments)
		return (-1);
	last_heredoc_i = 0;
	is_heredoc(command, comm, &last_heredoc_i);
	if (!comm->is_heredoc)
		last_heredoc_i = 0;
	is_input(command, comm, last_heredoc_i);
	is_output(command, comm);
	if (comm->error)
	{
		printf("%s: No such file or directory\n", comm->error);
		return (-1);
	}
	return (1);
}