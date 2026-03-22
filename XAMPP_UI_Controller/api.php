<?php
// PHP Script to interface with HC-05 COM Port on Windows via XAMPP
header("Access-Control-Allow-Origin: *");

if (isset($_POST['cmd']) && isset($_POST['port'])) {
    $cmd = $_POST['cmd'];
    $port = $_POST['port']; // e.g., COM5

    // In Windows, setup the COM port parameters before opening
    // This is required for HC-05 serial connection to work reliably.
    if (strtoupper(substr(PHP_OS, 0, 3)) === 'WIN') {
        exec("mode $port BAUD=9600 PARITY=N data=8 stop=1 xon=off");
    }

    // Try to open the Serial Port (the @ suppresses standard warnings)
    $fp = @fopen($port, "w");
    
    if (!$fp) {
        echo "ERROR: Could not open port $port. Ensure HC-05 is connected, paired to this PC, and port is correct.";
    } else {
        // Send the character
        fwrite($fp, $cmd);
        fclose($fp);
        echo "SUCCESS";
    }
} else {
    echo "ERROR: Missing parameters.";
}
?>
