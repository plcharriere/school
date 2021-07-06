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
	mysqli_query($link, "DELETE FROM orders WHERE id = " . intval($_GET["remove"]));
	die(header("Location: ./admin_orders.php"));
}

?>
<!DOCTYPE html>
<html>
	<?php include("inc/head.php"); ?>
	<body>
		<?php include("inc/header.php"); ?>

		<div class="margin-auto container">
		<center><h1>Administration : commandes</h1></center>
		<hr style="width:40%">
		<br />
		<center>
		<h2>Nombre de commande(s) : <?= $totalcommandes; ?></h2>
		<h2>Chiffre d'affaire : <?= $chiffre; ?>€ <?= ($chiffre == 0 ? "😭" : "🤑"); ?>
		</center>
		<br />
		<?php
			$query = mysqli_query($link, "SELECT * FROM orders ORDER BY time DESC");
			while($data = mysqli_fetch_assoc($query))
			{
		?>
			<h3 style="display:inline-block">Panier validé par : <?= $data["user_login"]; ?> le <?= date("d/m/Y à H:i:s", $data["time"]); ?></h3>
			<a href="?remove=<?= $data["id"]; ?>" class="button button-red" style="display: inline-block;float:right;">Supprimer</a>
			<hr />
			<table width="100%" class="basket">
		<tr >
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

			$items = unserialize($data["items"]);
			
			$total = 0;
			foreach ($items as $itemId => $quantity)
			{
				$query2 = mysqli_query($link, "SELECT * FROM items WHERE id = " . $itemId);
				if (mysqli_num_rows($query2) == 0)
				{
					echo "<td>Article introuvable</td>";
					continue;
				}
				$data2 = mysqli_fetch_assoc($query2);
					
					$total += $data2["price"] * $quantity;
		?>
	<tr>
				<td>
					<img style="width:128px;height:128px;" src="<?= $data2["img_url"]; ?>">
				</td>
				<td>
					<?= $data2["name"]; ?>
				</td>
				<td>
					<?= $quantity; ?>
				</td>
				<td>
					<?= $data2["price"]; ?>€
				</td>
				<td>
					<?= $data2["price"] * $quantity; ?>€
				</td>
			</tr>
		<?php
			}

			?>
			</table>
			<br />
		<?php
			}
		?>
		

		
		<br />
		</div>
		<?php include("inc/footer.php"); ?>
	</body>
</html>