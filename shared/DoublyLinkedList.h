#pragma once

#include <cassert>
#include <stdint.h>
#include <algorithm>

template<typename T>
class DoublyLinkedList
{
public:
	struct Node
	{
		T item = T();

		Node* left = nullptr;
		Node* right = nullptr;

		// 참고: prev/next가 아니라 left/right
	};

	DoublyLinkedList()
	{
	}

	~DoublyLinkedList()
	{
		Clear();
	}

	void Clear() // 모두 지워야(delete) 합니다.
	{	
		if(!first_) return; //0개라면 통과
		Node* pre_node=first_->right;
		Node* temp=first_;
		while(pre_node){
			delete pre_node->left;
			temp=pre_node;
			pre_node=pre_node->right;
		}
		delete temp;
		// TODO:
	}

	bool IsEmpty()
	{	
		
		return !first_; // TODO:
	}

	int Size()
	{
		int size = 0;

		Node* curr=first_;
		while(curr){
			size++;
			curr=curr->right;
		}
		return size;
	}

	void Print()
	{
		using namespace std;

		Node* current = first_;

		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << endl;

			cout << " Forward: ";
			while(current->right){
				cout << current->item<<' ';
				current=current->right;
			}
			cout << current->item;
			cout << endl;

			cout << "Backward: ";
			while(current->left){
				cout << current->item<<' ';
				current=current->left;
			}
			cout << current->item;
			cout << endl;
		}
	}

	Node* Find(T item)
	{
		Node* curr=first_;
		while(curr){
			if(curr->item==item){
				return curr;
			}
			curr=curr->right;
		}
		return nullptr; // TODO:
	}

	void InsertBack(Node* node, T item)
	{
		if (IsEmpty())
		{
			PushBack(item);
		}
		else
		{
			// TODO:
			Node* curr=first_;
			while(curr){
				if(curr==node){
					Node* temp=new Node;
					temp->left=node;  //좌
					temp->right=node->right; //우
					node->right->left=temp; //좌
					node->right=temp; //우
					temp->item=item;
					return;
				}
				curr=curr->right;
			}
		}
	}

	void PushFront(T item)
	{
		Node* temp=new Node;
		// TODO:
		if(first_){
		temp->right=first_;
		first_->left=temp;
		first_=temp;
		}else first_=temp;
		first_->item=item;
	}

	void PushBack(T item)
	{
		Node* curr=first_;
		while(curr->right){
			curr=curr->right;
		}
		curr->right=new Node;
		curr->right->left=curr;
		curr->right->item=item;
		// TODO:
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
		Node* temp=first_->right; //1번 후보
		if(temp) temp->left=nullptr;
		delete first_;
		first_=temp;
		// TODO:
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
		Node* curr=first_;
		while(curr->right){
			curr=curr->right;
		}
		Node* last=curr->left;
		if(last) last->right=nullptr;
		delete curr;
		// TODO:
	}

	void Reverse()
	{
		// TODO:
		Node* curr=first_;
		while(curr->right){
			std::swap(curr->left,curr->right);
			curr=curr->left;
		}
		std::swap(curr->left,curr->right);
		first_=curr;
	}

	T Front()
	{
		assert(first_);

		return first_->item; // TODO:
	}

	T Back()
	{
		assert(first_);
		Node* curr=first_;
		while(curr->right){
			curr=curr->right;
		}
		return curr->item; // TODO:
	}

protected:
	Node* first_ = nullptr;
};