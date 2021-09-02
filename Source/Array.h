#pragma once
#include <initializer_list>

namespace DataStructures
{
	template<typename T, unsigned long long S>
	class Array
	{
	private:
		T array[S] {};
		unsigned long long count = 0;

	public:
		Array()
		{}

		Array(const T& data)
		{
			Fill(data);
		}

		Array(const std::initializer_list<T>& list)
		{
			for(const T& data : list)
			{
				Add(data);
			}
		}

		~Array()
		{}

		T& operator[](const unsigned long long& index)
		{
			return array[index];
		}

		constexpr T operator[](const unsigned long long& index) const
		{
			return array[index];
		}

		void operator=(const std::initializer_list<T>& list)
		{
			Clear();

			for(const T& data : list)
			{
				Add(data);
			}
		}

		constexpr unsigned long long Size() const
		{
			return S;
		}

		constexpr unsigned long long Count() const
		{
			return count;
		}

		void Fill(const T& data)
		{
			count = S;

			for(unsigned long long index = 0; index < S; index++)
			{
				array[index] = data;
			}
		}

		void Clear()
		{
			count = 0;

			for(unsigned long long index = 0; index < S; index++)
			{
				array[index] = {};
			}
		}

		void Add(const T& data)
		{
			if(count < S)
			{
				count++;
				array[count - 1] = data;
			}
		}

		void Remove(const unsigned long long& index)
		{
			if(index >= 0 && index < count)
			{
				count--;
				array[index] = {};
				std::swap(array[index], array[count]);
			}
		}

		void Reverse()
		{
			for(unsigned long long i = 0; i < count / 2; i++)
			{
				std::swap(array[i], array[(count - 1) - i]);
			}
		}

		void Sort()
		{
			if(count < 2) return;

			unsigned int l = 0;
			unsigned int r = 0;
			unsigned int left = 0;
			unsigned int right = count - 1;

			while(left < right)
			{
				if(array[left] > array[right]) std::swap(array[left], array[right]);

				l = left;
				r = right;

				while(l < right)
				{
					if(array[l] > array[l + 1]) std::swap(array[l], array[l + 1]);
					if(array[r] < array[r - 1]) std::swap(array[r], array[r - 1]);

					l++;
					r--;
				}

				left++;
				right--;
			}
		}
	};
}