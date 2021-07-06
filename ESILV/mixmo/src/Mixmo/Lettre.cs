using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mixmo
{
    class Lettre
    {
		public char symbole;
		public int score;

		public string toString()
		{
			return symbole.ToString();
		}

		public Lettre(char sym, int sc)
		{
			symbole = sym;
			score = sc;
		}
    }
}
