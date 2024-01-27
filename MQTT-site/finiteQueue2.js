let actIndForFQ = 1;
let xx = new Array();
let yy = new Array();
let size = 0;


function createFiniteQueue(newSize, firstx, firsty){
    xx = new Array(size);
    yy = new Array(size);
    size = newSize;

    for (let index = 0; index < size; index++) {
        xx[index] = firstx;
        yy[index] = firsty;
    }
    actIndForFQ = 1;
}

function pushInfo(x, y) {
    console.log(xx + " " + x + " " + actIndForFQ);
    xx[actIndForFQ] = x;
    yy[actIndForFQ] = y;
    actIndForFQ = actIndForFQ + 1;
    if (actIndForFQ > size){
        actIndForFQ = 0;
    }
}

function obtainStoric(isX){
    let res;
    if(isX){
        let second = xx.slice(0, actIndForFQ);
        let first = xx.slice(actIndForFQ, size);
        res = first.concat(second);
    } else {
        let second = yy.slice(0, actIndForFQ);
        let first = yy.slice(actIndForFQ, size);
        res = first.concat(second);
    }
    return res;
}

function obtainStoricPushX(){
    return this.obtainStoric(true);
}

function obtainStoricPushY(){
    return this.obtainStoric(false);
}

// class FiniteQueue{

//     actIndex; // private variable
//     xx;
//     yy;
//     size;

//     __constructor(size, firstx, firsty){
        
//     }

    

    
// }