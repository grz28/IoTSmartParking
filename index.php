<?php 

session_start();

if (!isset($_SESSION["login"])){
	header("Location: login.php");
	exit;
}

require 'koneksi.php';


$kartu = query("SELECT * FROM pengguna");

 ?>

<!DOCTYPE html>
<html>
<head>
	<title>Halaman Admin</title>
</head>
<body>

	<a href="logout.php">Logout</a>
	
	<h1>Daftar ID Card</h1>
	<a href="tambah.php">Tambah ID Kartu Manual</a>
	
	<table border="1" cellpadding="5" cellspacing="0">

	<tr>
		<th>No</th>
		<th>Jam Masuk</th>
		<th>Jam Keluar</th>
		<th>Id Card</th>
		<th>Nama</th>
		<th>Golongan</th>
		<th>Status</th>
		<th>Aksi</th>
	</tr>

<?php $i = 1; ?>	
<?php foreach ( $kartu as $data ) :{
}  ?>
	<tr>
		<td><?= $i; ?></td>
		<td><?= $data["datemasuk"]; ?></td>
		<td><?= $data["datekeluar"]; ?></td>
		<td><?= $data["idcard"]; ?></td>
		<td><?= $data["nama"]; ?></td>
		<td><?= $data["golongan"]; ?></td>
		<td><?= $data["ket"]; ?></td> 
		<td>
			<a href="ubah.php?no=<?= $data["no"]; ?>">Edit</a> 
			<a href="hapus.php?no=<?= $data["no"]; ?>">Hapus</a>
		</td>
	</tr>

<?php $i++;  ?>
<?php endforeach; ?>

</table>
 

</body>
</html>