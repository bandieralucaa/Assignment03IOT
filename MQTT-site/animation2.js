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

const suggestedFreq = 1000;

sendNewValveOp.addEventListener("click", () => {
    //managePostQuery
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

    initPlot();

}, suggestedFreq);


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
    console.log(dataPoints);

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
            title: "Water level"
        },
    data: [{
        type: "line",
        dataPoints: dataPoints
    }]
    });

    chart.render();
}