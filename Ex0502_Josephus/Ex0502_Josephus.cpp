#include "../shared/Queue.h"

#include <iostream>

using namespace std;

int main()
{
	int n = 7, k = 3; // set n and k to the desired values

	Queue<int> q(n + 1);
	q.SetDebugFlag(false);

	// 처음에 n명 추가 (1, 2, ..., n)
	for (int i = 1; i <= n; i++)
		q.Enqueue(i);
	q.Print();

	// 마지막 한 명이 남을 때까지 반복
	{	//시뮬 해보자.
		int cnt=0;
		while((q.Size()!=1)){
			cnt++;
			q.Print();
			if(cnt==k){
				cout << "Executed " << q.Front()<< endl;
				q.Dequeue();
				cnt=0;
				continue;
			}
			int tmp=q.Front();
			q.Enqueue(tmp); //여기서 참조 오류 났었음 그러니깐 T&인데 그걸 그대로 넣고 Resize할때 쓰레기 값이 들어감.
			q.Dequeue();

		}
		// k-1 명은 맨 앞에서 뒤로 보내기

		// k 번째 사람 처형
		// cout << "Executed " << ... << endl;
	}
	cout << "Survivor: " << q.Front() << endl;

	return 0;
}