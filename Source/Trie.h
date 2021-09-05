#pragma once
#include <stdio.h>
#include <string.h>

#define SIZE 256

namespace DataStructures
{
	class Trie
	{
	private:
		struct Node
		{
			bool terminal = false;
			struct Node* chidren[SIZE];
		};

		Node* root = nullptr;

	public:
		Trie()
		{}
		
		~Trie()
		{}
		
		bool Search(char* signedText)
		{
			if(root == nullptr) return false;

			Node* rootPointer = root;
			int length = strlen(signedText);
			unsigned char* text = (unsigned char*)signedText;

			for(int i = 0; i < length; i++)
			{
				if(rootPointer->chidren[text[i]] == nullptr) return false;

				rootPointer = rootPointer->chidren[text[i]];
			}

			return rootPointer->terminal;
		}

		bool Insert(char* signedText)
		{
			if(root == nullptr) root = CreateNode();

			Node* rootPointer = root;
			int length = strlen(signedText);
			unsigned char* text = (unsigned char*)signedText;

			for(int i = 0; i < length; i++)
			{
				if(rootPointer->chidren[text[i]] == nullptr)
				{
					rootPointer->chidren[text[i]] = CreateNode();
				}

				rootPointer = rootPointer->chidren[text[i]];
			}

			if(rootPointer->terminal == true) return false;
			else {rootPointer->terminal = true; return true;}
		}
		
		bool Delete(char* signedText)
		{
			if(root == nullptr) return false;

			bool result = false;
			Node** nodePointer = &root;
			unsigned char* text = (unsigned char*)signedText;
			*nodePointer = Delete(*nodePointer, text, &result);
			
			return result;
		}
		
		void Print()
		{
			if(root == nullptr) {printf("Empty\n"); return;}

			Print(root, nullptr, 0);
		}
		
	private:
		Node* CreateNode()
		{
			Node* node = new Node();

			for(int i = 0; i < SIZE; i++)
			{
				node->chidren[i] = nullptr;
			}

			node->terminal = false;
			
			return node;
		}

		bool NodeTerminal(Node* node)
		{
			if(node == nullptr) return false;

			for(int i = 0; i < SIZE; i++)
			{
				if(node->chidren[i] != nullptr) return true;
			}

			return false;
		}

		Node* Delete(Node* node, unsigned char* text, bool deleted)
		{
			if(node == nullptr) return node;

			if(*text == '\0')
			{
				if(node->terminal == true)
				{
					deleted = true;
					node->terminal = false;

					if(NodeTerminal(node) == false) {delete node; node = nullptr;}
				}

				return node;
			}

			node->chidren[text[0]] = Delete(node->chidren[text[0]], text + 1, deleted);

			if(deleted == true && NodeTerminal(node) == false && node->terminal == false)
			{
				delete node;
				node = nullptr;
			}

			return node;
		}

		void Print(Node* node, unsigned char* prefix, int length)
		{
			unsigned char newPrefix[length + 2];
			memcpy(newPrefix, prefix, length);
			newPrefix[length + 1] = 0;

			if(node->terminal == true) printf("%s\n", prefix);

			for(int i = 0; i < SIZE; i++)
			{
				if(node->chidren[i] != nullptr)
				{
					newPrefix[length] = i;
					Print(node->chidren[i], newPrefix, length + 1);
				}
			}
		}
	};
}