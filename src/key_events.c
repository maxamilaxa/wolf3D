/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 00:17:56 by mkopiika          #+#    #+#             */
/*   Updated: 2019/07/28 19:25:46 by mkopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		change_location(t_point_d go, t_maze *m)
{
	if (m->maze[(unsigned int)m->pos_pl.y]
		[(unsigned int)(m->pos_pl.x + (go.x) * 3)] != m->sym_wl)
		m->pos_pl.x += go.x;
	if (m->maze[(unsigned int)(m->pos_pl.y + (go.y) * 3)]
				[(unsigned int)m->pos_pl.x] != m->sym_wl)
		m->pos_pl.y += go.y;
}

static void		turn_around(t_maze *m, t_point_d trn)
{
	t_point_d	proj;
	t_point_d	dirc;

	proj = m->proj_pl;
	dirc = m->dirc_pl;
	m->proj_pl.x = proj.x * trn.y - proj.y * trn.x;
	m->proj_pl.y = proj.x * trn.x + proj.y * trn.y;
	m->dirc_pl.x = dirc.x * trn.y - dirc.y * trn.x;
	m->dirc_pl.y = dirc.x * trn.x + dirc.y * trn.y;
}

void			key_events(t_sign sgn, t_maze *m, t_render *t)
{
	t_point_d	go;
	t_point_d	trn;

	trn = (t_point_d){.x = sin(t->rottn), .y = cos(t->rottn)};
	go = (t_point_d){.x = 0.028 * m->dirc_pl.x * sgn.sh,
					.y = 0.028 * m->dirc_pl.y * sgn.sh};
	if (sgn.up == 1 || sgn.w == 1)
		change_location(go, m);
	if (sgn.down == 1 || sgn.s == 1)
		change_location((t_point_d){ .x = go.x * -1, .y = go.y * -1 }, m);
	if (sgn.d == 1)
		change_location((t_point_d){ .x = go.y * -1, .y = go.x }, m);
	if (sgn.a == 1)
		change_location((t_point_d){ .x = go.y, .y = go.x * -1}, m);
	if (sgn.rgt == 1)
		turn_around(m, trn);
	if (sgn.lft == 1)
		turn_around(m, (t_point_d){.x = sin(-t->rottn), .y = cos(-t->rottn)});
}
