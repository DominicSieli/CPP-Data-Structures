#pragma once

namespace Data_Structures
{
	template<typename T>
	class Deque
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

	    Node* back = nullptr;
	    Node* front = nullptr;
	    unsigned long long count = 0;

	public:
		Deque()
		{}

		~Deque()
		{
			Delete();
		}

		void Enqueue_Back(const T& data)
		{
			count++;
			Node* node = new Node(data, nullptr, back);

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

		void Enqueue_Front(const T& data)
		{
			count++;
			Node* node = new Node(data, front, nullptr);

			if(back == nullptr || front == nullptr)
			{
				back = node;
				front = node;
			}
			else
			{
				front->previous = node;
				front = node;
			}
		}

		constexpr T Dequeue_Back()
		{
			T data {};

			if(back != nullptr)
			{
				count--;
				Node* node = back;
				data = back->data;
				back = back->previous;
				delete node;
			}

			if(back == nullptr)
			{
				front = nullptr;
			}

			return data;
		}

	    constexpr T Dequeue_Front()
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