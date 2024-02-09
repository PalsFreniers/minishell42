#include "minishell.h"

int	command_disection(char *command, t_com *comm)
{
	int	i;

	i = 0;
	comm->program = get_the_program(command, &i);
	if (!comm->program)
		return (-1);
	//printf("index de sortie prog name:%d", i);
	comm->arguments = get_the_arguments(command, &i, comm->program);
	if (!comm->arguments)
		return (-1);
	i = 0;
	is_heredoc(command, comm, &i);
	if (!comm->is_heredoc)
		i = 0;
	is_input(command, comm, &i);
	is_output(command, comm);
	return (1);
}