<?php

session_start();

$creds = [
	"pcharrie" => "a94a8fe5ccb19ba61c4c0873d391e987982fbbd3"
];

if (isset($_GET["logout"]))
{
	session_destroy();
	header("Location: /");
	die();
}

if (isset($_POST["login"], $_POST["password"]))
{
	if (isset($creds[$_POST["login"]]) && $creds[$_POST["login"]] == sha1($_POST["password"]))
		$_SESSION["logged"] = $_POST["login"];
	else
		$error = "Identifiants erronés.";
}

?>
<html>
	<head>
		<title>Login</title>
		<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
		<script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
		<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js" integrity="sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1" crossorigin="anonymous"></script>
		<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>
	</head>
	<body class="bg-light row h-100">
	<?php if(!isset($_SESSION["logged"])) { ?>
		<form method="POST" class="box bg-white rounded-lg shadow-sm w-25 m-auto p-4" style="margin-top:100px">
			<h2 class="text-center">Connexion</h2>
			<hr>
			<?php if(isset($error)) { ?>
			<div class="alert alert-danger" role="alert">
				<strong>Erreur :</strong> <?= $error; ?>
				<button type="button" class="close" data-dismiss="alert" aria-label="Close">
					<span aria-hidden="true">&times;</span>
				</button>
			</div>
			<?php } ?>
			<input class="form-control mb-2" type="text" name="login" placeholder="Nom d'utilisateur" />
			<input class="form-control mb-3" type="password" name="password" placeholder="Mot de passe" />
			<button class="btn btn-success w-100" type="submit">Envoyer</button>
		</form>
	<?php }else{ ?>
		<div class="box bg-white rounded-lg shadow-sm w-50 m-auto mt-5 p-4">
			<h2>Bienvenue, <strong><?= $_SESSION["logged"]; ?></strong> !</h2>
			<hr />
			<a class="text-danger" href="?logout">Me déconnecter</a>
		</div>
	<?php } ?>
	</body>
</html>
