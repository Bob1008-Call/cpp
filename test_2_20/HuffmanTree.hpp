#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <assert.h>
using namespace std;
#include <string>
#include <queue>
#include <algorithm>
#include <vector>


//不等长编码：一个字符的编码不能是另一个字符编码的前缀
//1.统计文件中每个字符出现的次数
//2.创建哈夫曼树（带权路径长度最短的二叉树：1.权值越大的节点越靠近根节点，用户提供权值的节点全部都是叶子节点）
//注意：weight--CharInfo--operator;过滤掉出现次数为0的字符--无效的权值--0次数；二叉树森林--每次都要获取最小的权值--小堆--优先级队列；优先级队列默认：大堆--比较器： > 仿函数
//
//3.通过哈夫曼树找每个字符的编码
//4.给每一个字符找一个更短（小于8个比特位）的编码
//将文件指针恢复到文件的起始地址；压缩结果的最后一个字节8个比特位可能不够

//压缩文件的格式：

//源文件后缀      -|
//字符次数的总行数 |-->解压缩需要用到的信息
//每个字符的次数  -|

//压缩数据
//提供一份压缩文件
//获取解压缩大的信息
//还原huffman树
//解压缩

//struct CharInfo
//{
//	char _ch;
//	long long _charCount;
//	string _strCode;
//};

template<class T>
struct HuffmanTreeNode
{
	HuffmanTreeNode()
	{}

	HuffmanTreeNode(const T& weight)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _weight(weight)
	{}

	struct HuffmanTreeNode<T>* _left;
	struct HuffmanTreeNode<T>* _right;
	struct HuffmanTreeNode<T>* _parent;
	T _weight;
};

template <class T>
struct NodeCompare
{
	bool operator()(const  T &n1, const T  &n2) const
	{
		return n1->_weight > n2->_weight;
	}
};

template<class T>
class HuffmanTree
{
public:
	typedef HuffmanTreeNode<T> Node;
public:
	HuffmanTree()
		:_root(nullptr)
	{}

    HuffmanTree(T* array, size_t size, const T& invalid)
	{
		_CreateHuffmanTree(array, size, invalid);
	}

	void _Destroy(Node* root)
	{
		if (root)
		{
			_Destroy(root->_left);
			_Destroy(root->_right);
			delete root;
			root = nullptr;
		}
	}

	~HuffmanTree()
	{
		_Destroy(_root);
	}

	Node* GetRoot()
	{
		return _root;
	}
private:

	void _CreateHuffmanTree(T* array,size_t size,const T&invalid)
	{
		assert(array);

		priority_queue<Node*, vector<Node*>, NodeCompare<Node*>> hp;

		for (size_t i = 0; i < size; i++)
		{
			if (array[i] != invalid )
			{
				hp.push(new HuffmanTreeNode<T>(array[i]));
			}
		}
		if (hp.empty())
		{
			_root = nullptr;
		}
		while (hp.size() > 1)
		{
			Node* left = hp.top();
			hp.pop();
			Node* right = hp.top();
			hp.pop();
			Node* parent = new HuffmanTreeNode<T>(left->_weight + right->_weight);
			parent->_right = right;
			parent->_left = left;
			right->_parent = parent;
			left->_parent = parent;
			hp.push(parent);
		}
		_root = hp.top();
		hp.pop();
	}
private:
	Node* _root;
};
