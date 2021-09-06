#pragma once
#include <vector>
#include <string>
#include <initializer_list>

#define SIZE 256

namespace DataStructures
{
	class Trie
	{
	private:
		struct Node
		{
			bool terminal = false;
			Node* children[SIZE] = {nullptr};
		};

		Node* root = nullptr;

	public:
		Trie()
		{}
		
		Trie(const std::initializer_list<std::string>& list)
		{
			for(const std::string& text : list)
			{
				Insert(text);
			}
		}
		
		~Trie()
		{}
		
		void Insert(const std::string& text)
		{
			if(root == nullptr) root = new Node();

			Node* node = root;

			for(unsigned int i = 0; i < text.length(); i++)
			{
				unsigned char index = (unsigned char)text[i];
				
				if(node->children[index] == nullptr)
				{
					node->children[index] = new Node();
				}

				node = node->children[index];
				node->terminal = true;
			}
		}
		
		bool Contains(const std::string& text)
		{
			if(root == nullptr) return false;

			Node* node = root;
			
			for(unsigned int i = 0; i < text.length(); i++)
			{
				unsigned char index = (unsigned char)text[i];
				
				if(node->children[index] == nullptr) return false;

				node = node->children[index];
			}

			return (node->terminal);
		}
	};
}