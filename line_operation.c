/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 22:57:02 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/17 17:04:31 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void update_origin_cursor(t_readline *readline)
{
	if(readline->cursor / readline->col == readline->row)
	readline->origin_cursor -= readline->col;
}

void rewrite_line(t_readline *readline)
{
	//update_origin_cursor(readline);
	const int current_cursor = readline->cursor;
	cur_goto(readline, readline->origin_cursor);
	tputs(tgetstr("cd", NULL), 0, output);
	ft_putstr(readline->cmd->tmp_line);
	cur_goto(readline, current_cursor);
}

void insert_in_line(t_readline *readline, char *str)
{
	char *new_line;
	char *line;
	char *tmp;
	int i;
	const int cur_position = readline->cursor - readline->origin_cursor;

	line = readline->cmd->tmp_line;
	if (readline->cmd->tmp_len == cur_position)
		new_line = ft_strjoin(line, str);
	else
	{
		tmp = (char[]){line[cur_position], 0};
		line[cur_position] = 0;
		new_line = ft_strnjoin((char *[]){line, str, tmp, &line[cur_position + 1]}, 4);
	}
	if (new_line)
	{
		free(line);
		readline->cmd->tmp_line = new_line;
		i = ft_strlen(str);
		readline->cmd->tmp_len += i;
		readline->cursor += i;
	}
	rewrite_line(readline);
}

void remove_from_line(t_readline *readline)
{
	char *new_line;
	char *line;
	const int cur_position = readline->cursor - readline->origin_cursor;

	line = readline->cmd->tmp_line;
	if (readline->cursor > readline->origin_cursor)
	{
		line[cur_position - 1] = 0;
		new_line = ft_strjoin(line, line + cur_position);
		if (new_line)
		{
			free(line);
			readline->cmd->tmp_line = new_line;
			readline->cmd->tmp_len--;
			readline->cursor--;
		}
	}
	rewrite_line(readline);
}
