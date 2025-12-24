#include <iostream>

#include "../shared/Stack.h"

using namespace std;

constexpr int kNumRows = 10;
constexpr int kNumCols = 9;

char maze[kNumRows][kNumCols] =
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', 'S', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '0', '1', '0', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '0', '1', '1', '1'},
	{'1', '1', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', 'G', '1'}, // <- 'G'를 만나면 종료
	{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
};

void PrintMaze()
{
	for (int j = 0; j < kNumRows; j++)
	{
		for (int i = 0; i < kNumCols; i++)
			cout << maze[j][i] << " ";
		cout << endl;
	}
}

struct Pos
{
	int row;
	int col;

	// 디버깅을 위한 편의 기능
	friend ostream& operator<<(ostream& os, const Pos& pos)
	{
		cout << "(" << pos.row << ", " << pos.col << ")" << flush;
		return os;
	}
};

/*void RecurMaze(Pos p)
{
	const char mark = maze[p.row][p.col];

	if (mark == 'G')
	{
		cout << "Found!" << endl;
		return;
	}
	//호출될때 아예 갈 수 있는 경우만 호출하자
	int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
	int nx,ny;
	maze[p.row][p.col]='X';
	for(int i=0; i<4; i++){
		ny=p.row+d[i][0];
		nx=p.col+d[i][1];
		if(maze[ny][nx]!='1'&&maze[ny][nx]!='X'){
			RecurMaze({ny,nx});
		}
	}
	

	// 방문했던 적이 없고 ('X'가 아니고)
	// 벽도 아닌 경우 ('1'도 아닌 경우)
	// if (...)
	//{
		// 'X' 표시

		// 옆으로 이동
	//}
}
*/
//조기 종료가 가능한 버전
int RecurMaze(Pos p)
{

	const char mark = maze[p.row][p.col];
	
	if (mark == 'G')
	{
		cout << "Found!" << endl;
		return -1;
	}
	//호출될때 아예 갈 수 있는 경우만 호출하자
	int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
	int nx,ny;
	maze[p.row][p.col]='X';
	for(int i=0; i<4; i++){
		ny=p.row+d[i][0];
		nx=p.col+d[i][1];
		if(maze[ny][nx]!='1'&&maze[ny][nx]!='X'){
			if(RecurMaze({ny,nx})==-1) return -1;
		}
	}
	// TODO:
	return 0;
}

void StackMaze()
{
	Stack<Pos> s;

	Pos start = { 1, 1 }; // i = 1, j = 1  시작 지점
	//Pos start;
	//start.row = 1;
	//start.col = 1;

	s.Push(start); // s.Push({1, 1});

	// s.Print(); // 디버깅에 사용 가능

	while (!s.IsEmpty())
	{
		Pos p = s.Top();
		s.Pop();

		cout << p << " "; // 디버깅 출력

		const char mark = maze[p.row][p.col];

		if (mark == 'G')
		{
			cout << "Found!" << endl;
			break;
		}
		maze[p.row][p.col]='X';
		int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
		int nx,ny;
		for(int i=0; i<4; i++){
			ny=p.row+d[i][0];
			nx=p.col+d[i][1];
			if(maze[ny][nx]!='1'&&maze[ny][nx]!='X'){
				s.Push({ny,nx});
			}
		}
		// TODO:
	}
}

int main()
{
	PrintMaze();

	RecurMaze({ 1, 1 });

	//StackMaze();

	PrintMaze();

	return 0;
}

