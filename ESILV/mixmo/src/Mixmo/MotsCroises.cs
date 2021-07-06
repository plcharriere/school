using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mixmo
{
 
    class MotsCroises
    {
		public char[][] grille;

        public char CharParPos(int x, int y)
        {
            if (x >= 0 && x < 10 && y >= 0 && y < 10)
                return grille[y][x];
            return ' ';
        }

        public void PlacerMot(string mot, int x, int y, int h)
        {
            foreach (char lettre in mot)
            {
                if (x >= 0 && x < 10 && y >= 0 && y < 10)
                    grille[y][x] = lettre;
                if (h > 0)
                    y++;
                else
                    x++;
            }
        }

        public bool GrilleVide()
        {
            for (int i = 0; i < 10; i++)
                for (int j = 0; j < 10; j++)
                    if (grille[i][j] != ' ')
                        return false;
            return true;
        }

        public string toString()
        {
            string s = "";
            s += "\t  1   2   3   4   5   6   7   8   9   10\n";
            s += "_________________________________________________\n";
            for (int y = 0; y < 10; y++)
            {
                s += (y + 1).ToString();
                s += "\t";
                for (int x = 0; x < 10; x++)
                {
                    s += "| ";
                    s += CharParPos(x, y);
                    s += " ";
                }
                s += "|";
                s += "\n";
            }
            return s;
        }

        public MotsCroises()
        {
            grille = new char[10][];
            for (int i = 0; i < 10; i++)
            {
                grille[i] = new char[10];
                for (int j = 0; j < 10; j++)
                    grille[i][j] = ' ';
            }
        }
    }
}
