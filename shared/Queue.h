#pragma once

#include <cassert>
#include <iostream>
#include <iomanip>
#include <string.h>
template<typename T>
class Queue // Circular Queue
{
public:
	Queue(int capacity = 2)
	{
		assert(capacity > 0);

		capacity_ = capacity;
		queue_ = new T[capacity_];
		front_ = rear_ = 0;
	}

	~Queue()
	{
		if (queue_) delete[] queue_;
	}

	bool IsEmpty() const
	{
		return front_ == rear_;
	}

	bool IsFull() const
	{
		// 원형 큐에서 꽉 찼다의 기준
		return (rear_ + 1) % capacity_ == front_;
	}

	T& Front() const
	{
		assert(!IsEmpty());

		return queue_[(front_ + 1) % capacity_]; // 주의 + 1
	}

	T& Rear() const
	{
		assert(!IsEmpty());

		return queue_[rear_];
	}

	int Size() const //왜 size 변수를 안만들어서 관리할까? 메모리 낭비땜시인가?
	{
		if(front_<=rear_){
			return rear_-front_;  //선형세계와 원형세계
		}else if(front_>rear_){
			return capacity_-front_+rear_;
		}
		// 하나하나 세는 방법 보다는 경우를 따져서 바로 계산하는 것이 빠릅니다.
	
		// if-else-if-else로 구현하는 경우
		//if (...)
		//	return ...;
		//else if (...)
		//	return ...;
		//else
		//	return 0;

		// 또는 if-else 하나로도 구현 가능합니다.
		// if (...)
		//	  return ...;
		// else
		//    return ...;

		return 0; // TODO: 임시
	}

	void Resize() // 2배씩 증가
	{
		int current_size = Size(); // 현재 데이터 개수 저장
		int old_capacity = capacity_; // 이전 용량 저장 (계산용)
		
		// 1. 새 메모리 할당
		T* temp = new T[capacity_ * 2];

		// 2. 데이터 복사 (항상 temp의 1번 인덱스부터 채움)
		if (front_ < rear_) 
		{
			// Case A: 데이터가 일렬로 있는 경우 (한 번에 복사)
			// 출처: queue_의 (front_ + 1)부터
			// 목적지: temp의 1번부터
			memcpy(temp + 1, queue_ + front_ + 1, sizeof(T) * current_size);
		}
		else 
		{
			// Case B: 데이터가 꼬리를 물고 있는 경우 (두 번에 나눠 복사)
			
			// 덩어리 1: front 뒤쪽 ~ 배열 끝
			int first_part = old_capacity - (front_ + 1);
			memcpy(temp + 1, queue_ + front_ + 1, sizeof(T) * first_part);

			// 덩어리 2: 배열 시작 ~ rear
			int second_part = rear_ + 1;
			// 목적지: temp의 (1 + 첫 덩어리 크기) 위치에 딱 붙여서
			memcpy(temp + 1 + first_part, queue_, sizeof(T) * second_part);
		}

		// 3. 멤버 변수 업데이트
		delete[] queue_;
		queue_ = temp;
		
		// 중요: front를 0으로 맞췄으므로, rear는 개수와 같습니다.
		front_ = 0; 
		rear_ = current_size; 
		capacity_ *= 2; // 용량 2배 증가
	}
	void Enqueue(const T& item) // 맨 뒤에 추가, Push()
	{
		if (IsFull())
			Resize();
		queue_[(++rear_)%capacity_]=item;
		// TODO:
		rear_%=capacity_;
	}

	void Dequeue() // 큐의 첫 요소 삭제, Pop()
	{
		assert(!IsEmpty());
		++front_%=capacity_;
		// TODO: 
	}

	void Print()
	{
		using namespace std;

		for (int i = (front_ + 1) % capacity_; i != (rear_ + 1) % capacity_; i = (i + 1) % capacity_)
			cout << queue_[i] << " ";
		cout << endl;

		if (print_debug_)
			PrintDebug();
	}

	void PrintDebug()
	{
		using namespace std;

		cout << "Cap = " << capacity_ << ", Size = " << Size();
		cout << endl;

		// front와 rear 위치 표시
		for (int i = 0; i < capacity_; i++) {
			if (i == front_) cout << " F ";
			else if (i == rear_) cout << " R ";
			else cout << "   ";
		}
		cout << endl;

		// 0 based index
		for (int i = 0; i < capacity_; i++)
			cout << setw(2) << i << " ";
		cout << endl;

		if (front_ < rear_)
		{
			// front 앞 사용하지 않은 공간
			for (int i = 0; i < front_ + 1; i++)
				cout << " - ";

			// 저장된 내용물
			for (int i = front_ + 1; i <= rear_; i++)
				cout << setw(2) << queue_[i] << " ";

			// rear 뒤 사용하지 않은 공간
			for (int i = rear_ + 1; i < capacity_; i++)
				cout << " * ";

			cout << endl << endl;
		}
		else if (front_ > rear_)
		{
			// rear 이전에 저장된 내용물
			for (int i = 0; i <= rear_; i++)
				cout << setw(2) << queue_[i] << " ";

			// rear와 front 사이 사용하지 않은 공간
			for (int i = rear_ + 1; i <= front_; i++)
				cout << " * ";

			// front 뒤 내용물
			for (int i = front_ + 1; i < capacity_; i++)
				cout << setw(2) << queue_[i] << " ";

			cout << endl << endl;
		}
		else // 비었을 경우
		{
			for (int i = 0; i < capacity_; i++)
				cout << " - ";
			cout << endl << endl;
		}
	}

	void SetDebugFlag(bool flag)
	{
		print_debug_ = flag;
	}

protected: // 뒤에서 상속해서 사용
	T* queue_; // array for queue elements
	int front_ = 0; // 시작 인덱스보다 하나 작은 값
	int rear_ = 0; // 마지막 인덱스 (첫 값은 1에 추가)
	int capacity_; // 빈 칸을 하나 둬야 하기 때문에 필요 메모리는 최대 저장량 + 1
	bool print_debug_ = false;
};
