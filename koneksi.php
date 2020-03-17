<?php 


$servername = "localhost";
$username = "root";
$password = "";
$database = "rfid";

$conn = mysqli_connect($servername, $username, $password, $database);

function query($query){
	global $conn;
	$hasil = mysqli_query($conn, $query);
	$rows = [];
	while( $row = mysqli_fetch_assoc($hasil)){
		$rows[] = $row;
	}
	return $rows;
	
}


function hapus($no){
	global $conn;
	mysqli_query($conn, "DELETE FROM pengguna WHERE no = $no");

return mysqli_affected_rows($conn);
}

function tambah($data){ //tambsh golngan here
	global $conn;
	$idcard = htmlspecialchars($data["idcard"]);
	$nama  = htmlspecialchars($data["nama"]);
	$golongan  = htmlspecialchars($data["golongan"]);
	$now = new DateTime();
	$datenow = $now->format("Y-m-d H:i:s");
		$query = "INSERT INTO pengguna VALUES('','', '$idcard', '$nama', '$golongan', '', '')";

	mysqli_query($conn, $query); 

return mysqli_affected_rows($conn);
}

function ubah($data){
	global $conn;

	$no = $data["no"];
	$idcard = htmlspecialchars($data["idcard"]);
	$nama  = htmlspecialchars($data["nama"]);
	$golongan  = htmlspecialchars($data["golongan"]);
	$ket  = htmlspecialchars($data["ket"]);

		$query = "UPDATE pengguna SET  idcard = '$idcard', nama = '$nama', golongan = '$golongan', ket = '$ket' WHERE no = $no ";

	mysqli_query($conn, $query); 

return mysqli_affected_rows($conn);
}

function registrasi($data){
	global $conn;

	$username = strtolower(stripslashes( $data["username"]));
	$password = mysqli_real_escape_string($conn, $data["password"]);
	$password2 = mysqli_real_escape_string($conn, $data["password2"]);

 	$result = mysqli_query ($conn, "SELECT username FROM user WHERE username = '$username' ");
 	
 	if (mysqli_fetch_assoc ($result) ){
 		echo "
 		<script>
 			alert('Username sudah Terdaftar');
 		</script>
 		";
 		return false;
 	}

	if ( $password !== $password2){
		echo "
		<script>
		alert('Konfirmasi Password Tidak Sesuai')
		</script>
		";

		return false;
	} 

	$password = password_hash($password, PASSWORD_DEFAULT);
	mysqli_query($conn, "INSERT INTO user VALUES('', '$username', '$password')");

	return mysqli_affected_rows($conn);
}

function readrfid($query){
	global $conn;
	$hasil = mysqli_query($conn, $query);
	$rows = [];
	while( $row = mysqli_fetch_assoc($hasil)){
		$rows[] = $row;
	}
	return $rows;
}

?>
