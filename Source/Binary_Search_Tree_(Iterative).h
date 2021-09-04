#pragma once
#include <queue>
#include <vector>

namespace DataStructures
{
	template<typename T>
	class BinarySearchTree
	{
	private:
		struct Node
		{
			T data {};
			Node* left = nullptr;
			Node* right = nullptr;
			Node* parent = nullptr;

			Node(const T& data) : data{data}, left{nullptr}, right{nullptr}, parent{nullptr}
			{}
		};

		Node* root = nullptr;

	public:
		BinarySearchTree()
		{}

		BinarySearchTree(const T& data) : root{new Node(data)}
        {}

		~BinarySearchTree()
		{}

		bool Contains(const T& data)
		{
			return Pointer(data);
		}

		std::vector<T> DepthFirstSearchInOrder()
		{
			std::vector<T> vector;
			TraverseInOrder(root, vector);
			
			return vector;
		}

		std::vector<T> DepthFirstSearchPreOrder()
		{
			std::vector<T> vector;
			TraversePreOrder(root, vector);
			
			return vector;
		}

		std::vector<T> DepthFirstSearchPostOrder()
		{
			std::vector<T> vector;
			TraversePostOrder(root, vector);
			
			return vector;
		}

		std::vector<T> BreadthFirstSearch()
		{
			Node* node = root;
			std::vector<T> vector;
			std::queue<Node*> queue;
			queue.push(node);

			while(queue.size() > 0)
			{
				node = queue.front();
				queue.pop();
				vector.push_back(node->data);

				if(node->left != nullptr) queue.push(node->left);
				if(node->right != nullptr) queue.push(node->right);
			}

			return vector;
		}

		void Insert(const T& data)
		{
			if(Contains(data) == true) return;

			Node* pointer = root;
			Node* node = new Node(data);

			while(true)
			{
				if(root == nullptr) {root = node; return;}

				if(data < pointer->data)
				{
					if(pointer->left != nullptr)
					{
						pointer = pointer->left;
					}
					else if(pointer->left == nullptr)
					{
						pointer->left = node;
						node->parent = pointer;
						
						return;
					}
				}
				else if(data > pointer->data)
				{
					if(pointer->right != nullptr)
					{
						pointer = pointer->right;
					}
					else if(pointer->right == nullptr)
					{
						pointer->right = node;
						node->parent = pointer;
						
						return;
					}
				}
			}
		}

		void Remove(const T& data)
		{
			Node* node = Pointer(data);

			if(node == nullptr) return;

			Node* successor = Successor(node);

			if(node == root)
			{
				root = successor;
			}
			else if(node != root)
			{
				if(node == node->parent->left)
				{
					node->parent->left = successor;
				}
				else if(node == node->parent->right)
				{
					node->parent->right = successor;
				}
			}

			if(successor != nullptr)
			{
				if(successor == node->left)
				{
					successor->right = node->right;

					if(node->right != nullptr)
					{
						node->right->parent = successor;
					}
				}
				else if(successor == node->right)
				{
					successor->left = node->left;

					if(node->left != nullptr)
					{
						node->left->parent = successor;
					}
				}
				else if(successor != node->left && successor != node->right)
				{
					if(successor->right != nullptr)
					{
						successor->parent->left = successor->right;
					}

					successor->right = node->right;
				}

				successor->parent = node->parent;
			}

			delete node;
		}

		void Invert()
		{
			if(root == nullptr) return;

			std::queue<Node*> que;
			que.push(root);

			while(que.empty() == false)
			{
				Node* node = que.front();
				que.pop();
				std::swap(node->left, node->right);
				
				if(node->left) que.push(node->left);
				if(node->right) que.push(node->right);
			}
		}

	private:
		void TraversePreOrder(Node* node, std::vector<T>& vector)
		{
			vector.push_back(node->data);

			if(node->left != nullptr) TraversePreOrder(node->left, vector);
			if(node->right != nullptr) TraversePreOrder(node->right, vector);
		}

		void TraverseInOrder(Node* node, std::vector<T>& vector)
		{
			if(node->left != nullptr) TraverseInOrder(node->left, vector);

			vector.push_back(node->data);

			if(node->right != nullptr) TraverseInOrder(node->right, vector);
		}

		void TraversePostOrder(Node* node, std::vector<T>& vector)
		{
			if(node->left != nullptr) TraversePostOrder(node->left, vector);
			if(node->right != nullptr) TraversePostOrder(node->right, vector);

			vector.push_back(node->data);
		}

		Node* Pointer(const T& data)
		{
			if(root == nullptr) return nullptr;

			Node* node = root;

			while(true)
			{
				if(node->data == data)
				{
					return node;
				}
				else
				{
					if(data < node->data)
					{
						if(node->left == nullptr)
						{
							return nullptr;
						}
						else
						{
							node = node->left;
							
							continue;
						}
					}
					else if(data > node->data)
					{
						if(node->right == nullptr)
						{
							return nullptr;
						}
						else
						{
							node = node->right;
							
							continue;
						}
					}
				}
			}
		}

		Node* Successor(const Node* node)
		{
			if(node->left == nullptr && node->right == nullptr)
			{
				return nullptr;
			}
			else if(node->left != nullptr && node->right == nullptr)
			{
				return node->left;
			}
			else if(node->right != nullptr && node->right->left == nullptr)
			{
				return node->right;
			}
			else if(node->right != nullptr && node->right->left != nullptr)
			{
				Node* successor = node->right->left;

				while(successor->left != nullptr)
				{
					successor = successor->left;
					
					return successor;
				}
			}

			return nullptr;
		}
	};
}