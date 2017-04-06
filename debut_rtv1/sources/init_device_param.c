/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_device_param.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 04:52:09 by fjanoty           #+#    #+#             */
/*   Updated: 2017/01/04 07:26:22 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Ici on va se les truc de base des device
*/

int		get_device_info(t_init_ocl_param *info)
{
	cl_int	ret[2];

	if (!info)
		return (0):
	ft_bzero(info, sizeof(t_init_ocl_param));
	ret[0] = clGetPlatformIDs(1, &inf.platform_id, &ret_num_platforms);
	(ret[0] < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	ret[1] = clGetDeviceIDs(info->platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &info->device_id, &ret_num_devices);
	(ret[1] < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	return (((ret[0] < 0 || ret[1] < 0)) ? -1 : 0);	
}

//	set_context
