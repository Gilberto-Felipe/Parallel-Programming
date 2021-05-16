
/*=============================================
=            Algoritmo naive con ciclo            =
=============================================*/

const getPrime = num => {
    if(num <= 1) return `${num} NO es primo`;
    for(let i = 2; i < num; i++)
        if(num % i === 0) return `${num} NO es primo`;
    return `${num} SÍ es primo`;
}
console.log(getPrime(2));

// Autor: Óscar Sánchez
// en https://www.mkyong.com/java/how-to-determine-a-prime-number-in-java/

/*=====  End of Section comment block  ======*/


/*=============================================
=            Algoritmo naive con recursividad            =
=============================================*/

const getPrime = (num, i) => {
    if (num <= 2) 
        return (num === 2) ? `${num} SÍ es primo` : `${num} NO es primo`; 
    if(num % i === 0) return `${num} NO es primo`; 
    if(i * i > num) return `${num} SÍ es primo`;

    return getPrime(num, i+1);
}
getPrime(2, 2);

// Autor: Shahnawaz_Ali
// en https://www.geeksforgeeks.org/recursive-program-prime-number/ 

/*=====  End of Section comment block  ======*/



/*=============================================
=            Algoritmo optimizado con ciclo           =
=============================================*/

const getPrime = num => {
    if(num <= 1) return `${num} NO es primo`;
    for(let i = 2, s = Math.sqrt(num); i <= s; i++)
        if(num % i === 0) return `${num} NO es primo`; 
    return `${num} SÍ es primo`;
}
console.log(getPrime(2));

// Autor: Ariya Hidayat 
// en https://ariya.io/2013/07/prime-numbers-factorial-and-fibonacci-series-with-javascript-array

/*=====  End of Section comment block  ======*/



/*=============================================
=            Algoritmo optimizado con recursividad           =
=============================================*/

const getPrime = (num, i) => {
    let s = Math.sqrt(num);
    if (num <= 2) 
        return (num === 2) ? `${num} SÍ es primo` : `${num} NO es primo`; 
    if(num % i === 0) return `${num} NO es primo`; 
    if(i > s) return `${num} SÍ es primo`;

    return getPrime(num, i+1);
}
console.log(getPrime(2, 2));

// Autor: adaptado por mi de Ariya Hidayat 
// En: 

/*=====  End of Section comment block  ======*/








