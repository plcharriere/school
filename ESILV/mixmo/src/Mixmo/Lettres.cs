using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mixmo
{
	class Lettres
	{
		public List<Lettre> list;

		public string toString()
		{
			string s = "";
			foreach (Lettre lettre in list)
				s += lettre.symbole + ",";
			if (s.Length > 0)
				s = s.Remove(s.Length - 1);
			return s;
		}

		public Lettres()
		{
			list = new List<Lettre>();
		}
	}
}
