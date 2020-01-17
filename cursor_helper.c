/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:44:38 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/16 23:40:15 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	set_virtual_origin(t_readline *readline)
{
	int		i;
	t_point	origin;

	origin = readline->o_cursor;
	i = readline->line_props.index;
	while (i > 0)
	{
		i--;
		origin.y += readline->line_props.details[i] / readline->col;
		origin.y += (readline->line_props.details[i] % readline->col) > 0;
		origin.x = 0;
	}
	readline->ov_cursor = origin;
}

void	set_idnex_from_cursor(t_readline *readline)
{
	int		index;
	int		i;

	i = readline->line_props.index;
	index = readline->cursor;
	while (i)
	{
		i--;
		index += readline->line_props.details[i];
	}
	readline->line_index = index;
}

void	set_cursor_from_index(t_readline *readline)
{
	int			index;
	int			i;
	const int	*details = readline->line_props.details;

	i = 0;
	index = 0;
	if (readline->cmd->tmp_len == readline->line_index)
	{
		readline->line_props.index = readline->line_props.linecount - 1;
		readline->cursor = details[readline->line_props.index];
		set_virtual_origin(readline);
		return ;
	}
	while (1)
	{
		if (i >= readline->line_props.linecount)
			break ;
		if (BETWEEN(readline->line_index, index, index + details[i] - 1))
			break ;
		index += readline->line_props.details[i];
		i++;
	}
	readline->line_props.index = i % readline->line_props.linecount;
	readline->cursor = readline->line_index - index;
	set_virtual_origin(readline);
}

void	get_cursor_position(t_readline *readline)
{
	char	*buff;
	int		col;
	int		row;

	buff = (char[21]){0};
	while (1)
	{
		ft_putstr_fd("\e[6n", 0);
		col = read(0, buff, 20);
		buff[col] = 0;
		if (ft_strchr(buff, '['))
			break ;
	}
	buff = (char *)ft_skip_unitl_char(buff, "[");
	row = ft_atoi(buff + 1);
	buff = (char *)ft_skip_unitl_char(buff, ";");
	col = ft_atoi(buff + 1);
	readline->o_cursor = (t_point){col - 1, row - 1};
	readline->ov_cursor = readline->o_cursor;
}
