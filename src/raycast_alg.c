/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_alg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 16:10:22 by mkopiika          #+#    #+#             */
/*   Updated: 2019/07/28 15:04:29 by mkopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		ray_length_calculate(t_var_ray *r, t_maze *m, t_point_i *mc)
{
	int			border;
	int			len;

	border = 0;
	len = 0;
	while (border == 0 && len < 200)
	{
		if (r->offcut.x < r->offcut.y)
		{
			r->offcut.x += r->delta.x;
			mc->x += r->move.x;
			r->offcut_s = 0;
		}
		else
		{
			r->offcut.y += r->delta.y;
			mc->y += r->move.y;
			r->offcut_s = 1;
		}
		if (m->maze[mc->y][mc->x] == m->sym_wl)
			border = 1;
		len++;
	}
}

static void		hight_calculate(t_var_ray *r, t_point_i mc)
{
	if (!r->offcut_s)
		r->fsh = (mc.x - r->pos_pl.x + (1.0 - r->move.x) / 2) / r->ray_d.x;
	else
		r->fsh = (mc.y - r->pos_pl.y + (1.0 - r->move.y) / 2) / r->ray_d.y;
	r->hig_w = (int)(H / r->fsh);
	r->from_to.x = (-((Uint32)r->hig_w >> 1u)) + (MD);
	if (r->from_to.x < 0)
		r->from_to.x = 0;
	r->from_to.y = ((Uint32)(r->hig_w) >> 1u) + (MD);
	if (r->from_to.y >= H)
		r->from_to.y = H - 1;
}

static void		distance_calculate(t_var_ray *r, t_point_i *mc)
{
	*mc = (t_point_i){.x = (int)r->pos_pl.x, .y = (int)r->pos_pl.y};
	if (r->ray_d.x < 0)
	{
		r->move.x = -1;
		r->offcut.x = (r->pos_pl.x - mc->x) * r->delta.x;
	}
	else
	{
		r->move.x = 1;
		r->offcut.x = (mc->x + 1.0 - r->pos_pl.x) * r->delta.x;
	}
	if (r->ray_d.y < 0)
	{
		r->move.y = -1;
		r->offcut.y = (r->pos_pl.y - mc->y) * r->delta.y;
	}
	else
	{
		r->move.y = 1;
		r->offcut.y = (mc->y + 1.0 - r->pos_pl.y) * r->delta.y;
	}
}

void			raycast_alg(t_data *data)
{
	t_var_ray	r;
	int			ray;

	ray = 0;
	r.dirc_pl = data->maze.dirc_pl;
	r.pos_pl = data->maze.pos_pl;
	r.proj_pl = data->maze.proj_pl;
	while (ray < W)
	{
		r.win_x = 1 - (2.0 * (double)ray / W);
		r.ray_d.x = r.dirc_pl.x + r.proj_pl.x * r.win_x;
		r.ray_d.y = r.dirc_pl.y + r.proj_pl.y * r.win_x;
		r.delta = (t_point_d){.x = fabs(1 / r.ray_d.x),
								.y = fabs(1 / r.ray_d.y)};
		distance_calculate(&r, &r.maze_cor);
		ray_length_calculate(&r, &data->maze, &r.maze_cor);
		hight_calculate(&r, r.maze_cor);
		put_texture(ray, &r, &data->sdl, data->maze);
		ray++;
	}
	if (SDL_UpdateWindowSurface(data->sdl.win_ptr) != 0)
		get_error(FAIL_SDL);
}
