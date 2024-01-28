var width = 600;
var height = 400;
var marginLeft = 50;
var marginTop = 20;

var years = [2000, 2001, 2002, 2003, 2004];
var values = [100, 150, 120, 200, 180];

var svg = d3.select("body").append("svg")
    .attr("width", width + marginLeft)
    .attr("height", height + marginTop)
    .append("g")
    .attr("transform", "translate(" + marginLeft + "," + marginTop + ")");

var data = years.map(function (year, index) {
    return { Year: year, Value: values[index] };
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
