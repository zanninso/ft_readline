/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 22:57:02 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/13 01:46:06 by aait-ihi         ###   ########.fr       */
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
	update_origin_cursor(readline);
	cur_goto(readline, readline->origin_cursor);
	tputs(tgetstr("cd", NULL), 0, output);
	ft_putstr(readline->line);
	cur_goto(readline, readline->cursor);
}

void insert_in_line(t_readline *readline, char c)
{
	char *new_line;
	char *line;
	char *tmp;
	const int cur_position = readline->cursor - readline->origin_cursor;

	line = readline->line;
	if (readline->line_len == cur_position)
	{
		tmp = (char[]){c, 0};
		readline->line[cur_position] = 0;
		new_line = ft_strjoin(readline->line, tmp);
	}
	else
	{
		tmp = (char[]){c, readline->line[cur_position], 0};
		readline->line[cur_position] = 0;
		new_line = ft_strnjoin((char *[]){line, tmp, &line[cur_position + 1]}, 3);
	}
	if (new_line)
	{
		free(line);
		readline->line = new_line;
		readline->line_len++;
		readline->cursor++;
	}
	rewrite_line(readline);
}

void remove_from_line(t_readline *readline)
{
	char *new_line;
	char *line;
	const int cur_position = readline->cursor - readline->origin_cursor;

	line = readline->line;
	if (readline->cursor > readline->origin_cursor)
	{
		line[cur_position - 1] = 0;
		new_line = ft_strjoin(line, line + cur_position);
		if (new_line)
		{
			free(line);
			readline->line = new_line;
			readline->line_len--;
			readline->cursor--;
		}
	}
	rewrite_line(readline);
}
