const COEFF_D = 86400;
const COEFF_H = 3600;
const COEFF_M = 60;
const COEFF_S = 1;
const COEFFSS = [COEFF_D, COEFF_H, COEFF_M, COEFF_S];

function parseActTime(){
    const date = new Date();
    let myVals = [date.getDate(), date.getHours(), date.getMinutes(), date.getSeconds()];
    let res = 0;
    for (let index = 0; index < myVals.length; index++) {
        res += (COEFFSS[index] * myVals[index]);
    }
    return res;
}

function prepareURLwithOkGet(arrKV){
    let res = "";
    for (let key in arrKV) {
        let value = arrKV[key];

        let toAdd = key + "=";

        if ( Array.isArray(value) ){
            let tmp = ""
            value.forEach(v => tmp += v + "§"); //anche qui gestire caso stringhe
            toAdd += tmp.substring(0, tmp.length-1);
        } else if (false) {
            //se è stringa, ma ancora non ho avuto modo di farlo
        } else {
            toAdd += value;
        }
        res += toAdd + "&";
    }
    return res.substring(0,res.length-1);
}


function uploadCSV() {
    $.ajax({
        type: 'GET',
        url: 'myController.php?codeQ=1&info=' . message,
        // success: function(data) {
        //     $('#notification-list').html(data);
        // },
        // error: function(error) {
        //     console.log('Errore durante l\'aggiornamento delle notifiche:', error);
        // }
    });
}


function uploadCSV2(info) {
    let xhr = new XMLHttpRequest();
        
    xhr.onreadystatechange = () => {
        if (xhr.readyState === 4 && xhr.status === 200) {
            console.log("SAVED: " + info);
        }
    };

    let args = {
        "codeQ" : 1,
        "info" : info
    }
    let ok = URLQ + "?" + prepareURLwithOkGet(args);
    console.log("EEE " +  ok);

    xhr.open('GET', ok, true);

    xhr.setRequestHeader('X-Requested-With', 'XMLHttpRequest'); // linea aggiunta per settare l' "X-Requested-With header" che indica che questa è una richiesta AJAX.
    xhr.send();
    
        // console.log("xhr done: inside");
}
