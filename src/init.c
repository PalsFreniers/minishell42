/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:53:37 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/05 22:55:17 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	init_cd_first(t_com *command, char **commands, int i, int command_c)
{
	command->command_id = i + 1;
	command->entry = ENTRY_PIPE;
	command->exit = EXIT_PIPE;
	command->command = commands[i];
	command->error = NULL;
	command->arguments = NULL;
	command->program = NULL;
	command->has_input = false;
	command->expand_hd = false;
	command->has_output = false;
	if (command_disection(commands[i], command))
		return (1);
	if (command->command_id == command_c)
	{
		if (command->exit == EXIT_PIPE)
			command->exit = EXIT_STDOUT;
	}
	if (command->command_id == 1 && command->entry == ENTRY_PIPE)
		command->entry = NO_ENTRY;
	command->input = NULL;
	return (0);
}

t_com	**init_command_data(int command_c, char **commands)
{
	t_com	**commands_data;
	int		i;

	commands_data = malloc((command_c + 1) * sizeof(t_com *));
	if (!commands_data)
		return (NULL);
	i = 0;
	while (i < command_c)
	{
		commands_data[i] = malloc(sizeof(t_com));
		if (!commands_data[i])
			return (commands_data);
		if (init_cd_first(commands_data[i], commands, i, command_c))
			return (NULL);
		i++;
	}
	commands_data[i] = NULL;
	return (commands_data);
}

t_main	*check_commands_integrity(t_main *thgg)
{
	int	i;

	i = 0;
	while (i < thgg->command_c)
	{
		if (!(thgg->commands[i++]))
		{
			printf("syntax error near unexpected token `|'\n");
			return (deinit_thgg(thgg));
		}
	}
	if (!thgg->commands)
		return (deinit_thgg(thgg));
	return (thgg);
}

t_main	*init_thgg(char **envp, char *o_usr_input)
{
	t_main	*thgg;

	thgg = malloc(sizeof(t_main));
	if (!thgg)
		return (NULL);
	thgg->commands = NULL;
	thgg->commands_data = NULL;
	thgg->usr_input = o_usr_input;
	thgg->envp = envp;
	thgg->paths = get_splitted_path(envp);
	thgg->command_c = get_command_number(thgg->usr_input);
	if (thgg->command_c < 1)
		return (thgg);
	thgg->commands = scrap_input(thgg->command_c, thgg->usr_input);
	if (!check_commands_integrity(thgg))
		return (NULL);
	thgg->commands_data = init_command_data(thgg->command_c, thgg->commands);
	if (!thgg->commands_data)
		return (deinit_thgg(thgg));
	return (thgg);
}
