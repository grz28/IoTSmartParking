<?php

require 'koneksi.php';
ini_set('date.timezone', 'Asia/Jakarta');
$now = new DateTime();

$idcard = $_GET['idcard'];
$datenow = $now->format("Y-m-d H:i:s");
$hasil = mysqli_query($conn, "SELECT * FROM rfid WHERE idcard = '$idcard' ");
$row = mysqli_fetch_array($hasil);

if (mysqli_num_rows($hasil) === 1 ){
	echo "ID CARD :", $row["idcard"];
/*edit atribut keluar masuk disini*/
	$sql = "UPDATE rfid SET ket = 'Keluar', datekeluar = '$datenow' WHERE idcard = '$idcard' ";
	$result = mysqli_query($conn, $sql);
	if (!$result) {
		die('Invalid query: ');
	}	
}
	mysqli_close($conn);
?>