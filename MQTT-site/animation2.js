const URLQ = "http://localhost:8080/";

//////////////////////////////////////////////////////////////
//// HTML blocks and interactions

// const displayActSamples = document.getElementById("displayActSamples");

// // const freqInput = document.getElementById("freq");

// const stateLabel = document.getElementById("stateDam");

// const canPlot = document.getElementById("canPlot");

const stateDamState = document.getElementById("stateDamState");

const actValveOp = document.getElementById("actValveOp");

const valveType = document.getElementById("valveType");

const sliderNewValveOp = document.getElementById("sliderNewValveOp");

const sendNewValveOp = document.getElementById("sendNewValveOp");

const valueWillSet = document.getElementById("valueWillSet");

let suggestedFreq = 1000;

sendNewValveOp.addEventListener("click", () => {
    let array = {"percentage" : parseInt(sliderNewValveOp.value), "time" : (new Date()).getTime()};
    console.log(array);
    console.log(JSON.stringify(array));
    formData = JSON.stringify(array);

    let xhr = new XMLHttpRequest();
    
    let ok = URLQ + "api/data/valveop";
    xhr.open('POST', ok);

    // xhr.setRequestHeader('X-Requested-With', 'XMLHttpRequest'); // linea aggiunta per settare l' "X-Requested-With header" che indica che questa è una richiesta AJAX.
    xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
    //xhr.setRequestHeader('Access-Control-Allow-Headers', '*');
    xhr.setRequestHeader('Access-Control-Allow-Origin', 'GET POST');
    //console.log("A " + xhr.getAllResponseHeaders());
    xhr.send(formData);
})

sliderNewValveOp.addEventListener("input", () => {
    valueWillSet.innerHTML = sliderNewValveOp.value;
})

sliderNewValveOp.addEventListener("change", () => {
    valueWillSet.innerHTML = sliderNewValveOp.value;
})

// document.getElementById("but").addEventListener("click", () => {
//     let t = freqInput.value;
//     if (MQTT_D) {
//         console.log(t);
//     }
//     let newF = parseInt(t);
    
//     if(Number.isInteger(newF)){
//         if (MQTT_D) {
//             console.log("SENDING " + newF);
//         }
//         client.publish(publish_topic, freqInput.value);
//     }
    
//     // console.log("ciao");
// })




setInterval(() => {

    getState();
    getAmountValveOp();
    getValveTypeConfig();

    initPlot();

}, suggestedFreq);


function getState(){
    let xhr = new XMLHttpRequest();
    
    let ok = URLQ + "api/data/damstate";
    xhr.onreadystatechange = () => {
        if (xhr.readyState === 4 && xhr.status === 200) {

            let res = JSON.parse(xhr.responseText);
            // console.log(res);
            stateDamState.innerHTML = res.state;
            suggestedFreq = res.freq;
        }
    };

    xhr.open('GET', ok, false);

    xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
    xhr.setRequestHeader('Access-Control-Allow-Origin', 'GET POST');
    xhr.send();
}


function getAmountValveOp(){
    let xhr = new XMLHttpRequest();
    
    let ok = URLQ + "api/data/valveop";
    xhr.onreadystatechange = () => {
        if (xhr.readyState === 4 && xhr.status === 200) {

            let res = JSON.parse(xhr.responseText);
            // console.log(res);
            actValveOp.innerHTML = res.percentage;
        }
    };

    xhr.open('GET', ok, false);

    xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
    xhr.setRequestHeader('Access-Control-Allow-Origin', 'GET POST');
    xhr.send();
}


function getValveTypeConfig(){
    let xhr = new XMLHttpRequest();
    
    let ok = URLQ + "api/data/valvetype";
    xhr.onreadystatechange = () => {
        if (xhr.readyState === 4 && xhr.status === 200) {

            let res = JSON.parse(xhr.responseText);
            // console.log(res);
            valveType.innerHTML = res.valveState;
        }
    };

    xhr.open('GET', ok, false);

    xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
    xhr.setRequestHeader('Access-Control-Allow-Origin', 'GET POST');
    xhr.send();
}






function initPlot(){
    let xhr = new XMLHttpRequest();
    
    let ok = URLQ + "api/data/samples";
    xhr.onreadystatechange = () => {
        if (xhr.readyState === 4 && xhr.status === 200) {

            let res = JSON.parse(xhr.responseText);
            plotSamples(res);
            //console.log(res);
            // // res.forEach(id => arrayMissMeds.push(id));
            // arrayMissMeds = res;
            // console.log("POST " + arrayMissMeds);
            // this.manageResults();
        }
    };

    xhr.open('GET', ok, false);

    // xhr.setRequestHeader('X-Requested-With', 'XMLHttpRequest'); // linea aggiunta per settare l' "X-Requested-With header" che indica che questa è una richiesta AJAX.
    xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
    //xhr.setRequestHeader('Access-Control-Allow-Headers', '*');
    xhr.setRequestHeader('Access-Control-Allow-Origin', 'GET POST');
    //console.log("A " + xhr.getAllResponseHeaders());
    xhr.send();
}



function plotSamples(doubleArr){
    if (false) { //!canPlot.checked){
        return;
    }

    //let x1 = obtainStoricPushX();
    //let y1 = obtainStoricPushY();


    // let minVX = x1[0];
    var dataPoints = [];
    // if (PLOT_D){
    //     console.log("DELTA: " + (x[x1.length] - minVX));
    // }

    for (var i = 0; i < doubleArr.length; i++) {
        dataPoints.push({
            x: new Date(doubleArr[i].x),//byIntTimeToDate(x1[i]),
            y: doubleArr[i].y
        });
    }
    // console.log(dataPoints);

    var chart = new CanvasJS.Chart("chartContainer", {
        title:{
            text: "Last samples"
        },
        axisX:{
            second: '%H:%M:%S',
            minute: '%H:%M:%S',
            hour: '%H:%M:%S',
            day: '%H:%M:%S',
            week: '%H:%M:%S',
            month: '%H:%M:%S',
            year: '%H:%M:%S',
            title: "timeline",
            //gridThickness: 2
        },
        axisY: {
            title: "Water level",
            minimum: 0,
            maximum: 1.5,
        },
    data: [{
        type: "line",
        dataPoints: dataPoints
    }]
    });

    //chart.SetYAxisRange(0,1.5);
    chart.render();
}