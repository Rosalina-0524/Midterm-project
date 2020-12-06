#include <iostream>
#include <numeric>
using namespace std;

const int MAX_M = 50;
const int MAX_N = 1000;

int arraySum(int a[], int n)
{
	int initial_sum = 0;
	return accumulate(a, a + n, initial_sum);
}

float arraySum(float a[], int n)
{
	float initial_sum = 0.0;
	return accumulate(a, a + n, initial_sum);
}

int main()
{
	int numMachine = 0, numOrder = 0, maxFix = 0; // m n h
	cin >> numMachine >> numOrder >> maxFix;

	float *ideal = new float[numMachine];  // a
	int *dRate = new int[numMachine];	   //b
	int *fixHr = new int[numMachine];	   //c
	int *beginYield = new int[numMachine]; // p0
	int *minYield = new int[numMachine];   // L
	for (int i = 0; i < numMachine; i++)
		cin >> ideal[i] >> dRate[i] >> fixHr[i] >> beginYield[i] >> minYield[i];

	float *orderQty = new float[numOrder]; // q
	int *deadline = new int[numOrder];	   // d
	for (int i = 0; i < numOrder; i++)
		cin >> orderQty[i] >> deadline[i];

	// here we go
	float total_qty = 0;
	for (int i = 0; i < numOrder; i++)
		total_qty += orderQty[i];

	float qty_per_hr = 0;
	float min_qty_per_hr = 1000;
	for (int i = 0; i < numMachine; i++)
	{
		qty_per_hr = ideal[i] * minYield[i] / 100;
		if (qty_per_hr < min_qty_per_hr)
			min_qty_per_hr = qty_per_hr;
	}
	// 即使所有訂單丟給同台機器所需最大的小時數
	int T = (total_qty / min_qty_per_hr) + 1;

	float yieldMatrix[MAX_M][numMachine] = {0.0};
	float bestyieldMatrix[][] = {0};
	float profit[MAX_M] = {0};

	int yield = 0;
	int totalyield = 0;

	// 無維修
	for (int i = 0; i < numMachine; i++)
	{
		yield = beginYield[i];
		totalyield = 0;
		for (int j = 0; j < T; j++)
		{
			yield -= dRate[i];
			if (yield < minYield[i])
			{
				yield = minYield[i];
			}
			yieldMatrix[i][j] = yield;
			totalyield += yield * ideal[i] / 100;
		}
		profit[i] = totalyield;
	}

	int bestprofitsum = arraySum(profit, numMachine);

	cout << bestprofitsum;

	/*
		int best_fix_time = 0,
		best_profit = profit;

	for (int i = 0; i < total_time; i++)
	{
		efficiency = begin;
		profit = 0;

		for (int j = 0; j < total_time; j++)
		{
			efficiency -= breakdown;
			if (j >= i and j <= i + fix_time - 1)
			{
				efficiency = 0;
			}
			else if (j == i + fix_time)
			{
				efficiency = 100;
			}
			else if (efficiency < stable)
			{
				efficiency = stable;
			}
			profit += efficiency * ideal / 100;
		}

		if (profit > best_profit)
		{
			best_profit = profit;
			best_fix_time = i + 1;
		}
	}
	cout << best_fix_time << "," << best_profit;

	*/

	return 0;
}

//pause = 1 <
/*
先排出m列原本的profit
最小的 ap 開始修 假設 h = 1 ... h
設一個計算已經修的cnt , cnt <= h

計算row 的總和有多大

有說一台機器最多能修幾次嗎

*/
