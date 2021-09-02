#pragma once

namespace Data_Structures
{
	template<typename T>
	class Queue
	{
	private:
		struct Node
		{
			T data {};
			Node* next = nullptr;

			Node(const T& data = {}, Node* next = nullptr) : data{data}, next{next}
			{}
		};

	    Node* back = nullptr;
	    Node* front = nullptr;
	    unsigned long long count = 0;

	public:
		Queue()
		{}

		~Queue()
		{
			Delete();
		}

		void Enqueue(const T& data)
		{
			count++;
			Node* node = new Node(data);

			if(back == nullptr || front == nullptr)
			{
				back = node;
				front = node;
			}
			else
			{
				back->next = node;
				back = node;
			}
		}

	    constexpr T Dequeue()
		{
			T data {};

			if(front != nullptr)
			{
				count--;
				Node* node = front;
				data = front->data;
				front = front->next;
				delete node;
			}

			if(front == nullptr)
			{
				back = nullptr;
			}

			return data;
		}

		constexpr T Front() const
		{
			if(front != nullptr)
			{
				return front->data;
			}

			return {};
		}

		constexpr T Back() const
		{
			if(back != nullptr)
			{
				return back->data;
			}

			return {};
		}

		constexpr bool Empty() const
		{
			return front == nullptr;
		}

		constexpr unsigned long long Count() const
		{
			return count;
		}

		void Delete()
		{
			while(front != nullptr)
			{
				count--;
				Node* node = front;
				front = front->next;
				delete node;
			}

			back = nullptr;
			front = nullptr;
		}
	};
}