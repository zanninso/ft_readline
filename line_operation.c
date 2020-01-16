/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 22:57:02 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/16 01:49:12 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void		rewrite_line(t_readline *readline)
{
	update_o_cursor(readline);
	tputs(tgoto(tgetstr("cm", 0), 0, readline->o_cursor.y), 0, output);
	tputs(tgetstr("cd", NULL), 0, output);
	ft_printf("➜  ft_readline git:(master) ");
	ft_putstr(readline->cmd->tmp_line);
	ft_printf(" ");
	cur_goto(readline, readline->cursor);
}

static void	put_new_line(t_readline *readline, char *new_line,
														int is_line, int len)
{
	free(readline->cmd->tmp_line);
	readline->cmd->tmp_line = new_line;
	readline->cmd->tmp_len += len;
	readline->line_index += len;
	readline->line_props.details[readline->line_props.index] += len;
	if (is_line)
		readline->line_props.details = get_line_details(readline);
	if (readline->line_props.details)
	{
		set_cursor_from_index(readline);
		rewrite_line(readline);
	}
}

void		insert_in_line(t_readline *readline, char *str)
{
	char		*new_line;
	const int	is_line = !!ft_strchr(str, '\n');
	const int	len = ft_strlen(str);

	if (str)
	{
		new_line = ft_strnew(readline->cmd->tmp_len + len);
		ft_strncpy(new_line, readline->cmd->tmp_line, readline->line_index);
		ft_strcat(new_line, str);
		ft_strcat(new_line, readline->cmd->tmp_line + readline->line_index);
		if (new_line)
			put_new_line(readline, new_line, is_line, len);
	}
}

void		remove_from_line(t_readline *readline, int start, int end)
{
	char		*new_line;
	char *const	line = readline->cmd->tmp_line;
	int			is_line;
	const int	len = end - start;

	if (start >= 0)
	{
		is_line = !!ft_strnstr(&line[start], "\n", len);
		line[start] = 0;
		new_line = ft_strjoin(line, line + end);
		if (new_line)
			put_new_line(readline, new_line, is_line, -len);
	}
}

int			*get_line_details(t_readline *readline)
{
	int		*ret;
	char	*tmp;
	int		line_count;
	int		i;
	char	*line;

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
			break ;
	}
	return (ret);
}
