#pragma once
#include <initializer_list>

namespace DataStructures
{
	template<typename T>
	class SingleLinkList
	{
	private:
		struct Node
		{
			T data {};
			Node* next = nullptr;

			Node(const T& data = {}, Node* next = nullptr) : data{data}, next{next}
			{}
		};

		Node* head = nullptr;
		Node* tail = nullptr;
		unsigned long long count = 0;

	public:
		SingleLinkList()
		{}
	
		SingleLinkList(const std::initializer_list<T>& list)
		{
			for(const T& data : list)
			{
				InsertTail(data);
			}
		}

		SingleLinkList(const SingleLinkList& copy)
		{
			Node* node = copy.head;

			while(node != nullptr)
			{
				InsertTail(node->data);
				node = node->next;
			}
		}

		~SingleLinkList()
		{
			DeleteList();
		}

		constexpr bool Empty() const
		{
			return head == nullptr;
		}

		constexpr unsigned long long Count() const
		{
			return count;
		}

		void DeleteList()
		{
			while(head != nullptr)
			{
				DeleteHead();
			}
		}

		constexpr T Head() const
		{
			if(head != nullptr) return head->data;

			return {};
		}

		constexpr T Tail() const
		{
			if(tail != nullptr) return tail->data;

			return {};
		}

		T& operator[](const unsigned long long& index)
		{
			Node* node = head;

			for(unsigned long long i = 0; i < index; i++)
			{
				node = node->next;
			}

			return node->data;
		}

		constexpr T operator[](const unsigned long long& index) const
		{
			Node* node = head;

			for(unsigned long long i = 0; i < index; i++)
			{
				node = node->next;
			}

			return node->data;
		}

		void operator=(const SingleLinkList& copy)
		{
			DeleteList();

			Node* node = copy.head;

			while(node != nullptr)
			{
				InsertTail(node->data);
				node = node->next;
			}
		}

		void operator=(const std::initializer_list<T>& list)
		{
			DeleteList();

			for(const T& data : list)
			{
				InsertTail(data);
			}
		}

		constexpr unsigned long long Contains(const T& data) const
		{
			if(head == nullptr) return 0;

			Node* node = head;
			unsigned long long instances = 0;

			while(node != nullptr)
			{
				if(node->data == data) instances++;

				node = node->next;
			}

			return instances;
		}

		void DeleteHead()
		{
			if(head == nullptr) return;
			
			count--;
			Node* node = head;
			head = head->next;
			delete node;

			if(head == nullptr) tail = nullptr;
		}

		void DeleteTail()
		{
			if(tail == nullptr) return;
			if(tail == head) {DeleteHead(); return;}
			
			Node* node = head;

			while(node->next != tail)
			{
				node = node->next;
			}

			count--;
			delete tail;
			tail = node;
			tail->next = nullptr;
		}

		void Delete(const unsigned long long& index)
		{
			if(head == nullptr) return;
			if(index < 0 || index >= count) return;
			if(index == 0) {DeleteHead(); return;}
			if(index == count - 1) {DeleteTail(); return;}

			Node* node = head;
			Node* nextNode = nullptr;

			for(unsigned long long i = 0; i < index - 1; i++)
			{
				node = node->next;
			}

			count--;
			nextNode = node->next->next;
			delete node->next;
			node->next = nextNode;
		}

		void InsertHead(const T& data)
		{
			count++;
			Node* node = new Node(data, head);
			head = node;

			if(count == 1) tail = head;
		}

		void InsertTail(const T& data)
		{
			if(tail == nullptr) {InsertHead(data); return;}

			count++;
			Node* node = new Node(data);
			tail->next = node;
			tail = node;
		}

		void Insert(const T& data, const unsigned long long& index)
		{
			if(index < 0) return;
			if(index == 0) {InsertHead(data); return;}
			if(index >= count - 1) {InsertTail(data); return;}

			count++;
			Node* previous = head;

			for(unsigned long long i = 0; i < index - 1; i++)
			{
				previous = previous->next;
			}

			Node* node = new Node(data, previous->next);
			previous->next = node;
		}

		void Reverse()
		{
			if(count < 2) return;

			Node* current = head;
			Node* next = head->next;
			Node* previous = nullptr;

			while(current != nullptr)
			{
				next = current->next;
				current->next = previous;
				previous = current;
				current = next;
			}

			std::swap(head, tail);
		}
	};
}