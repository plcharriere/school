using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mixmo
{

    class Dictionnaire
    {
		public Dictionary<int, List<string>> dictionnaire;

		// Ajoute un mot en fonction de sa taille dans le dictionnaire
		public bool AjouterMot(int taille, string mot)
		{
			if (taille != mot.Length)
				return false;
			if (!dictionnaire.ContainsKey(taille))
				dictionnaire[taille] = new List<string>();
			dictionnaire[taille].Add(mot);
			return true;
		}

		// Retourne un dictionnaire au même format que MotsPossibles.txt
		public string toString()
		{
			string s = "";
			foreach (KeyValuePair<int, List<string>> elem in dictionnaire)
			{
				s += elem.Key;
				s += "\n";
				foreach (string mot in elem.Value)
					s += mot + " ";
				s = s.Remove(s.Length - 1);
				s += "\n";
			}
			return s;
		}

		public bool RechDichoRecursif(int debut, int fin, string mot)
		{
			int milieu = (debut + fin) / 2;
			if (debut > fin) return false;
			else
				if (mot == dictionnaire[mot.Length].ElementAt(milieu))
					return true;
			else
				if (string.Compare(mot, dictionnaire[mot.Length].ElementAt(milieu)) > 0)
					return RechDichoRecursif(milieu + 1, fin, mot);
			else
				return RechDichoRecursif(debut, milieu - 1, mot);
		}

		public Dictionnaire()
		{
			dictionnaire = new Dictionary<int, List<string>>();
		}
    }
}
