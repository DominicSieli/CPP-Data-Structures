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

            Node(const T& data) : data{data}
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

        T Min()
        {
            return Min(root);
        }

        T Max()
        {
            return Max(root);
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

        bool Contains(const T& data)
        {
            Node* node = Pointer(root, data);

            return (node == nullptr) ? false : true;
        }

		void Insert(const T& data)
		{
			root = Insert(root, data);
		}

        void Remove(const T& data)
        {
            root = Remove(root, data);
        }

        void Invert()
		{
			Invert(root);
		}

        T Successor(const T& data)
        {
            Node* node = Pointer(root, data);
			
            return (node == nullptr) ? 0 : Successor(node);
        }

        T Predecessor(const T& data)
        {
            Node* node = Pointer(root, data);
			
            return (node == nullptr) ? 0 : Predecessor(node);
        }

    private:
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

        void Invert(Node* node)
		{
			if(node == nullptr) return;
			
			std::swap(node->left, node->right);
			Invert(node->left);
			Invert(node->right);
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

        Node* Pointer(Node* node, const T& data)
        {
            if(node == nullptr) return nullptr;
            else if(node->data == data) return node;
            else if(node->data < data) return Pointer(node->right, data);
            else if(node->data > data) return Pointer(node->left, data);
            else return nullptr;
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
            else if(node->data > data)
            {
                node->left = Insert(node->left, data);
                node->left->parent = node;
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
            else if(node->right->data == data)
            {
                node->right = Remove(node->right, data);
            }
            else if(node->left->data == data)
            {
                node->left = Remove(node->left, data);
            }

            return node;
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

                return (parent_node == nullptr) ? 0 : parent_node->data;
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

                return (parent_node == nullptr) ? 0 : parent_node->data;
            }
        }
    };
}