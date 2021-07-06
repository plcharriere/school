<?php

require_once("inc/config.php");

$items = [];
$valid_items = [];
$query = mysqli_query($link, "SELECT * FROM items");
while ($data = mysqli_fetch_assoc($query))
{
	$items[] = [$data["name"], $data["description"], explode(',', $data["categories"]), $data["price"], $data["id"], $data["img_url"]];
	$valid_items[] = $data["id"];
}
mysqli_free_result($query);

if (isset($_POST["add_basket"], $_POST["add_quantity"]) && is_numeric($_POST["add_quantity"]) && $_POST["add_quantity"] >= 1 && in_array($_POST["add_basket"], $valid_items))
{
	if (isset($_SESSION["basket"][$_POST["add_basket"]]))
	{
		$_SESSION["basket"][$_POST["add_basket"]] += $_POST["add_quantity"];
	}
	else
	{
		$_SESSION["basket"][$_POST["add_basket"]] = $_POST["add_quantity"];
	}
	$success = "Article ajouté au panier !";
}

?>
<!DOCTYPE html>
<html>
	<?php include("inc/head.php"); ?>
	<body>
		<?php include("inc/header.php"); ?>
		<div class="container">
		<?php	
		if (isset($_GET["category"]))
		{
			$query1 = mysqli_query($link, "SELECT * FROM categories WHERE id = " . intval($_GET["category"]));
			$data1 = mysqli_fetch_assoc($query1);
			if ($data1 == NULL)
			{

		?>
			<center><h1>Catégorie introuvable.</h1><center>
		<?php
			}
			else
			{
		?>
			<center><h1><?= $data1["name"]; ?></h1></center>
			<hr style="width: 20%"/>
			<?php if(isset($success)) { ?>
			<center>
			<div style="width: 50%" class="alert-green">
				<?= $success; ?>
			</div>
			</center>
		<?php } ?>
			<div class="wrap">
            <div class="items_container">
		<?php
				foreach($items as $item)
				{
					if (in_array($_GET["category"], $item[2]))
					{
		?>
            <div class="item">
				<figure>
					<img style="border-radius: 5px;width:128px;height:128px;" src="<?= $item[5]; ?>">
				</figure>
				<h3><?= $item[0]; ?></h3>
				<?= $item[3]; ?>€
				<br />
				<br />
				<form method="POST">
				<input type="number" style="width: 50%" name="add_quantity" min="1" max="100" value="1">
				<center><button type="submit" name="add_basket" value="<?= $item[4]; ?>" class="button-blue">Ajouter au panier</a><center>
				</form>
			</div>
		<?php
					}
				}
			}
			mysqli_free_result($query1);
		}else{
		?>
		<div style="background: rgba(173, 216, 230, 0.2);padding:50px;border-radius:5px;">
		<h1>Bienvenue sur <?= $title; ?> !</h1>
		<hr />
		<p>Retrouvez tous vos vinyls favoris à prix cassés !</p>
		<p>Vous retrouverez parmis nos catégories, les styles de vinyls suivants :</p>
		<ul>
		<?php
		$q = mysqli_query($link, "SELECT * FROM categories");
		while ($data = mysqli_fetch_assoc($q))
		{
		?>
		<li><a href="?category=<?= $data["id"]; ?>"><?= $data["name"]; ?></a></li>
		<?php
		}
		?>
		</ul>
		<h3>Nous vous souhaitons une agréable visite sur <?= $title; ?> !</h3>

		<?php } ?>
		<div>
        </div>
		</div>
		<?php include("inc/footer.php"); ?>
	</body>
</html>