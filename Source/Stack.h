#pragma once

namespace Data_Structures
{
	template<typename T>
	class Stack
	{
	private:
		struct Node
		{
			T data {};
			Node* next = nullptr;

			Node(const T& data = {}, Node* next = nullptr) : data{data}, next{next}
			{}
		};

		Node* top = nullptr;
		unsigned long long count = 0;

	public:
		Stack()
		{}

		~Stack()
		{
			Delete();
		}

		void Push(const T& data)
		{
			count++;
			Node* node = new Node(data, top);
			top = node;
		}

		constexpr T Pop()
		{
			if(top != nullptr)
			{
				count--;
				T data = top->data;
				Node* node = top;
				top = top->next;
				delete node;
				return data;
			}

			return {};
		}

		constexpr T Top() const
		{
			if(top != nullptr)
			{
				return top->data;
			}

			return {};
		}

		constexpr bool Empty() const
		{
			return top == nullptr;
		}

		constexpr unsigned long long Count() const
		{
			return count;
		}

		void Delete()
		{
			while(top != nullptr)
			{
				count--;
				Node* node = top;
				top = top->next;
				delete node;
			}
		}
	};
}