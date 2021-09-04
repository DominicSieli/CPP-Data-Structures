#pragma once
#include <list>
#include <string>
#include <initializer_list>

namespace DataStructures
{
    template<typename T, unsigned int S>
    class HashTable
    {
	private:
        std::list<std::pair<std::string, T>> table[S];
		
	public:
		HashTable()
		{}
		
		HashTable(const std::string& key, const T& data)
		{
			Insert(key, data);
		}
		
		HashTable(const std::initializer_list<std::pair<std::string, T>>& list)
		{
			for(auto& pair : list)
			{
				Insert(pair.first, pair.second);
			}
		}
		
		~HashTable()
		{}
		
        void Insert(const std::string& key, const T& data)
        {
            unsigned int hash = HashFunction(key);

            for(auto& pair : table[hash])
            {
				if(pair.first == key) {pair.second = data; return;}
            }
			
			table[hash].emplace_back(key, data);
        }

        T GetData(const std::string& key)
        {
            unsigned int hash = HashFunction(key);

            for(auto& pair : table[hash])
            {
                if(pair.first == key) return pair.second;
            }

            return {};
        }

        void Remove(const std::string& key)
        {
            unsigned int hash = HashFunction(key);
			
            for(auto& pair : table[hash])
            {
                if(pair.first == key) {table[hash].remove(pair); return;}
            }
        }

        bool Empty()
        {
            for(unsigned int i = 0; i < S; i++)
            {
                if(table[i].size() > 0) return false;
            }

            return true;
        }
		
	private:
        unsigned int HashFunction(const std::string& key)
        {
            unsigned int hash = 0;

            for(const char& chr : key)
            {
                hash += (unsigned int)chr;
            }

            return hash % S;
        }
    };
}