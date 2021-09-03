#pragma once
#include <queue>
#include <vector>

namespace DataStructures
{
	template<typename T>
	class AVLTree
	{
	private:
		struct Node
		{
			T data {};
			int height = 0;
			Node* left = nullptr;
			Node* right = nullptr;
			Node* parent = nullptr;

			Node(const T& data) : data{data}, height{0}, left{nullptr}, right{nullptr}, parent{nullptr}
			{}
		};

		Node* root = nullptr;

	public:
		AVLTree()
		{}

		AVLTree(const T& data) : root{new Node(data)}
		{}

		~AVLTree()
		{}

		T Min()
		{
			return Min(root);
		}

		T Max()
		{
			return Max(root);
		}

		bool Contains(const T& data)
		{
			Node* node = Search(root, data);
			
			return (node == nullptr) ? false : true;
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
			if(Contains(data) == false) root = Insert(root, data);
		}

		void Remove(const T& data)
		{
			root = Remove(root, data);
		}

		T Successor(const T& data)
		{
			Node* node = Search(root, data);
			
			return (node == nullptr) ? 0 : Successor(node);
		}

		T Predecessor(const T& data)
		{
			Node* node = Search(root, data);
			
			return (node == nullptr) ? 0 : Predecessor(node);
		}

	private:
		int Height(Node* node)
		{
			return (node == nullptr) ? -1 : node->height;
		}

		Node* RotateLeft(Node* node)
		{
			Node* pivot = node->right;
			pivot->parent = node->parent;
			node->parent = pivot;
			node->right = pivot->left;

			if(pivot->left != nullptr) pivot->left->parent = node;

			pivot->left = node;
			node->height = std::max(Height(node->left), Height(node->right)) + 1;
			pivot->height = std::max(Height(pivot->left), Height(pivot->right)) + 1;

			return pivot;
		}

		Node* RotateRight(Node* node)
		{
			Node* pivot = node->left;
			pivot->parent = node->parent;
			node->parent = pivot;
			node->left = pivot->right;

			if(pivot->right != nullptr) pivot->right->parent = node;

			pivot->right = node;
			node->height = std::max(Height(node->left), Height(node->right)) + 1;
			pivot->height = std::max(Height(pivot->left), Height(pivot->right)) + 1;

			return pivot;
		}

		Node* Insert(Node* node, const T& data)
		{
			if(node == nullptr)
			{
				node = new Node(data);
			}
			else if(node->data < data)
			{
				node->right = Insert(node->right, data);
				node->right->parent = node;
			}
			else
			{
				node->left = Insert(node->left, data);
				node->left->parent = node;
			}

			int pivot = Height(node->left) - Height(node->right);

			if(pivot == 2)
			{
				int pivot2 = Height(node->left->left) - Height(node->left->right);

				if(pivot2 == 1)
				{
					node = RotateRight(node);
				}
				else
				{
					node->left = RotateLeft(node->left);
					node = RotateRight(node);
				}
			}
			else if(pivot == -2)
			{
				int pivot2 = Height(node->right->left) - Height(node->right->right);

				if(pivot2 == -1)
				{
					node = RotateLeft(node);
				}
				else
				{
					node->right = RotateRight(node->right);
					node = RotateLeft(node);
				}

				node->height = std::max(Height(node->left), Height(node->right)) + 1;
			}

			return node;
		}

		Node* Remove(Node* node, const T& data)
		{
			if(node == nullptr) return nullptr;

			if(node->data == data)
			{
				if(node->left == nullptr && node->right == nullptr)
				{
					node = nullptr;
				}
				else if(node->left == nullptr && node->right != nullptr)
				{
					node->right->parent = node->parent;
					node = node->right;
				}
				else if(node->left != nullptr && node->right == nullptr)
				{
					node->left->parent = node->parent;
					node = node->left;
				}
				else
				{
					T successor = Successor(data);
					node->data = successor;
					node->right = Remove(node->right, successor);
				}
			}
			else if(node->data < data)
			{
				node->right = Remove(node->right, data);
			}
			else
			{
				node->left = Remove(node->left, data);
			}

			if(node != nullptr)
			{
				int pivot = Height(node->left) - Height(node->right);

				if(pivot == 2)
				{
					int pivot2 = Height(node->left->left) - Height(node->left->right);

					if(pivot2 == 1)
					{
						node = RotateRight(node);
					}
					else
					{
						node->left = RotateLeft(node->left);
						node = RotateRight(node);
					}
				}
				else if(pivot == -2)
				{
					int pivot2 = Height(node->right->left) - Height(node->right->right);

					if(pivot2 == -1)
					{
						node = RotateLeft(node);
					}
					else
					{
						node->right = RotateRight(node->right);
						node = RotateLeft(node);
					}
				}

				node->height = std::max(Height(node->left), Height(node->right)) + 1;
			}

			return node;
		}

		T Min(Node* node)
		{
			if(node == nullptr) return {};
			else if(node->left == nullptr) return node->data;
			else return Min(node->left);
			
			return {};
		}

		T Max(Node* node)
		{
			if(node == nullptr) return {};
			else if(node->right == nullptr) return node->data;
			else return Max(node->right);
			
			return {};
		}

		Node* Search(Node* node, const T& data)
		{
			if(node == nullptr) return nullptr;
			else if(node->data == data) return node;
			else if(node->data < data) return Search(node->right, data);
			else if(node->data > data) return Search(node->left, data);
			else return nullptr;
		}

		T Successor(Node* node)
		{
			if(node->right != nullptr)
			{
				return Min(node->right);
			}
			else
			{
				Node* parent = node->parent;
				Node* current = node;

				while((parent != nullptr) && (current == parent->right))
				{
					current = parent;
					parent = current->parent;
				}

				return (parent == nullptr) ? 0 : parent->data;
			}
		}

		T Predecessor(Node* node)
		{
			if(node->left != nullptr)
			{
				return Max(node->left);
			}
			else
			{
				Node* parent = node->parent;
				Node* current = node;

				while((parent != nullptr) && (current == parent->left))
				{
					current = parent;
					parent = current->parent;
				}

				return (parent == nullptr) ? 0 : parent->data;
			}
		}

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
	};
}