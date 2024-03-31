#include <iostream>
#include <vector>
#include <mutex>
#include <ctime>
#include "windows.h"
#include <chrono>
#include <thread>
#include <queue>
#include <algorithm>


#pragma warning(disable : 4996) 

std::mutex m;
int indexSameTime1 = 0;
int indexSameTime2 = 0;
int j = 0;

void carArrived(int carId, int direction)
{
	std::cout << "Car " << carId << " passed in direction " << direction << std::endl;
}

void MyFunc(std::queue<int>& cars, std::vector<int>& directions, std::vector<int>& arriveTimes)
{

	int tmp = arriveTimes.size();

	for (int i = 0; i < tmp; i++)
	{
		std::unique_lock<std::mutex> lock1(m);
		int direction = directions[j];
		int arriveTime = arriveTimes[i];
		if (direction == 3 || direction == 4)
		{
			if (indexSameTime2 == 0)
			{
				/*std::this_thread::sleep_for(std::chrono::seconds(arriveTime));*/
				carArrived(cars.front(), direction);
				cars.pop();
			}
			else
			{
				/*std::this_thread::sleep_for(std::chrono::seconds(arriveTime));*/
				for (int t = 0; t < indexSameTime2; t++)
				{
					carArrived(cars.front(), direction);
					cars.pop();
				}

				indexSameTime2 = 0;

			}
		}

		if (direction == 1 || direction == 2)
		{
			if (indexSameTime1 == 0)
			{
				/*std::this_thread::sleep_for(std::chrono::seconds(arriveTime));*/
				carArrived(cars.front(), direction);
				cars.pop();
			}
			else
			{
				/*std::this_thread::sleep_for(std::chrono::seconds(arriveTime));*/
				for (int t = 0; t < indexSameTime1; t++)
				{
					carArrived(cars.front(), direction);
					cars.pop();
					
				}
				indexSameTime1 = 0;
			}
		}

		j++;
	}
	

	
}

int main()
{
	std::vector<int> cars = { 1,3,5,2,4 };
	std::vector<int> directions = { 2,1,2,4,3 };
	std::vector<int> arriveTimes = { 10,20,30,40,40 };

	std::queue<int> q;

	for (int i = 0; i < cars.size(); i++)
	{
		q.push(cars[i]);
	}

	std::vector<int> arriveTime_1;
	std::vector<int> arriveTime_2;
	std::vector<int> arriveTime_3;
	std::vector<int> arriveTime_4;

	std::vector<std::thread> threads;
	for (int i = 0; i < cars.size(); i++)
	{
		if (directions[i] == 1)
		{
			arriveTime_1.push_back(arriveTimes[i]);
		}
		if (directions[i] == 2)
		{
			arriveTime_2.push_back(arriveTimes[i]);
		}
		if (directions[i] == 3)
		{
			arriveTime_3.push_back(arriveTimes[i]);
		}
		if (directions[i] == 4)
		{
			arriveTime_4.push_back(arriveTimes[i]);
		}
		
	}

	int min_size1 = min(arriveTime_1.size(), arriveTime_2.size());

	for (int i = 0; i < min_size1; i++)
	{
		if (arriveTime_1[i] == arriveTime_2[i])
		{
			indexSameTime1++;
		}
	}

	int min_size2 = min(arriveTime_3.size(), arriveTime_4.size());

	for (int i = 0; i < min_size2; i++)
	{
		if (arriveTime_3[i] == arriveTime_4[i])
		{
			indexSameTime2++;
		}
	}

	std::vector<int> arriveTime_1_1;
	std::vector<int> arriveTime_2_2;

	for (int i =0;i < arriveTime_1.size() - 1;i++)
	{

		if (arriveTime_1[i] == arriveTime_1[i+1] )
		{
			arriveTime_1_1.push_back(arriveTime_1[i]);
			arriveTime_1.erase(arriveTime_1.begin() + i);
		}
		
	}
	for (int i = 0; i < arriveTime_2.size() - 1; i++)
	{

		if (arriveTime_2[i] == arriveTime_2[i + 1])
		{
			arriveTime_2_2.push_back(arriveTime_2[i]);
			arriveTime_2.erase(arriveTime_1.begin() + i);
		}

	}

	threads.emplace_back(MyFunc, std::ref(q), std::ref(directions), std::ref(arriveTime_1)); // direction - 1
	threads.emplace_back(MyFunc, std::ref(q), std::ref(directions), std::ref(arriveTime_1_1)); // direction - 1

	threads.emplace_back(MyFunc, std::ref(q), std::ref(directions), std::ref(arriveTime_2)); // direction - 2
	threads.emplace_back(MyFunc, std::ref(q), std::ref(directions), std::ref(arriveTime_2_2)); // direction - 2

	threads.emplace_back(MyFunc, std::ref(q), std::ref(directions), std::ref(arriveTime_3)); // direction - 3		 

	threads.emplace_back(MyFunc, std::ref(q), std::ref(directions), std::ref(arriveTime_4)); // direction - 4		 



	for (auto& thread : threads) 
	{
		if (thread.joinable()) 
		{
			thread.join();
		}
	}

	return 0;
}