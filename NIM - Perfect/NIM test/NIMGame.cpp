#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

const int MAX = 100;

struct PileOfRocks
{
	int n;
	int a[MAX];
};

void InputPile(PileOfRocks& p)
{
	//Nhập số lượng đống ban đầu
	cout << "\nEnter the number of piles of rocks: ";
	while (!(cin >> p.n) || p.n <= 0 || p.n > MAX)
	{
		cout << "Invalid input! Please enter again within the range of 1 to " << MAX << ": ";
		cin.clear();
		cin.ignore(123, '\n');
	}
}

void InputRocks(PileOfRocks& p)
{
	//Tạo ra viên sỏi ngẫu nhiên cho mỗi đống
	srand((int)time(0)); //Truyền giá trị động, thời gian hiện hành (đảm bảo mỗi lần chạy rand() sẽ cho ra kết quả khác nhau)
	for (int i = 0; i < p.n; i++)
	{
		p.a[i] = 1 + rand() % 100;//(1+(0->99)=(1->100))
	}
}

void OutputRocks(PileOfRocks p)
{
	//Danh sách đống sỏi
	for (int i = 0; i < p.n; i++)
	{
		cout << "\nPile[" << i + 1 << "]: " << p.a[i];
	}
}

void PeopleTurn(PileOfRocks& p)
{
	int Pile, Rocks;
	cout << endl;
	cout << "\n========================================================================================================================";
	cout << "\n[YOUR'S TURN]";
	cout << "\n========================================================================================================================" << endl;
	cout << "\nRemaining: ";
	OutputRocks(p);
	//Nhập đống muốn bóc
	cout << "\n\nChoose a pile of rocks (1-" << p.n << "): ";
	while (!(cin >> Pile) || Pile < 1 || Pile > p.n || p.a[Pile - 1] == 0)
	{
		cout << "Invalid input! Please enter again: ";
		cin.clear();
		cin.ignore(123, '\n');
	}
	Pile--;
	//Nhập số viên sỏi muốn bóc
	cout << "\nChoose the number of rocks (1-" << p.a[Pile] << "): ";
	while (!(cin >> Rocks) || Rocks < 1 || Rocks > p.a[Pile])
	{
		cout << "Invalid input! Please enter again: ";
		cin.clear();
		cin.ignore(123, '\n');
	}
	p.a[Pile] -= Rocks;
	cout << "\nPeople takes " << Rocks << " rocks from Pile[" << Pile + 1 << "]" << endl;
}

int Count(PileOfRocks p)
{
	//Đếm đống sỏi
	int count = 0;
	for (int i = 0; i < p.n; i++)
	{
		if (p.a[i] > 0)
			count++;
	}
	return count;
}

bool CountA(PileOfRocks p)
{
	//Kiểm tra chỉ còn 2 đống còn sỏi với 1 đống có 1 viên sỏi
	for (int i = 0; i < p.n; i++)
	{
		if (p.a[i] == 1 && Count(p)==2)
		{
			return true;
		}
	}
	return false;
}

int CountB(PileOfRocks p)
{
	//Gán vị trí của đống sỏi có viên sỏi lớn hơn 1
	int vitriB = 0;
	for (int i = 0; i < p.n; i++)
	{
		if (p.a[i] > 1)
		{
			vitriB = i;
			break;
		}
	}
	return vitriB;
}

bool CountC(PileOfRocks p)
{
	//Kiểm tra có còn 1 đống duy nhất với số sỏi lớn hơn 1
	for (int i = 0; i < p.n; i++)
	{
		if (p.a[i] > 1 && Count(p) == 1)
		{
			return true;
		}
	}
	return false;
}

void ComputerTurn(PileOfRocks& p)
{
	cout << endl;
	cout << "\n========================================================================================================================";
	cout << "\n[COMPUTER'S TURN]";
	cout << "\n========================================================================================================================"<<endl;
	cout << "\nRemaining: ";
	OutputRocks(p);
	cout << endl;
	//Thuật toán nimsum
	int nims = 0;
	for (int i = 0; i < p.n; i++)
	{
		nims ^= p.a[i];
	}
	if (nims == 0)
	{
		srand(time(NULL));
		int Pile = rand() % (p.n);
		//Lập tới khi tìm được đống có sỏi khác 0
		while (p.a[Pile] == 0)
		{
			Pile = rand() % (p.n);
		}
		int Rocks = rand() % p.a[Pile] + 1;
		p.a[Pile] -= Rocks;
		cout << "\nThe computer takes " << Rocks << " rocks from Pile[" << Pile + 1 << "]" <<endl;
	}
	else
	{
		for (int i = 0; i < p.n; i++)
		{
			if ((p.a[i] ^ nims) < p.a[i] && p.a[i]>0)
			{
				//Nếu còn 2 đống và 1 trong 2 có số sỏi bằng 1
				if (CountA(p))
				{
					//Gán đống bằng vị trí có số sỏi lớn hơn 1, lấy hết sỏi trong đống đó
					int Pile = CountB(p);
					int Rocks = p.a[Pile];
					p.a[Pile] = 0;
					cout << "\nThe computer takes " << Rocks << " rocks from Pile[" << Pile + 1 << "]" << endl;
				}
				//Nếu còn 1 đống và sỏi lớn hơn 1
				else if (CountC(p))
				{
					//Gán đống bằng vị trí đống có sỏi lớn hơn 1, lấy chừa lại 1 viên sỏi
					int Pile = CountB(p);
					int Rocks = p.a[Pile]-1;
					p.a[Pile] = 1;
					cout << "\nThe computer takes " << Rocks << " rocks from Pile[" << Pile + 1 << "]" << endl;
				}
				else
				{
					int Rocks = p.a[i] - (p.a[i] ^ nims)-1;
					if (Rocks < 1 && p.a[i]>0)
					{
						Rocks = 1;
					}
					p.a[i] -= Rocks;
					cout << "\nThe computer takes " << Rocks << " rocks from Pile[" << i + 1<<"]" << endl;
					break;
				}
			}
		}
	}
}

int main()
{
		cout << "\n========================================================================================================================" << endl;
			PileOfRocks p;
			InputPile(p);
			InputRocks(p);
			OutputRocks(p);
		cout << "\n========================================================================================================================";
		cout << "\nCoin toss: ";
			string Toss = (rand() % 2 == 0) ? "People" : "Computer";
		cout << Toss << " First!";
		cout << "\n========================================================================================================================" << endl;
			while (Count(p) != 0)
			{
				if (Toss == "People")
				{
					PeopleTurn(p);
					Toss = "Computer";
				}
				else
				{
					ComputerTurn(p);
					Toss = "People";
				}
				OutputRocks(p);
			}
			if (Toss == "People")
			{
				cout << "\nPeople win!";
			}
			else
			{
				cout << "\nComputer win!";
			}
	return 0;
}