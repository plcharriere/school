<?php

if (!file_exists("../private/configuration"))
{
	die(header("Location: ./install.php"));
}

$config = unserialize(file_get_contents("../private/configuration"));

error_reporting(E_ALL);
ini_set("display_errors", "On");

session_start();

$title = $config["title"];

$link = mysqli_connect($config["mysql_host"], $config["mysql_user"], $config["mysql_passwd"], $config["mysql_db"]);

if (!$link) {
    echo "Erreur : Impossible de se connecter à MySQL." . PHP_EOL;
    echo "Errno de débogage : " . mysqli_connect_errno() . PHP_EOL;
    echo "Erreur de débogage : " . mysqli_connect_error() . PHP_EOL;
    exit;
}

if (!isset($_SESSION["basket"]))
	$_SESSION["basket"] = [];

?>