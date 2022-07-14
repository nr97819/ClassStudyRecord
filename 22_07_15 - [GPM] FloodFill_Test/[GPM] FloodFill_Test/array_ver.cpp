//
//#include <iostream>
//#include <conio.h>
//
//#include <vector>
//using std::vector;
//
//typedef struct POS
//{
//	int x;
//	int y;
//
//	POS()
//	{
//		x = 0;
//		y = 0;
//	}
//
//	POS(int _x, int _y)
//	{
//		x = _x;
//		y = _y;
//	}
//}element;
//
////#define WIDTH 7
////#define HEIGHT 7
//
//#define WIDTH 19
//#define HEIGHT 19
//
//static int map2[HEIGHT][WIDTH] = {
//	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
//	{1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
//	{1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
//	{1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1},
//	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
//	{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1},
//	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
//	{1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
//	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
//	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
//	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
//	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
//	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
//	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
//	{1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
//};
//
////static int map[HEIGHT][WIDTH] = {
////	0, 0, 0, 0, 0, 0, 0,
////	0, 1, 1, 1, 1, 1, 0,
////	0, 1, 0, 0, 0, 1, 0,
////	0, 1, 0, 0, 0, 1, 0,
////	0, 1, 0, 0, 0, 1, 0,
////	0, 1, 1, 1, 1, 1, 0,
////	0, 0, 0, 0, 0, 0, 0
////};
//
//void print_map()
//{
//	for (int j = 0; j < HEIGHT; ++j) {
//		for (int i = 0; i < WIDTH; ++i)
//			printf("%d ", map2[j][i]);
//		printf("\n");
//	}
//	printf("\n");
//}
//
//void print_stack(const vector<element>& _stack)
//{
//	printf("Stack : ");
//	if (_stack.empty())
//	{
//		printf("Empty");
//	}
//	else
//	{
//		//for (size_t i = 0; i <= _stack.size(); ++i)
//		for (vector<element>::const_iterator cit = _stack.begin(); cit != _stack.end(); ++cit)
//		{
//			printf("(%d, %d) ", cit->x, cit->y);
//		}
//	}
//	printf("\n");
//}
//
//int main()
//{
//	print_map();
//
//	vector<element> stack;
//	stack.clear();
//
//	stack.push_back(element(0, 0));
//	//Push(&to_visit, get_element(0, 0)); // start cell  (바깥 쪽 하얀색)
//	// Push(&to_visit, get_element(3, 3)); // start cell (안 쪽 하얀색)
//
//	while (!stack.empty()) 
//	{
//		element cell = stack.back();
//		stack.pop_back();
//
//		if (map2[cell.y][cell.x] == 1) // already visited
//			continue;
//
//		map2[cell.y][cell.x] = 1; // 방문 처리
//
//		// 현재 방문 중인 위치에서 갈 수 있는 곳들 스택에 넣기 (상하좌우)
//		if (cell.y - 1 >= 0 && map2[cell.y - 1][cell.x] == 0) // up
//			stack.push_back(element(cell.x, cell.y - 1));
//			//Push(&to_visit, get_element(cell.i, cell.j - 1));
//
//		if (cell.y + 1 < HEIGHT && map2[cell.y + 1][cell.x] == 0) // down
//			stack.push_back(element(cell.x, cell.y + 1));
//			//Push(&to_visit, get_element(cell.i, cell.j + 1));
//
//		if (cell.x - 1 >= 0 && map2[cell.y][cell.x - 1] == 0) // left
//			stack.push_back(element(cell.x - 1, cell.y));
//			//Push(&to_visit, get_element(cell.i - 1, cell.j));
//
//		if (cell.x + 1 < WIDTH && map2[cell.y][cell.x + 1] == 0) // right
//			stack.push_back(element(cell.x + 1, cell.y));
//			//Push(&to_visit, get_element(cell.i + 1, cell.j));
//
//		// 애니메이션 효과로 출력
//		system("cls"); // #include <conio.h> 에서 지원하는, 콘솔창 지우는 명령어! (clear screen 의 약자) system(커맨드)
//		print_stack(stack);
//		printf("Cell : (%d, %d)\n", cell.x, cell.y);
//		print_map();
//		int dummy = _getch(); // 사용자가 엔터 쳐야 다음으로 넘어가게끔
//	}
//
//	printf("Result:\n");
//	print_map();
//}