// xtree internal header

#ifndef XTREE
#define XTREE

using std::swap;
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
		myHead->isNil = true;
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
		TreeNode<value_type>* p = node->parent;
		TreeNode<value_type>* g = p->parent;
		TreeNode<value_type>* u = (p == g->left) ? g->right : g->left;

		if (p->isNil) { node->color = Color::Black; return; } 

		if (p->color == Color::Black) return; 

		else {
			if (u->color == Color::Red) {
				p->color = u->color = Color::Black;
				g->color = Color::Red;
				reBalance(g);
			}
			else {
				if (p == g->left)swap(p->color, g->color), LLRotation(p);
				else swap(p->color, g->color), RRRotation(p);
			}
		}

	}

	// rotate right at g, where p = g->left and node = p->left
	//void set< Kty >::LLbRotation( TreeNode< value_type > *node )
	void LLRotation(TreeNode< value_type >* p)
	{
		TreeNode<value_type>* g = p->parent;

		g->left = p->right;
		if (!p->right->isNil)p->right->parent = g;

		p->parent = g->parent;
		if (g->parent->isNil)myHead->parent = p;
		else (g == g->parent->left) ? g->parent->left = p : g->parent->right = p;

		p->right = g;
		g->parent = p;

	}

	// rotate left at g, where p = g->right and node = p->right
	//void set< Kty >::RRbRotation( TreeNode< value_type > *node )
	void RRRotation(TreeNode< value_type >* p)
	{
		TreeNode<value_type>* g = p->parent;

		g->right = p->left;
		if (!p->left->isNil)p->left->parent = g;

		p->parent = g->parent;
		if (g->parent->isNil)myHead->parent = p;
		else (g == g->parent->left) ? g->parent->left = p : g->parent->right = p;

		p->left = g;
		g->parent = p;

	}

	// erase node provided that the degree of node is at most one
	void eraseDegreeOne(TreeNode< value_type >* node)
	{
		TreeNode<value_type>* p = node->parent;
		TreeNode<value_type>* c = (node->left->isNil) ? node->right : node->left;

		if (p->isNil && c->color == Color::Black) {
			myHead->parent = c;
			c->parent = myHead;
		}
		else {
			(node == p->left) ? p->left = c : p->right = c;
			if (!c->isNil)c->parent = p;

			if (node->color == Color::Black && c->color == Color::Black)fixUp(c, p);
			else if (c->color == Color::Red)c->color = Color::Black;

		}
		mySize--;
		delete node;

	}

	// rebalance for deletion
	void fixUp(TreeNode< value_type >* N, TreeNode< value_type >* P)
	{
		TreeNode<value_type>* s = (N == P->left) ? P->right : P->left;
		if (s->color == Color::Black && s->right->color == Color::Red && N == P->left) {
			swap(P->color, s->color);
			s->right->color = Color::Black;
			RRRotation(s);
		}
		else if (s->color == Color::Black && s->left->color == Color::Red && N == P->right) {
			swap(P->color, s->color);
			s->left->color = Color::Black;
			LLRotation(s);
		}
		else if (s->color == Color::Black && s->right->color == Color::Black && s->left->color == Color::Black)
		{
			if (P->color == Color::Red) swap(s->color, P->color); 
			else s->color = Color::Red, fixUp(P, P->parent); 
		}

	}
	/*
	   // preorder traversal and inorder traversal
	   void twoTraversals()
	   {
		  cout << "Preorder sequence:\n";
		  preorder( myHead->parent );

		  cout << "\nInorder sequence:\n";
		  inorder( myHead->parent );
		  cout << endl;
	   }

	   // preorder traversal
	   void preorder( TreeNode< value_type > *node )
	   {
		  if( node != myHead )
		  {
			 cout << setw( 5 ) << node->myval << ( node->color == Color::Red ? "R" : "B" );
			 preorder( node->left );
			 preorder( node->right );
		  }
	   }

	   // inorder traversal
	   void inorder( TreeNode< value_type > *node )
	   {
		  if( node != myHead )
		  {
			 inorder( node->left );
			 cout << setw( 5 ) << node->myval << ( node->color == Color::Red ? "R" : "B" );
			 inorder( node->right );
		  }
	   }
	*/
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
		{                              // scaryVal.myHead->parent points to the root
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

			p = new TreeNode< value_type >;
			p->myval = val;
			p->left = scaryVal.myHead;
			p->right = scaryVal.myHead;
			p->isNil = false;
			p->parent = pp;
			p->color = Color::Red;
			scaryVal.mySize++;
			//           keyCompare.operator()( val, pp->myval )
			if (keyCompare(val, pp->myval)) // if( val < pp->myval )
				pp->left = p;
			else
				pp->right = p;

			//       if( scaryVal.myHead->left->myval > val )
			if (keyCompare(val, scaryVal.myHead->left->myval))
				scaryVal.myHead->left = p;
			//       if( scaryVal.myHead->right->myval < val )
			if (keyCompare(scaryVal.myHead->right->myval, val))
				scaryVal.myHead->right = p;

			if (pp->color == Color::Red) // pp cannot be the root
				scaryVal.reBalance(p);
		}
	}

	// Removes from the set container a single element whose value is val
	// This effectively reduces the container size by one, which are destroyed.
	// Returns the number of elements erased.
	size_type erase(const key_type& val)
	{
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
		{  // deletes the p pointed by p
			if (p->left == scaryVal.myHead || p->right == scaryVal.myHead)
				scaryVal.eraseDegreeOne(p);
			else
			{  // find the the p with smallest key in the right subtree of p
				TreeNode< key_type >* rightSubtreeMin = p->right;
				while (rightSubtreeMin->left != scaryVal.myHead)
					rightSubtreeMin = rightSubtreeMin->left;
				p->myval = rightSubtreeMin->myval;
				scaryVal.eraseDegreeOne(rightSubtreeMin);
			}

			return 1;
		}
	}

private:
	key_compare keyCompare;
	ScaryVal scaryVal;
};

#endif // XTREE