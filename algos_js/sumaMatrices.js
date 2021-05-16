/*======================================= 
SUMA DE 2 MATRICES DE NÚMEROS ALEATORIOS
=======================================*/

//========================= FUNCIONES =========================// 

// GENERAR MATRIZ
const genMatriz = (size, max, min) => {
    let m = new Array(size);
    for (let i = 0; i < size; i++) {
        m[i] = new Array(size);
        for (let j = 0; j < size; j++) {
            m[i][j] = Math.floor(Math.random() * max + min);
        }
    }
    console.table(m);
    return m;
}

// SUMAR MATRICES
const sumarMatrices = (a, b) => {
    let suma = new Array(size);
    for (let i = 0; i < size; i++) {
        suma[i] = new Array(size);
        for (let j = 0; j < size; j++) {
            suma[i][j] = matrizA[i][j] + matrizB[i][j];
        }
    }
    console.table(suma);
    // return suma;
}

//========================= INSTRUCCIONES =========================// 

// INPUT - VARIABLES
let size = 10;

// GENERAR MATRICES
let matrizA = genMatriz(size, 10, 1);
let matrizB = genMatriz(size, 10, 1);

// SUMAR MATRICES
sumarMatrices(matrizA, matrizB);

// OUTPUT - IMPRIMIR RESULTADO