<?php

require_once("inc/config.php");

if (!isset($_SESSION["user"]))
	die(header("Location: /"));

if (isset($_POST["remove"]))
{
	mysqli_query($link, "DELETE FROM users WHERE login = '" . $_SESSION["user"] . "'");
	mysqli_query($link, "DELETE FROM orders WHERE user_login = '" . $_SESSION["user"] . "'");
	unset($_SESSION["user"]);
	die(header("Location: /"));
}

?>
<!DOCTYPE html>
<html>
	<?php include("inc/head.php"); ?>
	<body>
		<?php include("inc/header.php"); ?>

		<div class="margin-auto box" style="width: 50%;">
		<center><h1>Supprimer mon compte</h1></center>
		<hr>
		<center>
		<h3>Êtes-vous sûr de vouloir supprimer votre compte ?<br />Vous ne pourrez plus revenir en arrière et vos commandes en cours seront annulées.</h3>
		<form method="POST">
			<center><a href="settings.php" class="button button-green" style="display: inline-block;width: 25%;display: inline-block">Annuler</a><button type="submit" name="remove" class="button-red" style="width: 25%;display: inline-block">Supprimer</button></center>
		</form>
		</center>
		</div>
		<?php include("inc/footer.php"); ?>
	</body>
</html>