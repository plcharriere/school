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

if (!isset($_GET["category"]))
{
	die(header("Location: ./admin_categories.php"));
}

$query = mysqli_query($link, "SELECT * FROM categories WHERE id = " . intval($_GET["category"]));
if (mysqli_num_rows($query) == 0)
	die(header("Location: ./admin_categories.php"));
$categdata = mysqli_fetch_assoc($query);
if ($categdata == NULL)
	die(header("Location: ./admin_categories.php"));

if (isset($_POST["newname"]) && strlen($_POST["newname"]) >= 1)
{
	mysqli_query($link, "UPDATE categories SET name = '" . htmlentities($_POST["newname"]) . "' WHERE id = " . intval($_GET["category"]));
	die(header("Location: ./admin_categories.php"));
}

?>
<!DOCTYPE html>
<html>
	<?php include("inc/head.php"); ?>
	<body>
		<?php include("inc/header.php"); ?>

		<div class="margin-auto container">
		<center><h1>Administration : modifier une catégorie</h1></center>
		<hr style="width:50%">

		<center>
		<form method="POST">
			Id : <input disabled placeholder="Id de la catégorie" style="width: 100px" value="<?= $categdata["id"]; ?>">
			<br />
			Nom : <input placeholder="Nom de la catégorie" name="newname" style="width: 30%;" value="<?= $categdata["name"]; ?>">
			<button type="submit" class="button button-green" style="width: 25%;">Envoyer</button>
		</form>
		</center>
		<br />
		</div>
		<?php include("inc/footer.php"); ?>
	</body>
</html>