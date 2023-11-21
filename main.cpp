#include <iostream>
#include <vector>
#include <cstdlib>

#include <string.h>
#include <random>

#include <set>
#include <algorithm>

//для работы со временем
#include <chrono>
#include <thread>

int main() {

	setlocale(LC_ALL, "ru");
	srand(time(NULL));

	std::random_device rd;
	std::mt19937 distr(rd());
	std::uniform_int_distribution<int> prov(0, 30000);

	///выбираем одинаковые числа
	std::set <int> A{ 1, 2, 3, 4, 5, 6, 7, 8 , 9 };
	std::set <int> B{ 6, 7, 8, 9, 10, 11, 12, 13 };
	std::vector <int> result;

	std::set_intersection(A.begin(), A.end(), B.begin(), B.end(),
		std::back_inserter(result));
	for (auto& e : result)
	{
		std::cout << e << " ";
	}

	///
	std::cout << std::endl;
	std::vector <int> ValA;
	ValA.reserve(20000); //резервирует метсо на вот столько элементов
	std::vector <int> ValB;
	ValB.reserve(20000);
	for (int i = 0; i < ValA.capacity(); i++)
	{
		ValA.push_back(prov(distr));
	}
	for (int i = 0; i < ValB.capacity(); i++)
	{
		ValB.push_back(prov(distr));
	}

	auto start_point = std::chrono::system_clock::now();
	std::vector <int> resultA;
	for (auto& e : ValA)
	{
		auto tmp = std::find(ValB.begin(), ValB.end(), e);
		if (tmp != ValB.end()) {
			auto tmp1 = std::find(resultA.begin(), resultA.end(), e);
			if (tmp1 == resultA.end()) {
				resultA.push_back(*tmp);
			}
		}
	}
	auto end_point = std::chrono::system_clock::now();
	auto t_diff = std::chrono::duration_cast<std::chrono::milliseconds>
		(end_point - start_point);
	std::cout << resultA.size() << " doubled elements " <<
		t_diff.count() << " ms\n";

	///
	std::set <int> A1{ValA.begin(),ValA.end()};
	std::set <int> B1{ValB.begin(),ValB.end()};
	std::vector <int> result1;

	std::set_intersection(A1.begin(), A1.end(), B1.begin(), B1.end(),
		std::back_inserter(result1));

	auto end_point1 = std::chrono::system_clock::now();
	auto t_diff1 = std::chrono::duration_cast<std::chrono::milliseconds>
		(end_point - start_point);
	std::cout << result1.size() << " doubled elements " <<
		t_diff1.count() << " ms\n";



	return 0;
}