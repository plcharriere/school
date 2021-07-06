<?php

require_once("inc/config.php");

if (!isset($_SESSION["user"]))
	die(header("Location: /"));

if (isset($_POST["currpasswd"], $_POST["newpasswd"], $_POST["renewpasswd"]))
{

	$currpasswd = mysqli_query($link, "SELECT id FROM users WHERE login = '" . $_SESSION["user"] . "' AND passwd = '" . hash("sha512", $_POST["currpasswd"]) . "'");
	if (mysqli_num_rows($currpasswd) == 1)
	{
		if (strlen($_POST["newpasswd"]) >= 8 && strlen($_POST["newpasswd"]) <= 32)
		{
			if ($_POST["newpasswd"] == $_POST["renewpasswd"])
			{
				$currpasswd = mysqli_query($link, "UPDATE users SET passwd = '" . hash("sha512", $_POST["newpasswd"]) . "' WHERE login = '" . $_SESSION["user"] . "'");
				$success = "Votre mot de passe a été changé.";
			}
			else
			{
				$error = "Les nouveaux mots de passes ne correspondent pas.";
			}
		}
		else
		{
			$error = "Votre nouveau mot de passe doit contenir entre 8 et 32 caractères.";
		}
	}
	else
	{
		$error = "Mot de passe actuel incorrecte.";
	}
	mysqli_free_result($currpasswd);
}

?>
<!DOCTYPE html>
<html>
	<?php include("inc/head.php"); ?>
	<body>
		<?php include("inc/header.php"); ?>

		<div class="margin-auto box">
		<center><h1>Paramètres</h1></center>
		<hr>
		<?php if(isset($error)) { ?>
			<div class="alert-red">
				<?= $error; ?>
			</div>
		<?php } ?>
		<?php if(isset($success)) { ?>
			<div class="alert-green">
				<?= $success; ?>
			</div>
		<?php } ?>
		<h3>Modifier mon mot de passe</h3>
		<form method="POST">
			<input type="password" name="currpasswd" placeholder="Mot de passe actuel">
			<input type="password" name="newpasswd" placeholder="Nouveau mot de passe">
			<input type="password" name="renewpasswd" placeholder="Confirmer le mot de passe">
			<center><button type="submit" class="button-green">Envoyer</button></center>
		</form>
		<br />
		<hr />
		<br />
		<center>
			<a href="remove.php" class="button button-red">Supprimer mon compte</a>
		</center>
		</div>
		<?php include("inc/footer.php"); ?>
	</body>
</html>