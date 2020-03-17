<?php 

require 'koneksi.php';
ini_set('date.timezone', 'Asia/Jakarta');
$cek = $_GET["cek"];
$now = new DateTime();
$datenow = $now->format("Y-m-d H:i:s");
//$hasil = mysqli_query($conn, "INSERT INTO slot VALUES('','$data','$datenow')");
//kasih tanggal juga kalo bisa
//$hasil = mysqli_query($conn, "SELECT * FROM pengguna WHERE idcard = '$idcard' ");
$member = mysqli_query($conn, "SELECT golongan FROM pengguna WHERE ket = 'Masuk' AND golongan = 'Member' ");
$jummember = mysqli_num_rows($member);


$tamu = mysqli_query($conn, "SELECT golongan FROM pengguna WHERE ket = 'Masuk' AND golongan = 'Tamu' ");
$jumtamu = mysqli_num_rows($tamu);
if ($cek = "cek"){
  if(($jummember + $jumtamu)>=8){ //
	echo "% Parkir Penuh";
   }
  else
{
	echo "% Tap Kartu Anda";
}
}
?>