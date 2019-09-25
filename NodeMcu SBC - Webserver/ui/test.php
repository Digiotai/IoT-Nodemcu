<?php
$connection = mysqli_connect('localhost', 'id8821146_madhu', 'madhu143', 'id8821146_madhu');
$result = mysqli_query($connection, "SELECT * FROM weather");


?>


<html>
  <head>
    <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
    <script type="text/javascript">
      google.charts.load('current', {'packages':['bar']});
      google.charts.setOnLoadCallback(drawChart);

      function drawChart() {
        var data = google.visualization.arrayToDataTable([
          ['id', 'temp', 'hum'],
          
         <?php
            
             if(mysqli_num_rows($result)> 0){
                 
                 while($row = mysqli_fetch_array($result)){
                     
                 echo "['".$row['id']."','".$row['temp']."',['".$row['hum']."']],";
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
    <div id="columnchart_material" style="width: 800px; height: 500px;"></div>
  </body>
</html>