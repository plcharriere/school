<?php

require_once("inc/config.php");

if (!isset($_SESSION["user"]))
	die(header("Location: /"));

$isAdmin = mysqli_query($link, "SELECT id FROM users WHERE login = '" . $_SESSION["user"] . "' AND admin = 1");
if (mysqli_num_rows($isAdmin) == 0)
{
	mysqli_free_result($isAdmin);
	die(header("Location: /"));
}
mysqli_free_result($isAdmin);



if (isset($_POST["imgurl"], $_POST["name"], $_POST["categories"], $_POST["price"]))
{
	if (strlen($_POST["imgurl"]) >= 1&& strlen($_POST["name"]) >= 1&& strlen($_POST["categories"]) >= 1&& strlen($_POST["price"]) >= 1)
	{
		mysqli_query($link, "INSERT INTO `items`(`id`, `categories`, `name`, `price`, `img_url`) VALUES (NULL, '" . $_POST["categories"] . "', '" . htmlentities($_POST["name"]) . "', " . intval($_POST["price"]) . ", '" . $_POST["imgurl"] . "')");
		die(header("Location: ./admin_items.php"));
	}
	else
	{
		$error = "Remplissez tout les champs";
	}
}

?>
<!DOCTYPE html>
<html>
	<?php include("inc/head.php"); ?>
	<body>
		<?php include("inc/header.php"); ?>

		<div class="margin-auto container">
		<center><h1>Administration : ajouter un article</h1></center>
		<hr style="width:50%">
		<?php if(isset($error)) { ?>
		<center>
		<div class="alert-red" style="width: 50%;">
				<?= $error; ?>
			</div>
		</center>
		<?php } ?>
		<center>
		<form method="POST">
			URL de l'image : <input placeholder="URL de l'image de l'article" name="imgurl" style="width: 30%;" value="<?= (isset($_POST["imgurl"]) ? $_POST["imgurl"] : ""); ?>"><br />
			Nom : <input placeholder="Nom de l'article'" name="name" style="width: 30%;" value="<?= (isset($_POST["name"]) ? $_POST["name"] : ""); ?>"><br />
			Catégories : <input placeholder="Catégories" name="categories" style="width: 30%;" value="<?= (isset($_POST["categories"]) ? $_POST["categories"] : ""); ?>"><br />
			Prix : <input type="number" min="0" max="99999" placeholder="Prix à l'unité" name="price" style="width: 30%;" value="<?= (isset($_POST["price"]) ? $_POST["price"] : ""); ?>"><br />
			<button type="submit" class="button button-green" style="width: 25%;">Envoyer</button>
		</form>
		</center>
		<br />
		</div>
		<?php include("inc/footer.php"); ?>
	</body>
</html>