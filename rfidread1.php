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
$ada = mysqli_query($conn, "SELECT idcard FROM pengguna");
$jummember = mysqli_num_rows($member);


$tamu = mysqli_query($conn, "SELECT golongan FROM pengguna WHERE ket = 'Masuk' AND golongan = 'Tamu' ");
$jumtamu = mysqli_num_rows($tamu);

   if(($jummember + $jumtamu)>=8){ //
	echo "% Parkir Penuh";
		}
		
   else if (($jummember + $jumtamu)<8){ //
	 if($val=mysqli_fetch_array($hasil)){
		$sql = $val['golongan'];
		$status = $val['ket'];
			if($status == "Masuk"){
			echo "% Belum  Tap Out";
			}
			else if($sql == "Member"){ //
				$update = mysqli_query($conn, "UPDATE pengguna SET ket = 'Masuk', datemasuk = '$datenow' WHERE idcard = '$idcard' ");
				echo "% Silahkan Masuk";
				echo " berhasil update member";
			}
			else if ($sql == "Tamu"){
				$update = mysqli_query($conn, "UPDATE pengguna SET ket = 'Masuk', datemasuk = '$datenow' WHERE idcard = '$idcard' ");
				echo "% Silahkan Masuk";
				echo " berhasil update tamu";
			}
			
		}
	else {
			echo "% ID not  Found";
			}	
		}
   
else{
	 echo "error";
	}

?>