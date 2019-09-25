<?php
 $Temperature = filter_input(INPUT_POST, 'Temperature');
 $Humidity = filter_input(INPUT_POST, 'Humidity');
 if (!empty($Temperature)){
if (!empty($Humidity)){
$host = "localhost";
$dbusername = "id8821146_ui";
$dbpassword = "madhu143";
$dbname = "id8821146_ui";
// Create connection
$conn = new mysqli ($host, $dbusername, $dbpassword, $dbname);

if (mysqli_connect_error()){
die('Connect Error ('. mysqli_connect_errno() .') '
. mysqli_connect_error());
}
else{
$sql = "INSERT INTO Ui (Temperature, Humidity)
values ('$Temperature','$Humidity')";
if ($conn->query($sql)){
echo "New record is inserted sucessfully";
}
else{
echo "Error: ". $sql ."
". $conn->error;
}
$conn->close();
}
}
else{
echo "Humidity should not be empty";
die();
}
}
else{
echo "Temperature should not be empty";
die();
}
?>