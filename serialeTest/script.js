var width = 500;
var height = 300;
var marginLeft = 50;  
var marginTop = 20; 

var svg = d3.select("body").append("svg")
    .attr("width", width + marginLeft)
    .attr("height", height + marginTop)
    .append("g")
    .attr("transform", "translate(" + marginLeft + "," + marginTop + ")");

    d3.csv("data.csv").then(function (data) {

    data.forEach(function (d) {
        d.Year = parseInt(d.Year);
        d.Value = parseInt(d.Value);
    });

    var xScale = d3.scaleLinear().domain([d3.min(data, d => d.Year), d3.max(data, d => d.Year)]).range([0, width]);
    var yScale = d3.scaleLinear().domain([0, d3.max(data, d => d.Value)]).range([height, 0]);

    var xAxis = d3.axisTop().scale(xScale);
    var yAxis = d3.axisLeft().scale(yScale);

    svg.append("g")
        .call(xAxis);

    svg.append("g")
        .call(yAxis);

    var line = d3.line()
        .x(d => xScale(d.Year))
        .y(d => yScale(d.Value));

    svg.append("path")
        .data([data])
        .attr("fill", "none")
        .attr("stroke", "blue")
        .attr("stroke-width", 2)
        .attr("d", line);

    svg.selectAll("circle")
        .data(data)
        .enter().append("circle")
        .attr("cx", d => xScale(d.Year))
        .attr("cy", d => yScale(d.Value))
        .attr("r", 5)
        .attr("fill", "red");
});
