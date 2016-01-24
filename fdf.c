#include "struct.h"
#include "get_next_line.h"
#include <mlx.h>
#include <stdio.h>
#include "libft/libft.h"
//Const fill_rect
#define RECTX 10
#define RECTY 10
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "struct.h"
#include <math.h>
# define RGB(r, g, b)(256 * 256 * (int)(r) + 256 * (int)(g) + (int)(b))
#define WIDTH 900
#define HEIGTH 900

int couleur(double t)
{
  return ((RGB(127.5 * (cos(t) + 1), 127.5 * (sin(t) + 1), 127.5 * (1 - cos(t)))));
}

char ***set_coord2(char ***coord, int i, int x, int y, int zoom);
char ***set_coord3(char ***coord, int i, int x, int y, int zoom, int rotate);

void draw_line2(void *mlx, void *win, float xi, float yi, float xf, float yf, int color)
{
  int dx,dy,i,xinc,yinc,cumul,x,y ;
  x = xi ;
  y = yi ;
  dx = xf - xi ;
  dy = yf - yi ;
  xinc = ( dx > 0 ) ? 1 : -1 ;
  yinc = ( dy > 0 ) ? 1 : -1 ;
  dx = abs(dx) ;
  dy = abs(dy) ;
  mlx_pixel_put(mlx, win, x, y, color);
  if ( dx > dy ) {
    cumul = dx / 2 ;
    for ( i = 1 ; i <= dx ; i++ ) {
      x += xinc ;
      cumul += dy ;
      if ( cumul >= dx ) {
	cumul -= dx ;
	y += yinc ; }
      mlx_pixel_put(mlx, win, x, y, color); } }
  else {
    cumul = dy / 2 ;
    for ( i = 1 ; i <= dy ; i++ ) {
      y += yinc ;
      cumul += dx ;
      if ( cumul >= dy ) {
	cumul -= dy ;
	x += xinc ; }
      mlx_pixel_put(mlx, win, x, y, color); } }
}

void draw_line_on_img(t_img *myimg,float xi, float yi, float xf, float yf, int color)
{
  int dx,dy,i,xinc,yinc,cumul,x,y ;
  x = xi ;
  y = yi ;
  dx = xf - xi ;
  dy = yf - yi ;
  xinc = ( dx > 0 ) ? 1 : -1 ;
  yinc = ( dy > 0 ) ? 1 : -1 ;
  dx = abs(dx) ;
  dy = abs(dy) ;
  my_pixel_put_to_image(myimg, x, y, color);
  if ( dx > dy ) {
    cumul = dx / 2 ;
    for ( i = 1 ; i <= dx ; i++ ) {
      x += xinc ;
      cumul += dy ;
      if ( cumul >= dx ) {
	cumul -= dx ;
	y += yinc ; }
      my_pixel_put_to_image(myimg, x, y, color); } }
  else {
    cumul = dy / 2 ;
    for ( i = 1 ; i <= dy ; i++ ) {
      y += yinc ;
      cumul += dx ;
      if ( cumul >= dy ) {
	cumul -= dy ;
	x += xinc ; }
      my_pixel_put_to_image(myimg, x, y, color); } }
}

static char *ft_join(char const *s1, char const *s2, int len1, int len2)
{
  char *join;
  int i;
  int j;

  i = 0;
  j = 0;
  join = malloc(sizeof(char) * (len1 + len2) + 1);
  while (s1[i] != '\0')
    {
      join[i] = s1[i];
      i++;
    }
  while (s2[j] != '\0')
    {
      join[i] = s2[j];
      i++;
      j++;
    }
  join[i] = '\0';
  return (join);
}

char *ft_strjoins(char const *s1, char const *s2)
{
  int len1;
  int len2;
  char *join;

  if (!s1 || !s2)
    return (NULL);
  len1 = ft_strlen(s1);
  len2 = ft_strlen(s2);
  join = ft_join(s1, s2, len1, len2);
  return (join);
}

void fill_iso_rect(void *mlx, void *win, int x, int y, int t,int color)
{
  draw_line2(mlx, win, x, y, x + t, y - t, color);
  draw_line2(mlx, win, x + t, y - t, x + (t * 2), y, color);
  draw_line2(mlx, win, x+(t * 2), y, x + t, y + t, color);
  draw_line2(mlx, win, x + t, y + t, x, y, color);
}

void legend(t_struct *param)
{
  mlx_string_put(param->mlx, param->win, 0, 0, 0x00FFFF, "Commande Disponible :");
  mlx_string_put(param->mlx, param->win, 0, 25, 0x00FFFF, "Zoom + : Q  | Zoom - : E");
  mlx_string_put(param->mlx, param->win, 0, 60, 0x00FFFF, "Deplacement :");
  mlx_string_put(param->mlx, param->win, 0, 80, 0x00FFFF, "Gauche : A");
  mlx_string_put(param->mlx, param->win, 0, 100, 0x00FFFF, "Droite : D");
  mlx_string_put(param->mlx, param->win, 0, 120, 0x00FFFF, "Haut : W");
  mlx_string_put(param->mlx, param->win, 0, 140, 0x00FFFF, "Bas : S");
  mlx_string_put(param->mlx, param->win, 0, 160, 0x00FFFF, "Return : R");
}

void place_img(t_struct *param, float xd, float yd)
{
  mlx_destroy_image(param->mlx, param->img->img_ptr);
  param->img->img_ptr = mlx_new_image(param->mlx, WIDTH, HEIGTH);
  set_coord(param->coord, param->i, xd, yd, param->zoom);
  draw_with_tab_on_img(param->coord, param->i, param->maxline, param);
  mlx_put_image_to_window(param->mlx, param->win, param->img->img_ptr, 0, 0);
}

void place_img2(t_struct *param, float xd, float yd)
{
  mlx_destroy_image(param->mlx, param->img->img_ptr);
  param->img->img_ptr = mlx_new_image(param->mlx, WIDTH, HEIGTH);
  set_coord2(param->coord, param->i, xd, yd, param->zoom);
  draw_with_tab_on_img(param->coord, param->i, param->maxline, param);
  mlx_put_image_to_window(param->mlx, param->win, param->img->img_ptr, 0, 0);
}


int close_mlx(int keycode, t_struct *param)
{
  static float x;
  static float y;
  static float xd;
  static float yd;
  static float rotate;
  static float r;
  
  if(!r)
    r = 0;
  if(!rotate)
    rotate = 0;
  if(!xd)
    xd = 300;
  if(!yd)
    yd = 60;
 
  if(keycode == 53)
    exit(1);
  if(keycode == 2)
    {
      xd += 40;
      place_img(param, xd, yd);
    }
  if(keycode == 1)
    {
      yd += 40;
      place_img(param, xd, yd);
    }
  if(keycode == 13)
    {
      yd -= 40;
      place_img(param, xd, yd);
    }
  if(keycode == 0)
    {
      xd -= 40;
      place_img(param, xd, yd);
    }
  if(keycode == 12)
    {
      if(param->zoom < 5)
	{
	  param->zoom += 1;
	}
      else
	param->zoom += 5;
      place_img(param, xd, yd);
    }
  if(keycode == 14)
    {
      if(param->zoom >= 10)
	param->zoom -= 5;
      else
	param->zoom -= 0.5;
      place_img(param, xd, yd);
    }
   if(keycode == 15)
    {
      if(r == 0)
	{
	  r++;
	  set_coord(param->coord, param->i, xd, yd, param->zoom);
	  place_img(param, xd, yd);	
	}
      else if(r == 1)
	{
	  r = 0;
	  set_coord2(param->coord, param->i, xd, yd, param->zoom);
	  place_img2(param, xd, yd);
	}      
    }
    if(keycode == 17)
    {
      mlx_destroy_image(param->mlx, param->img->img_ptr);
      param->img->img_ptr = mlx_new_image(param->mlx, WIDTH, HEIGTH);
      set_coord(param->coord, param->i, xd, yd, param->zoom);      
      draw_with_tab_on_img(param->coord, param->i, param->maxline, param);
      mlx_put_image_to_window(param->mlx, param->win, param->img->img_ptr, 0, 0);
    }
  return (0);
}

char **create_tab(char *argv, char **tab)
{
  char *line;
  char *yt;
  int fd;
  int ret;

  fd = 0;
  ret = 0;
  fd = open(argv, O_RDONLY);
  line = (char *)malloc(sizeof(char) * 2);
  while((ret = get_next_line(fd,&yt)))
    {
      line = ft_strjoins(line,yt);
      line = ft_strjoins(line, " \n ");
    }
  tab = ft_strsplit(line, ' ');
  return (tab);
}

char ***create_coord_tab(char **tab, char ***coord, int i)
{
  int index;
  
  index = 0;
  coord = (char ***)malloc(sizeof(char **) * i + 1);
  while(index < i)
    {
      coord[index] = (char **)malloc(sizeof(char *) * 5);
      index++;
    }
  index = 0;
  while(index < i)
    {
      coord[index][0] = (char *)malloc(sizeof(char) * 5);
      coord[index][1] = (char *)malloc(sizeof(char) * 5);
      coord[index][2] = tab[index];
      index++;
    }
  return (coord);
}

char ***set_coord3(char ***coord, int i, int x, int y, int zoom, int rotate)
{
  int index;
  int xdep;
  int ydep;
  int xtemp;
  int ytemp;
  int j;
  int v;

  v = 0;
  j = 0;
  index = 0;
  xdep = x;
  ydep = y;
  while(index < i)
    {
      if(j == 0)
	{
	  coord[index][0] = ft_itoa(x);
	  coord[index][1] = ft_itoa(y);
	}
      else
	{
	  coord[index][0] = ft_itoa(xtemp);
	  coord[index][1] = ft_itoa(ytemp);
	  j = 0;
	}
      if(coord[index][2][0] == '\n')
	{
	  x = xdep;
	  y = ydep;
	  //	  x -= zoom - rotate;//a achanger
	  y += zoom;
	  xdep = x;
	  ydep = y;
	}
      else
	{
	  x += zoom;
	  //y += zoom - rotate;// a changer
	  if(coord[index][2][0] != '0')
	    {
	      v = ft_atoi(coord[index][2]);
	      xtemp = x + v;
	      ytemp =  y - ((v * 2)  + 1);
	      j++;
	    }
	}
      index++;
    }
  return (coord);
}

char ***set_coord2(char ***coord, int i, int x, int y, int zoom)
{
  int index;
  int xdep;
  int ydep;
  int xtemp;
  int ytemp;
  int j;
  int v;

  v = 0;
  j = 0;
  index = 0;
  xdep = x;
  ydep = y;
  while(index < i)
    {
      if(j == 0)
	{
	  coord[index][0] = ft_itoa(x);
	  coord[index][1] = ft_itoa(y);
	}
      else
	{
	  coord[index][0] = ft_itoa(xtemp);
	  coord[index][1] = ft_itoa(ytemp);
	  j = 0;
	}
      if(coord[index][2][0] == '\n')
	{
	  x = xdep;
	  y = ydep;
	   x -= zoom;
	  y += zoom;
	  xdep = x;
	  ydep = y;
	}
      else
	{
	  x += zoom;
		  y += zoom;
	  if(coord[index][2][0] != '0')
	    {
	      v = ft_atoi(coord[index][2]);
	      if(v > 0)
		v = -v;
	      xtemp = x + v;
	      ytemp =  y - ((v * 2)  + 1);;
	      j++;
	    }
	}
      index++;
    }
  return (coord);
}

char ***set_coord(char ***coord, float i, float x, float y, float zoom)
{
  int index;
  float xdep;
  float ydep;
  float xtemp;
  float ytemp;
  float j;
  float v;

  v = 0;
  j = 0;
  index = 0;
  xdep = x;
  ydep = y;
  while(index < i)
    {
      if(coord[index][2][0] == '\n')
	{
	  x = xdep;
	  y = ydep;
	  x -= zoom;
	  y += zoom;
	  xdep = x;
	  ydep = y;
	}
      else
	{
	  x += zoom;
	  y += zoom;
	  if(coord[index][2][0] != '0')
	    {
	      v = ft_atoi(coord[index][2]);
	      xtemp = x + v;
	      ytemp = y - ((v * 2)  + 1);
	      j++;
	    }
	}
      if(j == 0)
	{
	  coord[index][0] = ft_itoa(x);
	  coord[index][1] = ft_itoa(y);
	}
      else
	{
	  coord[index][0] = ft_itoa(xtemp);
	  coord[index][1] = ft_itoa(ytemp);
	  j = 0;
	}
      index++;
    }
  return (coord);
}

void draw_with_tab(char ***coord, int i, int maxline, t_struct *param)
{
  int x1;
  int x2;
  int y1;
  int y2;
  int index;
  int color;
  int val1;
  int futurindex;
  int val2;


  val1 = 0;
  val2 = 0;
  futurindex = 0;
  color = 0xA0FFFF;
  index = 0;
  x1 = 0;
  x2 = 0;
  y1 = 0;
  y2 = 0;
  while(index + 1 < i)
    {
      if(index + 1 < i)
	{
	  x1 = ft_atoi(coord[index][0]);
	  y1 = ft_atoi(coord[index][1]);
	  x2 = ft_atoi(coord[index + 1][0]);
	  y2 = ft_atoi(coord[index + 1][1]);
	  val1 = ft_atoi(coord[index][2]);
	  val2 = ft_atoi(coord[index + 1][2]);
	  if(coord[index + 1][2][0] != '\n')
	    {
	      draw_line2(param->mlx, param->win, x1, y1, x2, y2, color + ((val1 + val2) * 0xA0));
	    }
	  else
	    futurindex++;
	}
      if(index + maxline + 1 < i)
	{
	  x1 = ft_atoi(coord[index][0]);
	  y1 = ft_atoi(coord[index][1]);
	  x2 = ft_atoi(coord[index + maxline + 1][0]);
	  y2 = ft_atoi(coord[index + maxline + 1][1]);
	  val1 = ft_atoi(coord[index][2]);
	  val2 = ft_atoi(coord[index + maxline + 1][2]);
	  if(coord[index + maxline + 1][2][0] != '\n')
	    {
	      draw_line2(param->mlx, param->win, x1, y1, x2, y2, color + ((val1 + val2) * 0xA0));	
	    }
	}
      if(futurindex > 0)
	{
	  index += 2;
	  futurindex = 0;
	}
      else
	index++;
    }
}

int testa(x1,y1,x2,y2)
{
  if((x1 >= WIDTH) || (x2 >= WIDTH) || (y1 >= WIDTH) || (y2 >= WIDTH) || (y1 <= 0) || (y2 <= 0))
    return (0);
  return (1);
}

void draw_with_tab_on_img(char ***coord, int i, int maxline, t_struct *param)
{
  int x1;
  int x2;
  int y1;
  int y2;
  int index;
  int color;
  int val1;
  int futurindex;
  int val2;


  val1 = 0;
  val2 = 0;
  futurindex = 0;
  color = 0xA0FFFF;
  index = 0;
  x1 = 0;
  x2 = 0;
  y1 = 0;
  y2 = 0;
  while(index + 1 < i)
    {
      if(index + 1 < i)
	{
	  x1 = ft_atoi(coord[index][0]);
	  y1 = ft_atoi(coord[index][1]);
	  x2 = ft_atoi(coord[index + 1][0]);
	  y2 = ft_atoi(coord[index + 1][1]);
	  val1 = ft_atoi(coord[index][2]);
	  val2 = ft_atoi(coord[index + 1][2]);
	  if(coord[index + 1][2][0] != '\n' && testa(x1,y1,x2,y2))
	    {
	      draw_line_on_img(param->img,x1, y1, x2, y2, couleur(val1 + val2));
	    }
	  else
	    futurindex++;
	}
      if(index + maxline + 1 < i)
	{
	  x1 = ft_atoi(coord[index][0]);
	  y1 = ft_atoi(coord[index][1]);
	  x2 = ft_atoi(coord[index + maxline + 1][0]);
	  y2 = ft_atoi(coord[index + maxline + 1][1]);
	  val1 = ft_atoi(coord[index][2]);
	  val2 = ft_atoi(coord[index + maxline + 1][2]);
	  if(coord[index + maxline + 1][2][0] != '\n' && testa(x1,y1,x2,y2))
	    {
	      draw_line_on_img(param->img,x1, y1, x2, y2, couleur(val1 + val2));
	    }
	}
      if(futurindex > 0)
	{
	  index += 2;
	  futurindex = 0;
	}
      else
	index++;
    }
}  

void    my_pixel_put_to_image(t_img *myimg,int x, int y, int color)
{

  int i;
  unsigned char color1;
  unsigned char color2;
  unsigned char color3;
  myimg->data = mlx_get_data_addr(myimg->img_ptr, &myimg->bpp, &myimg->sizeline, &myimg->endian);

  myimg->data[y * myimg->sizeline + x * myimg->bpp / 8 ] = color % 256;
  color /= 256;
  myimg->data[y * myimg->sizeline + x * myimg->bpp / 8 + 1] = color % 256;
  color /= 256;
  myimg->  data[y * myimg->sizeline + x * myimg->bpp / 8 + 2] = color % 256;
}

int dothis()
{
  ft_putstr("lol");
  return (0);
}

int main(int argc, char **argv)
{ 
  void *mlx;
  void *win;
  char *line;
  int i;
  int maxline;
  t_struct *mystruct;
  char ***coord;
  char **tab;
  int index;
  t_img *myimg;

  index = 0;
  maxline = 0;
  i = 0;
  
//GERER ERREUR PARAM  
  if(argc != 2)
    {
      printf("Bug arg");
      return (0);
    }

////////////Init mlx//
  mlx = mlx_init();
  ///////////////

  //  mlx_put_image_to_window(mlx_ptr, win_ptr, myimg->img_ptr, 0, 0);

  /////////Create win////////
  win = mlx_new_window(mlx, WIDTH, HEIGTH, "42");
  ////////////\\\\\\\\\\\\\\\\\\\\\
  
  //Create struct////
 mystruct = malloc(sizeof(mystruct) * 6);
  mystruct->mlx = mlx;
  mystruct->win = win;
  mystruct->zoom = 20;
  legend(mystruct);
  /////////////////
  
  //creation du tab////
  tab = create_tab(argv[1], tab);
  /////////////////

  /////////Take my max range tab///////
  while(tab[i])
    i++;
  /////////////////
  
  ////////set coord and mallloc||||||||||||
  coord = create_coord_tab(tab, coord, i);
  coord = set_coord(coord, i, 300, 60, mystruct->zoom);
  ////////////////////////////////
  
  /////MY maxline//////
  while(tab[index][0] != '\n')
    {
      if(tab[index][0] != ' ')
	maxline++;
      index++;
    }
  //////////////////////

  mystruct->i = i;
  mystruct->maxline = maxline;
  mystruct->coord = coord;
  
  
  
  ///////Function appeler quand on fait un truc a la fenetre, faut le remettre dans le new fen//////////////////////
  // mlx_expose_hook (mystruct->win, dothis, 0);  
  ////////////////////////

  myimg = (t_img *)malloc(sizeof(t_img) * 10);
  myimg->img_ptr = mlx_new_image(mlx, WIDTH, HEIGTH);//Taille fenetre remplacer par variable
  myimg->mlx_ptr = mlx;
  mystruct->img = myimg;
   //draw_line_on_img(myimg,100, 100, 200, 100, 0xf8f8ff);
  //  mlx_put_image_to_window(mlx, win, myimg->img_ptr, 0, 00);

   ////Draw with my tab
  draw_with_tab_on_img(coord, i, maxline, mystruct);
  place_img(mystruct, 100, 100);
  ////////////////////////////
   
  //Fonction pour utiliser le clavier
  mlx_key_hook(mystruct->win, close_mlx, mystruct);
  ///////////////////////////
  
  //Boucle pour tenir la fenetre
  mlx_loop(mlx);
  ///////////////////
  return(0);

}
