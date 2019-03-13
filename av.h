#include <new>
#include <iostream>
#include <algorithm>

#ifndef __avl_tree_h__
#define __avl_tree_h__

template<class K, class V>
class avl_tree
{
	struct node;
	struct node
	{
		K key;
		V value;
		node* left;
		node* right;
		int h;
		node(K key, V val): key(key), 
		value(val), left(0), right(0),
		h(1) {};
	};
	node* root;
	int height(const node* n) { return n? n->h : 0; }
	int balance(const node* n) { return height(n->right) - height(n->left); }
	void reheight(node* n) { n->h = std::max(height(n->left), height(n->right)) + 1; }
	node* turn_left(node* n)
	{
		node* new_root = n->right;
		n->right = new_root->left;
		new_root->left = n;
		reheight(n);
		reheight(new_root);
		return new_root;
	}
	node* turn_right(node* n)
	{
		node* new_root = n->left;
		n->left = new_root->right;
		new_root->right = n;
		reheight(n);
		reheight(new_root);
		return new_root;
	}
	node* rebalance(node* n)
	{
		if(!n) return 0;
		reheight(n);
		if(balance(n) == 2)
		{
			if(balance(n->right) < 0)
				n->right = turn_right(n->right);
			return turn_left(n);
		}
		if(balance(n) == -2)
		{
			if(balance(n->left) > 0)
				n->left = turn_left(n->left);
			return turn_right(n);
		}
		return n;
	}
	node* insert(node* n, K key, V value)
	{
		if(!n)
		{
			try { n = new node(key, value); }
			catch(std::bad_alloc&)
			{ 
				std::cerr << "Can't insert element in avl tree" << std::endl;
				exit(1);
			}
			return n;
		}
		if(key < n->key)
			n->left = insert(n->left, key, value);
		else
			n->right = insert(n->right, key, value);
		return rebalance(n);
	}
	node* remove_min(node* n, node* iter)
	{
		if(iter->left)
			iter->left = remove_min(n, iter->left);
		else
		{
			
			node* r = iter->right;
			n->key = iter->key;
			n->value = iter->value;
			delete iter;
			iter = r;
		}
		return rebalance(iter);
	}
	node* remove(node* n, K key)
	{
		if(!n) return 0;
		if(key < n->key)
			n->left = remove(n->left, key);
		else if( n->key < key)
			n->right = remove(n->right, key);
		else
		{
			node *l = n->left, *r = n->right;
			if(!l && !r)
			{
				delete n;
				return 0;
			}
			if(!r)
				return l;
			n->right = remove_min(n, r);
		}
		return rebalance(n);
	}
	node* search(node* n, K key)
	{
		if(!n)
			return 0;
		node* iter;
		for(iter=n; iter; )
		{
			if(key < iter->key)
				iter = iter->left;
			else if(iter->key < key)
				iter = iter->right;
			else
				return iter;
		}
		return 0;
	}
	void tree_delete(node* n)
	{
		if(n->left)
			tree_delete(n->left);
		if(n->right)
			tree_delete(n->right);
		delete n;
	}
public:
	avl_tree(): root(0) {};
	void add(K key, V value) { root = insert(root, key, value); }
	void del(K key){ root = remove(root, key); }
	V* find(K key)
	{ 	node* n = search(root, key);
		if(n) 
			return &(n->value); 
		else 
			return 0; 
	}
	~avl_tree(){ if(root) tree_delete(root); }
};

#endif