#pragma once

#include <cassert>
#include <stdint.h>
using namespace std;
template<typename T>
class SinglyLinkedList
{
public:
	struct Node
	{
		T item = T();
		Node* next = nullptr;
	};

	SinglyLinkedList()
	{
	}

	SinglyLinkedList(const SinglyLinkedList& list)
	{
		Node* current_list=list.first_;
		first_=new Node;
		Node* current=first_;
		while(current_list){
			current->item=current_list->item;
			current_list=current_list->next;
			if(current_list){
				current->next=new Node;
				current=current->next;
			}
		}
	}

	~SinglyLinkedList()
	{
		Clear();
	}

	void Clear() // 모두 지워야(delete) 합니다.
	{
		// TODO: 모두 삭제
		if(first_){
			Node* current=first_;
			while(current){
				Node* temp=current;
				current=current->next;
				delete temp;
			}
		}
	}

	bool IsEmpty()
	{
		return first_ == nullptr;
	}

	int Size()
	{
		int size = 0;
		Node* current=first_; //이거 말고 다른 방법 없나 (재귀 제외)
		while(current){
			current=current->next;
			size++;
		}
		// TODO: size를 하나하나 세어서 반환

		return size;
	}

	T Front()
	{
		assert(first_);
		
		return first_->item; // TODO: 수정
	}

	T Back()
	{
		assert(first_);
		Node* current=first_;
		for(int i=0; i<Size()-1; i++){
			current=current->next;
		}
		return current->item; // TODO: 수정
	}

	Node* Find(T item)
	{
		// TODO: item이 동일한 노드 포인터 반환
		Node* current=first_;
		while(current){ //edge 케이스 통과
			if(current->item==item){
				return current;
			}
			current=current->next;
		}
		return nullptr;
	}

	void InsertBack(Node* node, T item)
	{
		Node* temp=node->next;
		node->next=new Node;
		node->next->item=item;
		node->next->next=temp;
		// TODO:
	}

	void Remove(Node* n) //보고있는 노드 지우기
	{
		assert(first_);
		Node* current=first_;
		while(current){
			if(current->next==n){ //만약 다음 주소가 찾는 주소랑 같으면
				current->next=n->next;
				delete n;
				return;
			}
			current=current->next;
		}
		//여기 왔다는건 first가 문제라는뜻;
		first_=first_->next;
		delete n;
		// 하나 앞의 노드를 찾아야 합니다.
		// TODO:
	}

	void PushFront(T item)
	{
		// first_가 nullptr인 경우와 아닌 경우 나눠서 생각해보기 (결국은 두 경우를 하나로 합칠 수 있음)
		Node* next_node=first_;
		first_=new Node;
		first_->item=item;
		first_->next=next_node;
		// 새로운 노드 만들기
		// TODO:

		// 연결 관계 정리
		// TODO:
	}

	void PushBack(T item)
	{
		if (first_)
		{
			Node* current=first_;
			for(int i=0; i<Size()-1; i++){
				current=current->next;
			}
			current->next=new Node;
			current->next->item=item;
			current->next->next=nullptr;
			// TODO:
		}
		else
		{	
			first_=new Node;
			first_->item=item;
			// TODO:
		}
	}

	void PopFront()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopFront()" << endl;
			return;
		}

		assert(first_);

		Node* temp=first_;
		first_=first_->next;
		delete temp;
		// TODO: 메모리 삭제
	}

	void PopBack()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopBack()" << endl;
			return;
		}

		// 맨 뒤에서 하나 앞의 노드를 찾아야 합니다.

		assert(first_);
		Node* current=first_;
		Node* temp=nullptr;
		for(int i=0; i<Size()-1; i++){
			temp=current;
			current=current->next;
		}
		delete current;
		if(temp){
		temp->next=nullptr;
		// TODO: 메모리 삭제
		}else 
		first_=nullptr;
	}

	void Reverse()
	{	
		Node* temp=nullptr;
		Node* prev=nullptr;
		Node* curr=first_;
		for(int i=0; i<Size()-1; i++){
			temp=curr->next;
			curr->next=prev;
			prev=curr;
			curr=temp;
		}
		first_=curr;
		// TODO: 
	}
	/*
	void Reverse_init(Node* node, Node* pre_node){
		if(node->next==nullptr){
			first_=node;
			node->next=pre_node;
			return;
		}
		Reverse_init(node->next,node);
		node->next=pre_node;
	}
		*/
	void SetPrintDebug(bool flag)
	{
		print_debug_ = flag;
	}

	void Print()
	{
		using namespace std;

		Node* current = first_;

		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << " ";

			while (current)
			{
				if (print_debug_)
				{
					//cout << "[" << current << ", " << current->item << ", " << current->next << "]";

					// 주소를 짧은 정수로 출력 (앞 부분은 대부분 동일하기때문에 뒷부분만 출력)
					cout << "[" << reinterpret_cast<uintptr_t>(current) % 100000 << ", "
						<< current->item << ", "
						<< reinterpret_cast<uintptr_t>(current->next) % 100000 << "]";
				}
				else
				{
					cout << current->item;
				}

				if (current->next)
					cout << " -> ";
				else
					cout << " -> NULL";

				current = current->next;
			}
			cout << endl;
		}
	}

protected:
	Node* first_ = nullptr;

	bool print_debug_ = false;
};