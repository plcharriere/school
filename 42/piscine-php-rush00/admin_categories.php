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

if (isset($_GET["remove"]))
{
	mysqli_query($link, "DELETE FROM categories WHERE id = " . intval($_GET["remove"]));
	die(header("Location: ./admin_categories.php"));
}

if (isset($_POST["newcateg"]) && strlen($_POST["newcateg"]) >= 1)
{
	mysqli_query($link, "INSERT INTO `categories`(`id`, `name`) VALUES (NULL, '" . htmlentities($_POST["newcateg"]) . "')");
}

?>
<!DOCTYPE html>
<html>
	<?php include("inc/head.php"); ?>
	<body>
		<?php include("inc/header.php"); ?>

		<div class="margin-auto container">
		<center><h1>Administration : catégories</h1></center>
		<hr>


		<table width="100%">
		<tr>
			<td>
				<b>Id</b>
			</td>
			<td>
				<b>Nom</b>
			</td>
			<td>
			</td>
			<td>
			</td>
		</tr>
		<?php
			$query = mysqli_query($link, "SELECT * FROM categories");
			while($data = mysqli_fetch_assoc($query))
			{

		?>
			<tr>
				<td>
					<?= $data["id"]; ?>
				</td>
				<td style="width:95%">
					<?= $data["name"]; ?>
				</td>
				<td>
					<a href="admin_categories_edit.php?category=<?= $data["id"]; ?>" class="button button-green" style="display: inline-block;">Modifier</a>
				</td>
				<td>
					<a href="?remove=<?= $data["id"]; ?>" class="button button-red" style="display: inline-block;">Supprimer</a>
				</td>
			</tr>
		<?php
			}
		?>
		</table>
		<br />
		<br />
		<center>
		<form method="POST">
			<input placeholder="Nom de la nouvelle catégorie" name="newcateg" style="width: 30%;">
			<button type="submit" class="button button-green" style="width: 25%;">Ajouter une catégorie</button>
		</form>
		</center>
		<br />
		</div>
		<?php include("inc/footer.php"); ?>
	</body>
</html>