/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 22:57:02 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/09 20:38:53 by aait-ihi         ###   ########.fr       */
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
	t_point current_cursor = readline->cursor;
	cur_goto(readline, readline->o_cursor);
	tputs(tgetstr("cd", NULL), 0, output);
	ft_putstr(readline->cmd->tmp_line);
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
		readline->line_props.details[readline->cursor.y - readline->o_cursor.y] += i;
		readline->cursor.x += i;
	}
	rewrite_line(readline);
}

// void remove_from_line(t_readline *readline)
// {
// 	char *new_line;
// 	char *line;
// 	const int cur_position = readline->cursor - readline->o_cursor;

// 	line = readline->cmd->tmp_line;
// 	if (readline->cursor > readline->o_cursor)
// 	{
// 		line[cur_position - 1] = 0;
// 		new_line = ft_strjoin(line, line + cur_position);
// 		if (new_line)
// 		{
// 			free(line);
// 			readline->cmd->tmp_line = new_line;
// 			readline->cmd->tmp_len--;
// 			readline->cursor--;
// 		}
// 	}
// 	rewrite_line(readline);
// }

int *get_line_details(t_readline *readline)
{
	int *ret;
	char *tmp;
	int line_count;
	int i;
	char *line;

	line = readline->cmd->tmp_line;
	line_count = 1 + ft_str_occurence(line, '\n');
	if(!(ret = malloc(sizeof(int) * line_count)))
		return (NULL);
	i = 0;
	readline->line_props.linecount = line_count;
	while((tmp = (char *)ft_skip_unitl_char(line, "\n")))
	{
		*tmp  == '\n' ? tmp++ : 0;
		ret[i++] = tmp - line;
		line = tmp;
		if (*tmp == '\0')
			break;
	}
	return (ret);
}