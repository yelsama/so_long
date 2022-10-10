/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:36:36 by ymohamed          #+#    #+#             */
/*   Updated: 2022/10/10 21:05:48 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game_ptr	mygame;
	t_wind_dims	wind;

	if (argc < 2)
		ft_printf("Error\nNo map has been chosen, prog exiting");
	if (argc < 2)
		return (0);
	if (!map_is_valid(argv[1], &wind, ".ber"))
		return (0);
	//check rout validity
	mygame.map_name = argv[1];  // might ber removed
	mygame.g_wind_name = "so_long";
	if (!initiate_g(&mygame, &wind))
		return (0);
	mlx_loop(mygame.game_ptr);
	return (0);
}
//
// #include <stdio.h>
// #include <stdlib.h>
 
// typedef  struct      s_mlx
// {
//     void        * mlx;
//     void        * win;
//     int             cnt;
// } t_mlx;
 
// int         keypress_event( int  keycode, t_mlx * mlx)
// {
//     mlx-> cnt++ ;
//     printf ( "cnt: %d\n" , mlx-> cnt);
//     printf ( "keycode : %d\n" , keycode);
//     if  (keycode ==  53 )
//         exit( 0 );
//     return  ( 0 );
// }
 
// int         main( void )
// {
//     t_mlx mlx;
 
//     mlx.cnt =  0 ;
//     mlx.mlx =  mlx_init();
//     mlx.win =  mlx_new_window(mlx.mlx,  600 ,  400 ,  "mlx" );
 
//     mlx_hook(mlx.win,  2 , 1 , & keypress_event, & mlx);
//     mlx_loop(mlx.mlx);
//     return  ( 0 );
// }