//#include "PriorityQueue.h";
//#include <string>;
//
//
//std::string randomString(int length) {
//
//	std::string source = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
//
//	std::string output = "";
//
//	for (int i = 0; i < length; i++) {
//
//		output += source[std::rand() % source.size()];
//
//	}
//
//	return output;
//
//}
//
//template <typename X> void print_priority_queue(PriorityQueue<X> pq) {
//
//	typename std::vector<X> elements = pq.get_all_elements();
//	std::vector<int> priorities = pq.get_all_priorities();
//
//	std::cout << "\n[";
//	for (int i = 0; i < elements.size() - 1; i++) {
//
//		std::cout << "(" << priorities[i] << ", " << elements[i] << "), ";
//
//	}
//	std::cout << "(" << priorities[elements.size() - 1] << ", " << elements[elements.size() - 1] << ")]" << std::endl;
//
//}
//
//int main()
//{
//	PriorityQueue<std::string> pq;
//	std::vector<std::pair<int, std::string> > pairs;
//
//	for (int i = 0; i < rand() % 10 + 1; i++) {
//
//		pairs.push_back(std::pair<int, std::string>(rand() % 100, randomString(rand() % 10 + 1)));
//
//	}
//
//	pq.insert_all(pairs);
//
//	print_priority_queue(pq);
//	return 0;
//}
//
//
