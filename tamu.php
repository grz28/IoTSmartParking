<?php 

require 'koneksi.php';
ini_set('date.timezone', 'Asia/Jakarta');
$data = $_GET["data"];
$now = new DateTime();
$datenow = $now->format("Y-m-d H:i:s");

$tamu = mysqli_query($conn, "SELECT * FROM tamu ORDER BY id DESC LIMIT 1");
if($test=mysqli_fetch_array($tamu)){
	$hasil1 = $test['jumlah'];
	if (($data == "Masuk") & ($hasil1<4)){
		$jumlah = $hasil1 + 1;
		echo $jumlah;
		$tambah = mysqli_query($conn, "INSERT INTO tamu VALUES('','$datenow','$jumlah','$data')");
		echo "% Masuk Portal 2";
	} 
	else if (($data == "Masuk") & ($hasil1>=4)){
		echo $hasil1;
		echo "% Parkir Penuh";
	}
	else if ($data == "Keluar"){
        $jumlah = $hasil1 - 1;
        echo $jumlah;
        $tambah = mysqli_query($conn, "INSERT INTO tamu VALUES('','$datenow','$jumlah','$data')");
		echo "% Silahkan Lewat";
	}
	elseif (($data != "Masuk") or ($data != "Keluar")) {
	echo "% input salah";
	}
}

//if ($tambah){
//	echo "Data Berhasil ditambahkan ke DB";
//} else
//{
//	echo "Gagal";
//}

?>