/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 22:57:02 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/15 05:07:56 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void rewrite_line(t_readline *readline)
{
	update_o_cursor(readline);
	tputs(tgoto(tgetstr("cm", 0), 0,readline->o_cursor.y), 0, output);
	tputs(tgetstr("cd", NULL), 0, output);
	ft_printf("➜  ft_readline git:(master) ");
	ft_putstr(readline->cmd->tmp_line);
	ft_printf(" ");
	cur_goto(readline, readline->cursor);
}

void insert_in_line(t_readline *readline, char *str)
{
	char *new_line;
	char *line;
	const int i = ft_strlen(str);
	
	line = readline->cmd->tmp_line;
	new_line = ft_strnew(readline->cmd->tmp_len + i);
	ft_strncpy(new_line, line, readline->line_index);
	ft_strcat(new_line, str);
	ft_strcat(new_line, line + readline->line_index);
	if (new_line)
	{
		free(line);
		readline->cmd->tmp_line = new_line;
		readline->cmd->tmp_len += i;
		readline->line_index += i;
		readline->line_props.details[readline->line_props.index] += i;
		if (ft_strchr(str, '\n'))
			readline->line_props.details = get_line_details(readline);
		set_cursor_from_index(readline);
	}
	rewrite_line(readline);
}

void remove_from_line(t_readline *readline, int start, int end)
{
	char *new_line;
	char *line;
	int is_line;
	const int len = end - start;

	line = readline->cmd->tmp_line;
	if (start >= 0)
	{
		is_line = !!ft_strnstr(&line[start], "\n", len);
		line[start] = 0;
		new_line = ft_strjoin(line, line + end);
		if (new_line)
		{
			free(line);
			readline->cmd->tmp_line = new_line;
			readline->cmd->tmp_len -= len;
			readline->line_index -= len;
			readline->line_props.details[readline->line_props.index] -= len;
			if (is_line == '\n')
				readline->line_props.details = get_line_details(readline);
			set_cursor_from_index(readline);
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
	if (!(ret = ft_memalloc(sizeof(int) * line_count)))
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