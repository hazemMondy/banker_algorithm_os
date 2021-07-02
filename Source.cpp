#include<iostream>
using namespace std;

int c, d, req;

void calculateNeed(int** need, int** maxm,
	int** allot, bool z)
{

	for (int i = 0; i < c; i++)
		for (int j = 0; j < d; j++)
			need[i][j] = maxm[i][j] - allot[i][j];

	if (z) {
		cout << "need output PxR :" << endl;
		for (int i = 0; i < c; i++) {
			for (int j = 0; j < d; j++) {
				cout << need[i][j] << " ";
			}
			cout << endl;
		}
	}
}
void printq(int* safeSeq) {
	cout << "Yes , Safe state <";
	for (int i = 0; i < c; i++)
	{
		if (i == 0 && req == 1)
		{
			cout << "P" << safeSeq[i] << "req" << ",";
			continue;
		}
		if (i == (c - 1))
		{
			cout << "P" << safeSeq[i] << ">";
		}
		else
			cout << "P" << safeSeq[i] << ",";
	}

}


bool isSafe(int* processes, int* avail, int** maxm,
	int** allot)
{

	int** need = new int* [c];
	for (int i = 0; i < c; i++)
	{
		need[i] = new int[d];
	}



	calculateNeed(need, maxm, allot, 0);


	bool* finish = new bool[c];
	for (int i = 0; i < c; i++)
		finish[i] = 0;


	int* safeSeq = new int[c];


	int* work = new int[c];
	for (int i = 0; i < d; i++)
		work[i] = avail[i];

	int count = 0;
	while (count < c)
	{

		bool found = false;
		for (int p = 0; p < c; p++)
		{

			if (finish[p] == 0)
			{

				int j;
				for (j = 0; j < d; j++)
					if (need[p][j] > work[j])
						break;

				if (j == d)
				{

					for (int k = 0; k < d; k++)
						work[k] += allot[p][k];

					safeSeq[count++] = p;
					finish[p] = 1;
					found = true;
				}
			}
		}

		if (found == false)
		{
			cout << "System is not in safe state";
			return false;
		}
	}

	printq(safeSeq);
	return true;
}


int main()
{

	int no_proc;
	cout << "please enter nomber of proccess :" << endl;
	cin >> no_proc;
	c = no_proc;
	int* processes = new int[no_proc];

	for (int i = 0; i < no_proc; i++)
		processes[i] = i;


	int* avail;
	cout << "please enter number of available resources :" << endl;
	cin >> d;
	avail = new int[d];
	cout << "please enter the available resources matrix :" << endl;
	for (int i = 0; i < d; i++)
		cin >> avail[i];



	int** maxm = new int* [no_proc];

	for (int i = 0; i < no_proc; i++)
		maxm[i] = new int[d];

	cout << "please enter the maxm matrix: " << endl;
	for (int i = 0; i < no_proc; i++)
	{
		for (int j = 0; j < d; j++)
			cin >> maxm[i][j];
	}


	int** allot = new int* [no_proc];
	for (int i = 0; i < no_proc; i++)
		allot[i] = new int[d];

	cout << "please enter allot matrx :" << endl;
	for (int i = 0; i < c; i++)
	{
		for (int j = 0; j < d; j++)
			cin >> allot[i][j];
	}

	int** need = new int* [c];
	for (int i = 0; i < c; i++)
	{
		need[i] = new int[d];
	}
	//calculateNeed(need, maxm, allot, 1);




	cout << "do you want the safe state? please answer with yes or no" << endl;
	string s;
	cin >> s;
	if (s == "yes" || s == "Yes" || s == "YES" || s == "y")
	{
		for (int i = 0; i < c; i++) {
			for (int j = 0; j < d; j++) {
				if (!(maxm[i][j] - allot[i][j]))
				{
					cout << "no,not safe";
					return 0;
				}
			}
		}

		isSafe(processes, avail, maxm, allot);
		calculateNeed(need, maxm, allot, 1);
	}


	cout << "\ndo you want the immediate requests? please answer with yes or no" << endl;
	cin >> s;

	if (s == "yes" || s == "Yes" || s == "YES" || s == "y")
	{
		// Immediate Request
		int* RS = new int[d];

		int bim;
		bool ok = true;


		cout << "Enter Process Number: ";
		cin >> bim;


		cout << "please enter request resources: ";
		for (int i = 0; i < d; i++)
			cin >> RS[i];
		calculateNeed(need, maxm, allot, 0);

		for (size_t i = 0; i < d; i++)
		{
			if (RS[i] > need[bim][i])
			{
				ok = false;
				break;
			}
			if (RS[i] > avail[i])
			{
				ok = false;
				break;
			}
		}
		if (!ok)
		{
			cout << "No,request rejected as shortage in resources " << endl;
			return 0;
		}

		// add to alloc, subtract from available and need
		for (int i = 0; i < d; i++)
		{
			allot[bim][i] += RS[i];
			avail[i] -= RS[i];
			need[bim][i] -= RS[i];
		}
		req = 1;
	}

	isSafe(processes, avail, maxm, allot);
	calculateNeed(need, maxm, allot, 2);




	// Check system is in safe state or not

	return 0;
}