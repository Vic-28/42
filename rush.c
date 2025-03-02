#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Entrada valida: 4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2
// Tamaño del tablero
int g_size = 4;

// Función para contar cuántas cajas son visibles en una fila o columna
int count_visible(int *line) {
    int max_height = 0;
    int visible = 0;
    for (int i = 0; i < g_size; i++) {
        if (line[i] > max_height) {
            visible++;
            max_height = line[i];
        }
    }
    return visible;
}

// Función para verificar si la solución es válida según las restricciones de visibilidad
int check_valid(int grid[g_size][g_size], int up[g_size], int down[g_size], int left[g_size], int right[g_size]) {
    // Verificar filas
    for (int i = 0; i < g_size; i++) {
        if (count_visible(grid[i]) != left[i]) {
            return 0;
        }
        int row_reverse[g_size];
        for (int j = 0; j < g_size; j++) {
            row_reverse[j] = grid[i][g_size - 1 - j];
        }
        if (count_visible(row_reverse) != right[i]) {
            return 0;
        }
    }

    // Verificar columnas
    for (int j = 0; j < g_size; j++) {
        int column[g_size];
        for (int i = 0; i < g_size; i++) {
            column[i] = grid[i][j];
        }
        if (count_visible(column) != up[j]) {
            return 0;
        }
        int column_reverse[g_size];
        for (int i = 0; i < g_size; i++) {
            column_reverse[i] = grid[g_size - 1 - i][j];
        }
        if (count_visible(column_reverse) != down[j]) {
            return 0;
        }
    }
    return 1; // La solución es válida
}

// Función para intentar resolver el tablero usando backtracking
int solve(int grid[g_size][g_size], int up[g_size], int down[g_size], int left[g_size], int right[g_size], int row, int col) {
    if (row == g_size) {
        return check_valid(grid, up, down, left, right);
    }
    
    // Avanzar a la siguiente fila si se ha completado la columna
    if (col == g_size) {
        return solve(grid, up, down, left, right, row + 1, 0);
    }

    // Intentar colocar cada número del 1 al 4 en la casilla actual
    for (int num = 1; num <= g_size; num++) {
        int valid = 1;

        // Verificar si el número ya está en la fila o columna
        for (int i = 0; i < g_size; i++) {
            if (grid[row][i] == num || grid[i][col] == num) {
                valid = 0;
                break;
            }
        }

        // Si es válido, colocar el número y avanzar
        if (valid) {
            grid[row][col] = num;
            //printf("Colocando %d en (%d, %d)\n", num, row, col); // Depuración
            if (solve(grid, up, down, left, right, row, col + 1)) {
                return 1;
            }
            grid[row][col] = 0; // Deshacer si no se encuentra una solución
           // printf("Deshaciendo %d en (%d, %d)\n", num, row, col); // Depuración
        }
    }

    return 0; // No se encontró solución
}

int main(int argc, char *argv[]) {
    
    // Verificar que se proporcionen exactamente 16 números como argumentos
    if (argc - 1 != 16) { 
        printf("Error: Debes proporcionar exactamente 16 números.\n");
        return 1;
    }

    int up[g_size], down[g_size], left[g_size], right[g_size];

    // Rellenar los arreglos con los valores proporcionados por los argumentos
    for (int i = 0; i < g_size; i++) {
        up[i] = atoi(argv[i+1]);  // Los primeros 4 números son para "up"
        down[i] = atoi(argv[i+5]);  // Los siguientes 4 números son para "down"
        left[i] = atoi(argv[i+9]);  // Los siguientes 4 números son para "left"
        right[i] = atoi(argv[i+13]);  // Los últimos 4 números son para "right"
    }

    int grid[g_size][g_size];  // Declarar el tablero vacío

    // Inicializar el tablero vacío manualmente
    for (int i = 0; i < g_size; i++) {
        for (int j = 0; j < g_size; j++) {
            grid[i][j] = 0;
        }
    }

    // Llamar a la función de solución
    if (solve(grid, up, down, left, right, 0, 0)) {
        // Imprimir el tablero si se encuentra una solución
        for (int i = 0; i < g_size; i++) {
            for (int j = 0; j < g_size; j++) {
                printf("%d ", grid[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("Error\n");  // Si no se encuentra solución
    }

    return 0;
}
