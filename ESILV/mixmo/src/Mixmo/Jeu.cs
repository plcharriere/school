using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Net.Mime.MediaTypeNames;

namespace Mixmo
{
    class Jeu
    {
		static Random r;
		static List<Joueur> joueurs;
		static List<Lettre> lettres;
		static Lettres pioche;
		static Dictionnaire dictionnaire;

		private static bool ChargerLettres()
		{
			Console.WriteLine("Chargements des lettres à partir du fichier \"Lettres.txt\"");

			if (!(File.Exists("Lettres.txt")))
			{
				Console.WriteLine("Erreur : fichier \"Lettres.txt\" introuvable.");
				return false;
			}
			StreamReader reader = new StreamReader("Lettres.txt");
			string ligne;
			int i = 1;
			while (!string.IsNullOrEmpty(ligne = reader.ReadLine()))
			{
				string[] split = ligne.Split(',');
				int nb;
				int score;
				if (split.Length != 3 || split[0].Length != 1)
				{
					Console.WriteLine("Erreur : ligne {0} '{1}'", i, ligne, ligne);
					return false;
				}
				nb = Convert.ToInt32(split[1]);
				score = Convert.ToInt32(split[2]);
				for (int j = 0; j < nb; j++)
					pioche.list.Add(new Lettre(split[0][0], score));
				i++;
			}
			return true;
		}

		private static bool ChargerDictionnaire()
		{
			Console.WriteLine("Chargements du dictionnaire à partir du fichier \"MotsPossibles.txt\"");

			if (!(File.Exists("MotsPossibles.txt")))
			{
				Console.WriteLine("Erreur : fichier \"MotsPossibles.txt\" introuvable.");
				return false;
			}
			StreamReader reader = new StreamReader("MotsPossibles.txt");
			string ligne;
			int i = 1;
			while (!reader.EndOfStream)
			{
				ligne = reader.ReadLine();
				int taille = Convert.ToInt32(ligne);
				i++;
				ligne = reader.ReadLine();
				string[] mots = ligne.Split(' ');
				foreach (string mot in mots)
				{
					if (!(dictionnaire.AjouterMot(taille, mot)))
					{
						Console.WriteLine("Erreur : taille de {0} erronée pour le mot \"\"", taille, mot);
						return false;
					}
				}
				i++;
			}
			return true;
		}

		private static void DemanderJoueurs()
		{
			int nbJoueurs = 2;
			for (int i = 0; i < nbJoueurs; i++)
			{
				string nom = "";
				while (string.IsNullOrEmpty(nom))
				{
					Console.WriteLine("Entrez le nom du joueur {0} :", i + 1);
					nom = Console.ReadLine();
				}
				joueurs.Add(new Joueur(i + 1, nom));
			}
		}

		static void AfficherGrilles()
		{
			int i = 1;
			foreach (Joueur joueur in joueurs)
			{
				Console.Write(joueur.grille.toString());
				Console.Write("Joueur {0} ({1}) : ", i++, joueur.nom);
				foreach (Lettre lettre in joueur.lettres.list)
					Console.Write("{0} ", lettre.symbole);
				Console.WriteLine();
				Console.WriteLine();
			}
		}

		static void Jouer()
		{
			Console.Clear();
			AfficherGrilles();
			int i = -1;
			while (i < 0 || i > joueurs.Count())
			{
				Console.WriteLine("Saisissez le joueur :");
				i = Convert.ToInt32(Console.ReadLine());
			}
			Joueur joueur = joueurs.ElementAt(i - 1);
			Console.WriteLine("{0}, saisissez le mot trouvé :", joueur.nom);
			string mot = Console.ReadLine();
			if (dictionnaire.RechDichoRecursif(0, dictionnaire.dictionnaire[mot.Length].Count, mot))
				joueur.PlacerMot(mot);
			else
			{
				Console.WriteLine("Ce mot n'existe pas dans le dictionnaire.");
				Console.WriteLine("Appuyez sur Entrée pour continuer");
				Console.ReadLine();
			}
			if (joueur.lettres.list.Count == 0)
			{
				FinJeu(joueur.numero);
				return;
			}
			Jouer();
		}

		static void FinJeu(int gagnant)
		{
			int score1 = (gagnant == 1 ? 20 : 0);
			int score2 = (gagnant == 2 ? 20 : 0);

			Joueur joueur1 = joueurs.ElementAt(0);
			Joueur joueur2 = joueurs.ElementAt(1);

			foreach (string mot in joueur1.mots)
			{
				if (mot.Length >= 5)
					score1 += mot.Length;
				foreach (char lettre in mot)
				{
					foreach (Lettre lettre2 in lettres)
					{
						if (lettre2.symbole == lettre)
							score1 += lettre2.score;
						break;
					}
				}
			}

			foreach (string mot in joueur2.mots)
			{
				if (mot.Length >= 5)
					score1 += mot.Length;
				foreach (char lettre in mot)
				{
					foreach (Lettre lettre2 in lettres)
					{
						if (lettre2.symbole == lettre)
							score1 += lettre2.score;
						break;
					}
				}
			}

			Console.Clear();
			Console.WriteLine("Fin de la partie !");
			Console.WriteLine("-----------------------");
			Console.WriteLine("Scores :");
			Console.WriteLine("Joueur 1 ({0}) : {1} points", joueur1.nom, score1);
			Console.WriteLine("Joueur 2 ({0}) : {1} points", joueur2.nom, score2);
			Console.WriteLine("-----------------------");
			if (score1 == score2)
				Console.WriteLine("Égalité !");
			else if (score1 > score2)
				Console.WriteLine("Joueur {0} ({1}) remporte la partie !", joueur1.numero, joueur1.nom);
			else if (score1 < score2)
				Console.WriteLine("Joueur {0} ({1}) remporte la partie !", joueur2.numero, joueur2.nom);
			Console.WriteLine("Appuyez sur Entrée pour quitter");
			Console.ReadLine();
		}

		static void Main(string[] args)
        {
			r = new Random();
			joueurs = new List<Joueur>();
			lettres = new List<Lettre>();
			pioche = new Lettres();
			dictionnaire = new Dictionnaire();

			Console.WriteLine("Bienvenue sur Mixmo !");
			Console.WriteLine("-----------------------");

			if (ChargerLettres() && ChargerDictionnaire())
			{
				Console.WriteLine("-----------------------");

				DemanderJoueurs();

				if (joueurs.Count() > 0)
				{
					foreach (Joueur joueur in joueurs)
						joueur.Add_Lettres(6, pioche, r);

					Console.WriteLine("-----------------------");
					Console.WriteLine("Parfait ! Vous êtes prêts ?");
					Console.WriteLine("Appuyez sur Entrée pour lancer la partie.");
					Console.ReadLine();
					Jouer();
				}
			}
        }
    }
}
