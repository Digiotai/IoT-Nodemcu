<!DOCTYPE html>
<html>
<head>
 <title>Data</title>
 
 <style>
  table {
   border: 2px solid #dddddd;
   width: 80%;
   color: #1c1b1b;
   font-family: monospace;
   font-size: 20px;
   text-align: center;
   margin-top: 30px;
   margin-left: 130px;
    } 
         
         
 th {
   background-color: #006cfb;
   color: white;
    }
    
  tr:nth-child(odd) {background-color: #FFC300}
    
  . tr {
      background-color: #F74E2C; 
   } 
  
  .center {
  display: block;
  margin-left: auto;
  margin-right: auto;
  margin-top: 20px;
 
}

.chart {
    margin: 100px 120px;
}
 </style>

<body>
    
        <a href="https://www.Digiotai.com" target="_blank">
    <IMG SRC="Digotai Logo Mobile.png"  class="center" ALT="www.digiotai.com" WIDTH=180 HEIGHT=100>
        </a>
        
        
    

     <table>
 <tr>
  <th>Time</th>
  <th>Temperature</th> 
  <th>Humidity</th>
  
 
 </tr>
 
  <?php
$conn = mysqli_connect("localhost", "id8821146_ui", "madhu143", "id8821146_ui");


  // Check connection
  if ($conn->connect_error) {
   die("Connection failed: " . $conn->connect_error);
  } 
  
  $sql = "SELECT Temperature, Humidity, Time FROM Ui  ORDER BY id DESC LIMIT 10";
 
  $result = $conn->query($sql);
  
  //$date = new DateTime($mysql_column['Time']);
  
  //if ($result->num_rows > 0) {
 
   // output data of each row
   while($row = $result->fetch_assoc()) {
    echo "<tr><td>" .$row["Time"] . "</td><td>" . $row["Temperature"] . "</td><td>"
. $row["Humidity"].   "</td></tr>";
}
echo "</table>";
//} else { echo "0 results"; }
$conn->close();
?>

</table>

  <div class="chart">
      
      
      <?php
$connection = mysqli_connect('localhost', 'id8821146_ui', 'madhu143', 'id8821146_ui');

$result = mysqli_query($connection, "SELECT * FROM Ui");

//if($result){
 //echo "connected";
//}

?>

<html>
  <head>
    <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
    <script type="text/javascript">
      google.charts.load('current', {'packages':['bar']});
      google.charts.setOnLoadCallback(drawChart);

      function drawChart() {
        var data = google.visualization.arrayToDataTable([
          ['Time', 'Temperarute', 'Humidity'],
            
            <?php
            
             if(mysqli_num_rows($result)> 0){
                 
                 while($row = mysqli_fetch_array($result)){
                     
                 echo "['".$row['Time']."','".$row['Temperature']."','".$row['Humidity']."'],";
             }
             }
             ?>
          
        ]);

        var options = {
          chart: {
            title: 'Temperature & Humidity',
            
          }
        };

        var chart = new google.charts.Bar(document.getElementById('columnchart_material'));

        chart.draw(data, google.charts.Bar.convertOptions(options));
      }
    </script>
  </head>
  <body>
    <div id="columnchart_material" style="width: 500px; height: 250px;"></div>
  </body>
</html>
  </div>

 </head>

</body>
</html>