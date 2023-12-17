#pragma once
#include <iostream>

#define MAX_STACK_SIZE 1000
#define EXP_COEF 1.5

template <class T>
class TStack {
private:
    T* begin;
    size_t size;
    T* end;

public:
    explicit TStack(size_t _n = 2);
    TStack(const TStack<T>& stack);
    TStack(TStack<T>&& stack) noexcept;

    ~TStack() { delete[] begin; }

    T& Top();
    const T& Top() const;

    void Pop();
    void Push(const T& el);

    size_t Size() const noexcept;
    bool IsEmpty() const noexcept;

    TStack& operator= (TStack<T>&& stack) noexcept;
    bool operator== (const TStack<T>& stack) const;
    bool operator!= (const TStack<T>& stack) const;
};


template<class T>
TStack<T>::TStack(size_t _n)
{
	if ((_n < 1) || (_n > MAX_STACK_SIZE))
	{
		throw std::exception("wrong size");
	}
	size = _n;
	begin = new T[size];
	end = begin;
}

template<class T>
TStack<T>::TStack(const TStack<T>& a)
{
	size = a.size;
	begin = new T[size];
	for (int i = 0; a.begin + i < a.end; i++)
	{
		begin[i] = a.begin[i];
	}
	end = begin + (a.end - a.begin);
}


template<class T>
void TStack<T>::Push(const T& el)
{
	if (end - begin >= size)
	{
		size_t oldSize = size;
		size = size_t(size * EXP_COEF);
		T* tmp = new T[size];
		for (int i = 0; i < oldSize; i++)
		{
			tmp[i] = begin[i];
		}
		delete[] begin;
		end = tmp + (end - begin);
		begin = tmp;
	}
	*end = el;
	end++;
}

template<class T>
T& TStack<T>::Top() 
{
	if (end == begin)
	{
		throw std::exception("Stack is empty");
	}
	return *(end - 1);
}


template<class T>
bool TStack<T>::operator==(const TStack<T>& a) const
{
	if ((end - begin) != (a.end - a.begin))
	{
		return false;
	}
	for (int i = 0; i < end - begin; i++)
	{
		if (begin[i] != a.begin[i])
		{
			return false;
		}
	}
	return true;
}

template<class T>
inline TStack<T>::TStack(TStack<T>&& stack) noexcept {
	begin = stack.begin;
	stack.begin = nullptr;
	size = stack.size;
	end = stack.end;
}

template<class T>
inline TStack<T>& TStack<T>::operator=(TStack<T>&& stack) noexcept {
	std::swap(begin, stack.begin);
	size = stack.size;
	end = stack.end;
	return *this;
}

template<class T>
inline size_t TStack<T>::Size() const noexcept {
	return size;
}

template<class T>
inline bool TStack<T>::IsEmpty() const noexcept {
	return end == begin;
}

template<class T>
void TStack<T>::Pop()
{
	if (end == begin)
	{
		throw std::exception("Stack is empty");
	}
	end--;
}

template<class T>
inline bool TStack<T>::operator!=(const TStack<T>& stack) const {
	return !(*this == stack);
}