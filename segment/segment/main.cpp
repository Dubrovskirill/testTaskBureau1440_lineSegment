#include <iostream>
#include <vector>
#include <algorithm>

//структура для храния координат отрезка
struct Segment {
	double start, end;
	
	Segment(double start, double end) 
		: start(start), end(end) {}
};


//два отрезка не пересекаются, если конец одного меньше начала другого
//иначе они пересекаются
bool doSegmentsIntersect(const Segment& s1, const Segment& s2) {
	return !(s1.end < s2.start || s2.end < s1.start);
}

// Находит минимальное количество точек для покрытия всех отрезков
int findMinPoints(const std::vector<Segment>& segments) {
	if (segments.empty()) return 0;
	
	std::vector<bool> used(segments.size(), false);
	int points = 0;
	
	for (size_t i = 0; i < segments.size(); ++i) {
		// Если отрезок еще не обработан
		if (!used[i]) {
			// Находим все отрезки, которые пересекаются с текущим
			std::vector<size_t> intersecting;
			for (size_t j = i; j < segments.size(); ++j) {
				if (!used[j] && doSegmentsIntersect(segments[i], segments[j])) {
					intersecting.push_back(j);
				}
			}
			
			// Помечаем все пересекающиеся отрезки как использованные
			for (size_t idx : intersecting) {
				used[idx] = true;
			}
			
			points++;
		}
	}
	
	return points;
}

int main() {
	int n;
	std::cout << "Enter the number of segments:";
	std::cin >> n;
	
	std::vector<Segment> segments;
	for (int i = 0; i < n; ++i) {
		double start, end;
		std::cin >> start >> end;
		segments.emplace_back(start, end);
	}
	
	int result = findMinPoints(segments);
	std::cout << "Minimum number of points:" << result << std::endl;
	
	return 0;
}