#pragma once
#include <initializer_list>

namespace DataStructures
{
	template<typename T>
	class Vector
	{
	private:
	    T* vector = nullptr;
		unsigned long long size = 0;
		unsigned long long count = 0;

	public:
		Vector(const unsigned long long& startSize = 0, const T& data = {})
		{
			size = startSize;
			vector = new T[startSize];
			Fill(data);
		}

		Vector(const std::initializer_list<T>& list) : vector{new T[list.size()]}, size{list.size()}, count{0}
		{
			for(const T& data : list)
			{
				Add(data);
			}
		}

		Vector(const Vector& copy) : vector{new T[copy.size]}, size{copy.size}, count{copy.count}
		{
			for(unsigned long long index = 0; index < size; index++)
			{
				vector[index] = copy[index];
			}
		}

		~Vector()
		{
			delete[] vector;
			vector = nullptr;
		}

		T& operator[](const unsigned long long& index)
		{
			return vector[index];
		}

		constexpr T operator[](const unsigned long long& index) const
		{
			return vector[index];
		}

		void operator=(const std::initializer_list<T>& list)
		{
			Delete();

			for(const T& data : list)
			{
				Add(data);
			}
		}

		constexpr unsigned long long Size() const
		{
			return size;
		}

		constexpr unsigned long long Count() const
		{
			return count;
		}

		void Fill(const T& data)
		{
			count = size;

			for(unsigned long long index = 0; index < size; index++)
			{
				vector[index] = data;
			}
		}

		void Clear()
		{
			count = 0;

			for(unsigned long long index = 0; index < size; index++)
			{
				vector[index] = {};
			}
		}

		void Delete()
		{
			size = 0;
			count = 0;
			delete[] vector;
			vector = nullptr;
		}

		void Trim()
		{
			size = count;

			T* newVector = new T[size];

			for(unsigned long long index = 0; index < count; index++)
			{
				newVector[index] = vector[index];
			}

			delete[] vector;
			vector = newVector;
		}

		void Add(const T& data, const unsigned long long& expansion = 1)
		{
			count++;

			if(count > size)
			{
				size += expansion;
				T* newVector = new T[size];

				for(unsigned long long index = 0; index < count; index++)
				{
					newVector[index] = vector[index];
				}

				delete[] vector;
				vector = newVector;
			}

			vector[count - 1] = data;
		}

		void Remove(const unsigned long long& index)
		{
			if(index >= 0 && index < count)
			{
				count--;
				vector[index] = {};
				std::swap(vector[index], vector[count]);
			}
		}

		void Reverse()
		{
			for(unsigned long long index = 0; index < count / 2; index++)
			{
				std::swap(vector[index], vector[(count - 1) - index]);
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
				if(vector[left] > vector[right]) std::swap(vector[left], vector[right]);

				l = left;
				r = right;

				while(l < right)
				{
					if(vector[l] > vector[l + 1]) std::swap(vector[l], vector[l + 1]);
					if(vector[r] < vector[r - 1]) std::swap(vector[r], vector[r - 1]);

					l++;
					r--;
				}

				left++;
				right--;
			}
		}
	};
}