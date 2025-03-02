//malloc  lo podemos usar para dear el tamaño de los arrays ddeterminados desde el principio
//Ya que reserva los bytes indicados para cada variable
// Para eso sera el usar FREE, para el final de las operaciones ir liberando la memoria

#include <stdio.h>
#include <unistd.h>

//Definimos el tamaño del tablero con una variable global

int g_size = 4;

int main(int args, char **argv)
{
    //Verifico que la cantidad de argumentos  sea de 16
    if (args -1 != 16)
    {
        write(1, "ERROR: Debe de haber 16 numeros con espacios (1 2 3 4 ...)", 58);
        write(1, '\n', 1);
        return (1);
    }

    //Definimos los  tamaños de cada columna y fila para la impresión del tablero
    
    int up[g_size], down[g_size], left[g_size], right[g_size];

    int i;

    i = 0;
    while (i < g_size)
    {
        up[i] = ft_convertInt(argv[i+1]); //Los primeros 4 numeros los dirigimos a up
        down[i] = ft_convertInt(argv[i+5]); //Los siguientes 4 a down
        left[i] = ft_convertInt(argv[i+9]);// los siguientes 4 a left
        right[i] = ft_convertInt(argv[i+13]); //Los siguientes 4 a rigth
        i++;
    }

    int board[g_size][g_size]; //Declaramos el tablero con el tamaño 4X4
    
    int j;

    j = 0;
    i = 0;
    while (i < g_size) //Inicializamos el tablero vacio
    {
      while (j < g_size)
      {
        board[i][j] = 0;
        j++;
      }
      i++;
        
    }
    

    return(0);
}


int ft_isValid()  //Comprobamos que no se repitan nummeros
{
  
}


int ft_solver()
{
    
}


int ft_convertInt(char *a)
{
    int aux;

    aux = a[0] - '0'; //Esto nos permite que caracteres de entre 0 y 9 sean devueltos como numeros enteros, ya que juega con su valor ascii

    return aux;
}
