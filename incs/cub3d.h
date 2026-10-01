#ifndef CUB3D_H
# define CUB3D_H


# include <math.h>
# include <X11/keysym.h>
# include "../libft/incs/libft.h"
# include "../minilibx-linux/mlx.h"

# define BG_COLOR	0x1A1A2E		// dark purlple
# define IMG_WIDTH	1920
# define IMG_HEIGHT 1080 

typedef struct s_data
{
	// t_view	view;
	// t_point	*points;
	// t_map	map;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*mlx_win;
	// t_hook	keys;
	int		fd;
	//BONUS
	int		nb_maps;
}				t_data;

#endif
