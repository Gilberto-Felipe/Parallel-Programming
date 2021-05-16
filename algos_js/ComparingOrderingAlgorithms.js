/*==================================================
                TIEMPO DE ALGORITMOS
===================================================*/

/*---------------------Funciones-------------------*/

// FUNCIÓN GENERAR ALEATORIOS
const random = (rango, max, min) => {
    let alea = [];
    for (let index = 0; index < rango; index++) {
        alea.push(Math.floor(Math.random() * max + min))    
    }   
    // console.log(alea);
    return alea;
}

// FUNCIÓN ALGORITOMO SENCILLO DE COMPARACIÓN
const extrem = alea => {
    let min = alea[0];
    let max = alea[0];
    for(let i = 1; i < alea.length; i++){

        if (alea[i] < min) {
            min = alea[i];
        }
        if (alea[i] > max) {
            max = alea[i];
        }
    }
    console.log(min + " min");
    console.log(max + " max");
}

// FUNCIÓN ALGORITMO BURBUJA
const burbuja = (alea) => {
    for (let i = 0; i < alea.length; i++) {
        for (let j = 0; j < alea.length - i; j++) {
            if (alea[j] > alea[j+1]) {
                let temp = alea[j+1];
                alea[j+1] = alea[j];
                alea[j] = temp; 
            }
        }
    }
    //console.log(alea);
    console.log(alea[0] + " minimo");
    console.log(alea[alea.length-1] + " máximo");
    //return alea;
}

// FUNCIÓN TIMER 
const timer = (fun, param) => {
    let start = Date.now();
    fun(param);
    console.log("Tiempo: " + (Date.now() - start) + "ms");
}


/*===================================
INSTRUCCIONES
====================================*/

let alea = random(1440000, 1440000,1);
timer(extrem, alea);
timer(burbuja, alea);


// 1440k = burbuja 7565189 ms