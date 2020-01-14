/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 22:57:02 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/14 09:34:37 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void rewrite_line(t_readline *readline)
{
	//update_o_cursor(readline);
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
	char *tmp;
	const int i = ft_strlen(str);

	line = readline->cmd->tmp_line;
	new_line = NULL;
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
		if (ft_strchr(str, '\n'))
			readline->line_props.details = get_line_details(readline);
		else 
			readline->line_props.details[readline->line_props.index] += i;
		readline->line_index += i;
		set_cursor_from_index(readline);
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
				readline->line_props.details = get_line_details(readline);
				set_cursor_from_index(readline);
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