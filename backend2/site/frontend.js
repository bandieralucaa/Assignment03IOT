//const ff = document.getElementById("myForm");

const val = document.getElementById("value");
const tim = document.getElementById("time");
const pl = document.getElementById("place");
const butt = document.getElementById("sub");


sub.addEventListener("click", () => {

    let array = {"value" : val.value, "time" : tim.value, "place": pl.value};
    // let myVals = new Array();
    // myVals["value"] = val.value;
    // myVals["time"] = tim.value;
    // myVals["place"] = pl.value;
    console.log(array);
    console.log(JSON.stringify(array));
    formData = JSON.stringify(array);

    fromClientToServer(formData);
    
    //event.preventDefault();
    // Perform validation and processing here
    //ff.submit();
    
});

function fromClientToServer(formData){
    let xhr = new XMLHttpRequest();
    
    let ok = "http://localhost:8080/api/data";
    xhr.open('POST', ok);

    // xhr.setRequestHeader('X-Requested-With', 'XMLHttpRequest'); // linea aggiunta per settare l' "X-Requested-With header" che indica che questa è una richiesta AJAX.
    xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
    //xhr.setRequestHeader('Access-Control-Allow-Headers', '*');
    xhr.setRequestHeader('Access-Control-Allow-Origin', 'GET POST');
    //console.log("A " + xhr.getAllResponseHeaders());
    xhr.send(formData);

    // var xhr = new XMLHttpRequest();
    // var url = "http://localhost:8080/api/data";
    // xhr.open("POST", url, true);
    // xhr.setRequestHeader("Content-Type", "application/json");
    
    // xhr.onreadystatechange = function () {
    //     if (xhr.readyState === 4 && xhr.status === 200) {
    //         console.log("OK");
    //         // var json = JSON.parse(xhr.responseText);
    //         // console.log(json.email + ", " + json.password);
    //     }
    // };
    // var data = formData;// JSON.stringify({"email": "hey@mail.com", "password": "101010"});
    // xhr.send(data);
    // console.log("xhr done: inside");
    // $.ajax({
    //     type: "POST",
    //     url: "http://localhost:8080/api/data",
    //     data: formData,
    //     //success: function(){},
    //     dataType: "json",
    //     contentType : "application/json"
    //     });
}
//ff.addEventListener('submit', (event) => {

    

    // let formData = JSON.stringify($("#myForm").serializeArray());
    // console.log(formData);
    // setTimeout(() => {
    //     $.ajax({
    //         type: "POST",
    //         url: "http://localhost:8080/api/data",
    //         data: formData,
    //         success: function(){},
    //         dataType: "json",
    //         contentType : "application/json"
    //         });
    //     //event.preventDefault();
    //     // Perform validation and processing here
    //     ff.submit();
    // }, 3000);
    
// });

  

// function submitForm() {
//     const form = document.getElementById('myForm');
//     form.addEventListener('submit', (event) => {
//       event.preventDefault();
//       // Perform validation and processing here
//     });

//     form.submit();
// }