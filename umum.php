<?php 

session_start();
require 'koneksi.php';
$kartu1 = query("SELECT * FROM pengguna WHERE ket = 'Masuk' ORDER BY datemasuk DESC");
$slot = query("SELECT *FROM slot ORDER BY id DESC LIMIT 1");
ini_set('date.timezone', 'Asia/Jakarta');
$now = new DateTime();
$datenow = $now->format("Y-m-d H:i:s");
 ?>

<!DOCTYPE html>
<html>
<head>
	<title>Smart Parking Main Page</title>
</head>
<body>

	<a href="login.php">Login</a>
	
	<h1>Informasi Slot Parkir</h1>
	
	<h3> /-----/-----/ Slot Parkir Digunakan :  /-----/-----/</h3>	
	<table border="1" cellpadding="5" cellspacing="0">

	<tr>
		
		<th>Golongan</th>
		<th>Jam Masuk :</th>
		
	</tr>

<?php $i = 1; ?>	
<?php foreach ( $kartu1 as $data ) :{
}  ?>
	<tr>
		
		<td><?= $data["golongan"]; ?></td>
		<td><?= $data["datemasuk"]; ?></td>
		
	</tr>


<?php endforeach; ?>

</table>

 <br> Jumlah Maksimal Slot Parkir : 8 </br>
 <br> Jumlah parkir yang tersedia :  
 
 <?php
 
$pengguna = mysqli_query($conn, "SELECT golongan FROM pengguna WHERE ket = 'Masuk' ");
$jumpengguna = mysqli_num_rows($pengguna);
$tersedia = 8 - $jumpengguna;
echo ($tersedia); 
?>
</br>

<br></br>
<h3> /-----/-----/ Informasi Slot Parkir :  /-----/-----/</h3>	
<br> Tanggal dan Jam Saat Ini:  
 <?php
echo $datenow; 
?>
</br>
<br> Informasi Lokasi Parkir Terbaru : </br>
<table border="1" cellpadding="5" cellspacing="0">

	<tr>
		
		<th>Waktu :</th>
		<th>Informasi Slot :</th>
		
	</tr>

<?php $i = 1; ?>	
<?php foreach ( $slot as $data ) :{
}  ?>
	<tr>
		
		<td><?= $data["date"]; ?></td>
		<td><?= $data["lokasi"]; ?></td>
		
	</tr>


<?php endforeach; ?>

</table>

</body>
</html>