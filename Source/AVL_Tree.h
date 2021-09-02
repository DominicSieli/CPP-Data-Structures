#pragma once

#include <queue>
#include <vector>

namespace Data_Structures
{
	template<typename T>
	class AVL_Tree
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
		AVL_Tree()
		{}

		AVL_Tree(const T& data) : root{new Node(data)}
		{}

		~AVL_Tree()
		{}

		T Min()
		{
			return Min(root);
		}

		T Max()
		{
			return Max(root);
		}

		bool Search(const T& data)
		{
			Node* node = Search(root, data);

			return (node == nullptr) ? false : true;
		}

		std::vector<T> Depth_First_Search_In_Order()
		{
			std::vector<T> vector;
			Traverse_In_Order(root, vector);
			return vector;
		}

		std::vector<T> Depth_First_Search_Pre_Order()
		{
			std::vector<T> vector;
			Traverse_Pre_Order(root, vector);
			return vector;
		}

		std::vector<T> Depth_First_Search_Post_Order()
		{
			std::vector<T> vector;
			Traverse_Post_Order(root, vector);
			return vector;
		}

		std::vector<T> Breadth_First_Search()
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

				if(node->left != nullptr)
				{
					queue.push(node->left);
				}

				if(node->right != nullptr)
				{
					queue.push(node->right);
				}
			}

			return vector;
		}

		void Insert(const T& data)
		{
			root = Insert(root, data);
		}

		void Remove(const T& data)
		{
			root = Remove(root, data);
		}

		T Successor(const T& data)
		{
			Node* node = Search(root, data);
			return node == nullptr ? 0 : Successor(node);
		}

		T Predecessor(const T& data)
		{
			Node* node = Search(root, data);
			return node == nullptr ? 0 : Predecessor(node);
		}

	private:
		int Height(Node* node)
		{
			return node == nullptr ? -1 : node->height;
		}

		Node* Rotate_Left(Node* node)
		{
			Node* balance_node = node->right;
			balance_node->parent = node->parent;
			node->parent = balance_node;
			node->right = balance_node->left;

			if(balance_node->left != nullptr)
			{
				balance_node->left->parent = node;
			}

			balance_node->left = node;
			node->height = std::max(Height(node->left), Height(node->right)) + 1;
			balance_node->height = std::max(Height(balance_node->left), Height(balance_node->right)) + 1;

			return balance_node;
		}

		Node* Rotate_Right(Node* node)
		{
			Node* balance_node = node->left;
			balance_node->parent = node->parent;
			node->parent = balance_node;
			node->left = balance_node->right;

			if(balance_node->right != nullptr)
			{
				balance_node->right->parent = node;
			}

			balance_node->right = node;
			node->height = std::max(Height(node->left), Height(node->right)) + 1;
			balance_node->height = std::max(Height(balance_node->left), Height(balance_node->right)) + 1;

			return balance_node;
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

			int balance = Height(node->left) - Height(node->right);

			if(balance == 2)
			{
				int balance2 = Height(node->left->left) - Height(node->left->right);

				if(balance2 == 1)
				{
					node = Rotate_Right(node);
				}
				else
				{
					node->left = Rotate_Left(node->left);
					node = Rotate_Right(node);
				}
			}
			else if(balance == -2)
			{
				int balance2 = Height(node->right->left) - Height(node->right->right);

				if(balance2 == -1)
				{
					node = Rotate_Left(node);
				}
				else
				{
					node->right = Rotate_Right(node->right);
					node = Rotate_Left(node);
				}

				node->height = std::max(Height(node->left), Height(node->right)) + 1;
			}

			return node;
		}

		Node* Remove(Node* node, const T& data)
		{
			if(node == nullptr)
			{
				return nullptr;
			}

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
				int balance = Height(node->left) - Height(node->right);

				if(balance == 2)
				{
					int balance2 = Height(node->left->left) - Height(node->left->right);

					if(balance2 == 1)
					{
						node = Rotate_Right(node);
					}
					else
					{
						node->left = Rotate_Left(node->left);
						node = Rotate_Right(node);
					}
				}
				else if(balance == -2)
				{
					int balance2 = Height(node->right->left) - Height(node->right->right);

					if(balance2 == -1)
					{
						node = Rotate_Left(node);
					}
					else
					{
						node->right = Rotate_Right(node->right);
						node = Rotate_Left(node);
					}
				}

				node->height = std::max(Height(node->left), Height(node->right)) + 1;
			}

			return node;
		}

		T Min(Node* node)
		{
			if(node == nullptr)
			{
				return {};
			}
			else if(node->left == nullptr)
			{
				return node->data;
			}
			else
			{
				return Min(node->left);
			}

			return {};
		}

		T Max(Node* node)
		{
			if(node == nullptr)
			{
				return {};
			}
			else if(node->right == nullptr)
			{
				return node->data;
			}
			else
			{
				return Max(node->right);
			}

			return {};
		}

		Node* Search(Node* node, const T& data)
		{
			if(node == nullptr)
			{
				return nullptr;
			}
			else if(node->data == data)
			{
				return node;
			}
			else if(node->data < data)
			{
				return Search(node->right, data);
			}
			else if(node->data > data)
			{
				return Search(node->left, data);
			}
			else
			{
				return nullptr;
			}
		}

		T Successor(Node* node)
		{
			if(node->right != nullptr)
			{
				return Min(node->right);
			}
			else
			{
				Node* parent_node = node->parent;
				Node* current_node = node;

				while((parent_node != nullptr) && (current_node == parent_node->right))
				{
					current_node = parent_node;
					parent_node = current_node->parent;
				}

				return parent_node == nullptr ? 0 : parent_node->data;
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
				Node* parent_node = node->parent;
				Node* current_node = node;

				while((parent_node != nullptr) && (current_node == parent_node->left))
				{
					current_node = parent_node;
					parent_node = current_node->parent;
				}

				return parent_node == nullptr ? 0 : parent_node->data;
			}
		}

		void Traverse_Pre_Order(Node* node, std::vector<T>& vector)
		{
			vector.push_back(node->data);

			if(node->left != nullptr)
			{
				Traverse_Pre_Order(node->left, vector);
			}

			if(node->right != nullptr)
			{
				Traverse_Pre_Order(node->right, vector);
			}
		}

		void Traverse_In_Order(Node* node, std::vector<T>& vector)
		{
			if(node->left != nullptr)
			{
				Traverse_In_Order(node->left, vector);
			}

			vector.push_back(node->data);

			if(node->right != nullptr)
			{
				Traverse_In_Order(node->right, vector);
			}
		}

		void Traverse_Post_Order(Node* node, std::vector<T>& vector)
		{
			if(node->left != nullptr)
			{
				Traverse_Post_Order(node->left, vector);
			}

			if(node->right != nullptr)
			{
				Traverse_Post_Order(node->right, vector);
			}

			vector.push_back(node->data);
		}
	};
}