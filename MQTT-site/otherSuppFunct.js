const COEFF_D = 86400*100;
const COEFF_H = 3600*100;
const COEFF_M = 60*100;
const COEFF_S = 1*100;
const COEFF_CS = 1
const COEFFSS = [COEFF_D, COEFF_H, COEFF_M, COEFF_S, COEFF_CS];

function parseActTime(){
    const date = new Date();
    let myVals = [date.getDate(), date.getHours(), date.getMinutes(), date.getSeconds(), (Math.floor(date.getMilliseconds()/100))];
    
    let res = 0;
    for (let index = 0; index < COEFFSS.length; index++) {
        res += (COEFFSS[index] * myVals[index]);
    }
    return res;
}

function byIntTimeToDate(toConvert) {
    const date = new Date();
    let remains = toConvert;
    const times = [];
    for (let index = 0; index < COEFFSS.length; index++) {
        let tmp = Math.floor(remains / COEFFSS[index]);
        times.push(tmp);
        remains -= tmp * COEFFSS[index];
    }
    let res = "";
    for (let index = 0; index < COEFFSS.length; index++) {
        res += times[index] + ":";
    }
    console.log(res.substring(0, (res.length-1)));
    return new Date(date.getFullYear(), date.getMonth(), times[0], times[1], times[2], times[3], times[4]);
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
            if (AJAX_D) {
                console.log("SAVED: " + info);
            }
        }
    };

    let args = {
        "codeQ" : 1,
        "info" : info
    }

    let ok = URLQ + "?" + prepareURLwithOkGet(args);
    if (AJAX_D) {
        console.log("EEE " +  ok);
    }

    xhr.open('GET', ok, true);

    xhr.setRequestHeader('X-Requested-With', 'XMLHttpRequest'); // linea aggiunta per settare l' "X-Requested-With header" che indica che questa è una richiesta AJAX.
    xhr.send();
    
        // console.log("xhr done: inside");
}
