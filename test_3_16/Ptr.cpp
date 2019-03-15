#include <mutex>
#include <stdio.h>
template<class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr = nullptr)
		:_ptr(ptr)
		, _owner(false)
	{
		if (_ptr)
		{
			_owner = true;
		}
	}

	AutoPtr(const AutoPtr<T>& ap)
		:_ptr(ap._ptr)
		, _owner(ap._owner)
	{
		ap._owner = false;
	}

	AutoPtr<T>& operator=(const AutoPtr<T>& ap)
	{
		if (this != &ap)
		{
			if (_ptr && _owner)
			{
				delete _ptr;
			}

			_ptr = ap._ptr;
			_owner = ap._owner;
			ap._owner = false;
		}
		return *this;
	}

	~AutoPtr()
	{
		if (_ptr && _owner)
		{
			delete _ptr;
			_ptr = nullptr;
			_owner = false;
		}
	}

	T* operator->()
	{
		return _ptr;
	}

	T& operator*()
	{
		return *_ptr;
	}
private:
	T* _ptr;
	mutable bool _owner;
};

void test()
{
	AutoPtr<int> ap1(new int);
	AutoPtr<int> ap2(ap1);

	*ap1 = 10;
	*ap2 = 20;
}
void test1()
{
	AutoPtr<int> ap1(new int);
	AutoPtr<int> ap2(ap1);
	AutoPtr<int> ap3(ap1);

	if (1)
	{
		AutoPtr<int> ap4(ap2);
	}
	*ap1 = 10;
	*ap2 = 20;
}

template<class T>
class UniquePtr
{
public:
	UniquePtr(T* ptr = nullptr)
		:_ptr(ptr)
	{}

	~UniquePtr()
	{
		if (_ptr)
		{
			delete _ptr;
			_ptr = nullptr;
		}
	}

	T* operator->()
	{
		return _ptr;
	}

	T& operator*()
	{
		return *_ptr;
	}

private:
	UniquePtr(const UniquePtr<T>& up);
	UniquePtr<T>& operator=(const UniquePtr<T>&);
private:
	T* _ptr;
};

//共享类型智能指针 +引用计数

template<class T>
struct DFDef
{
	void operator()(T*& pf)
	{
		delete pf;
		pf = nullptr;
	}
};

template<class T>
struct Free
{
	void operator()(T*& p)
	{
		free(p);
		p = nullptr;
	}
};

struct FClose
{
	void operator()(FILE* pf)
	{
		fclose(pf);
		pf = nullptr;
	}
};

template<class T,class DF = DFDef<T>>
class SharePtr
{
public:
	SharePtr(T* ptr = nullptr)
		:_ptr(ptr)
		, _pCount(nullptr)
		, _pMutex(new mutex)
	{
		if (_ptr)
		{
			_pCount = new int(1);
		}
	}

	SharePtr(const SharePtr<T>& sp)
		:_ptr(sp._ptr)
		, _pCount(sp._pCount)
		, _pMutex(sp._pMutex)
	{
		if (_pCount)
			AddRef();
	}

	//1.sp2没有管理资源
	//2.sp2管理资源，但是没有共享--释放资源以及计数
	//3.sp2管理资源，与其他对象共享--计数-1

	//1.sp1没有资源
	//2.sp2有资源
	SharePtr<T>& operator=(const SharePtr<T>& sp)
	{
		if (this != &sp)
		{
			//管理资源，没有共享
			Release();
			//管理资源也共享
			_ptr = sp._ptr;
			_pCount = sp._pCount;
			if (_pCount)
				AddRef();
		}
		return *this;
	}

	~SharePtr()
	{
		Release();
	}

	T* operator->()
	{
		return _ptr;
	}

	T& operator*()
	{
		return *_ptr
	}

	int GetCount()
	{
		assert(_pCount);
		return *_pCount;
	}

private:
	void Release()
	{
		if (_ptr && 0 == SubRef())
		{
			DF()(_ptr);
			delete _pCount;
		}
	}

	void AddRef()
	{
		_pMutex->lock();
		++(*_pCount);
		_pMutex->unlock();
	}

	int SubRef()
	{
		if (_pCount)
		{
			_pMutex->lock();
			--(*_pCount);
			_pMutex->unlock();
		}
		return *_pCount;
	}
private:
	T* _ptr;
	int* _pCount;
	mutex* _pMutex;
};

struct Node
{
	weak_ptr<Node> _pre;
	weak_ptr<Node> _next;

	~Node()
	{
		cout << "~Node" << this << endl;
	}
	int data;
};

void test4()
{
	shared_ptr<Node> Node1(new Node);
	shared_ptr<Node> Node2(new Node);
	Node1->_next = Node2;;
	Node2->_pre = Node1;
	cout << "Node1.use_count" << Node1.use_count() << endl;
	cout << "Node2.use_count" << Node1.use_count() << endl;
}

void test3()
{
	SharePtr<int> sp1(new int);
	SharePtr<int> sp2(sp1);

	SharePtr<int> sp3(new int);
	SharePtr<int> sp4(sp3);

	sp4 = sp2;
	sp3 = sp2;
}
void test2()
{
	UniquePtr<int> up1(new int);
	//UniquePtr<int> up2(up1);//已经将拷贝构造重载设为私有
	UniquePtr<int> up2;
	//up2 = up1;//同样的，已经将赋值运算重载设为私有
}


void test5()
{
	FILE* pf = fopen("1.txt", "w");
	SharePtr<FILE, FClose> sp1(pf);
	SharePtr<int, Free<int>> sp2((int*)malloc(sizeof(int)));
	SharePtr<int> sp3(new int);
}

