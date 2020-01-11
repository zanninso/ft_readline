/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 22:57:02 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/11 02:10:49 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

// void update_o_cursor(t_readline *readline)
// {
// 	if(readline->cursor / readline->col == readline->row)
// 	readline->o_cursor -= readline->col;
// }

void rewrite_line(t_readline *readline)
{
	//update_o_cursor(readline);
	int current_cursor = readline->cursor;
	int index = readline->line_props.index;

	readline->line_props.index = 0;
	set_virtual_origin(readline);
	cur_goto(readline, 0);
	tputs(tgetstr("cd", NULL), 0, output);
	ft_putstr(readline->cmd->tmp_line);
	readline->line_props.index = index;
	set_virtual_origin(readline);
	cur_goto(readline, current_cursor);
}

void insert_in_line(t_readline *readline, char *str)
{
	char *new_line;
	char *line;
	char *tmp;
	const int i = ft_strlen(str);

	line = readline->cmd->tmp_line;
	if (readline->cmd->tmp_len == readline->line_index)
		new_line = ft_strjoin(line, str);
	else
	{
		tmp = (char[]){line[readline->line_index], 0};
		line[readline->line_index] = 0;
		new_line = ft_strnjoin((char *[]){line, str, tmp, &line[readline->line_index + 1]}, 4);
	}
	if (new_line)
	{
		free(line);
		readline->cmd->tmp_line = new_line;
		readline->cmd->tmp_len += i;
		readline->line_props.details[readline->line_props.index] += i;
		readline->cursor += i;
	}
	rewrite_line(readline);
}

void remove_from_line(t_readline *readline)
{
	char *new_line;
	char *line;
	char c;

	line = readline->cmd->tmp_line;
	if (readline->line_index > 0)
	{
		c = line[readline->line_index - 1];
		line[readline->line_index - 1] = 0;
		new_line = ft_strjoin(line, line + readline->line_index);
		if (new_line)
		{
			free(line);
			readline->cmd->tmp_line = new_line;
			readline->cmd->tmp_len--;
			readline->line_index--;
			readline->line_props.details[readline->line_props.index]--;
			if (c == '\n')
			{
				readline->line_props.index--;
				readline->cursor = readline->line_props.details[readline->line_props.index];
				readline->line_props.details = get_line_details(readline);
			}
			else
				readline->cursor--;
		}
	}
	rewrite_line(readline);
}

int *get_line_details(t_readline *readline)
{
	int *ret;
	char *tmp;
	int line_count;
	int i;
	char *line;

	line = readline->cmd->tmp_line;
	line_count = 1 + ft_str_occurence(line, '\n');
	if (!(ret = malloc(sizeof(int) * line_count)))
		return (NULL);
	i = 0;
	readline->line_props.linecount = line_count;
	while ((tmp = (char *)ft_skip_unitl_char(line, "\n")))
	{
		*tmp == '\n' ? tmp++ : 0;
		ret[i++] = tmp - line;
		line = tmp;
		if (*tmp == '\0')
			break;
	}
	return (ret);
}