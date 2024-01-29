<?php

function byJPTimeToIntDate($toConvert){
    $d = explode("__", $toConvert);
    $dd = explode("_", $d[0]);
    $hh = explode("_", $d[1]);

    $coeffD = 86400;
    $coeffH = 3600;
    $coeffM = 60;
    $coeffS = 1;
    $coeffs = array($coeffD, $coeffH, $coeffM, $coeffS);
    $vals = array($dd[2], $hh[0], $hh[1], $hh[2]);
    $amountVals = sizeof($vals);
    $ret = 0;
    for ($i = 0; $i < $amountVals ; $i++) { 
        $ret += intval($vals[$i]) * $coeffs[$i];
    }
    return $ret;

}

function saveOnCSV(){
    $datoToSave = $_GET["info"];
    $a = date("Y-m-d H:i:s", time());
    // // echo $a . "<br>";
    $b = str_replace(" ","__",$a);
    $b = str_replace(":","_",$b);
    $time = str_replace("-","_",$b);

    $d = DIRECTORY_SEPARATOR;

    $actDir = __DIR__;
    $adaptPath = "";
    $byRootToDirCSV = "";
    $dirWhereCSV = $actDir . $adaptPath . $byRootToDirCSV;

    $csvName = "myCsv.csv";

    $absoluteName = $dirWhereCSV . $d . $csvName;

    if (!file_exists($absoluteName)){
        $myfile = fopen($absoluteName, "w");
        fwrite($myfile, "time,OKtime,date\n");
        fclose($myfile);
    }

    // echo $datoToSave;
    // echo "<br>";
    // echo $data;
    // echo "<br>";
    // echo $dirWhereCSV;

    $fp = fopen($absoluteName, 'a');
    $toPrint = array($time, byJPTimeToIntDate($time), $datoToSave);

    fputcsv($fp, $toPrint);
        // string $separator = ",",
        // string $enclosure = "\"",
        // string $escape = "\\",
        // string $eol = "\n"
    // ): int|false

    fclose($fp);
    //$imgName = $userNickname . "__" . $b;
}



$codeQ = $_GET["codeQ"];
switch ($codeQ) {
    case "1":
        saveOnCSV();
        break;
    
    default:
        # code...
        break;
}



?>