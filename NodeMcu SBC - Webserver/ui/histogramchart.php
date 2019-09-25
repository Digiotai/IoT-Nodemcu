<?php
$connection = mysqli_connect('localhost', 'id8821146_madhu', 'madhu143', 'id8821146_madhu');
$result = mysqli_query($connection, "SELECT * FROM weather");
?>

<html>
  <head>
    <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
    <script type="text/javascript">
      google.charts.load("current", {packages:["corechart"]});
      google.charts.setOnLoadCallback(drawChart);
      function drawChart() {
        var data = google.visualization.arrayToDataTable([
          ['id', 'temp', 'hum'],
        
        <?php
            
             if(mysqli_num_rows($result)> 0){
                 
                 while($row = mysqli_fetch_array($result)){
                     
                 echo "['".$row['id']."','".$row['temp']."','".$row['hum']."'],";
             }
             }
            ?>
          
]);
        var options = {
          title: 'Temperature & Humidity',
          legend: { position: 'none' },
        };

        var chart = new google.visualization.Histogram(document.getElementById('chart_div'));
        chart.draw(data, options);
      }
    </script>
  </head>
  <body>
    <div id="chart_div" style="width: 900px; height: 500px;"></div>
  </body>
</html>