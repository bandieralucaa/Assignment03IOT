////////////////////constanst
const MQTT_D = false;
const PLOT_D = false;
const AJAX_D = false;
const POL_D = true;

const URLQ = "myController.php";


const FNormal = 5000;
const FDanger = 1000;

const D1 = 0.15;
const D2 = 0.25;
const D3 = 0.35;
const D4 = 0.45;
const AMOUNTD = 4;
const DD = [D1, D2, D3, D4];
const stateString = ["ALARM-TOO-LOW", "NORMAL STATE", "PRE-ALARM-TOO-HIGH", "ALARM-TOO-HIGH", "ALARM-TOO-HIGT-CRITIC"];
///////////////


const amountSamples = 100;
//let act = 0;
// createFiniteQueue(amountSamples, 0, 0);
createFiniteQueueDEBUG(amountSamples);


/////////////////////////////////////////////////////////////////////////////
//////////// MQTT management


let host = "localhost"; //powered by moquitto
let port = 8080; //PORTA DELLA WEBSOCKET


/***
    * Browser
    * This document explains how to use MQTT over WebSocket with the ws and wss protocols.
    * EMQX's default port for ws connection is 8083 and for wss connection is 8084.
    * Note that you need to add a path after the connection address, such as /mqtt.
    */
const url = 'mqtt://' + host + ':' + port;
/***
    * Node.js
    * This document explains how to use MQTT over TCP with both mqtt and mqtts protocols.
    * EMQX's default port for mqtt connections is 1883, while for mqtts it is 8883.
    */
// const url = 'mqtt://broker.emqx.io:1883'

// Create an MQTT client instance
const options = {
    // Clean session
    clean: true,
    connectTimeout: 4000,
    // Authentication //for now, anonymus connections are allowed
    // clientId: 'Server',
    // username: 'emqx_test',
    // password: 'emqx_test',
}

const client  = mqtt.connect(url, options);

const publish_topic = "river/freq";
const subscribe_topic = "river/sample";




//////////////////////////////////////////////////////////////
//// HTML blocks and interactions

const displayActSamples = document.getElementById("displayActSamples");

const freqInput = document.getElementById("freq");

const stateLabel = document.getElementById("stateDam");

const canPlot = document.getElementById("canPlot");



document.getElementById("but").addEventListener("click", () => {
    let t = freqInput.value;
    if (MQTT_D) {
        console.log(t);
    }
    let newF = parseInt(t);
    
    if(Number.isInteger(newF)){
        if (MQTT_D) {
            console.log("SENDING " + newF);
        }
        client.publish(publish_topic, freqInput.value);
    }
    
    // console.log("ciao");
})










///////////// quando si connette, devo poter controllare la frequenza: mi iscrivo
client.on('connect', function () {
    if (MQTT_D) {
        console.log('Connected');
    }

    // Subscribe to a topic
    client.subscribe(subscribe_topic, function (err) {
        if (!err) {
            if (MQTT_D) {
                console.log("mi sono iscritto a: " + subscribe_topic); //debug print
            }
                // Publish a message to a topic
                //   client.publish(publish_topic, 'Hello mqtt');
                //   console.log()



                // TODO: valutare se sbloccare i controlli
        }
    });
});





///////// Receive messages
client.on('message', function (topic, message) {
    if(topic == "river/sample"){
        // if (act == amountSamples){
        //     displayActSamples.innerHTML = "";
        //     act = 0;
        // }
        // console.log(topic + " / " + message);
        // displayActSamples.innerHTML += topic + " / " + message + "\n";
        // act++;

        let sampledMeasure = parseFloat(message);

        damPolicy(sampledMeasure);

        uploadCSV2(message);
        //pushInfo(parseActTime(), sampledMeasure);
        pushInfo(new Date(), sampledMeasure);
        
        // fq.pushInfo(counter, parseFloat(message));
        // counter = counter + 1;
        displayActSamples.innerHTML = "";
        displayActSamples.innerHTML += obtainStoricPushX() + "\n"; // fq.obtainStoricPushX() + "\n";
        displayActSamples.innerHTML += obtainStoricPushY() + "\n";
        // d3.select("path.line").remove();
        // d3.selectAll("path.line").remove();
        document.querySelector("#my_dataviz").innerHTML = "";
        
        // d3.select("#wrapper").selectAll("svg").remove();
        if(canPlot.checked){
            plotFunc3();
        }
        
        // if (act == amountSamples){
        //     displayActSamples.innerHTML = "";
        //     act = 0;
        // }
        // console.log(topic + " / " + message);
        // displayActSamples.innerHTML += topic + " / " + message + "\n";
        // act++;
    }
    // message is Buffer
    //   console.log(message.toString());
    //   client.end()
})







//////////////////////////////////////////////////////////////////////////////////////////////////

function getActFreqToConsider(actState){
    if (actState < 2) {
        return FNormal;
    } else {
        return FDanger;
    }
}

///////////////////////////////////////////////////////////////////////



let actLev = 0; //1 -> to

function damPolicy(sampledMeasure) {
    let newLev = 0;
    let mustExit = false;
    while(newLev < AMOUNTD && !(mustExit)) {
        if (newLev != 0) {
            mustExit = (sampledMeasure <= DD[newLev]);
        } else {
            mustExit = (sampledMeasure < DD[newLev]);
        }
        if (!mustExit){
            newLev = newLev + 1;
        }
    }
    if (POL_D){
        console.log("LEVEL: " + actLev);
    }    
    switchState(newLev);

}

function switchState(newLev) {
    if (actLev != newLev) {
        freqToSet = getActFreqToConsider(newLev);
        stateLabel.innerHTML = stateString[newLev];
        if(POL_D){
            console.log("POLICY CHANGE: new state -> " + stateString[newLev]);
        }
        switch (newLev) {
            case 0:
                //freqCampionamento = nomale
                //aperturaValvola = 0
                break;
            
            case 1:
                //freqCampionamento = nomale
                //aperturaValvola = 25
                break;
            
            case 2:
                //freqCampionamento = danger
                //aperturaValvola = 25
                break;
            
            case 3:
                //freqCampionamento = danger
                //aperturaValvola = 50
                break;

            case 4:
                //freqCampionamento = danger
                //aperturaValvola = 100
                break;
        }
        client.publish(publish_topic, freqToSet + "");
        if(POL_D){
            console.log("POLICY CHANGE: setted " + freqToSet + " now");
        }
        actLev = newLev;    
    }
    
}



















// function plotFunc(){
//     let x_data = obtainStoricPushX();
//     let y_data = obtainStoricPushY();
//     let minX = d3.min(x_data);
//     let maxX = d3.max(x_data);
//     let minY = d3.min(y_data);
//     let maxY = d3.max(y_data);
//     let lineInnerHeight = 200;
//     let lineInnerWidth = 200;
//     lineSvg = d3.select('#linechart');

//     var x = d3.scaleLinear().domain([minX, maxX]).range([0, lineInnerWidth]);
//     var y = d3.scaleLinear().domain([minY, maxY]).range([lineInnerHeight, 0]);

//     var line = d3.line()
//     .x(function(d, i) {
//         return x(x_data[i]);
//     })
//     .y(function(d, i) {
//         return y(y_data[i]);
//     });

//     let g = lineSvg.append('g');
//     var xAxis = d3.axisBottom().scale(x);
//     g.append("g")
//     .attr("class", "axis")
//     .attr("transform", "translate(35," + (lineInnerHeight) + ")")
//     .call(xAxis);

//     var yAxis = d3.axisLeft().scale(y);
//     g.append("g")
//     .attr("class", "axis")
//     .attr("transform", "translate(35,0)")
//     .call(yAxis);

//     g.append('path')
//     .attr('d', line(x_data))
//     .attr("transform", "translate(35,0)");
// }

function plotFunc2(){
    // Draw a very simple line using d3 functions
    // using simple arrays of x and y values.
    // Alas, you must convert to a more complex form
    // to use them!

    let margin = {top: 20, right: 20, bottom: 20, left: 20},
    width = 600 - margin.left - margin.right,
    height = 270 - margin.top - margin.bottom;

    let xdata = obtainStoricPushX();
    let ydata = obtainStoricPushY();

    // var xdata = d3.range(0, 20);
    // var ydata = [1, 4, 5, 9, 10, 14, 15, 15, 11, 10, 5, 5, 4, 8, 7, 5, 5, 5, 8, 10];

    // d3.js functions want x,y data in a not-so-intuitive structure
    // Assemble the needed array structure (Thanks to FernofTheAndes on SO)
    // The new structure is technically an array of objects.
    // Each object has the structure {property: value}
    // In this case, each object is one x, y pair

    var xy = []; // start empty, add each element one at a time
    for(var i = 0; i < xdata.length; i++ ) {
        xy.push({x: xdata[i], y: ydata[i]});
    };

    if (PLOT_D) {
        console.log("xy is:", xy); // shows the data structure
    }
    

    var xscl = d3.scaleLinear()
        .domain(d3.extent(xy, function(d) {return d.x;})) //use just the x part
        .range([margin.left, width + margin.left]);

    var yscl = d3.scaleLinear()
        .domain(d3.extent(xy, function(d) {return d.y;})) // use just the y part
        .range([height + margin.top, margin.top]);

    var slice = d3.line()
        .x(function(d) { return xscl(d.x);}) // apply the x scale to the x data
        .y(function(d) { return yscl(d.y);}); // apply the y scale to the y data

    if (PLOT_D) {
        console.log("slice(xy) is:", slice(xy)); // shows the exact pen moves
    }

    var svg = d3.select('#my_dataviz')
        .append("svg");

    svg.append('rect') // outline for reference
        .attr({x: margin.left, y: margin.top,
            width: width,
            height: height,
            stroke: 'black',
            'stroke-width': 0.5,
            fill:'white'});

    svg.append("path")
        .attr("class", "line")
        .attr("d", slice(xy)) // use the return value of slice(xy) as the data, 'd'
        .style("fill", "none")
        .style("stroke", "red")
        .style("stroke-width", 2);
}









function plotFunc3(){
    let x1 = obtainStoricPushX();
    let y1 = obtainStoricPushY();
    let minVX = x1[0];
    var dataPoints = [];
    if (PLOT_D){
        console.log("DELTA: " + (x[x1.length] - minVX));
    }

    for (var i = 0; i < x1.length; i++) {
        dataPoints.push({
            x: x1[i],//byIntTimeToDate(x1[i]),
            y: y1[i]
        });
    }

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