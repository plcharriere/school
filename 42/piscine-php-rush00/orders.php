<?php

require_once("inc/config.php");

if (!isset($_SESSION["user"]))
	die(header("Location: /"));

$totalcommandes = 0;

$q = mysqli_query($link, "SELECT * FROM orders WHERE user_login = '" . $_SESSION["user"] . "'");
while ($data = mysqli_fetch_assoc($q))
{
	$totalcommandes++;
}
mysqli_free_result($q);

?>
<!DOCTYPE html>
<html>
	<?php include("inc/head.php"); ?>
	<body>
		<?php include("inc/header.php"); ?>

		<div class="margin-auto container">
		<center><h1>Mes commandes</h1></center>
		<hr style="width:40%">
		<br />
		<center>
		<h2>Nombre total de commande(s) : <?= $totalcommandes; ?></h2>
		</center>
		<br />
		<?php
			$query = mysqli_query($link, "SELECT * FROM orders WHERE user_login = '" . $_SESSION["user"] . "' ORDER BY time DESC");
			while($data = mysqli_fetch_assoc($query))
			{
		?>
			<h3>Panier validé le <?= date("d/m/Y à H:i:s", $data["time"]); ?></h3>
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