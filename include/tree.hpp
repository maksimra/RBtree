#pragma once

#include <limits.h>
#include <queue>
#include <utility>
#include <vector>

namespace Trees
{
enum NodeColor
{
    RED = 1,
    BLACK = 2
};

template <typename KeyT> class Node
{
  public:
    KeyT key;
    Node *prnt;
    Node *left;
    Node *right;
    size_t capacity;
    NodeColor color = BLACK;

    Node(KeyT key_, size_t capacity_ = 1) : key(key_), capacity(capacity_)
    {
    }
    Node(const Node &rhs)
    {
        key = rhs.key;
        capacity = rhs.capacity;
        color = rhs.color;
    }
};

template <typename KeyT, typename Comp> class SearchTree
{
    inline static Node<KeyT> nil{0, 0};
    Node<KeyT> *root_ = &nil;
    Comp compare;

    size_t get_number_of_smaller(const Node<KeyT> *node) const
    {
        size_t less_than = node->capacity - node->right->capacity;
        int n_space = 0;

        while (node->prnt != &nil)
        {
            if (compare(node->prnt->key, node->key) < 0)
            {
                less_than += node->prnt->capacity - node->prnt->right->capacity;
            }

            node = node->prnt;
        }

        return less_than;
    }

    static void fixup_capacity(Node<KeyT> *node, Node<KeyT> *nil_ptr)
    {
        Node<KeyT> *cur_node = node;
        while (cur_node->prnt != nil_ptr)
        {
            cur_node = cur_node->prnt;
            cur_node->capacity--;
        }
    }

    Node<KeyT> *get_copy_tree(const SearchTree &rhs)
    {
        std::queue<std::pair<Node<KeyT> *, Node<KeyT> *>> queue;
        Node<KeyT> *tmp_root = &nil;
        tmp_root = new Node<KeyT>(*(rhs.root_));
        tmp_root->prnt = &nil;
        queue.push({rhs.root_, tmp_root});

        while (!queue.empty())
        {
            Node<KeyT> *rhs_node = queue.front().first;
            Node<KeyT> *new_node = queue.front().second;
            queue.pop();

            if (rhs_node->left != &nil)
            {
                Node<KeyT> *left_node = new Node<KeyT>(*(rhs_node->left));
                left_node->prnt = new_node;
                new_node->left = left_node;
                queue.push({rhs_node->left, left_node});
            }
            else
            {
                new_node->left = &nil;
            }

            if (rhs_node->right != &nil)
            {
                Node<KeyT> *right_node = new Node<KeyT>(*(rhs_node->right));
                right_node->prnt = new_node;
                new_node->right = right_node;
                queue.push({rhs_node->right, right_node});
            }
            else
            {
                new_node->right = &nil;
            }
        }

        return tmp_root;
    }

    void delete_tree(Node<KeyT> *root)
    {
        if (root_ == &nil)
            return;

        std::queue<Node<KeyT> *> queue;

        queue.push(root);
        while (!queue.empty())
        {
            Node<KeyT> *node = queue.front();
            queue.pop();

            if (node->left != &nil)
                queue.push(node->left);
            if (node->right != &nil)
                queue.push(node->right);

            delete node;
        }
    }

  public:
    SearchTree(Comp compare_) : compare(compare_){};
    SearchTree(const SearchTree &rhs) : compare(rhs.compare)
    {
        if (rhs.root_ == &nil)
            return;

        Node<KeyT> *copy_tree = &nil;

        try
        {
            copy_tree = get_copy_tree(rhs);
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            delete_tree(copy_tree);
            return;
        }
        root_ = copy_tree;
    }

    SearchTree(SearchTree &&rhs) noexcept
              : compare(rhs.compare) 
    {
        root_ = rhs.root_;
        rhs.root_ = &nil;
    }

    SearchTree &operator=(SearchTree &&rhs)
    {
        if (this != &rhs)
        {
            root_ = rhs.root_;
            rhs.root_ = &nil;
        }
        return *this;
    }
    

    SearchTree &operator=(const SearchTree &rhs)
    {
        if (this != &rhs)
        {
            SearchTree temp_tree(rhs);
            std::swap(*this, temp_tree);
        }
        return *this;
    }

    ~SearchTree()
    {
        delete_tree(root_);
    }

    void insert(KeyT key)
    {
        Node<KeyT> *new_node = new Node<KeyT>(key);

        Node<KeyT> *parrent_node = &nil;
        Node<KeyT> *cur_node = root_;

        while (cur_node != &nil)
        {
            if (compare(key, cur_node->key) == 0)
            {
                delete new_node;
                fixup_capacity(cur_node, &nil);
                return;
            }

            parrent_node = cur_node;
            cur_node->capacity++;

            if (compare(key, cur_node->key) < 0)
            {
                cur_node = cur_node->left;
            }
            else
            {
                cur_node = cur_node->right;
            }
        }

        new_node->prnt = parrent_node;

        if (parrent_node == &nil)
        {
            root_ = new_node;
        }
        else if (compare(new_node->key, parrent_node->key) < 0)
            parrent_node->left = new_node;
        else
            parrent_node->right = new_node;

        new_node->left = new_node->right = &nil;
        new_node->color = RED;

        insert_fixup(new_node);
    }

    void insert_fixup(Node<KeyT> *new_node)
    {
        while (new_node->prnt->color == RED)
        {
            if (new_node->prnt == new_node->prnt->prnt->left)
            {
                Node<KeyT> *uncle = new_node->prnt->prnt->right;
                if (uncle->color == RED)
                {
                    new_node->prnt->color = BLACK;
                    uncle->color = BLACK;
                    new_node->prnt->prnt->color = RED;
                    new_node = new_node->prnt->prnt;
                }
                else if (new_node == new_node->prnt->right)
                {
                    new_node = new_node->prnt;
                    left_rotate(new_node);
                }
                else
                {
                    new_node->prnt->color = BLACK;
                    new_node->prnt->prnt->color = RED;
                    right_rotate(new_node->prnt->prnt);
                }
            }
            else
            {
                Node<KeyT> *uncle = new_node->prnt->prnt->left;
                if (uncle->color == RED)
                {
                    new_node->prnt->color = BLACK;
                    uncle->color = BLACK;
                    new_node->prnt->prnt->color = RED;
                    new_node = new_node->prnt->prnt;
                }
                else if (new_node == new_node->prnt->left)
                {
                    new_node = new_node->prnt;
                    right_rotate(new_node);
                }
                else
                {
                    new_node->prnt->color = BLACK;
                    new_node->prnt->prnt->color = RED;
                    left_rotate(new_node->prnt->prnt);
                }
            }
        }
        root_->color = BLACK;
    }

    void left_rotate(Node<KeyT> *node)
    {
        Node<KeyT> *right_node = node->right;

        node->right = right_node->left;

        if (right_node->left != &nil)
        {
            right_node->left->prnt = node;
        }

        right_node->prnt = node->prnt;
        if (node->prnt == &nil)
            root_ = right_node;
        else if (node == node->prnt->left)
            node->prnt->left = right_node;
        else
            node->prnt->right = right_node;

        right_node->left = node;
        node->prnt = right_node;

        node->capacity =
            ((node->right != &nil) ? node->right->capacity : 0) + ((node->left != &nil) ? node->left->capacity : 0) + 1;

        right_node->capacity = ((right_node->right != &nil) ? right_node->right->capacity : 0) +
                               ((right_node->left != &nil) ? right_node->left->capacity : 0) + 1;
    }

    void right_rotate(Node<KeyT> *node)
    {
        Node<KeyT> *left_node = node->left;

        node->left = left_node->right;

        if (left_node->right != &nil)
        {
            left_node->right->prnt = node;
        }

        left_node->prnt = node->prnt;
        if (node->prnt == &nil)
            root_ = left_node;
        else if (node == node->prnt->right)
            node->prnt->right = left_node;
        else
            node->prnt->left = left_node;

        left_node->right = node;
        node->prnt = left_node;

        node->capacity =
            ((node->right != &nil) ? node->right->capacity : 0) + ((node->left != &nil) ? node->left->capacity : 0) + 1;

        left_node->capacity = ((left_node->right != &nil) ? left_node->right->capacity : 0) +
                              ((left_node->left != &nil) ? left_node->left->capacity : 0) + 1;
    }

    Node<KeyT> *lower_bound(KeyT key) const
    {
        Node<KeyT> *node = root_;
        Node<KeyT> *prev_node = node;

        while (node != &nil)
        {
            if (compare(node->key, key) == 0)
                return node;

            prev_node = node;

            if (compare(key, node->key) < 0)
            {
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }

        while (prev_node != &nil && compare(prev_node->key, key) < 0)
        {
            prev_node = prev_node->prnt;
        }

        return prev_node;
    }

    Node<KeyT> *upper_bound(KeyT key) const
    {
        Node<KeyT> *node = root_;
        Node<KeyT> *prev_node = node;

        while (node != &nil)
        {
            if (compare(node->key, key) == 0)
                return node;

            prev_node = node;

            if (compare(key, node->key) < 0)
            {
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }

        while (prev_node != &nil && compare(prev_node->key, key) > 0)
        {
            prev_node = prev_node->prnt;
        }

        return prev_node;
    }

    int distance(Node<KeyT> *first, Node<KeyT> *second) const
    {
        if (first != &nil && second != &nil)
        {
            size_t less_than_first = get_number_of_smaller(first);
            size_t less_than_second = get_number_of_smaller(second);

            return less_than_second - less_than_first;
        }
        return -1;
    }
};
} // namespace Trees
