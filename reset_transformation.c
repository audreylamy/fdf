/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_transformation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamy <alamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 17:29:58 by alamy             #+#    #+#             */
/*   Updated: 2018/02/15 12:26:17 by alamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_reset_event(t_env *tmp)
{
	tmp->move_x = 0;
	tmp->move_y = 0;
	tmp->move_rotation_x = 0;
	tmp->move_rotation_y = 0;
	tmp->move_rotation_z = 0;
	tmp->zoom = 0;
	tmp->zoom_z = 0;
	tmp->projection = 0;
	tmp->clic_proj = 0;
}

t_vector4	ft_reset_rot_zoom(t_vector4 vec_h, t_vector4 result, t_env *t)
{
	t_vector4	res;
	t_matrix4	m_rotation_x;
	t_matrix4	m_rotation_y;
	t_matrix4	m_rotation_z;
	t_matrix4	m_homo;

	m_homo = matrix_homothetie(vec_h);
	m_rotation_x = matrix_rotation_x((30.0 + t->move_rotation_x)
	* PI / 180);
	m_rotation_y = matrix_rotation_y((30.0 + t->move_rotation_y) * PI / 180);
	m_rotation_z = matrix_rotation_z((0.0 + t->move_rotation_z) * PI / 180);
	res = ft_cal_homothetie(result, m_homo);
	res = ft_cal_rotation_x(res, m_rotation_x);
	res = ft_cal_rotation_y(res, m_rotation_y);
	res = ft_cal_rotation_z(res, m_rotation_z);
	return (res);
}

t_vector4	ft_reset_transformation(t_data *data, t_env *tmp)
{
	t_vector4	vector_trans;
	t_matrix4	m_translation;
	t_vector4	vector_homo;
	t_matrix4	m_projection;
	t_vector4	result;

	ft_reset_event(tmp);
	vector_trans = create_vector4((WINDOW_L / 2) - ((tmp->nb_col * TILE_WIDTH)
	/ 2), (WINDOW_H / 2) - ((tmp->nb_line * TILE_HEIGHT) / 2), 0, 1);
	vector_homo = create_vector4(1.0, 1.0, 1.0, 1.0);
	m_translation = matrix_translation(vector_trans);
	m_projection = matrix_proj(85.0 * PI / 180, WINDOW_L / WINDOW_H,
	1.0, 100.0);
	result = create_vector4(data->x0, data->y0, data->z0, data->w0);
	result = ft_reset_rot_zoom(vector_homo, result, tmp);
	result = ft_cal_translation(result, m_translation);
	result = ft_cal_projection(result, m_projection);
	return (result);
}
