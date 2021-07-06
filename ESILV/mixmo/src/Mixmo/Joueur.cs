using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;

namespace Mixmo
{
    class Joueur
    {
		public int numero;
		public string nom;
		public int score;
		public Lettres lettres;
		public MotsCroises grille;
		public List<string> mots;

		public bool Add_Lettres(int nb, Lettres pioche, Random r)
		{
			int i;
			for (i = 0; i < nb; i++)
			{
				if (pioche.list.Count == 0)
					break;
				int index = r.Next(pioche.list.Count);
				lettres.list.Add(pioche.list[index]);
				pioche.list.RemoveAt(index);
			}
			if (i > 0)
				return true;
			return false;
		}

		public void Add(string mot)
		{
			mots.Add(mot);
		}

		public void OteLettre(string mot)
		{
			foreach (char caractere in mot)
			{
				foreach (Lettre lettre in lettres.list)
				{
					if (lettre.symbole == caractere)
					{
						lettres.list.Remove(lettre);
						break;
					}
				}
			}
		}

		public bool PlacerMot(string mot)
		{
			int x = 0, y = 0, h = 0;
			string ligne = "";
			string[] split = "".Split(',');
			while (split.Length != 3)
			{
				Console.WriteLine("Saisissez la position x,y,h :");
				ligne = Console.ReadLine();
				split = ligne.Split(',');
				x = Convert.ToInt32(split[0]);
				y = Convert.ToInt32(split[1]);
				h = Convert.ToInt32(split[2]);
			}
			if (!(PeutPlacerMot(mot, x, y, h)))
			{
				Console.WriteLine("Vous ne pouvez pas placer le mot \"{0}\" en {1},{2},{3}", mot, x, y, h);
				Console.WriteLine("Appuyez sur Entrée pour continuer");
				Console.ReadLine();
				return false;
			}
			return true;
		}

		public bool PeutPlacerMot(string mot, int x, int y, int h)
		{
			if (x < 1 || y < 1 || h > 1 || h < 0)
				return false;
			if ((h > 0 && mot.Length > 10 - y + 1) || (h == 0 && mot.Length > 10 - x + 1))
				return false;
			if (grille.GrilleVide())
			{
				if (!PossedeLettres(mot))
					return false;
				Add(mot);
				OteLettre(mot);
				grille.PlacerMot(mot, x - 1, y - 1, h);
				return true;
			}
			x -= 1;
			y -= 1;
			int x2 = x;
			int y2 = y;
			List<char> characteres = new List<char>();
			foreach (char lettre in mot)
			{
				if (grille.grille[y2][x2] != ' ' && grille.grille[y2][x2] != lettre)
					return false;
				if (grille.grille[y2][x2] != ' ')
					characteres.Add(grille.grille[y2][x2]);
				if (h > 0)
					y2++;
				else
					x2++;
			}
			if (characteres.Count == 0)
				return false;
			string mot2 = string.Copy(mot);
			foreach (char charactere in characteres)
				mot = mot.Replace(charactere.ToString(), string.Empty);
			if (!PossedeLettres(mot))
				return false;
			Add(mot2);
			OteLettre(mot);
			grille.PlacerMot(mot2, x, y, h);
			return true;
		}

		public bool PossedeLettres(string mot)
		{
			List<Lettre> pioche = new List<Lettre>(lettres.list);
			foreach (char charactere in mot)
			{
				bool trouve = false;
				foreach (Lettre lettre in pioche)
				{
					if (lettre.symbole == charactere)
					{
						trouve = true;
						pioche.Remove(lettre);
						break;
					}
				}
				if (!trouve)
				{
					Console.WriteLine("Vous n'avez pas les lettres pour placer ce mot.");
					return false;
				}
			}
			return true;
		}

		public string toString()
		{
			return nom;
		}

		public Joueur(int num, string nomJoueur)
		{
			numero = num;
			nom = nomJoueur;
			lettres = new Lettres();
			grille = new MotsCroises();
			score = 0;
			mots = new List<string>();
		}
	}
}
