#pragma once
#include <initializer_list>

namespace DataStructures
{
	template<typename T>
	class DoubleLinkList
	{
	private:
		struct Node
		{
			T data {};
			Node* next = nullptr;
			Node* previous = nullptr;

			Node(const T& data = {}, Node* next = nullptr, Node* previous = nullptr) : data{data}, next{next}, previous{previous}
			{}
		};

		Node* head = nullptr;
		Node* tail = nullptr;
		unsigned long long count = 0;

	public:
		DoubleLinkList(const std::initializer_list<T>& list = {})
		{
			for(const T& data : list)
			{
				InsertTail(data);
			}
		}

		DoubleLinkList(const DoubleLinkList& copy)
		{
			Node* node = copy.head;

			while(node != nullptr)
			{
				InsertTail(node->data);
				node = node->next;
			}
		}

		~DoubleLinkList()
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

		void operator=(const DoubleLinkList& copy)
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
			if(head != nullptr)
			{
				count--;
				Node* node = head;
				head = head->next;
				delete node;

				if(head != nullptr) head->previous = nullptr;
			}

			if(head == nullptr) tail = nullptr;
		}

		void DeleteTail()
		{
			if(tail != nullptr)
			{
				if(tail == head) {DeleteHead(); return;}

				count--;
				tail = tail->previous;
				delete tail->next;
				tail->next = nullptr;
			}
		}

		void Delete(const unsigned long long& index)
		{
			if(head == nullptr) return;
			if(index < 0 || index > count - 1) return;
			if(index == 0) {DeleteHead(); return;}
			if(index > 0 && index == count - 1) {DeleteTail(); return;}

			count--;
			Node* node = head;

			for(unsigned long long i = 0; i < index; i++)
			{
				node = node->next;
			}

			node->previous->next = node->next;
			node->next->previous = node->previous;
			delete node;
		}

		void InsertHead(const T& data)
		{
			count++;
			Node* node = new Node(data, head, nullptr);

			if(head != nullptr) head->previous = node;

			head = node;

			if(count == 1) tail = head;
		}

		void InsertTail(const T& data)
		{
			if(head == nullptr) {InsertHead(data); return;}

			count++;
			Node* node = new Node(data, nullptr, tail);
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

			for(unsigned long long i = 0; i < index - 1; i++) previous = previous->next;

			Node* node = new Node(data, previous->next, previous);
			previous->next = node;
			node->next->previous = node;
		}

		void Reverse()
		{
			if(head == nullptr) return;

			Node* left = head;
			Node* right = tail;

			for(unsigned int i = 0; i < count / 2; i++)
			{
				std::swap(left->data, right->data);
				left = left->next;
				right = right->previous;
			}
		}
	};
}