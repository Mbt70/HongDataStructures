#pragma once

#include "Queue.h"

#include <cassert>
#include <iostream>
#include <iomanip>

// Double Ended Queue (덱, dequeue와 구분)
template<typename T>
class Deque : public Queue<T>
{

	typedef Queue<T> Base;

public:
	Deque(int capacity)
		: Queue<T>(capacity)
	{
	}

	T& Front()
	{
		return Base::Front();
	}

	T& Back()
	{
		return Base::Rear();
	}

	void PushFront(const T& item)
	{
		if (Base::IsFull())
			Base::Resize();
		//queue_[--front_%capacity_]=item; //나머지 연산시 음수 가능 주의
		//front%=capcity_;
		this->queue_[this->front_]=item;
		this->front_=(this->front_-1+this->capacity_)%this->capacity_;
		std::cout << this->front_ <<"앞";
		// TODO:
	}

	void PushBack(const T& item)
	{
		Base::Enqueue(item);
	}

	void PopFront()
	{
		Base::Dequeue();
	}

	void PopBack()
	{
		assert(!Base::IsEmpty());
		this->rear_=(this->rear_-1+this->capacity_)%this->capacity_;
		// TODO:
	}

private:
	// Queue와 동일
};
