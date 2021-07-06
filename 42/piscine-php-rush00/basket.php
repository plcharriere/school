<?php

require_once("inc/config.php");

if (isset($_POST["remove"]) && isset($_SESSION["basket"][$_POST["remove"]]))
{
	$_SESSION["basket"][$_POST["remove"]]--;
	if ($_SESSION["basket"][$_POST["remove"]] <= 0)
		unset($_SESSION["basket"][$_POST["remove"]]);
}

if (isset($_POST["order"]))
{
	if (isset($_SESSION["user"]))
	{
		mysqli_query($link, "INSERT INTO `orders`(`id`, `user_login`, `items`, `time`) VALUES (NULL,'" . $_SESSION["user"] . "', '" . serialize($_SESSION["basket"]) . "', " . time() . ")");
		$_SESSION["basket"] = [];
		$success = "Merci pour votre commande !";
	}
	else
	{
		$error = "Veuillez vous connecter pour pouvoir valider votre panier.";
	}
}

?>
<!DOCTYPE html>
<html>
	<?php include("inc/head.php"); ?>
	<body>
		<?php include("inc/header.php"); ?>

		<div class="margin-auto container">
		<center><h1>Panier</h1></center>
		<hr style="width: 40%">
		<?php if(isset($error)) { ?>
			<div class="alert-red">
				<?= $error; ?>
			</div>
		<?php } ?>
		<?php if(isset($success)) { ?>
			<center>
			<div style="width: 50%" class="alert-green">
				<?= $success; ?>
			</div>
			</center>
		<?php } ?>
		<?php if (empty($_SESSION["basket"])) { ?>
		<center><h3 style="margin: 50px;">Votre panier est vide.</h3></center>
		<?php }else{?>
		<br />
		<table width="100%" class="basket" cellpadding=0 cellspacing=0 style="border-collapse: collapse;">
		<tr style="border-bottom: 1px solid #e5e5e5;">
			<td>
			</td>
			<td>
				Nom
			</td>
			<td>
				Quantité
			</td>
			<td>
				Prix à l'unité
			</td>
			<td>
				Prix total
			</td>
			<td>
			</td>
		</tr>
				<?php

				$total = 0;
				$totalquant = 0;
				foreach($_SESSION["basket"] as $item => $quantity)
				{

					$query = mysqli_query($link, "SELECT * FROM items WHERE id = " . $item);
					$data = mysqli_fetch_assoc($query);
					if ($data == NULL)
						continue;
					$total += $data["price"] * $quantity;
					$totalquant += $quantity;
				?>

			<tr>
				<td>
					<img style="width:128px;height:128px;" src="<?= $data["img_url"]; ?>">
				</td>
				<td>
					<?= $data["name"]; ?>
				</td>
				<td>
					<?= $quantity; ?>
				</td>
				<td>
					<?= $data["price"]; ?>€
				</td>
				<td>
					<?= $data["price"] * $quantity; ?>€
				</td>
				<td>
					<form method="POST">
						<button type="submit" name="remove" class="button-red" value="<?= $data["id"]; ?>">Supprimer</button>
					</form>
				</td>
			</tr>
				<?php

				}

				?>
		</table>
		<center>
			<h2><?= $totalquant; ?> article<?= ($totalquant > 1 ? "s" : "" )?></h2>
			<h2>Total : <?= $total; ?>€</h2>
			<form method="POST">
				<button type="submit" name="order" class="button-green" style="width: 30%">Commander</button>
			</form>
			<br />
		</center>
			<?php } ?>
		</div>
		<?php include("inc/footer.php"); ?>
	</body>
</html>