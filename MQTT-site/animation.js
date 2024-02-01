const DEBUG = false;
const URLQ = "http://localhost:8080/";

//////////////////////////////////////////////////////////////
//// HTML blocks and interactions

const stateDamState = document.getElementById("stateDamState");

const actValveOp = document.getElementById("actValveOp");

const valveType = document.getElementById("valveType");

const sliderNewValveOp = document.getElementById("sliderNewValveOp");

const sendNewValveOp = document.getElementById("sendNewValveOp");

const valueWillSet = document.getElementById("valueWillSet");

const sliderNewFreqReload = document.getElementById("sliderNewFreqReload");

const freqReloadWillSet = document.getElementById("freqReloadWillSet");

const suggestedFrequence = document.getElementById("suggestedFrequence");

const autoChangeRefresh = document.getElementById("autoChangeRefresh");

let actFreq = 1000;

//send new valve opening to server
sendNewValveOp.addEventListener("click", () => {
    let array = {"percentage" : parseInt(sliderNewValveOp.value), "time" : (new Date()).getTime()};
    if(DEBUG) {
        console.log(array);
        console.log(JSON.stringify(array));
    }
    formData = JSON.stringify(array);

    let xhr = new XMLHttpRequest();
    
    let ok = URLQ + "river/valveop";
    xhr.open('POST', ok);

    xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
    xhr.setRequestHeader('Access-Control-Allow-Origin', 'GET POST');
    xhr.send(formData);
})

//update the label of this input
sliderNewValveOp.addEventListener("input", () => {
    valueWillSet.innerHTML = sliderNewValveOp.value;
})

// //update the label of this input
// sliderNewValveOp.addEventListener("change", () => {
//     valueWillSet.innerHTML = sliderNewValveOp.value;
// })


//FEATURE: management of frequence of plot update 
const warningMessage = document.getElementById("warningMessage");


sliderNewFreqReload.addEventListener("input", () => {
    actFreq = sliderNewFreqReload.value;
    freqReloadWillSet.value = sliderNewFreqReload.value;
    warningMessage.innerHTML = "Frequence " + actFreq + " ms setted";
})


freqReloadWillSet.addEventListener("change", () => {
    let tmp = freqReloadWillSet.value;
    if(Number.isInteger(parseInt(tmp)) && !isNaN(tmp)){
        let parsed = parseInt(tmp);
        warningMessage.innerHTML = "Frequence " + parsed + " ms setted";
        if (parsed > 10000){
            warningMessage.innerHTML = "Frequence is too slow, 10sec setted";
            parsed = 10000;
        } else if (parsed < 1000){
            warningMessage.innerHTML = "Frequence is too high, 1sec setted";
            parsed = 1000;
        }
        sliderNewFreqReload.value = parsed;
        actFreq = parsed;

    } else {
        warningMessage.innerHTML = "Please insert an integer value between 1000 and 10000";
    }
})


setInterval(() => {
    getState();
    getAmountValveOp();
    getValveTypeConfig();
}, 1000);


function coreRecFunction(){
    setTimeout(() => {
        initPlot();

        coreRecFunction();
    }, actFreq);
}

coreRecFunction();


//AJAX request to get dam state and update it on HTML page
function getState(){
    let xhr = new XMLHttpRequest();
    
    let ok = URLQ + "river/damstate";
    xhr.onreadystatechange = () => {
        if (xhr.readyState === 4 && xhr.status === 200) {

            let res = JSON.parse(xhr.responseText);
            
            stateDamState.innerHTML = res.state;
            suggestedFrequence.innerHTML = res.freq;

            if (autoChangeRefresh.checked){
                freqReloadWillSet.value = res.freq;
                sliderNewFreqReload.value = res.freq;
                actFreq = res.freq;
            }
        }
    };

    xhr.open('GET', ok, false);

    xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
    xhr.setRequestHeader('Access-Control-Allow-Origin', 'GET POST');
    xhr.send();
}

//let user modify reload frequence if automatic change not flag
autoChangeRefresh.addEventListener("change", () => {
        freqReloadWillSet.disabled = autoChangeRefresh.checked;
        sliderNewFreqReload.value = autoChangeRefresh.checked;
})

//AJAX request to get valve opening and update it on HTML page
function getAmountValveOp(){
    let xhr = new XMLHttpRequest();
    
    let ok = URLQ + "river/valveop";
    xhr.onreadystatechange = () => {
        if (xhr.readyState === 4 && xhr.status === 200) {
            let res = JSON.parse(xhr.responseText);
            actValveOp.innerHTML = res.percentage;
        }
    };

    xhr.open('GET', ok, false);

    xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
    xhr.setRequestHeader('Access-Control-Allow-Origin', 'GET POST');
    xhr.send();
}

//AJAX request to get valve config type (aka "its state") and update it on HTML page
function getValveTypeConfig(){
    let xhr = new XMLHttpRequest();
    
    let ok = URLQ + "river/valvetype";
    xhr.onreadystatechange = () => {
        if (xhr.readyState === 4 && xhr.status === 200) {
            let res = JSON.parse(xhr.responseText);
            valveType.innerHTML = res.valveState;
            sendNewValveOp.disabled = (res.valveState == "Automatic");
        }
    };

    xhr.open('GET', ok, false);

    xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
    xhr.setRequestHeader('Access-Control-Allow-Origin', 'GET POST');
    xhr.send();
}





//AJAX request to refresh plotting
function initPlot(){
    let xhr = new XMLHttpRequest();
    
    let ok = URLQ + "river/samples";
    xhr.onreadystatechange = () => {
        if (xhr.readyState === 4 && xhr.status === 200) {
            let res = JSON.parse(xhr.responseText);
            plotSamples(res);
        }
    };

    xhr.open('GET', ok, false);
    xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
    xhr.setRequestHeader('Access-Control-Allow-Origin', 'GET POST');
    xhr.send();
}

function plotSamples(doubleArr){
    let dataPoints = [];
    
    for (let i = 0; i < doubleArr.length; i++) {
        dataPoints.push({
            x: new Date(doubleArr[i].x),
            y: doubleArr[i].y
        });
    }

    let chart = new CanvasJS.Chart("chartContainer", {
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
            title: "Timeline",
        },
        axisY: {
            title: "Water level",
            minimum: 0,
            maximum: 0.6,
            interval: 0.15,
            stripLines:[
                {
                    startValue:0.0,
                    endValue:0.15,                
                    color:"#6fced8",
                    label : "L0",
                    labelAlign: "near",
                    labelFontColor: "#000000",
                    opacity: .3,
                },
                {
                    startValue:0.15,
                    endValue:0.25,                
                    color:"#00f800",
                    label : "L1",
                    labelAlign: "near",
                    labelFontColor: "#000000",
                    opacity: .3,
                },
                {
                    startValue:0.25,
                    endValue:0.35,                
                    color:"#ff8f00",
                    label : "L2",
                    labelAlign: "near",
                    labelFontColor: "#000000",
                    opacity: .3,
                },
                {
                    startValue:0.35,
                    endValue:0.45,                
                    color:"#ff0000",
                    label : "L3",
                    labelAlign: "near",
                    labelFontColor: "#000000",
                    opacity: .3,
                },
                {
                    startValue:0.45,
                    endValue:0.6,                
                    color:"#ff0000",
                    label : "L4",
                    labelAlign: "near",
                    labelFontColor: "#000000",
                    opacity: .5,
                }
                ]
        },
    data: [{
        type: "line",
        dataPoints: dataPoints
    }]
    });
    
    chart.render();
}