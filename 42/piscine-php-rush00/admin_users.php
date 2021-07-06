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

$chiffre = 0;
$totalcommandes = 0;

$q = mysqli_query($link, "SELECT * FROM orders");
while ($data = mysqli_fetch_assoc($q))
{
	$totalcommandes++;
	$a = unserialize($data["items"]);
	foreach($a as $itemid => $quant)
	{
		$query2 = mysqli_query($link, "SELECT * FROM items WHERE id = " . $itemid);
		if ($data2 = mysqli_fetch_assoc($query2))
		{
			$chiffre += $data2["price"] * $quant;
		}
		mysqli_free_result($query2);
	}
}
mysqli_free_result($q);

if (isset($_GET["remove"]))
{
	if ($_GET["remove"] == 1)
	{
		$error = "Vous ne pouvez pas supprimer l'utilisateur root.";
	}
	else
	{
		mysqli_query($link, "DELETE FROM users WHERE id = " . intval($_GET["remove"]));
		die(header("Location: ./admin_users.php"));
	}
}

?>
<!DOCTYPE html>
<html>
	<?php include("inc/head.php"); ?>
	<body>
		<?php include("inc/header.php"); ?>

		<div class="margin-auto container">
		<center><h1>Administration : utilisateurs</h1></center>
		<hr style="width:40%">
		<?php if(isset($error)) { ?>
			<div class="alert-red">
				<?= $error; ?>
			</div>
		<?php } ?>
		<br />
		<table width="100%" class="basket">
		<tr >
			<td>
				Nom d'utilisateur
			</td>
			<td>
				Date d'inscription
			</td>
			<td>
				Commandes passées
			</td>
			<td>
			</td>
		</tr>
		<?php
			$query = mysqli_query($link, "SELECT * FROM users ORDER BY id DESC");
			while($data = mysqli_fetch_assoc($query))
			{
		?>
		<tr >
			<td>
				<?= $data["login"]; ?>
			</td>
			<td>
				<?= date("d/m/Y H:i:s", $data["register_date"]); ?>
			</td>
			<td>
				<?php
					$q = mysqli_query($link, "SELECT id FROM orders WHERE user_login = '" . $data["login"] . "'");
					echo mysqli_num_rows($q);
					mysqli_free_result($q);

				?>

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
		</div>
		<?php include("inc/footer.php"); ?>
	</body>
</html>