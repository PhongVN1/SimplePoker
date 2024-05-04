#include<iostream>
#include<ctime>
#include<cstdlib>
#include<string>
using namespace std;
string suits[4] = { "\6","\5","\4","\3" };
string faces[13] = { "2", "3", "4", "5","6", "7", "8", "9", "10", "J", "Q","K","A" };//0-12
int cnt(1);
int pos_x(0), pos_y(0);
int deck[4][13];
int findX(int a)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 13; j++)
		{
			if (deck[i][j] == a)
			{
				return j;
			}
		}
	return 0;
}//
int findY(int a)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 13; j++)
		{
			if (deck[i][j] == a)
			{
				return i;
			}
		}
	return 0;
}//

int isOnePair(int* a)
{
	if (findX(a[0]) == findX(a[1]))//a[0] =1
	{
		pos_x = findX(a[0]);
		return 1;
	}
	else if (findX(a[1]) == findX(a[2]))
	{
		pos_x = findX(a[1]);
		return 1;
	}
	else if (findX(a[2]) == findX(a[3]))
	{
		pos_x = findX(a[2]);
		return 1;
	}
	else if (findX(a[3]) == findX(a[4]))
	{
		pos_x = findX(a[3]);
		return 1;
	}
	else return 0;
}
//100
int isTwoPairs(int* a)
{
	if (findX(a[0]) == findX(a[1]) && findX(a[2]) == findX(a[3]))
	{
		pos_x = findX(a[3]);
		return 1;
	}
	else if (findX(a[0]) == findX(a[1]) && findX(a[3]) == findX(a[4]))
	{
		pos_x = findX(a[3]);
		return 1;
	}
	else if (findX(a[1]) == findX(a[2]) && findX(a[3]) == findX(a[4]))
	{
		pos_x = findX(a[3]);
		return 1;
	}
	else return 0;
}
//200
int isThreeOfKind(int* a)
{
	if (findX(a[0]) == findX(a[1]) && findX(a[1]) == findX(a[2]))
	{
		pos_x = findX(a[2]);
		return 1;
	}
	else if (findX(a[1]) == findX(a[2]) && findX(a[2]) == findX(a[3]))
	{
		pos_x = findX(a[3]);
		return 1;
	}
	else if (findX(a[2]) == findX(a[3]) && findX(a[3]) == findX(a[4]))
	{
		pos_x = findX(a[4]);
		return 1;
	}
	else return 0;
}
//300
int isStraight(int* a)
{
	for (int i = 0; i < 4; i++)
	{
		if (findX(a[i]) != findX(a[i + 1]) - 1)
			return 0;
	}
	pos_x = findX(a[4]);
	return 1;
}
//400
int isFlush(int* a)
{

	for (int i = 0; i < 4; i++)
	{
		if (findY(a[i]) != findY(a[i + 1]))
			return 0;
	}
	pos_x = findX(a[4]);
	return 1;
}
//500
int isFullHouse(int* a)
{
	if (findX(a[0]) == findX(a[1]) && findX(a[1]) == findX(a[2]) && findX(a[3]) == findX(a[4]))
	{
		pos_x = findX(a[0]);
		return 1;
	}
	else if (findX(a[2]) == findX(a[3]) && findX(a[3]) == findX(a[4]) && findX(a[0]) == findX(a[1]))
	{
		pos_x = findX(a[2]);
		return 1;
	}
	else return 0;
}
//600
int isFourOfKind(int* a)
{
	if (findX(a[0]) == findX(a[1]) && findX(a[1]) == findX(a[2]) && findX(a[2]) == findX(a[3]))
	{
		pos_x = findX(a[0]);
		return 1;
	}
	else if (findX(a[1]) == findX(a[2]) && findX(a[2]) == findX(a[3]) && findX(a[3]) == findX(a[4]))
	{
		pos_x = findX(a[1]);
		return 1;
	}
	else return 0;
}
//700
int isStraightFlush(int* a)
{
	if (isStraight(a) && isFlush(a))
	{
		pos_x = findX(a[4]);
		return 1;
	}
	else return 0;
}
//800
int isRoyalFlush(int* a)
{
	if (isStraightFlush(a) && isStraightFlush(a))
	{
		for (int i = 0; i < 4; i++)
		{
			if (findX(a[i]) + 1 != findX(a[i + 1]))
			{
				return 0;
			}
		}
		return 1;
	}
	return 0;
}
//900
//
bool check(int mem, int n, int m)
{
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= (n == 0) * m + (n != 0) * 12; j++)
		{
			if (deck[i][j] == mem)
				return false;
		}
	return true;
}//

void shuffleCards(int deck[4][13])
{
	int mem;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 13; j++)
		{
			mem = rand() % 52 + 1;
			if (check(mem, i, j))
				deck[i][j] = mem;
			else if (j == 0)
			{
				i--;
				j = 12;
			}
			else j--;
		}
}//

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void printCardsShuffling(int deck[4][13])
{
	for (int i = 1; i <= 52; i++)
	{
		cout << i << "(" << suits[findY(i)] << "," << faces[findX(i)] << ") ";
		if (i % 5 == 0)
			cout << endl;
	}
}//

int checkHand(int* a)
{
	if (isRoyalFlush(a))return 900;
	else if (isStraightFlush(a))return 800 + pos_x;
	else if (isFourOfKind(a))return 700 + pos_x;
	else if (isFullHouse(a))return 600 + pos_x;
	else if (isFlush(a))return 500 + pos_x;
	else if (isStraight(a))return 400 + pos_x;
	else if (isThreeOfKind(a))return 300 + pos_x;
	else if (isTwoPairs(a))return 200 + pos_x;
	else if (isOnePair(a))return 100 + pos_x;
	else return findX(a[4]);

}

int** createHandTest(int deck[4][13])
{
	int** test;
	test = new int* [1];
	for (int i = 0; i < 1; i++)
	{
		test[i] = new int[6];// a[5] to store a point of the card of player have; 
	}
	return test;
}

int** dealingForHand(int deck[4][13])
{
	int** test;
	test = new int* [1];
	for (int i = 0; i < 1; i++)
	{
		test[i] = new int[6];// a[5] to store a point of the card of player have; 
	}
	return test;
}

void getStatusOfHand(int point)
{

	if (point / 900 == 1)cout << " Royal Flush";
	else if (point / 800 == 1)cout << " Straight Flush " << faces[(point % 800)];
	else if (point / 700 == 1)cout << " Four Of Kind " << faces[(point % 700)];
	else if (point / 600 == 1)cout << " Full House " << faces[(point % 600)];
	else if (point / 500 == 1)cout << " Flush " << faces[(point % 500)];
	else if (point / 400 == 1)cout << " Straight " << faces[(point % 400)];
	else if (point / 300 == 1)cout << " Three Of Kind " << faces[(point % 300)];
	else if (point / 200 == 1)cout << " Two Pairs " << faces[point % 200];
	else if (point / 100 == 1)cout << " One Pair " << faces[(point % 100)];
	else cout << " Highest Card " << faces[(point)];
}

void evaluateHands(int num, int** hand)
{
	for (int i = 0; i < num; i++)
	{
		hand[i][5] = checkHand((int*)hand[i]);
	}
	int max = hand[0][5];
	for (int i = 1; i < num; i++)
	{
		if (max <= hand[i][5])
		{
			max = hand[i][5];
		}
	}
	for (int i = 0; i < num; i++)
	{
		cout << "\n Player " << i + 1 << " has ";
		getStatusOfHand(hand[i][5]);
		cout << endl;
	}
	for (int i = 0; i < num; i++)
	{
		if (max == hand[i][5])
		{
			cout << " The winner is Player " << i + 1 << " with : ";
			getStatusOfHand(max);
			cout << endl;
		}
	}
}

void printHand(int** hand, int num)
{
	for (int i = 0; i < num; i++)
	{
		cout << "\n Player " << i + 1 << " has ";
		for (int j = 0; j < 5; j++)
		{
			cout << "(" << suits[findY(hand[i][j])] << "," << faces[findX(hand[i][j])] << ") ";

		}
	}
}

void sortHand(int** hand, int num)
{
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < 4; j++)
		{

			for (int n = j + 1; n < 5; n++)
			{
				findX(hand[i][n]);
				if (findX(hand[i][j]) > findX(hand[i][n]))
					swap(hand[i][j], hand[i][n]);
			}
		}
	}
}

int** dealingForHands(int deck[4][13], int& num)
{
	int** hand;
	do
	{
		cout << "Input the number of player ( 2-8 players ) : ";
		cin >> num;
	} while (num < 1 && num>8);
	hand = new int* [num];
	for (int i = 0; i < num; i++)
	{
		hand[i] = new int[6];// a[5] to store a point of the card of player have; 
	}
	for (int j = 0; j < 5; j++)
		for (int i = 0; i < num; i++)
		{
			hand[i][j] = cnt++;
		}
	sortHand(hand, num);
	return hand;
}

void freeArr(int** hand, int num)
{
	for (int i = 0; i < num; i++)
		delete[] hand[i];
	delete[] hand;

}

void defaultDeck()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 13; j++)
		{
			deck[i][j] = -1;
		}
}

void Display()
{
	cout << endl << endl << endl << endl;
	cout << "\t\t\t\t\3 \4 \5 \6 \3 \4 \5 \6 \3 \4 \5 \6 \3 \4 \5 \6 \3 \4 \5 \6 \3 \4 \5 \6 \3 \4 \5 \6 \3" << endl;
	cout << "\t\t\t\t\4 ########    ########    #    #    #######    #######  \6" << endl;
	cout << "\t\t\t\t\5 #      #    #      #    #   #     #          #      # \5" << endl;
	cout << "\t\t\t\t\6 #      #    #      #    #  #      #          #      # \4" << endl;
	cout << "\t\t\t\t\3 ########    #      #    ##        #######    #######  \3" << endl;
	cout << "\t\t\t\t\4 #           #      #    #  #      #          # #      \6" << endl;
	cout << "\t\t\t\t\5 #           #      #    #   #     #          #    #   \5" << endl;
	cout << "\t\t\t\t\6 #           ########    #    #    #######    #      # \4" << endl;
	cout << "\t\t\t\t\3 \4 \5 \6 \3 \4 \5 \6 \3 \4 \5 \6 \3 \4 \5 \6 \3 \4 \5 \6 \3 \4 \5 \6 \3 \4 \5 \6 \3" << endl;
	cout << endl << endl;
}

void nPlayerGame()
{
	Display();
	int num, t;
	char a;
	int** hand = dealingForHands(deck, num);
	cout << "How many times do you want to play ?";
	cin >> t;
	cout << "Do you want to print deck every new game ? Y/N\t";
	cin >> a;
	system("cls");
	Display();
	while (t > 0)
	{
		shuffleCards(deck);
		if (a == 'Y' || a == 'y')printCardsShuffling(deck);
		sortHand(hand, num);
		printHand(hand, num);
		evaluateHands(num, hand);
		t--;
		cout << "________________________________________________\n";
		defaultDeck();
	}
	freeArr(hand, num);
}

void singlePlayerGame()
{
	Display();
	int cnt(1);
	int  t;
	char a;
	int** Hand;
	Hand = createHandTest(deck);
	cout << endl;
	srand((int)time(0));
	cout << "How many times do you want to play ?";
	cin >> t;
	cout << "Do you want to print deck every new game ? Y/N\t";
	cin >> a;
	system("cls");
	Display();
	while (t > 0)
	{

		shuffleCards(deck);
		if (a == 'Y' || a == 'y')printCardsShuffling(deck);
		cnt = 1;
		for (int i = 0; i < 1; i++)
			for (int j = 0; j < 5; j++)
			{
				Hand[i][j] = cnt++;
			}
		sortHand(Hand, 1);
		printHand(Hand, 1);
		evaluateHands(1, Hand);
		t--;
		cout << "________________________________________________\n";
		defaultDeck();
	}
	freeArr(Hand, 1);
}

void testGame()
{
	Display();
	int cnt(1);
	int** testHand;
	shuffleCards(deck);
	printCardsShuffling(deck);
	testHand = createHandTest(deck);
	cout << endl;
	for (int i = 0; i < 1; i++)
		for (int j = 0; j < 5; j++)
		{
			cout << "Chose your " << cnt++ << " -card ";
			cin >> testHand[i][j];
		}
	sortHand(testHand, 1);
	printHand(testHand, 1);
	evaluateHands(1, testHand);
	freeArr(testHand, 1);
	// 1 17 28 41 36 
}

void menu()
{
	Display();
	cout << "\n\n\t\t\t\t\t\t      1 : Start Game \n";
	cout << "\n\n\t\t\t\t\t\t      2 : Test Game \n";
	cout << "\n\n\t\t\t\t\t\t      0 : Exit Game \n";
	cout << "\n\n\t\t\t\t\t\t      Your option is : ";
	int otp;
	cin >> otp;
	if (otp == 1)
	{
		do {
			system("cls");
			Display();
			cout << "\n\n\t\t\t\t\t\t      1 : Single player mode \n";
			cout << "\n\n\t\t\t\t\t\t      2 : Multiplayer mode \n";
			cout << "\n\n\t\t\t\t\t\t      0 : Exit Game \n";
			cin >> otp;
			system("cls");
			if (otp == 2)nPlayerGame();
			else if (otp == 1) singlePlayerGame();
			cout << "\n\n\t\t\t\t\t\t___________END____________";
			cout << "\n\n\t\t\t\t\t\t      1 : Continute Game \n";
			cout << "\n\n\t\t\t\t\t\t      0 : Exit Game \n";
			cin >> otp;
		} while (otp == 1);
	}
	else if (otp == 2)
	{
		system("cls");
		testGame();
	}
}
void main()
{
	srand((int)time(0));
	menu();
}

