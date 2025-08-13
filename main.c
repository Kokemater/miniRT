#include "minirt.h"

typedef struct s_state
{
    void    *mlx;
    void    *win;
    int     counter;
}   t_state;

// El loop debe devolver int y recibir void* como parámetro
int loop(void *param)
{
    t_state *state = (t_state *)param;

    printf("Frame %d\n", state->counter++);
    // Aquí puedes dibujar en la ventana con mlx_pixel_put, imágenes, etc.
    return (0);
}

int main(int argc, char *argv[])
{
    t_state state;

    (void)argc;
    (void)argv;

    state.counter = 0;
    state.mlx = mlx_init();
    if (!state.mlx)
    {
        fprintf(stderr, "Error: no se pudo inicializar MiniLibX\n");
        return (1);
    }

    state.win = mlx_new_window(state.mlx, 800, 800, "MiniRT - MiniLibX");
    if (!state.win)
    {
        fprintf(stderr, "Error: no se pudo crear la ventana\n");
        return (1);
    }

    // Registramos el loop
    mlx_loop_hook(state.mlx, loop, &state);

    // Inicia el bucle principal
    mlx_loop(state.mlx);

    return (0);
}
