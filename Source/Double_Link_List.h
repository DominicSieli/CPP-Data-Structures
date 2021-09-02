#pragma once

#include <initializer_list>

namespace Data_Structures
{
	template<typename T>
	class Double_Link_List
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
		Double_Link_List(const std::initializer_list<T>& initializer_list = {})
		{
			for(const T& data : initializer_list)
			{
				Insert_Tail(data);
			}
		}

		Double_Link_List(const Double_Link_List& copy_list)
		{
			Node* node = copy_list.head;

			while(node != nullptr)
			{
				Insert_Tail(node->data);
				node = node->next;
			}
		}

		~Double_Link_List()
		{
			Delete_List();
		}

		constexpr bool Empty() const
		{
			return head == nullptr;
		}

		constexpr unsigned long long Count() const
		{
			return count;
		}

		void Delete_List()
		{
			while(head != nullptr)
			{
				Delete_Head();
			}
		}

		constexpr T Head() const
		{
			if(head != nullptr)
			{
				return head->data;
			}

			return {};
		}

		constexpr T Tail() const
		{
			if(tail != nullptr)
			{
				return tail->data;
			}

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

		void operator=(const Double_Link_List& copy_list)
		{
			Delete_List();

			Node* node = copy_list.head;

			while(node != nullptr)
			{
				Insert_Tail(node->data);
				node = node->next;
			}
		}

		void operator=(const std::initializer_list<T>& list)
		{
			Delete_List();

			for(const T& data : list)
			{
				Insert_Tail(data);
			}
		}

		constexpr unsigned long long Contains(const T& data) const
		{
			if(head == nullptr)
			{
				return 0;
			}

			Node* node = head;
			unsigned long long data_count = 0;

			while(node != nullptr)
			{
				if(node->data == data)
				{
					data_count++;
				}

				node = node->next;
			}

			return data_count;
		}

		void Delete_Head()
		{
			if(head != nullptr)
			{
				count--;
				Node* node = head;
				head = head->next;
				delete node;

				if(head != nullptr)
				{
					head->previous = nullptr;
				}
			}

			if(head == nullptr)
			{
				tail = nullptr;
			}
		}

		void Delete_Tail()
		{
			if(tail != nullptr)
			{
				if(tail == head)
				{
					Delete_Head();
					return;
				}

				count--;
				tail = tail->previous;
				delete tail->next;
				tail->next = nullptr;
			}
		}

		void Delete(const unsigned long long& index)
		{
			if(head == nullptr)
			{
				return;
			}

			if(index < 0 || index > count - 1)
			{
				return;
			}

			if(index == 0)
			{
				Delete_Head();
				return;
			}

			if(index > 0 && index == count - 1)
			{
				Delete_Tail();
				return;
			}

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

		void Insert_Head(const T& data)
		{
			count++;
			Node* node = new Node(data, head, nullptr);

			if(head != nullptr)
			{
				head->previous = node;
			}

			head = node;

			if(count == 1)
			{
				tail = head;
			}
		}

		void Insert_Tail(const T& data)
		{
			if(head == nullptr)
			{
				Insert_Head(data);
				return;
			}

			count++;
			Node* node = new Node(data, nullptr, tail);
			tail->next = node;
			tail = node;
		}

		void Insert(const T& data, const unsigned long long& index)
		{
			if(index < 0)
			{
				return;
			}

			if(index == 0)
			{
				Insert_Head(data);
				return;
			}

			if(index >= count - 1)
			{
				Insert_Tail(data);
				return;
			}

			count++;
			Node* previous_node = head;

			for(unsigned long long i = 0; i < index - 1; i++)
			{
				previous_node = previous_node->next;
			}

			Node* node = new Node(data, previous_node->next, previous_node);
			previous_node->next = node;
			node->next->previous = node;
		}

		void Reverse()
		{
			if(head == nullptr)
			{
				return;
			}

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