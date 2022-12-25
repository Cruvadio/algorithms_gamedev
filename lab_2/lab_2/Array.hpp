#pragma once

#include <cstdlib>
#include <utility>

template <typename T>
class Array final
{
private:
	int size_;
	int capacity_;

	T* pitems_;

public:
	Array();
	Array(int capacity);
	Array(const Array& other);
	Array(Array&& other);
	~Array();

	int insert(const T& value);
	int insert(int index, const T& value);
	void remove(int index);

	Array& operator=(Array other);

	const T& operator[] (int index) const;
	T& operator[] (int index);

	int size() const;
	int capacity() const;

	class Iterator 
	{
		Array* pi_;
		int direction_;
		int index_;
	public:
		const T& get() const;
		void set(const T& value);
		void next();
		bool hasNext() const;
		friend Array;
	};

	class ConstIterator
	{
		Array* pi_;
		int direction_;
		int index_;
	public:
		const T& get() const;
		void next();
		bool hasNext() const;
		friend Array;
	};

	Iterator iterator();
	ConstIterator iterator() const;

	Iterator reverseIterator();
	ConstIterator reverseIterator() const;
};

constexpr int kDefaultArrayCapacity = 8;

template<typename T>
Array<T>::Array() : capacity_ (kDefaultArrayCapacity), size_ (0)
{
	pitems_ = (T*)std::malloc(capacity_ * sizeof(T));
}

template<typename T>
Array<T>::Array(int capacity) : capacity_(capacity), size_(0)
{
	pitems_ = std::malloc(capacity * sizeof(T));
}

template<typename T>
Array<T>::Array(const Array& other): capacity_(other.capacity_), size_(other.size_)
{
	pitems_ = (T*) std::malloc(capacity_ * sizeof(T));
	for (int i = 0; i < size_; ++i)
		new (pitems_ + i) T(other.pitems_[i]);
}

template<typename T>
Array<T>::Array(Array&& other)
{
	capacity_ = other.capacity_;
	size_ = other.size_;
	pitems_ = other.pitems_;
	other.pitems_ = nullptr;
	other.capacity_ = 0;
	other.size_ = 0;
}

template<typename T>
Array<T>::~Array()
{
	for (int i = 0; i < size_; ++i)
	{
		pitems_[i].~T();
	}
	std::free(pitems_);
}

template<typename T>
inline int Array<T>::insert(const T& value)
{
	if (capacity_ < size_ + 1)
	{
		capacity_ *= 2;
		T* p = (T*)std::malloc(capacity_ * sizeof(T));
		for (int i = 0; i < size_; ++i)
		{
			new (p + i) T(std::move(pitems_[i]));
			pitems_[i].~T();
		}
		std::free(pitems_);
		pitems_ = p;
	}

	new (pitems_ + size_) T(value);
	size_++;
	return size_ - 1;
}

template<typename T>
int Array<T>::insert(int index, const T& value)
{
	if (index < 0 || index > size_)
		return -1;

	if (capacity_ < size_ + 1)
	{
		capacity_ *= 2;
		T* p = std::malloc(capacity_ * sizeof(T));
		for (int i = 0; i < index; ++i)
		{
			new (p + i) T(std::move(pitems_[i]));
			pitems_[i].~T();
		}
		new (p + index) T(value);
		for (int i = index; i < size_; ++i)
		{
			new (p + i + 1) T(std::move(pitems_[i]));
			pitems_[i].~T();
		}
		std::free(pitems_);
		pitems_ = p;
	}
	else 
	{
		new (pitems_ + size) pitems_[size_ - 1];
		if (size > index)
		{
			for (int i = size_ - 1; i > index; i--)
			{
				pitems_[i] = std::move(pitems_[i - 1]);
			}
		}
		pitems_[index] = value;

	}
	size_++;
	return index;
}


template<typename T>
void Array<T>::remove(int index)
{
	if (index >= size_ || index < 0 || size_ <= 0)
		return;
	if (index < size_ - 1)
	{
		for (int i = index; i < size_ - 1; ++i)
		{
			pitems_[i] = std::move(pitems_[i + 1]);
		}
	}
	pitems_[size_ - 1].~T();
	size_--;
}

template<typename T>
Array<T>& Array<T>::operator=(Array<T> other)
{
	std::swap(pitems_, other.pitems_);
	std::swap(capacity_, other.capacity_);
	std::swap(size_, other.size_);
	return *this;
}

template<typename T>
const T& Array<T>::operator[](int index) const
{
	return pitems_[index];
}

template<typename T>
T& Array<T>::operator[](int index)
{
	return pitems_[index];
}

template<typename T>
inline int Array<T>::size() const
{
	return size_;
}

template<typename T>
inline int Array<T>::capacity() const
{
	return capacity_;
}

template<typename T>
typename Array<T>::Iterator Array<T>::iterator()
{
	Iterator it;
	it.pi_ = this;
	it.direction_ = 1;
	it.index_ = 0;
	return it;
}

template<typename T>
typename Array<T>::ConstIterator Array<T>::iterator() const
{
	ConstIterator it;
	it.pi_ = this;
	it.direction_ = 1;
	it.index_ = 0;
	return it;
}

template<typename T>
typename Array<T>::Iterator Array<T>::reverseIterator()
{
	Iterator it;
	it.pi_ = this;
	it.direction_ = -1;
	it.index_ = size - 1;
	return it;
}

template<typename T>
typename Array<T>::ConstIterator Array<T>::reverseIterator() const
{
	ConstIterator it;
	it.pi_ = this;
	it.direction_ = -1;
	it.index_ = size - 1;
	return it;
}

template<typename T>
inline const T& Array<T>::Iterator::get() const
{
	return (*pi)[index_];
}

template<typename T>
inline void Array<T>::Iterator::set(const T& value)
{
	(*pi)[index_] = std::move(value);
}

template<typename T>
inline void Array<T>::Iterator::next()
{
	index_ += direction_;
}

template<typename T>
inline bool Array<T>::Iterator::hasNext() const
{
	if (index_ + direction_ > pitems_->size_ || index_ + direction_ < 0)
		return false;
	return true;
}

template<typename T>
inline const T& Array<T>::ConstIterator::get() const
{
	return (*pi_)[index_];
}

template<typename T>
inline void Array<T>::ConstIterator::next()
{
	index_ += direction_;
}

template<typename T>
inline bool Array<T>::ConstIterator::hasNext() const
{
	return (index_ + direction_ < pitems_->size_) && (index_ + direction_ >= 0);
}


