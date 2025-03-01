function generarSudoku4x4() {
    const size = 4;  // Tamaño del Sudoku (4x4)
    const subGridSize = 2; // Tamaño del bloque (2x2)
    let board = Array.from({ length: size }, () => Array(size).fill(0));// Aquí se determina el tamaño del tablero

    function esValido(fila, columna, num) {
        // Verificar si el número ya está en la fila o en la columna
        for (let i = 0; i < size; i++) {
            if (board[fila][i] === num || board[i][columna] === num) {
                return false;
            }
        }
        // Verificar el bloque 
        let startRow = Math.floor(fila / subGridSize) * subGridSize;
        let startCol = Math.floor(columna / subGridSize) * subGridSize;
        for (let i = 0; i < subGridSize; i++) {
            for (let j = 0; j < subGridSize; j++) {
                if (board[startRow + i][startCol + j] === num) {
                    return false;
                }
            }
        }
        return true;
    }

    function resolverSudoku(fila = 0, columna = 0) {
        if (fila === size) return true; // Sudoku completado
        if (columna === size) return resolverSudoku(fila + 1, 0); // Siguiente fila

        let numeros = [1, 2, 3, 4].sort(() => Math.random() - 0.5); // Mezcla aleatoria
        for (let num of numeros) {
            if (esValido(fila, columna, num)) {
                board[fila][columna] = num;
                if (resolverSudoku(fila, columna + 1)) return true;
                board[fila][columna] = 0; // Retroceder si no funciona
            }
        }
        return false;
    }

    resolverSudoku();
    return board;
}

// Generar y mostrar el Sudoku resuelto
let sudoku = generarSudoku4x4();
console.log("Sudoku 4x4 generado automáticamente:\n");
console.log(sudoku.map(row => row.join(" ")).join("\n"));
