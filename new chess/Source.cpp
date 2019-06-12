#include<iostream>
#include<string>
using namespace std;
bool linecheck(int a, int b, int x, int y);
bool diagonal(int a, int b, int x, int y);
bool onlyone = false;
class piece
{
public:
	string box;
	piece()
	{
		box = "    ";
	}
	virtual bool move(string &p, string &d, int &a, int &b, int &x, int &y) = 0;
	virtual string print() = 0;
};
piece *board[8][8];
class space :public piece
{
public:
	string spc;
	space(string pass)
	{
		spc = pass;
	}
	string print()
	{
		return spc;
	}
	bool move(string &p, string &d, int &a, int &b, int &x, int &y)
	{
		return false;
	}
};
class pawn : public piece
{
	bool t, f;
	string name, space;
public:
	pawn()
	{
		t = true;
		f = false;
	}
	pawn(string  n)
	{
		name = n;
		t = true;
		f = false;
		space = "    ";
	}
	string print()
	{
		return name;
	}
	bool move(string &p, string &d, int &a, int &b, int &x, int &y)
	{
		if (p == " BP ")
		{
			if ((b == y) && (a == 1) && (x == 2 || x == 3) && (d == "    "))
			{

				d = p;
				p = "    ";
				return t;
			}
			else if ((x == a + 1) && (b == y) && (d == "    "))
			{

				swap(p, d);
				return t;
			}
			else if ((x == a + 1) && (y == b - 1 || y == b + 1) && (d != "    ") && (d[1] != 'B'))
			{
				d = p;
				p = "    ";
				return t;
			}
			else return false;
		}
		else if (p == " WP ")
		{
			if ((y == b) && (a == 6) && (x == 5 || x == 4) && (d == "    "))
			{

				d = p;
				p = "    ";
				return t;
			}
			else if ((x == a - 1) && (b == y) && (d == "    "))
			{
				swap(p, d);
				return t;
			}
			else if ((d[1] != 'W') && (d != "    ") && (x == a - 1) && (y == b - 1 || y == b + 1))
			{

				d = p;
				p = "    ";
				return t;
			}
		}
	 return false;
	}
};
class king :public piece
{
public:
	bool t, f;
	string sapce, name;
	king()
	{
		t = true;
		f = false;
	}
	king(string n)
	{
		t = true;
		f = false;
		name = n;
		sapce = "    ";
	}
	string print()
	{
		return name;
	}
	bool move(string &p, string &d, int &a, int &b, int &x, int &y)
	{
		if (d == "    ")
		{
			if ((x == a + 1 || x == a - 1 || x == a) && (b == y + 1 || b == y - 1 || b == y))
			{
				swap(p, d);
				return t;
			}
			else return f;
		}
		else if (p[1] == 'B')
		{
			if (d[1] == 'W')
			{
				if ((x == a + 1 || x == a - 1 || x == a) && (b == y + 1 || b == y - 1 || b == y))
				{
					d = p;
					p = "    ";
					return t;
				}
				else return f;
			}
			else return f;
		}
		else if (p[1] == 'W')
		{
			if (d[1] == 'B')
			{
				if ((x == a + 1 || x == a - 1 || x == a) && (b == y + 1 || b == y - 1 || b == y))
				{
					d = p;
					p = "    ";
					return t;
				}
				else return f;
			}
			else return f;
		}
		else return f;
	}
};
class bishops : public piece
{
public:
	bool t, f;
	string space, name;
	bishops()
	{
		t = true;
		f = false;
		space = "    ";
	}
	bishops(string n)
	{
		t = true;
		f = false;
		space = "    ";
		name = n;
	}
	string print()
	{
		return name;
	}
	bool move(string &p, string &d, int &a, int &b, int &x, int &y)
	{
		if ((d == "    ") && (diagonal(a, b, x, y)))
		{
			swap(p, d);
			return t;
		}
		else if ((p[1] == 'B') && (d[1] == 'W') && (diagonal(a, b, x, y)))
		{
			d = p;
			p = space;
			return t;
		}
		else if ((p[1] == 'W') && (d[1] == 'B') && (diagonal(a, b, x, y)))
		{
			d = p;
			p = space;
			return t;
		}
		return f;
	}
};
class rooks :public piece
{
public:
	string name, space;
	bool t, f;
	rooks()
	{
		t = true;
		f = false;
	}
	rooks(string n)
	{
		t = true;
		f = false;
		name = n;
		space = "    ";
	}
	string print()
	{
		return name;
	}
	bool move(string &p, string &d, int &a, int &b, int &x, int &y)
	{
		if (d == "    ")
		{
			if (linecheck(a, b, x, y))
			{
				if ((a == x) || (b == y))
				{

					swap(p, d);
					return t;
				}
				else return false;
			}
			else return false;
		}
		else if ((p[1] == 'B') && (d[1] == 'W'))
		{
			if ((linecheck(a, b, x, y)) && (a == x || b == y))
			{
				if ((a == x) || (b == y))
				{

					d = p;
					p = "    ";
					return true;
				}
				else return false;
			}
			else return false;
		}
		else if ((p[1] == 'W') && (d[1] == 'B'))
		{
			if (linecheck(a, b, x, y))
			{
				if ((a == x) || (b == y))
				{

					d = p;
					p = "    ";
					return true;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}

};
class night :public piece
{
public:
	string name, space;
	bool t, f;
	night()
	{
		t = true;
		f = false;
	}
	night(string n)
	{
		t = true;
		f = false;
		name = n;
		space = "    ";
	}
	string print()
	{
		return name;
	}
	bool move(string &p, string &d, int &a, int &b, int &x, int &y)
	{
		if ((d == "    "))
		{
			if (((x == a + 2 || x == a - 2) && (y == b - 1 || y == b + 1)) || ((y == b + 2 || y == b - 2) && (x == a + 1 || x == a - 1)))
			{
				swap(d, p);
				return t;
			}
		}
		else if ((d[1] == 'B') && (p[1] == 'W'))
		{
			if (((x == a + 2 || x == a - 2) && (y == b - 1 || y == b + 1)) || ((y == b + 2 || y == b - 2) && (x == a + 1 || x == a - 1)))
			{
				d = p;
				p = "    ";
				return t;
			}
			else return f;
		}
		else if ((d[1] == 'W') && (p[1] == 'B'))
		{
			if (((x == a + 2 || x == a - 2) && (y == b - 1 || y == b + 1)) || ((y == b + 2 || y == b - 2) && (x == a + 1 || x == a - 1)))
			{
				d = p;
				p = "    ";
				return t;
			}
			else return f;
		}
		else return f;
	}
};
class queen : public piece
{
public:
	bool t, f;
	string space, name;
	queen()
	{
		t = true;
		f = false;
		space = "    ";
	}
	queen(string n)
	{
		name = n;
		t = true;
		f = false;
		space = "    ";
	}
	string print()
	{
		return name;
	}
	bool move(string &p, string &d, int &a, int &b, int &x, int &y)
	{
		if (d == "    ")
		{
			if ((linecheck(a, b, x, y)) || (diagonal(a, b, x, y)))
			{
				swap(p, d);
				return t;
			}
		}
		else if ((p[1] == 'B') && (d[1] == 'W'))
		{
			if ((linecheck(a, b, x, y)) || (diagonal(a, b, x, y)))
			{
				d = p;
				p = space;
				return t;
			}
		}
		else if ((p[1] == 'W') && (d[1] == 'B') && ((linecheck(a, b, x, y)) || (diagonal(a, b, x, y))))
		{
			d = p;
			p = space;
			return t;
		}
		return f;
	}
};
void print(string p, string d, int a, int b, int x, int y)
{
	cout << endl << endl << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << "\t\t+---+---+---+---+---+---+---+---+---+---+---+---+" << endl;
		cout << "\t\t|" << board[i][0]->print() << " |" << board[i][1]->print() << " |" << board[i][2]->print() << " |" << board[i][3]->print() << " |" << board[i][4]->print() << " |" << board[i][5]->print() << " |" << board[i][6]->print() << " |" << board[i][7]->print() << " |" << endl;
		if (i == 7)
			cout << "\t\t+---+---+---+---+---+---+---+---+---+---+---+---+" << endl;
	}
}
bool linecheck(int a, int b, int x, int y)
{
	int c = 0;
	if ((a == x) && (b < y))
	{
		while ((b <= y) && (board[a][b + 1]->print() == "    "))
		{
			b++;
			c++;
			if (b == y)
			{
				return true;
			}
		}b -= c;
		c = 0;
		while ((b < y) && (board[a][b + 1]->print() == "    "))
		{
			c++;
			b++;
			if (b == y - 1)
				return true;
		}b -= c;
		c = 0;
	}
	else if ((a == x) && (b > y))
	{
		while ((b >= y) && (board[a][b - 1]->print() == "    "))
		{
			b--;
			c++;
			if (b == y)
			{
				return true;
			}
		}b += c;
		c = 0;
		while ((b > y) && (board[a][b - 1]->print() == "    "))
		{
			b--;
			c++;
			if (b == y - 1)
				return true;
		}b += c;
		c = 0;
	}
	else if ((b == y) && (a < x))
	{

		while ((board[a + 1][y]->print() == "    ") && (a <= x))
		{
			a++;
			c++;
			if (a == x)
				return true;
		}a -= c;
		c = 0;
		while ((a < x) && (board[a + 1][y]->print() == "    "))
		{
			a++;
			c++;
			if (a == x - 1)
				return true;
		}a -= c;
		c = 0;
	}
	else if ((b == y) && (a > x))
	{
		while ((a >= x) && (board[a][y - 1]->print() == "    "))
		{
			a--;
			c++;
			if (a == x)
				return true;
		}a += c;
		c = 0;
		while ((a > x) && (board[a][y - 1]->print() == "    "))
		{
			a--;
			c++;
			if (a == x - 1)
				return true;
		}a += c;
		c = 0;
	}
	return false;
}
bool diagonal(int a, int b, int x, int y)
{
	int i = 0, j = 0;
	if ((x > a) && (y > b))
	{
		while (((a <= x) && (b <= y)) && (board[a + 1][b + 1]->print() == "    " ))
		{
			a++;
			b++;
			i++;
			j++;
			if ((a == x) && (y == b))
			{
				return true;
			}
		}
		a -= i; b -= j;
		while (((a < x) && (y < b)) && (board[a + 1][b + 1]->print() == "    " ))
		{
			a++;
			b++;
			i++;
			j++;
			if ((a == x) && (y == b))
			{
				return true;
			}
		}
		a -= i; b -= j;
	}
	else if ((x > a) && (y < b))
	{
		while ((a <= x) && (b >= y) && (board[a + 1][b - 1]->print() == "    " ))
		{
			a++;
			b--;
			i++;
			j++;
			if ((a == x) && (b == y))
			{
				return true;
			}
		}
		a -= i; b += j;
		while ((a < x) && (b > y) && (board[a + 1][b - 1]->print() == "    " ))
		{
			a++;
			b--;
			i++;
			j++;
			if ((a == x) && (b == y))
			{
				return true;
			}
		}
		a -= i; b += j;
	}
	else if ((x < a) && (y < b))
	{
		while ((a >= x) && (b >= y) && (board[a - 1][b - 1]->print() == "    " ))
		{
			a--;
			b--;
			i++;
			j++;
			if ((a == x) && (b == y))
			{
				return true;
			}
		}a += i; b += j;
		while ((a > x) && (b > y) && (board[a - 1][b - 1]->print() == "    " ))
		{
			a--;
			b--;
			i++;
			j++;
			if ((a == x) && (b == y))
			{
				return true;
			}
		}a += i; b += j;
	}
	else if ((x <= a) && (y >= b))
	{
		while ((x <= a) && (y >= b) && (board[a - 1][b + 1]->print() == "    " ))
		{
			a--;
			b++;
			i++;
			j++;
			if ((a == x) && (b == y))
			{
				return true;
			}
		}a += i;
		b -= j;
		while ((x < a) && (y > b) && (board[a - 1][b + 1]->print() == "    " ))
		{
			a--;
			b++;
			i++;
			j++;
			if ((a == x) && (b == y))
			{
				return true;
			}
		}a += i;
		b -= j;
	}
	return false;
}
void inicialization()
{
	for (int i = 0; i < 8; i++)
	{
		board[1][i] = new pawn(" BP ");
		board[6][i] = new pawn(" WP ");
	}
	board[0][0] = new rooks(" BR ");
	board[0][7] = new rooks(" BR ");
	board[7][0] = new rooks(" WR ");
	board[7][7] = new rooks(" WR ");
	board[0][1] = new night(" BN ");
	board[0][6] = new night(" BN ");
	board[7][1] = new night(" WN ");
	board[7][6] = new night(" WN ");
	board[0][2] = new bishops(" BB ");
	board[0][5] = new bishops(" BB ");
	board[7][2] = new bishops(" WB ");
	board[7][5] = new bishops(" WB ");
	board[0][3] = new king(" BK ");
	board[7][3] = new king(" WK ");
	board[0][4] = new queen(" BQ ");
	board[7][4] = new queen(" WQ ");
	for (int i = 2; i <= 5; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j] = new space("    ");
		}
	}
}
int main()
{
	inicialization();
	string d, p;
	bool tern = true;
	int a = 0, b = 0, x = 0, y = 0, c=0;
	while (1)
	{
		print(p, d, a, b, x, y);
		if (c % 2 == 0)
		{
			cout << "its white turn " << endl;
		}
		else {
			cout << "its black turn " << endl;
		}
		cout << "enter the X position:";
		cin >> a;
		cout << "enter the Y position:";
		cin >> b;
		cout << "enter the X distination:";
		cin >> x;
		cout << "enter the Y distination:";
		cin >> y;
		system("CLS");
		p = board[a][b]->print();
		d = board[x][y]->print();
		if ((a >= 0) && (a < 8) && (b >= 0) && (b < 8) && (x >= 0) && (x < 8) && (y >= 0) && (y < 8))
		{
			if (c % 2 == 0 && board[a][b]->print()[1]=='W')
			{
				if (board[a][b]->move(p, d, a, b, x, y))
				{
					board[x][y] = board[a][b];
					board[a][b] = new space("    ");
					c++;
				}
				else cout << "wrong entery" << endl;
			}
			else if (c % 2 != 0 && board[a][b]->print()[1] == 'B')
			{
				if (board[a][b]->move(p, d, a, b, x, y))
				{
					board[x][y] = board[a][b];
					board[a][b] = new space("    ");
					c++;
				}
				else cout << "wrong entery" << endl;
			}
			else cout << "wrong entery" << endl;
		}
		else cout << "entery out of range" << endl;
	}
	system("pause");
}