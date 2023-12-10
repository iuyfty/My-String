#pragma once

#pragma  warning(disable : 6386)

#include <iostream>


class MyString
{
private:
	size_t size;
	size_t capacity;
	char* string;
public:
	MyString() noexcept
		:
		string(nullptr),
		size(0),
		capacity(0) {}

	MyString(const size_t& _size) 
		try :
		size(_size),
		capacity(_size),
		string(new char[capacity]) 
	{} catch (...) { delete[] string; throw; }
	MyString(const char* other)
	{
		size_t str_size = strlen(other);
		size = str_size;
		capacity = str_size;
		string = nullptr;
		try
		{
			string = new char[str_size];
			for (unsigned int i = 0; i < str_size; ++i)
			{
				string[i] = other[i];
			}
		}
		catch (...)
		{
			delete[] string;
			throw;
		}
	}

	MyString(const MyString& other)
	{
		size = other.size;
		capacity = other.capacity;
		delete[] string;
		try {
			string = new char[capacity];
			for (unsigned int i = 0; i < size; ++i)
			{
				string[i] = other.string[i];
			}
		}
		catch (...)
		{
			delete[] string;
			throw;
		}
	}
	MyString& operator=(const MyString& other)
	{
		capacity = other.capacity;
		size = other.size;
		delete[] string;
		string = new char[capacity];
		for (unsigned int i = 0; i < size; ++i)
		{
			string[i] = other.string[i];
		}
		return *this;
	}
	MyString(MyString&& other) noexcept
	{
		size = other.size;
		capacity = other.capacity;
		delete[] string;
		string = other.string;
		other.string = nullptr;
	}
	MyString& operator=(MyString&& other) noexcept
	{
		size = other.size;
		capacity = other.capacity;
		delete[] string;
		string = other.string;
		other.string = nullptr;
		return *this;
	}
	~MyString()
	{
		delete[] string;
	}
public:
	char& operator[](const size_t& index)
	{
		if (index < 0 || index >= size)
			throw std::out_of_range("out of range");
		return string[index];
	}
	bool operator==(const MyString& other) const
	{
		if (size != other.size)
			return false;
		for (unsigned int i = 0; i < size; ++i)
		{
			if (string[i] != other.string[i])
				return false;
		}
		return true;
	}
	bool operator!=(const MyString& other) const
	{
		return !(*this == other);
	}
	MyString& operator+=(const MyString& other)
	{
		if (capacity >= other.size + size)
		{
			for (unsigned int i = size, j = 0; i < other.size; ++i, ++j)
			{
				string[i] = other.string[j];
			}
			size += other.size;
			return *this;
		}
		MyString new_string(size + other.size);
		for (unsigned int i = 0; i < size; ++i) 
			new_string.string[i] = string[i];
		for (unsigned int i = 0; i < other.size; ++i) 
			new_string.string[size + i] = other.string[i];
		capacity = new_string.capacity;
		size = new_string.size;
		
		delete[] string;
		string = new_string.string;
		new_string.string = nullptr;
	}
	friend std::ostream& operator<<(std::ostream& out, const MyString& string)
	{
		for (unsigned int i = 0; i < string.size; ++i)
		{
			out << string.string[i];
		}
		return out;
	}
public:
	size_t get_size()
	{
		return size;
	}
	size_t get_capacity()
	{
		return capacity;
	}
	void set_string(const char* other)
	{
		size_t size_len = strlen(other);
		if (size_len <= capacity)
		{
			for (unsigned int i = 0; i < size_len; ++i)
			{
				string[i] = other[i];
			}
			size = size_len;
			return;
		}
		MyString new_string(size_len + 10);
		new_string.size = size_len;
		for (unsigned int i = 0; i < size_len; ++i)
		{
			new_string.string[i] = other[i];
		}
		delete[] string;
		size = new_string.size;
		capacity = new_string.capacity;
		string = new_string.string;
		new_string.string = nullptr;
	}
	void resize(const size_t& new_size)
	{
		if (new_size < 0 || new_size >= size)
			throw std::out_of_range("out of range");
		size = new_size;
	}
	void shrink_to_fit()
	{
		if (size == capacity)
			return;
		MyString new_string(size);
		for (unsigned int i = 0; i < size; ++i)
		{
			new_string.string[i] = string[i];
		}
		capacity = new_string.capacity;
		size = new_string.size;
		delete[] string;
		string = new_string.string;
		new_string.string = nullptr;
	}
	bool empty() noexcept
	{
		return size == 0;
	}
	void erase(const size_t& index)
	{
		if (size == 0)
			throw std::out_of_range("Can't erase, arr empty!");
		if(index < 0 || index >= size)
			throw std::out_of_range("out of range");
		for (unsigned int i = index; i < size - 1; ++i)
		{
			std::swap(string[i], string[i + 1]);
		}
		size--;
	}
	void pop_back()
	{
		if (size == 0)
			return; // nothing
		size--;
	}
	void push_back(const char& ch)
	{
		if (size + 1 <= capacity)
		{
			string[size++] = ch;
			return;
		}
		MyString new_vector(capacity + 20); // add some capacity
		new_vector.size = capacity + 1;
		for (unsigned int i = 0; i < size; ++i)
		{
			new_vector.string[i] = string[i];
		}
		new_vector.string[new_vector.size - 1] = ch;
		capacity = new_vector.capacity;
		size = new_vector.size;
		delete[] string;
		string = new_vector.string;
		new_vector.string = nullptr;
	}
	void insert(const char& ch, const size_t& index)
	{
		if (index >= size || index < 0)
			throw std::out_of_range("out of range");
		if (size + 1 <= capacity)
		{
			for (unsigned int i = size; i >= 0; --i)
			{
				if (i == index)
				{
					string[i] = ch;
					size++;
					return;
				}
				std::swap(string[i], string[i - 1]);
			}
		}
		MyString new_string(capacity + 20); // add some capacity
		new_string.size = capacity + 1;
		for (unsigned int i = 0, j = 0; i < size; ++i, ++j)
		{
			if (index == i)
			{
				new_string.string[j] = ch;
				j++;
			}	
			new_string.string[j] = string[i];
		}
		capacity = new_string.capacity;
		size = new_string.size;
		delete[] string;
		string = new_string.string;
		new_string.string = nullptr;
	}
	void slice(const size_t& start, const size_t& end)
	{
		if (start < 0 || start >= size)
			throw std::out_of_range("out of range");
		if (end < 0 || end >= size)
			throw std::out_of_range("out of range");
		if (start >= end)
			throw std::out_of_range("start > end");
		for (unsigned int i = start, j = 0; i < end; ++i, ++j)
		{
			string[j] = string[i];
		}
		size = end - start;
	}
	void clear()
	{
		size = 0;
	}
};