let actIndForFQ = 1;
let xx = new Array();
let yy = new Array();
let size = 0;

function summonRandomNumber(min, max) {
    console.log(min + " / " + max);
    let coeff = Math.abs(Math.random());
    let delta = max - min;
    return delta * coeff + min;
}

function createFiniteQueue(newSize, firstx, firsty){
    xx = new Array(newSize);
    yy = new Array(newSize);
    size = newSize;

    for (let index = 0; index < size; index++) {
        xx[index] = firstx;
        yy[index] = firsty;
    }
    actIndForFQ = 1;
}

function createFiniteQueueDEBUG(newSize) {
    xx = new Array(newSize);
    yy = new Array(newSize);
    size = newSize;

    const exeed = 0.05;
    let actDate = new Date();
    const isDanger = false;
    const amountDateForDanger = Math.floor(newSize/7);
    const amountDateForOK = Math.floor(newSize/5);

    let actAmount = isDanger ? amountDateForDanger : amountDateForOK;
    let lastCheckPoint = 0;
    let index = 0;
    while (index < newSize) {
        let tmpTime = actDate.getTime();
        if ((index-lastCheckPoint) > actAmount) {
            lastCheckPoint += actAmount;
            actAmount = isDanger ? amountDateForDanger : amountDateForOK;
        }
        tmpTime += isDanger ? FDanger : FNormal;
        xx[index] = new Date(tmpTime);
        actDate = xx[index];
        yy[index] = summonRandomNumber((DD[0] - exeed), (DD[DD.length - 1] + exeed));
        index++;
    }
    actIndForFQ = 1;
}

function pushInfo(x, y) {
    //console.log(xx + " " + x + " " + actIndForFQ);
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