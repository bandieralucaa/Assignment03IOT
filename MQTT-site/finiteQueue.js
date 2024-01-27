// let actIndForFQ = 1;

class FiniteQueue{

    actIndex; // private variable
    xx;
    yy;
    size;

    __constructor(size, firstx, firsty){
        xx = new Array(size);
        yy = new Array(size);
        size = size;

        for (let index = 0; index < size; index++) {
            xx[index] = firstx;
            yy[index] = firsty;
        }
        actIndForFQ = 1;
    }

    pushInfo(x, y) {
        console.log(xx + " " + x + " " + actIndForFQ);
        xx[actIndForFQ] = x;
        yy[actIndForFQ] = y;
        actIndForFQ = actIndForFQ + 1;
        if (actIndForFQ > this.size){
            actIndForFQ = 0;
        }
    }

    obtainStoric(isX){
        let res;
        if(isX){
            let second = this.xx.slice(0,this.actIndex);
            let first = this.xx.slice(this.actIndex,this.size);
            res = first.concat(second);
        } else {
            let second = this.yy.slice(0,this.actIndex);
            let first = this.yy.slice(this.actIndex,this.size);
            res = first.concat(second);
        }
        return res;
    }

    obtainStoricPushX(){
        return this.obtainStoric(true);
    }

    obtainStoricPushY(){
        return this.obtainStoric(false);
    }
}