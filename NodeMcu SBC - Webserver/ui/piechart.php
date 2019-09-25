<?php
$connection = mysqli_connect('localhost', 'id8821146_ui', 'madhu143', 'id8821146_ui');
$result = mysqli_query($connection, "SELECT * FROM Ui");
?>

<html>
  <head>
    <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
    <script type="text/javascript">
      google.charts.load("current", {packages:["corechart"]});
      google.charts.setOnLoadCallback(drawChart);
      function drawChart() {
        var data = google.visualization.arrayToDataTable([
          ['Temperature', 'Humidity'],
        
         <?php
            
             if(mysqli_num_rows($result)> 0){
                 
                 while($row = mysqli_fetch_array($result)){
                     
                 echo "['".$row['Temperature']."','".$row['Humidity']."'],";
             }
             }
            ?>
          
        ]);

        var options = {
          title: 'Temperature & Humidity',
          is3D: true,
        };

        var chart = new google.visualization.PieChart(document.getElementById('piechart_3d'));
        chart.draw(data, options);
      }
    </script>
  </head>
  <body>
    <div id="piechart_3d" style="width: 900px; height: 500px;"></div>
  </body>
</html>