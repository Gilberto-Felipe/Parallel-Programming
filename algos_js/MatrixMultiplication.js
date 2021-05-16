/*======================================= 
PRODUCTO DE MATRICES CON DIFERENTES FILAS Y COLUMNAS
=======================================*/

/* REGLA MATEMÁTICA:
* Se puede sacar el producto de 2 matrices solo si el n de filas de la 1a matriz es igual al número de columnas de la 2a.
*/

//========================= FUNCIONES =========================// 

// GENERAR MATRIZ
const genMatriz = (filas, columnas, max, min) => {
    let m = new Array();
    for (let i = 0; i < filas; i++) {
        m[i] = new Array();
        for (let j = 0; j < columnas; j++) {
            m[i][j] = Math.floor(Math.random() * max + min);
        }       
    }
    // console.table(m);
    return m;
}

// MULTIPLICAR MATRICES
const multiplicarMatrices = (a, b) => {
    var aNumRows = a.length, aNumCols = a[0].length,
        bNumRows = b.length, bNumCols = b[0].length,
        m = new Array(aNumRows);  // initialize array of rows
    for (var r = 0; r < aNumRows; ++r) {
        m[r] = new Array(bNumCols); // initialize the current row
        for (var c = 0; c < bNumCols; ++c) {
            m[r][c] = 0;             // initialize the current cell
            for (var i = 0; i < aNumCols; ++i) {
                m[r][c] += a[r][i] * b[i][c];
            }
        }
    }
    return m;
}

// FUNCIÓN TIMER 
const timer = (fun, filas, columnas) => {
    let start = Date.now();
    fun(filas, columnas);
    console.log("Tiempo: " + (Date.now() - start) + "ms");
}

//========================= INSTRUCCIONES =========================// 

// GENERAR MATRICES
let matrizA = genMatriz(8000, 8000, 10, 1);
let matrizB = genMatriz(8000, 8000, 10, 1);

// SUMAR MATRICES
//console.table(multiplicarMatrices(matrizA, matrizB));

// TOMAR TIEMPO DE RESOLUCIÓN
timer(multiplicarMatrices, matrizA, matrizB);





// OUTPUT - IMPRIMIR RESULTADO

// ver algoritomo https://www.youtube.com/watch?v=x7zua7fhyIw 

// revisar los valores en https://onlinemschool.com/math/assistance/matrix/multiply/ 

// el algoritmo funciona