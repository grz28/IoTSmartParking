<?php 
// jika jumlah member + tamu >=8, parkir penuh
// jika jumlah member + tamu < 8, silahkan masuk

require 'koneksi.php';
ini_set('date.timezone', 'Asia/Jakarta');
$idcard = $_GET["idcard"];
$now = new DateTime();
$datenow = $now->format("Y-m-d H:i:s");

$hasil = mysqli_query($conn, "SELECT * FROM pengguna WHERE idcard = '$idcard' ");
$member = mysqli_query($conn, "SELECT golongan FROM pengguna WHERE ket = 'Masuk' AND golongan = 'Member' ");
$jummember = mysqli_num_rows($member);


$tamu = mysqli_query($conn, "SELECT golongan FROM pengguna WHERE ket = 'Masuk' AND golongan = 'Tamu' ");
$jumtamu = mysqli_num_rows($tamu);
//cara 1
//$start_date = mysqli_query($conn, "SELECT datemasuk FROM rfid WHERE idcard = '$idcard' ");
//$awal  = strtotime($start_date);
//$akhir = $datenow;
//$diff  = $akhir - $awal;

//$jam   = floor($diff / (60 * 60));
//$menit = $diff - $jam * (60 * 60);
//echo 'Waktu tinggal: ' . $jam .  ' jam, ' . floor( $menit / 60 ) . ' menit';

//cara sql


//cara3

//$start_date = new DateTime(mysqli_query($conn, "SELECT datemasuk FROM rfid WHERE idcard = '$idcard' "));
//$masuk = $start_date->format('Y-m-d H:i:s');
//echo $masuk;

echo "        ";

if($val=mysqli_fetch_array($hasil)){
	$sql = $val['golongan'];
	$status = $val['ket'];
		if($status == "Keluar"){
			echo "% Belum TapIn";
			}
		else if($sql == "Member"){ //
				$update = mysqli_query($conn, "UPDATE pengguna SET ket = 'Keluar', datekeluar = '$datenow' WHERE idcard = '$idcard' ");
				echo "% Silahkan Lewat";
				//echo " berhasil update member";
			}
		else if ($sql == "Tamu"){
			
				$update = mysqli_query($conn, "UPDATE pengguna SET ket = 'Keluar', datekeluar = '$datenow' WHERE idcard = '$idcard' ");
				// cetak tarif disini
			    //cara sql
				$waktu = mysqli_query($conn, "SELECT TIMESTAMPDIFF(MINUTE,(select datemasuk from pengguna where idcard = '$idcard'),(select datekeluar from pengguna where idcard = '$idcard'))"); //MINUTE bisa diganti ganti second, hour, dll
				while ($row = mysqli_fetch_array($waktu)) {
					//echo $row[0]; 
					$bayar = $row[0] * 1500;
					
					echo "% Silahkan Lewat ";
					echo "Tarif ", $bayar;
						
				}
			}
		}
		else  {
		echo "% ID not Found";
		}
		
	
   


?>