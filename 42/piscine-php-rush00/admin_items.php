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
	mysqli_query($link, "DELETE FROM items WHERE id = " . intval($_GET["remove"]));
	die(header("Location: ./admin_items.php"));
}

?>
<!DOCTYPE html>
<html>
	<?php include("inc/head.php"); ?>
	<body>
		<?php include("inc/header.php"); ?>

		<div class="margin-auto container">
		<center><h1>Administration : articles</h1></center>
		<hr>


		<table width="100%">
		<tr>
			<td>
				<b>Id</b>
			</td>
			<td>
				<b>Image</b>
			</td>
			<td>
				<b>Nom</b>
			</td>
			<td>
				<b>Catégorie(s)</b>
			</td>
			<td>
				Prix
			</td>
			<td>
			</td>
			<td>
			</td>
		</tr>
		<?php
			$query = mysqli_query($link, "SELECT * FROM items");
			while($data = mysqli_fetch_assoc($query))
			{

		?>
			<tr>
				<td>
					<?= $data["id"]; ?>
				</td>
				<td>
					<img style="width:128px;height:128px;" src="<?= $data["img_url"]; ?>" />
				</td>
				<td style="width:55%">
					<?= $data["name"]; ?>
				</td>
				<td>
					<?= $data["categories"]; ?>
				</td>
				<td>
					<?= $data["price"]; ?>
				</td>
				<td>
					<a href="admin_items_edit.php?itemid=<?= $data["id"]; ?>" class="button button-green" style="display: inline-block;">Modifier</a>
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
			<a type="submit" href="admin_items_add.php" class="button button-green" style="width: 25%;">Ajouter un article</a>
		</center>
		<br />
		</div>
		<?php include("inc/footer.php"); ?>
	</body>
</html>