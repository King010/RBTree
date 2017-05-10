#pragma once 
#include<iostream>
using namespace std;

enum COLOR{RED,BLACK};

template<class K,class V>
struct RBTreeNode
{
	RBTreeNode*_pLeft;
	RBTreeNode*_pRight;
	RBTreeNode*_pParent;
	K _key;
	V _value;
	COLOR _color;
	RBTreeNode(const K key, const V value,COLOR color=RED)
		:_pLeft(NULL)
		, _pRight(NULL)
		, _pParent(NULL)
		, _key(key)
		, _value(value)
		, _color(color)
	{}
};

template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	
	RBTree()
	{
		_pRoot == NULL;
	}
	RBTree(const K&key, const V&value)
	{}
	bool Insert(const K&key,const V&value)
	{
		if (_pRoot == NULL)
		{
			_pRoot = new Node(key, value,BLACK);
			return true;
		}
		Node*pCur = _pRoot;
		Node*pParent = NULL;
		while (pCur)
		{
			if (pCur->_key > key)
			{
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else if (pCur->_key < key)
			{
				pParent = pCur;
				pCur = pCur->_pRight;
			}
			else
				return false;
		}

		pCur = new Node(key, value);
		if (key<pParent->_key)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;

		pCur->_pParent = pParent;
		while (pParent!=NULL&&pParent != _pRoot&&RED == pParent->_color)
		{
			Node*grandFather = pParent->_pParent;
			if (pParent == grandFather->_pLeft)
			{
				Node*uncle = grandFather->_pRight;
				if (uncle&&uncle->_color == RED)
				{
					grandFather->_color = RED;
					pParent->_color = BLACK;
					uncle->_color = BLACK;
					pCur = grandFather;
					pParent = pCur->_pParent;
				}
				else
				{
					if (pParent->_pRight == pCur)
					{
						RotateLeft(pParent);
						std::swap(pParent, pCur);
					}
					pParent->_color = BLACK;
					grandFather->_color = RED;
					RotateRight(grandFather);
				}
			}
			else
			{
				Node*uncle = grandFather->_pLeft;
				if (uncle&&uncle->_color == RED)
				{
					pParent->_color = BLACK;
					uncle->_color = BLACK;
					grandFather->_color = RED;
					pCur = grandFather;
					pParent = pCur->_pParent;
				}
				else
				{
					if (pCur == pParent->_pLeft)
					{
						RotateRight(pParent);
						std::swap(pCur, pParent);
					}
					grandFather->_color = RED;
					pParent->_color = BLACK;
					RotateLeft(grandFather);
				}
			}
		}
		_pRoot->_color = BLACK;
		return true;
	}

	void InOrder()
	{
		_Inorder(_pRoot);
	}
	bool CheckRBTree()
	{
		if (_pRoot == NULL)
			return true;
		if (_pRoot->_color == RED)
		{
			cout << "违反性质" << endl;
			return false;
		}
		int blackCount = 0;
		Node*pCur = _pRoot;
		while (pCur)
		{
			if (pCur->_color == BLACK)
				blackCount++;
			pCur = pCur->_pLeft;
		}
		int k = 0;
		return _CheckRBTree(_pRoot, blackCount, k);
	}

private:

	bool _CheckRBTree(Node*pRoot, const size_t blackcount, size_t k)
	{
		if (pRoot == NULL)
			return true;
		Node*parent = pRoot->_pParent;
		if (pRoot->_color == BLACK)
			k++;
		if (parent && parent->_color==RED &&parent->_pParent->_color == RED)
		{
			cout << "违反规则相邻结点为红色" << endl;
			return false;
		}
		if (pRoot->_pLeft == NULL&&pRoot->_pRight == NULL)
		{
			if (k != blackcount)
			{
				cout << "黑色结点个数不相等" << endl;
				return false;
			}
		}
		return _CheckRBTree(pRoot->_pLeft, blackcount, k) && _CheckRBTree(pRoot->_pRight, blackcount, k);
	}

	void RotateLeft(Node *parent)
	{
		Node*subR = parent->_pRight;
		Node*subRL = subR->_pLeft;

		parent->_pRight = subRL;
		if (subRL != NULL)
			subRL->_pParent = parent;
		subR->_pLeft = parent;
		subR->_pParent = parent->_pParent;
		Node*ppParent = parent->_pParent;
		parent->_pParent = subR;

		if (ppParent == NULL)
		{
			_pRoot = subR;
			subR->_pParent = NULL;
		}
		else
		{
			if (ppParent->_pLeft == parent)
				ppParent->_pLeft = subR;
			else
				ppParent->_pRight = subR;
			subR->_pParent = ppParent;
		}
		parent = subR;
	}
	void RotateRight(Node *parent)
	{
		Node*subL = parent->_pLeft;
		Node*subLR = subL->_pRight;

		parent->_pLeft = subLR;
		if (subLR != NULL)
			subLR->_pParent = parent;
		subL->_pRight = parent;
		subL->_pParent = parent->_pParent;
		Node*ppParent = parent->_pParent;
		parent->_pParent = subL;

		if (ppParent == NULL)
		{
			_pRoot = subL;
			subL->_pParent = NULL;
		}
		else
		{
			if (ppParent->_pLeft == parent)
				ppParent->_pLeft = subL;
			else
				ppParent->_pRight = subL;
			subL->_pParent = ppParent;
		}
		parent = subL;

	}
	

	void _Inorder(Node*proot)
	{
		if (proot == NULL)
			return;
		_Inorder(proot->_pLeft);
		cout << proot->_key << " ";
		_Inorder(proot->_pRight);
	}
private:
	Node*_pRoot;
};

