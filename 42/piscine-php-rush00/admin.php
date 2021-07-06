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

?>
<!DOCTYPE html>
<html>
	<?php include("inc/head.php"); ?>
	<body>
		<?php include("inc/header.php"); ?>

		<div class="margin-auto box">
		<center><h1>Administration</h1></center>
		<hr>
		<?php if(isset($error)) { ?>
			<div class="alert-red">
				<?= $error; ?>
			</div>
		<?php } ?>
		<center>
			<a href="admin_orders.php" class="button button-blue">Gestion des commandes</a>
			<a href="admin_categories.php" class="button button-blue">Gestion des catégories</a>
			<a href="admin_items.php" class="button button-blue">Gestion des articles</a>
			<a href="admin_users.php" class="button button-blue">Gestion des utilisateurs</a>
		</center>

		</div>
		<?php include("inc/footer.php"); ?>
	</body>
</html>