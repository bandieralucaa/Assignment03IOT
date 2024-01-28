<?php
// exec("mode COM3 BAUD=9600 PARITY=N data=8 stop=1 xon=off");

// $serialPort = fopen("COM3", "r+");
// if (!$serialPort) {
//     die("Errore nell'apertura della porta seriale.");
// } else {
//     echo "Porta seriale aperta correttamente.<br>";
// }


// $readData = fread($serialPort, 1024);
// if ($readData !== false && !empty($readData)) {
//     echo $readData;
// } else {
//     echo "Nessun dato valido ricevuto dalla porta seriale.";
// }

// file_put_contents("log.txt", "Richiesta AJAX ricevuta: " . date("Y-m-d H:i:s") . "\n", FILE_APPEND);
// file_put_contents("log.txt", "Dati ricevuti: " . $readData . "\n", FILE_APPEND);
// echo "Lunghezza dati: " . strlen($readData) . "<br>";

// fclose($serialPort);

//READ SERIAL PORT COM3
exec("mode COM3 BAUD=9600 PARITY=N data=8 stop=1 xon=off");
$serialPort = fopen("COM3", "r+");
if (!$serialPort) {
    die("Errore nell'apertura della porta seriale.");
} else {
    echo "Porta seriale aperta correttamente.<br>";
}

$readData = fread($serialPort, 1024);
if ($readData !== false && !empty($readData)) {
    echo $readData;
} else {
    echo "Nessun dato valido ricevuto dalla porta seriale.";
}

file_put_contents("log.txt", "Richiesta AJAX ricevuta: " . date("Y-m-d H:i:s") . "\n", FILE_APPEND);
file_put_contents("log.txt", "Dati ricevuti: " . $readData . "\n", FILE_APPEND);
echo "Lunghezza dati: " . strlen($readData) . "<br>";

fclose($serialPort);


?> 
