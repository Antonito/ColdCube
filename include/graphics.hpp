#ifndef	GRAPHICS_H_
# define GRAPHICS_H_

# include <lapin.h>

typedef struct		s_texture
{
  int			width;
  int			height;
  t_color		*pixels;
}			t_texture;

typedef struct					s_bmp
{
  __attribute__((packed)) unsigned short	type;
  __attribute__((packed)) unsigned int		size;
  __attribute__((packed)) unsigned int		reserved;
  __attribute__((packed)) unsigned int		offset;
  __attribute__((packed)) unsigned int		size_struct;
  __attribute__((packed)) int			width;
  __attribute__((packed)) int			height;
  __attribute__((packed)) unsigned short	one;
  __attribute__((packed)) unsigned short	color_resolution;
  __attribute__((packed)) unsigned int		compression;
  __attribute__((packed)) unsigned int		byte_size;
  __attribute__((packed)) int			resolution_hor;
  __attribute__((packed)) int			resolution_ver;
  __attribute__((packed)) unsigned int		nb_colors;
  __attribute__((packed)) unsigned int		nb_imp_colors;
}						t_bmp;

#endif	/* !GRAPHICS_H_ */
