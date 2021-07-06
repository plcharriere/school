<table class="nav">
	<tr>
		<td>
			<a href="/"><b><?= $title; ?></b></a>
		</td>
		<?php
			$res = mysqli_query($link, "SELECT * FROM categories");
			$total = mysqli_num_rows($res);
			$i = 1;
			while ($data = mysqli_fetch_assoc($res))
			{
		?>
		<td <?php if($i == $total) { echo ''; } ?>><a href="/?category=<?= $data["id"]; ?>"><?= $data["name"]; ?></a></td>
		<?php 
				$i++;
		}
		mysqli_free_result($res)
		 ?>
		<td style="width:30%">
		</td>
		<?php
			if (isset($_SESSION["user"]))
			{
		?>
		<td><?= $_SESSION["user"]; ?></td>
		<?php
			$isadmin = mysqli_query($link, "SELECT id FROM users WHERE login = '" . $_SESSION["user"] . "' AND admin = 1");
			if (mysqli_num_rows($isadmin) == 1) {
		?>
		<td>
			<a href="admin.php">Administration</a>
		</td>
		<?php
			}
			mysqli_free_result($isadmin);
		?>
		<td>
			<a href="orders.php">Mes commandes</a>
		</td>
		<td>
			<a href="settings.php">Paramètres</a>
		</td>
		<td>
			<a href="logout.php">Déconnexion</a>
		</td>
		<?php
			} else {
		?>
		<td>
			<a href="login.php">Connexion</a>
		</td>
		<td>
			<a href="register.php">Inscription</a>
		</td>
		<?php } ?>
		<td>
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
			}
			?>
			<a href="basket.php">Panier (<?= $totalquant; ?> article<?= ($totalquant > 1 ? "s" : "" )?>, <?= $total; ?>€)</a>
		</td>
	</tr>
</table>
<br />