/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:44:03 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/11 02:30:51 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void cur_up(t_readline *readline)
{
	readline->cursor += readline->cursor < readline->line_len / readline->col ? readline->col : 0;
	cur_goto(readline, readline->cursor);
}

void cur_down(t_readline *readline)
{
	readline->cursor += readline->cursor > readline->col ? readline->col : 0;
	cur_goto(readline, readline->cursor);
}

void cur_left(t_readline *readline)
{
	readline->cursor -= readline->cursor == 0 ? 0 : 1;
	cur_goto(readline, readline->cursor);
}

void cur_right(t_readline *readline)
{
	readline->cursor += readline->cursor == readline->line_len ? 0 : 1;
	cur_goto(readline, readline->cursor);
}
