/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:44:03 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/16 23:13:08 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	cur_move_by_word(t_readline *readline, int button)
{
	char		*tmp;
	const char	*line = readline->cmd->tmp_line;

	tmp = NULL;
	if (button == BUTTON_ALT_RIGHT)
	{
		tmp = (char *)ft_skip_unitl_char(line + readline->line_index, "\n '\";");
		tmp = ft_skip_chars(tmp, "\n '\";");
	}
	else if (button == BUTTON_ALT_LEFT)
	{
		tmp = ft_rskip_chars(line, "\n '\";", readline->line_index - 1);
		tmp = ft_rskip_unitl_char(line, "\n '\";", tmp - line);
		if (ft_isinstr(*tmp, "\n '\";"))
			tmp++;
	}
	readline->line_index += tmp - &line[readline->line_index];
	set_cursor_from_index(readline);
	cur_goto(readline, readline->cursor);
}

void	cur_up(t_readline *readline)
{
	t_line		line_props;
	const int	*details = readline->line_props.details;
	const int	cursor = readline->cursor;

	if (readline->line_props.index > 0)
	{
		readline->line_props.index--;
		line_props = readline->line_props;
		readline->cursor = ft_min(details[line_props.index] - 1, cursor);
		set_virtual_origin(readline);
		cur_goto(readline, readline->cursor);
	}
}

void	cur_down(t_readline *readline)
{
	t_line		line_props;
	const int	*details = readline->line_props.details;
	const int	cursor = readline->cursor;

	if (readline->line_props.index + 1 < readline->line_props.linecount)
	{
		readline->line_props.index++;
		line_props = readline->line_props;
		readline->cursor = ft_min(details[line_props.index] - 1, cursor);
		set_virtual_origin(readline);
		cur_goto(readline, readline->cursor);
	}
}

void	cur_left(t_readline *readline)
{
	t_line	line_props;

	line_props = readline->line_props;
	if (readline->cursor - 1 < 0 && readline->line_props.index > 0)
	{
		readline->cursor = line_props.details[line_props.index - 1] - 1;
		return (cur_up(readline));
	}
	else if (readline->line_index - 1 < 0)
		return ;
	readline->cursor--;
	cur_goto(readline, readline->cursor);
}

void	cur_right(t_readline *readline)
{
	t_line	line_props;

	line_props = readline->line_props;
	if (readline->cursor + 1 >= line_props.details[line_props.index])
		if (readline->line_props.index + 1 < readline->line_props.linecount)
		{
			readline->cursor = 0;
			return (cur_down(readline));
		}
	if (readline->cursor >= line_props.details[line_props.index])
		return ;
	readline->cursor++;
	cur_goto(readline, readline->cursor);
}
