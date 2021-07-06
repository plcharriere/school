<?php

if (file_exists("../private/configuration"))
{
	die(header("Location: /"));
}

if (isset($_POST["sent"]))
{
	if (isset($_POST["title"], $_POST["mysql_host"], $_POST["mysql_user"], $_POST["mysql_passwd"], $_POST["mysql_db"]))
	{
		if (empty($_POST["title"]))
		{
			$error = "Entrez un nom de site.";
		}
		else
		{

			$link = mysqli_connect($_POST["mysql_host"], $_POST["mysql_user"], $_POST["mysql_passwd"], $_POST["mysql_db"]);
			if ($link == null)
			{
				$error = "Erreur lors de la connection au serveur MySQL : " . mysqli_connect_error();
			}
			else
			{
				$data = [];
				$data["title"] = $_POST["title"];
				$data["mysql_host"] = $_POST["mysql_host"];
				$data["mysql_user"] = $_POST["mysql_user"];
				$data["mysql_passwd"] = $_POST["mysql_passwd"];
				$data["mysql_db"] = $_POST["mysql_db"];
				if (!file_exists("../private"))
					mkdir("../private");
				if (file_put_contents("../private/configuration", serialize($data)) != false)
				{
					mysqli_query($link, "CREATE DATABASE IF NOT EXISTS " . htmlentities($_POST["mysql_db"]));

					$sql = "-- phpMyAdmin SQL Dump
					-- version 4.8.5
					-- https://www.phpmyadmin.net/
					--
					-- Host: localhost:3306
					-- Generation Time: May 26, 2019 at 02:32 PM
					-- Server version: 5.6.43
					-- PHP Version: 5.6.40
					
					SET SQL_MODE = \"NO_AUTO_VALUE_ON_ZERO\";
					SET AUTOCOMMIT = 0;
					START TRANSACTION;
					SET time_zone = \"+00:00\";
					
					--
					-- Database: `rush`
					--
					
					-- --------------------------------------------------------
					
					--
					-- Table structure for table `categories`
					--
					
					CREATE TABLE `categories` (
					  `id` int(11) NOT NULL,
					  `name` text NOT NULL
					) ENGINE=InnoDB DEFAULT CHARSET=utf8;
					
					--
					-- Dumping data for table `categories`
					--
					
					INSERT INTO `categories` (`id`, `name`) VALUES
					(1, 'UK Bass'),
					(2, 'Rap'),
					(3, 'Rock');
					
					-- --------------------------------------------------------
					
					--
					-- Table structure for table `items`
					--
					
					CREATE TABLE `items` (
					  `id` int(11) NOT NULL,
					  `categories` text NOT NULL,
					  `name` varchar(255) NOT NULL,
					  `description` text NOT NULL,
					  `price` int(11) NOT NULL,
					  `img_url` varchar(255) NOT NULL
					) ENGINE=InnoDB DEFAULT CHARSET=utf8;
					
					--
					-- Dumping data for table `items`
					--
					
					INSERT INTO `items` (`id`, `categories`, `name`, `description`, `price`, `img_url`) VALUES
					(7, '1', 'Congi', '', 15, 'https://www.redeyerecords.co.uk/imagery/28942-2.jpg'),
					(8, '1', 'Cluekid', '', 15, 'https://www.redeyerecords.co.uk/imagery/28952-1.jpg'),
					(9, '1', 'Samba - ENV007', '', 10, 'https://www.redeyerecords.co.uk/imagery/27693-1.jpg'),
					(10, '1', 'Samba X Chokez', '', 8, 'https://www.redeyerecords.co.uk/imagery/28431-1.jpg'),
					(11, '1', 'Kahn', '', 8, 'https://www.redeyerecords.co.uk/imagery/26833-1.jpg'),
					(12, '1', 'COMMODO, GANTZ, KAHN', '', 10, 'https://www.redeyerecords.co.uk/imagery/27103-1.jpg'),
					(13, '3', 'The Doors', '', 25, 'https://res.cloudinary.com/reverb-lp/image/upload/c_fill,f_auto,g_center,h_450,w_450/v1/v2/images/b2f37084-9094-4663-9f4c-c8e69d793db6'),
					(14, '3', 'Led Zeppelin', '', 15, 'https://res.cloudinary.com/reverb-lp/image/upload/c_limit,f_auto,h_1200,w_1200/v1/v2/images/50db868b-8315-496c-a195-b41d53001548'),
					(15, '3', 'Metallica', '', 26, 'https://dvfnvgxhycwzf.cloudfront.net/media/SharedImage/imageFull/.fXTAYy4V/SharedImage-75200.jpg?t=ea0c95da91ab2109ddec'),
					(16, '3', 'Black Sabbath', '', 65, 'https://dvfnvgxhycwzf.cloudfront.net/media/SharedImage/image575/.fHpeS8LW/SharedImage-81122.jpg?t=4d5417c621e62063d74e'),
					(17, '3', 'Nirvana', '', 18, 'https://dvfnvgxhycwzf.cloudfront.net/media/SharedImage/image575/.fcuTrE5U/SharedImage-53183.jpg?t=301cc6d818dba94eb139'),
					(18, '3', 'Ironside', '', 25, 'https://dvfnvgxhycwzf.cloudfront.net/media/SharedImage/image575/.fE4wUcjW/SharedImage-87525.jpg?t=7463251e0ce147de5157'),
					(19, '2', 'Yung Lean', '', 15, 'https://img.discogs.com/GtqNcEGiTzlinATSPj_69Jp6_kY=/fit-in/600x600/filters:strip_icc():format(jpeg):mode_rgb():quality(90)/discogs-images/R-11491309-1517263536-7589.jpeg.jpg'),
					(20, '2', 'Mac Miller', '', 25, 'https://s7d5.scene7.com/is/image/UrbanOutfitters/50861095_001_b?\$xlarge$&hei=900&qlt=80&fit=constrain'),
					(21, '2', 'SLOWTHAI', '', 22, 'https://dvfnvgxhycwzf.cloudfront.net/media/SharedImage/image600/.fiaJknnW/SharedImage-89358.jpg?t=767a7ff32560696a5a31'),
					(22, '2', 'Snoop dogg', '', 17, 'https://dvfnvgxhycwzf.cloudfront.net/media/SharedImage/image600/.f_M-8WqW/SharedImage-90503.jpg?t=e060f7647f519b9070ce'),
					(23, '2', '\$uicideboy$', '', 15, 'https://cdn.shopify.com/s/files/1/0016/2840/5843/products/BLACK-RED-VINYL-SPLIT_b2e839ad-0b4c-4a06-9ddd-e9c6f9a6e5d4_1024x1024.png?v=1533131920'),
					(24, '2', 'Ghostemane', '', 16, 'https://merchbar.imgix.net/product/vinylized/upc/21/811408032100.jpg?w=640&h=640&quality=40&auto=compress%252Cformat&dpr=2');
					
					-- --------------------------------------------------------
					
					--
					-- Table structure for table `orders`
					--
					
					CREATE TABLE `orders` (
					  `id` int(11) NOT NULL,
					  `user_login` varchar(255) NOT NULL,
					  `items` text NOT NULL,
					  `time` int(11) NOT NULL
					) ENGINE=InnoDB DEFAULT CHARSET=utf8;
					
					-- --------------------------------------------------------
					
					--
					-- Table structure for table `users`
					--
					
					CREATE TABLE `users` (
					  `id` int(11) NOT NULL,
					  `login` varchar(255) NOT NULL,
					  `passwd` text NOT NULL,
					  `admin` int(11) NOT NULL DEFAULT '0',
					  `register_date` int(11) NOT NULL
					) ENGINE=InnoDB DEFAULT CHARSET=utf8;
					
					--
					-- Dumping data for table `users`
					--
					
					INSERT INTO `users` (`id`, `login`, `passwd`, `admin`, `register_date`) VALUES
					(1, 'root', 'fa585d89c851dd338a70dcf535aa2a92fee7836dd6aff1226583e88e0996293f16bc009c652826e0fc5c706695a03cddce372f139eff4d13959da6f1f5d3eabe', 1, " . time() . ");
					
					--
					-- Indexes for dumped tables
					--
					
					--
					-- Indexes for table `categories`
					--
					ALTER TABLE `categories`
					  ADD PRIMARY KEY (`id`);
					
					--
					-- Indexes for table `items`
					--
					ALTER TABLE `items`
					  ADD PRIMARY KEY (`id`);
					
					--
					-- Indexes for table `orders`
					--
					ALTER TABLE `orders`
					  ADD UNIQUE KEY `id` (`id`);
					
					--
					-- Indexes for table `users`
					--
					ALTER TABLE `users`
					  ADD PRIMARY KEY (`id`);
					
					--
					-- AUTO_INCREMENT for dumped tables
					--
					
					--
					-- AUTO_INCREMENT for table `categories`
					--
					ALTER TABLE `categories`
					  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=15;
					
					--
					-- AUTO_INCREMENT for table `items`
					--
					ALTER TABLE `items`
					  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=25;
					
					--
					-- AUTO_INCREMENT for table `orders`
					--
					ALTER TABLE `orders`
					  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;
					
					--
					-- AUTO_INCREMENT for table `users`
					--
					ALTER TABLE `users`
					  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;
					COMMIT;
					";

					$res = mysqli_multi_query($link, $sql);
					if ($res != false)
					{
						while (mysqli_next_result($link));
						die(header("Location: /install.php"));
					}
					else
					{
						$error = "Une erreur est survenue lors de la création des tables.";
						unlink("../private/configuration");
					}
				}
				else
				{
					$error = "Une erreur est survenue lors de la création du fichier de configuration.";
				}
			}
		}
	}
}

?>
<!DOCTYPE html>
<html>
	<head>
		<title>Installation</title>
		<link href="style.css" rel="stylesheet">
	</head>
	<body>
	<div class="container" style="width: 50%; margin: auto;">
		<center>
			<h1>Installation</h1>
			<hr />
			<?php if(isset($error)) { ?>
			<div class="alert-red">
				<?= $error; ?>
			</div>
			<?php } ?>
			<form method="POST">
				<input name="title" placeholder="Titre du site" value="<?= (isset($_POST["title"]) ? $_POST["title"] : "")?>">
				<input name="mysql_host" placeholder="Adresse du serveur MySQL" value="<?= (isset($_POST["mysql_host"]) ? $_POST["mysql_host"] : "")?>">
				<input name="mysql_user" placeholder="Nom d'utilisateur MySQL" value="<?= (isset($_POST["mysql_user"]) ? $_POST["mysql_user"] : "")?>">
				<input name="mysql_passwd" type="password" placeholder="Mot de passe MySQL" value="<?= (isset($_POST["mysql_passwd"]) ? $_POST["mysql_passwd"] : "")?>">
				<input name="mysql_db" placeholder="Nom de la base de donnée MySQL" value="<?= (isset($_POST["mysql_db"]) ? $_POST["mysql_db"] : "")?>">
				<button type="submit" class="button-green" style="width: 50%" name="sent">Envoyer</button>
			</form>
		</center>
	</div>
	<?php include("inc/footer.php"); ?>
	</body>
</html>