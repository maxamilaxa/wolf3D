/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 21:38:44 by mkopiika          #+#    #+#             */
/*   Updated: 2019/07/26 22:34:40 by mkopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_valid	*make_line(t_valid *line, char *string)
{
	if (!line)
	{
		if (!(line = (t_valid*)malloc(sizeof(t_valid))))
			get_error(FAIL_MALLOC);
		line->str = ft_strdup(string);
		line->length = ft_strlen(string);
		line->nxt = NULL;
		line->prv = NULL;
		return (line);
	}
	else
	{
		if (!(line->nxt = (t_valid*)malloc(sizeof(t_valid))))
			get_error(FAIL_MALLOC);
		line->nxt->str = ft_strdup(string);
		line->nxt->length = ft_strlen(string);
		line->nxt->nxt = NULL;
		line->nxt->prv = line;
		return (line->nxt);
	}
}

static void		rows_validation(t_maze *m, t_valid *l, int y)
{
	int			i;

	i = -1;
	while (++i < l->length)
	{
		if ((l->str[0] != m->sym_wl) || (l->str[l->length - 1] != m->sym_wl))
			get_error(FAIL_INVAL);
		if ((y == (m->sz - 1) || y == 0) && (l->str[i] != m->sym_wl))
			get_error(FAIL_INVAL);
		if ((l->str[i] != m->sym_wl) && (l->str[i] != m->sym_fr) &&
				(l->str[i] != m->sym_pl))
			get_error(FAIL_INVAL);
		if ((m->is_area == 0) && (l->str[i] == m->sym_fr) && (m->is_area = 1))
			m->pos_pl = (t_point_d){.x = i + 0.5, .y = y + 0.5};
		if ((m->is_play == 0) && (l->str[i] == m->sym_pl) && (m->is_play = 1))
			m->pos_pl = (t_point_d){.x = i + 0.5, .y = y + 0.5};
	}
}

static void		check_symbol(t_maze *m, t_valid *list)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	if (!(m->maze = (char**)malloc(sizeof(char*) * m->sz)))
		get_error(FAIL_MALLOC);
	while (list)
	{
		rows_validation(m, list, y);
		m->maze[y] = list->str;
		list = list->nxt;
		y++;
	}
	if (!m->is_area && !m->is_play)
		get_error(FAIL_INVAL);
}

void			maze_validation(int fd, t_data *data)
{
	int			rows;
	int			res;
	char		*str;

	res = 0;
	rows = 0;
	data->lst = NULL;
	while ((res = get_next_line(fd, &str)) > 0)
	{
		data->lst = make_line(data->lst, str);
		if (data->lst->prv && (data->lst->length != data->lst->prv->length))
			get_error(FAIL_INVAL);
		ft_strdel(&str);
		rows++;
	}
	if ((!data->lst) || res == -1)
		get_error(FAIL_MAZE);
	if ((data->lst && (rows != data->lst->length)) || rows < 5 || rows > 80)
		get_error(FAIL_INVAL);
	data->maze.sz = data->lst->length;
	while (data->lst->prv)
		data->lst = data->lst->prv;
	check_symbol(&data->maze, data->lst);
}
