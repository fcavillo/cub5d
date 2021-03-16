# include "minilibx-linux/mlx.h"

int     main(void)
{
    void    *mlx;
    void    *img;
    char    *relative_path = "./textures/greystone.xpm";
    int     img_width;
    int     img_height;

    mlx = mlx_init();
    img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
}

/* escape
typedef struct  s_vars {
    void        *mlx;
    void        *win;
}               t_vars;

int             close(int keycode, t_vars *vars)
{
    if (keycode == 65307)
        mlx_destroy_window(vars->mlx, vars->win);
}

}

int             main(void)
{
    t_vars      vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
    mlx_hook(vars.win, 2, 1L<<0, close, &vars);
    mlx_loop(vars.mlx);
} 

pixel window
typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int             main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;
    int i = 0;

    mlx = mlx_init(); //init la mlx
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!"); //cree la fenetre
    img.img = mlx_new_image(mlx, 1920, 1080); //creer image
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian); //obtenir adresse pixels


    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0); //push l'image sur la window
    mlx_loop(mlx); //rendre la window
}*/

/*
int     main(void)
{
    void    *mlx;
    void    *mlx_win;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    mlx_loop(mlx);
}   

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}


int             main(void)
{
    void    *mlx;
    void    *mlx_win;
    //int i = 0;
    t_data  img;

mlx = mlx_init();
mlx_win = mlx_new_window(mlx, 1500, 1080, "Hello world!");
mlx_loop(mlx);

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    img.img = mlx_new_image(mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    for (int i = 0; i < 500; i++)
        my_mlx_pixel_put(&img, i, i, 0x00FF00FF);
    for (int i = 0; i < 500; i++)
        my_mlx_pixel_put(&img, i, 5, 0x00FF0000);
    for (int i = 0; i < 500; i++)
        my_mlx_pixel_put(&img, 5, i, 0x00FFFFFF);
    for (int i = 0; i < 500; i++)
        my_mlx_pixel_put(&img, 500, i, 0x000000FF);
    for (int i = 0; i < 500; i++)
        my_mlx_pixel_put(&img, i, 500, 0x00000000);
    for (int i = 0; i < 500; i++)
        my_mlx_pixel_put(&img, 5, i, 0x00FF00FF);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}*/