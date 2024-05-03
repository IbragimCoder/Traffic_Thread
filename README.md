The essence of the task is in threads.There are several roads, cars pass along these roads (each road is a thread). There is a time in which the car passes the road. Distribute traffic light flows according to traffic rules.

The code allocates the travel time and direction and transmits them to the streams.

This code is a simulation of the movement of cars at an intersection with two traffic lights.


void car Arrived(in card, int direction)
This function displays a message that a car with a certain CarID has passed in the specified direction.

void MyFunc(std::queue<int>& char, std::vector<int>& directions, std::vector<int>& arriveTimes)
This function simulates the movement of cars at an intersection. It takes a queue of cars of cars, a vector of directions of directions and a vector of arrival times.
```c++
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
			trafficLight_A++;
			if (trafficLight_A == 1)
			{
				std::cout << "Traffic Light on road B is green" << std::endl;
				trafficLight_B = 0;
			}
			
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
			trafficLight_B++;
			if (trafficLight_B == 1)
			{
				std::cout << "Traffic Light on road A is green" << std::endl;
				trafficLight_A = 0;
			}

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

```
