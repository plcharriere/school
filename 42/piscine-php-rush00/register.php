<?php

require_once("inc/config.php");

if (isset($_SESSION["user"]))
	die(header("Location: /"));

if (isset($_POST["login"], $_POST["passwd"], $_POST["repasswd"]))
{
	if (strlen($_POST["login"]) < 3 || strlen($_POST["login"]) > 10 || !ctype_alnum($_POST["login"]))
	{
		$error = "Votre nom d'utilisateur doit comporter entre 3 et 10 caractères alphanumériques.";
	}
	else if (strlen($_POST["passwd"]) < 8 || strlen($_POST["passwd"]) > 32)
	{
		$error = "Votre mot de passe doit contenir entre 8 et 32 caractères.";
	}
	else if ($_POST["passwd"] != $_POST["repasswd"])
	{
		$error = "Les deux mots de passes ne correspondent pas.";
	}
	else
	{
		$res = mysqli_query($link, "SELECT id FROM users WHERE login = '" . htmlentities($_POST["login"]) . "'");
		if ($res != NULL && mysqli_fetch_assoc($res) == NULL)
		{
			$create = mysqli_query($link, "INSERT INTO users (id, login, passwd, register_date) VALUES (NULL, '" . htmlentities($_POST["login"]) . "', '" . hash("sha512", $_POST["passwd"]) . "', " . time() . ")");
			if ($create == true)
			{
				$_SESSION["user"] = $_POST["login"];
				die(header("Location: /"));
			}
			else
			{
				$error = "Une erreur est survenue. Merci de réessayer.";
			}
			mysqli_free_result($create);
		}
		else
		{
			$error = "Désolé, ce nom d'utilisateur est déjà prit.";
		}
		mysqli_free_result($res);
	}
}

?>
<!DOCTYPE html>
<html>
	<?php include("inc/head.php"); ?>
	<body>
		<?php include("inc/header.php"); ?>

		<div class="margin-auto box">
		<center><h1>Inscription</h1></center>
		<hr>
		<?php if(isset($error)) { ?>
			<div class="alert-red">
				<?= $error; ?>
			</div>
		<?php } ?>
		<form method="POST">
			<input placeholder="Nom d'utilisateur" name="login">
			<div class="input-info">Votre nom d'utilisateur doit comporter entre 3 et 10 caractères alphanumériques</div>
			<input type="password" placeholder="Mot de passe" name="passwd">
			<div class="input-info">Votre mot de passe doit contenir entre 8 et 32 caractères</div>
			<input type="password" placeholder="Confirmer le mot de passe" name="repasswd">
			<div class="input-info">Confirmez votre mot de passe</div>
			<center>
				<button class="button-green" style="width: 40%" type="submit">Envoyer</button>
			</center>
		</form>
		</div>
		<?php include("inc/footer.php"); ?>
	</body>
</html>