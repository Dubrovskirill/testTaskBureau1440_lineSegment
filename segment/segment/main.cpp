#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

//идея оптимизации
//отсортировать все отрезки по праву концу
//Берем правый конец первого отрезка как первую точку
//gропускаем все отрезки, которые содержат эту точку
//gовторяем для оставшихся отрезков

//структура для храния координат отрезка
struct Segment {
	double start, end;
	
	Segment(double start, double end) 
		: start(start), end(end) {}
};

// Функция сравнения для сортировки отрезков
bool compareSegments(const Segment& a, const Segment& b) {
	return a.end < b.end;
}

//два отрезка не пересекаются, если конец одного меньше начала другого
//иначе они пересекаются
bool doSegmentsIntersect(const Segment& s1, const Segment& s2) {
	return !(s1.end < s2.start || s2.end < s1.start);
}

//находит минимальное количество точек для покрытия всех отрезков
int findMinPoints(std::vector<Segment>& segments) {
	if (segments.empty()) return 0;
	
	std::sort(segments.begin(), segments.end(), compareSegments);
	
	int points = 0;
	double lastPoint = segments[0].end; 
	points++;
	
	for (size_t i = 1; i < segments.size(); ++i) {
		if (segments[i].start > lastPoint) {
			lastPoint = segments[i].end; 
			points++;
		}
	}
	
	return points;
}

int main() {
	
	std::ifstream file("data_prog_contest_problem_1.txt");
	if (!file.is_open()) {
		std::cout << "File opening error" << std::endl;
		return 1;
	}
	
	int n;
	file >> n; 
	
	std::vector<Segment> segments;
	for (int i = 0; i < n; ++i) {
		double start, end;
		file >> start >> end;
		segments.emplace_back(start, end);
	}
	
	file.close(); 
	
	int result = findMinPoints(segments);
	std::cout << "Minimum number of points: " << result << std::endl;
	
	return 0;
}