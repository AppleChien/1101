// xtree internal header

#define red Color::Red
#define black Color::Black
using std::swap;

#ifndef XTREE
#define XTREE

enum class Color { Red, Black }; // colors for link to parent

template< typename Ty >
struct TreeNode
{
	using NodePtr = TreeNode*;
	using value_type = Ty;

	NodePtr    left;   // left subtree, or smallest element if head
	NodePtr    parent; // parent, or root of tree if head
	NodePtr    right;  // right subtree, or largest element if head
	Color      color;  // Red or Black, Black if head
	bool       isNil;  // true only if head (also nil) node
	value_type myval;  // the stored value, unused if head
};

// CLASS TEMPLATE TreeVal
template< typename Ty >
class TreeVal
{
public:
	using NodePtr = TreeNode< Ty >*;

	using value_type = Ty;
	using size_type = size_t;

	TreeVal()
		: myHead(new TreeNode< value_type >),
		mySize(0)
	{
		myHead->left = myHead;
		myHead->parent = myHead;
		myHead->right = myHead;
		myHead->color = Color::Black;
		myHead->isNil = true; //§PÂ_¬O§_¬°header node
	}

	~TreeVal()
	{
		clear(myHead->parent);
		delete myHead;
	}

	// Removes all elements from the set object (which are destroyed)
	void clear(TreeNode< value_type >* node)
	{
		if (!node->isNil) // node is not an external node
		{
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}

	// rebalance for insertion
	void reBalance(TreeNode< value_type >* node)
	{  // node->parent cannot be the root

		// p -> parent, g -> grand, u -> uncle
		TreeNode< value_type >* p = node->parent;
		TreeNode< value_type >* g = p->parent;
		TreeNode< value_type >* u = p == g->left ? g->right : g->left;

		if (p->isNil) { //node is the root, make node black
			node->color = black;
			return;
		}

		if (p->color == black)
			return;

		if (u->color == red) { //LLr, LRr, RLr, RRr
			p->color = u->color = black;
			g->color = red;
			reBalance(g);
		}
		else {
			if (p == g->left) {
				if (node == p->left) {
					LLRotation(p); // rotate right at g
					swap(p->color, g->color); // LLb
				}
				else {
					LRRotation(node); // rotate left at p first, then rotate right at g
					swap(node->color, g->color); // LRb
				}
			}
			else {
				if (node == p->left) {
					RLRotation(node); // rotate right at p first, then rotate left at g
					swap(node->color, g->color); // RLb
				}
				else {
					RRRotation(p); // rotate left at g
					swap(p->color, g->color);  // RRb
				}
			}
		}
	}

	// rotate right at g, where p = g->left and node = p->left
	void LLRotation(TreeNode< value_type >* p)
	{
		TreeNode< value_type >* g = p->parent;

		//connect g and p's right child
		g->left = p->right;
		if (!p->right->isNil) 
			p->right->parent = g;

		//connect g's parent and p
		p->parent = g->parent;
		if (g->parent->isNil) 
			myHead->parent = p;
		else g == g->parent->left ? g->parent->left = p : g->parent->right = p;

		//connect p and g
		p->right = g;
		g->parent = p;
	}

	// LR rotation; p = g->left and node = p->right
	void LRRotation(TreeNode< value_type >* node)
	{
		// LRb rotation
		RRRotation(node); // rotate left at p first
		LLRotation(node); // then rotate right at g
	}

	// RL rotation; p = g->right and node = p->left
	void RLRotation(TreeNode< value_type >* node)
	{
		// RLb rotation
		LLRotation(node); // rotate right at p first
		RRRotation(node); // then rotate left at g
	}

	// rotate left at g, where p = g->right and node = p->right
	void RRRotation(TreeNode< value_type >* p)
	{
		TreeNode< value_type >* g = p->parent;

		//connect g and p's left child
		g->right = p->left;
		if (!p->left->isNil) 
			p->left->parent = g;

		//connect g's parent and p
		p->parent = g->parent;
		if (g->parent->isNil) 
			myHead->parent = p;
		else g == g->parent->left ? g->parent->left = p : g->parent->right = p;

		//connect p and g
		p->left = g;
		g->parent = p;
	}

	// erase node provided that the degree of node is at most one
	void eraseDegreeOne(TreeNode< value_type >* node)
	{
		/*TreeNode< value_type >* p = node->parent;
		TreeNode< value_type >* c = node->left->isNil ? node->right : node->left;

		if (p->isNil && c->color == black){	
			myHead->parent = c;
			c->parent = myHead;
		}
		else{		
			node == p->left ? p->left = c : p->right = c;
			if (!c->isNil) c->parent = p;

			if (node->color == black && c->color == black) fixUp(c, p);
			else if (c->color == red) c->color = black;
		}

		delete node;
		mySize--;*/

		TreeNode< value_type >* M = node;
		TreeNode< value_type >* P = node->parent;
		TreeNode< value_type >* C = node->left->isNil ? node->right : node->left;

		// Simple Case 3 -> M and C are black, and M is the root
		if (M->color == black && C->color == black && P->isNil)
		{   // delete M and make C be the root
			myHead->parent = C;
			C->parent = myHead;
			delete M;
			--mySize;
			return;
		}

		// Simple Case 1 -> M is red or M is a leaf node : delete M and connect P and C

		// connect P and C
		M == P->left ? P->left = C : P->right = C;
		if (!C->isNil) C->parent = P;

		// Complex Case -> M and C are black, and M is not the root : connect P and C, then rebalance
		if (M->color == black && C->color == black && !P->isNil) fixUp(C, P);

		// Simple Case 2 -> M is black, C is red : delete M, connect P and C, and make C black
		if (M->color == black && C->color == red) C->color = black;

		delete M;
		--mySize;

	}

	// rebalance for deletion
	void fixUp(TreeNode< value_type >* N, TreeNode< value_type >* P)
	{
		TreeNode< value_type >* S = N == P->left ? P->right : P->left; // N's sibling

		// Case 1
		if (S->color == red && N == P->left){
		   // Case 1.1 -> S is red and N is P's left child
			swap(P->color, S->color);
			RRRotation(S); // rotate left at P
			// update S, then go to Case 2.1, 3.1, or 4
		}
		if (S->color == red && N == P->right){
		   // Case 1.2 -> S is red and N is P's right child
			swap(P->color, S->color);
			LLRotation(S); // rotate right at P
			// update S, then go to Case 2.2, 3.2, or 4
		}

		// update S
		S = N == P->left ? P->right : P->left;

		// Case 3
		if (S->color == black && S->right->color == black && N == P->left && S->left->color == red){
		   // Case 3.1 -> S and SR are black, N is P's left child, but SL is red
			swap(S->color, S->left->color);
			LLRotation(S->left); // rotate right at S
			// update S, then go to Case 2.1
		}
		if (S->color == black && S->left->color == black && N == P->right && S->right->color == red){
		   // Case 3.2 -> S and SL are black, N is P's right child, but SR is red
			swap(S->color, S->right->color);
			RRRotation(S->right); // rotate left at S
			// update S, then go to Case 2.2
		}

		// update S
		S = N == P->left ? P->right : P->left;

		// Case 2
		if (S->color == black && S->right->color == red && N == P->left){
		   // Case 2.1 -> S is black, SR is red and N is P's left child
			swap(P->color, S->color);
			S->right->color = black;
			RRRotation(S); // rotate left at P
			return;
		}
		if (S->color == black && S->left->color == red && N == P->right){
		   // Case 2.2 -> S is black, SL is red and N is the right child of P
			swap(P->color, S->color);
			S->left->color = black;
			LLRotation(S); // rotate right at P
			return;
		}

		// Case 4 -> S, SR and SL are black, but P is red
		if (S->color == black && S->right->color == black && S->left->color == black && P->color == red){
		   // Just exchange the colors of S and of P
			swap(S->color, P->color);
			return;
		}

		// Case 5 -> S, SR, SL and P are black
		if (S->color == black && S->right->color == black && S->left->color == black && P->color == black){
		
			S->color = red;
			fixUp(P, P->parent);
		}
	}

	NodePtr myHead;   // pointer to head node
	size_type mySize; // number of elements
};

// CLASS TEMPLATE Tree
template< typename Traits >
class Tree // ordered red-black tree for map/multimap/set/multiset
{
public:
	using value_type = typename Traits::value_type;

protected:
	using ScaryVal = TreeVal< value_type >;

public:
	using key_type = typename Traits::key_type;
	using key_compare = typename Traits::key_compare;

	using size_type = size_t;

	Tree(const key_compare& parg)
		: keyCompare(parg),
		scaryVal()
	{
	}

	~Tree()
	{
	}

	// Extends the container by inserting a new element,
	// effectively increasing the container size by one.
	void insert(const value_type& val)
	{
		if (scaryVal.mySize == 0)
		{
			TreeNode< value_type >* root = new TreeNode< value_type >;
			root->myval = val;
			root->left = scaryVal.myHead;
			root->right = scaryVal.myHead;
			root->isNil = false;
			root->parent = scaryVal.myHead;
			root->color = Color::Black;
			scaryVal.myHead->left = root;
			scaryVal.myHead->parent = root;
			scaryVal.myHead->right = root;
			scaryVal.mySize = 1;
		}
		else
		{                           // scaryVal.myHead->parent points to the root
			TreeNode< value_type >* p = scaryVal.myHead->parent;
			TreeNode< value_type >* pp = nullptr;
			while (p != scaryVal.myHead)
			{
				pp = p;
				//              keyCompare.operator()( val, p->myval )
				if (keyCompare(val, p->myval)) // if( val < p->myval )
					p = p->left;
				else if (keyCompare(p->myval, val)) // if( val > p->myval )
					p = p->right;
				else
					return;
			}


			TreeNode<value_type>* temp = new TreeNode<value_type>;
			temp->isNil = 0;
			temp->myval = val;
			temp->right = temp->left = temp->parent = scaryVal.myHead;
			temp->color = red;

			if (keyCompare(val, pp->myval)) {
				pp->left = temp;
				if (keyCompare(temp->myval, scaryVal.myHead->left->myval))
					scaryVal.myHead->left = temp;
			}
			else {
				pp->right = temp;
				if (keyCompare(scaryVal.myHead->right->myval, temp->myval))
					scaryVal.myHead->right = temp;
			}
			temp->parent = pp;
			scaryVal.mySize++;

			scaryVal.reBalance(temp);

		}
	}

	// Removes from the set container a single element whose value is val
	// This effectively reduces the container size by one, which are destroyed.
	// Returns the number of elements erased.
	size_type erase(const key_type& val)
	{
		//TreeNode< value_type >* h = scaryVal.myHead; // reference
		TreeNode< key_type >* p = scaryVal.myHead->parent; // p points to the root
		while (p != scaryVal.myHead && val != p->myval)
		{
			//           keyCompare.operator()( val, p->myval )
			if (keyCompare(val, p->myval)) // if( val < p->myval )
				p = p->left;
			else
				p = p->right;
		}

		if (p == scaryVal.myHead) // not found
			return 0;
		else // found
		{  // deletes the node pointed by p
			// if the node has two children
			if (!p->left->isNil && !p->right->isNil){
			   // let the node's right subtree's leftmost node's val replace node's val
				TreeNode< value_type >* temp = p->right;
				while (!temp->left->isNil) temp = temp->left;
				p->myval = temp->myval;
				p = temp; // delete RL
			}

			// update head's pointers
			/*if (p == h->left) 
				h->left = p->parent;
			if (p == h->right) 
				h->right = p->parent;*/

			scaryVal.eraseDegreeOne(p);

			return 1;

		}
	}

private:
	key_compare keyCompare;
	ScaryVal scaryVal;
};

#endif // XTREE