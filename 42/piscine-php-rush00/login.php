<?php

require_once("inc/config.php");

if (isset($_SESSION["user"]))
	die(header("Location: /"));

if (isset($_POST["login"], $_POST["passwd"]))
{
	if (empty($_POST["login"]) || empty($_POST["passwd"]))
		$error = "Identifiants erronés.";
	else
	{
		$res = mysqli_query($link, "SELECT id FROM users WHERE login = '" . htmlentities($_POST["login"]) . "' AND passwd = '" . hash("sha512", $_POST["passwd"]) . "'");
		if (mysqli_num_rows($res) == 1)
		{
			$_SESSION["user"] = $_POST["login"];
			die(header("Location: /"));
		}
		else
		{
			$error = "Identifiants erronés.";
		}
	}
}

?>
<!DOCTYPE html>
<html>
	<?php include("inc/head.php"); ?>
	<body>
		<?php include("inc/header.php"); ?>

		<div class="margin-auto box">
		<center><h1>Connexion</h1></center>
		<hr>
		<?php if(isset($error)) { ?>
			<div class="alert-red">
				<?= $error; ?>
			</div>
		<?php } ?>
		<form method="POST">
			<input placeholder="Nom d'utilisateur" name="login">
			<br />
			<input type="password" placeholder="Mot de passe" name="passwd">
			<center>
				<button class="button-green" style="width: 40%" type="submit">Envoyer</button>
			</center>
		</form>
		</div>
		<?php include("inc/footer.php"); ?>
	</body>
</html>