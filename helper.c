/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 23:23:56 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/13 23:40:22 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int get_virtua_line_count(t_readline *readline)
{
	int count;
	int i;
	const int *details = readline->line_props.details;

	i = 0;
	count = !!((details[i] + readline->o_cursor.x) % readline->col);
    count += ((details[i] + readline->o_cursor.x) / readline->col);
	i++;
	while (i < readline->line_props.linecount)
	{
		count += !!(details[i] % readline->col) + (details[i] / readline->col);
		i++;
	}
	return (count);
}

void update_o_cursor(t_readline *readline)
{
	int diff;

	diff = (get_virtua_line_count(readline) + readline->o_cursor.y) - readline->row;
	if (diff > 0)
	{
		readline->o_cursor.y -= diff;
		set_virtual_origin(readline);
	}
}

int output(int c)
{
	ft_putchar(c);
	return (0);
}
