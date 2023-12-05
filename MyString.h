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
	MyString()
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
		this->size = str_size;
		this->capacity = str_size;
		try
		{
			this->string = new char[str_size];
			for (unsigned int i = 0; i < str_size; ++i)
			{
				this->string[i] = other[i];
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
		this->size = other.size;
		this->capacity = other.capacity;
		delete[] this->string;
		try {
			this->string = new char[this->capacity];
			for (unsigned int i = 0; i < this->size; ++i)
			{
				this->string[i] = other.string[i];
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
		this->capacity = other.capacity;
		this->size = other.size;
		delete[] this->string;
		this->string = new char[this->capacity];
		for (unsigned int i = 0; i < this->size; ++i)
		{
			this->string[i] = other.string[i];
		}
		return *this;
	}
	MyString(MyString&& other) noexcept
	{
		this->size = other.size;
		this->capacity = other.capacity;
		delete[] this->string;
		this->string = other.string;
		other.string = nullptr;
	}
	MyString& operator=(MyString&& other) noexcept
	{
		this->size = other.size;
		this->capacity = other.capacity;
		delete[] this->string;
		this->string = other.string;
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
		if (index < 0 || index >= this->size)
			throw std::out_of_range("out of range");
		return this->string[index];
	}
	bool operator==(const MyString& other) const
	{
		if (this->size != other.size)
			return false;
		for (unsigned int i = 0; i < this->size; ++i)
		{
			if (this->string[i] != other.string[i])
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
		if (this->capacity <= other.size + this->size)
		{
			for (unsigned int i = this->size, j = 0; i < other.size; ++i, ++j)
			{
				this->string[i] = other.string[j];
			}
			this->size += other.size;
			return *this;
		}
		MyString new_string(this->size + other.size);
		for (unsigned int i = 0; i < this->size; ++i) 
			new_string.string[i] = this->string[i];
		for (unsigned int i = 0; i < other.size; ++i) 
			new_string.string[this->size + i] = other.string[i];
		this->capacity = new_string.capacity;
		this->size = new_string.size;
		
		delete[] this->string;
		this->string = new_string.string;
		new_string.string = nullptr;
	}
	friend std::ostream& operator<<(std::ostream& out, const MyString& string)
	{
		for (unsigned int i = 0; i < string.size; ++i)
		{
			out << string.string[i];
		}
		out << '\0';
		return out;
	}
public:
	size_t get_size()
	{
		return this->size;
	}
	size_t get_capacity()
	{
		return this->capacity;
	}
	void set_string(const char* other)
	{
		size_t size_len = strlen(other);
		if (size_len <= this->capacity)
		{
			for (unsigned int i = 0; i < size_len; ++i)
			{
				this->string[i] = other[i];
			}
			this->size = size_len;
			return;
		}
		MyString new_string(size_len + 10);
		new_string.size = size_len;
		for (unsigned int i = 0; i < size_len; ++i)
		{
			new_string.string[i] = other[i];
		}
		delete[] this->string;
		this->size = new_string.size;
		this->capacity = new_string.capacity;
		this->string = new_string.string;
		new_string.string = nullptr;
	}
	void set_size(const size_t& new_size)
	{
		if (new_size < 0 || new_size >= this->size)
			throw std::out_of_range("out of range");
		this->size = new_size;
	}
	void shrink_to_fit()
	{
		if (this->size == this->capacity)
			return;
		MyString new_string(this->size);
		for (unsigned int i = 0; i < this->size; ++i)
		{
			new_string.string[i] = this->string[i];
		}
		this->capacity = new_string.capacity;
		this->size = new_string.size;
		delete[] this->string;
		this->string = new_string.string;
		new_string.string = nullptr;
	}
	bool empty() noexcept
	{
		return this->size == 0;
	}
	void erase(const size_t& index)
	{
		if (this->size == 0)
			throw std::out_of_range("Can't erase, arr empty!");
		if(index < 0 || index >= this->size)
			throw std::out_of_range("out of range");
		for (unsigned int i = index; i < this->size - 1; ++i)
		{
			std::swap(this->string[i], this->string[i + 1]);
		}
		this->size--;
	}
	void pop_back()
	{
		if (this->size == 0)
			return; // nothing
		this->size--;
	}
	void push_back(const char& ch)
	{
		if (this->size + 1 <= this->capacity)
		{
			this->string[this->size++] = ch;
			return;
		}
		MyString new_vector(this->capacity + 20); // add some capacity
		new_vector.size = this->capacity + 1;
		for (unsigned int i = 0; i < this->size; ++i)
		{
			new_vector.string[i] = this->string[i];
		}
		new_vector.string[new_vector.size - 1] = ch;
		this->capacity = new_vector.capacity;
		this->size = new_vector.size;
		delete[] this->string;
		this->string = new_vector.string;
		new_vector.string = nullptr;
	}
	void insert(const char& ch, const size_t& index)
	{
		if (index >= this->size || index < 0)
			throw std::out_of_range("out of range");
		if (this->size + 1 <= this->capacity)
		{
			for (unsigned int i = this->size; i != 0; ++i)
			{
				if (i == index)
				{
					this->string[i] = ch;
					this->size++;
					return;
				}
				else
				{
					std::swap(this->string[i], this->string[i + 1]);
				}
			}
		}
		MyString new_string(this->capacity + 20); // add some capacity
		new_string.size = this->capacity + 1;
		for (unsigned int i = 0, j = 0; i < this->size; ++i, ++j)
		{
			if (index == i)
			{
				new_string.string[j] = ch;
				j++;
				new_string.string[j] = this->string[i];
			}
			else
			{
				new_string.string[j] = this->string[i];
			}
		}
		this->capacity = new_string.capacity;
		this->size = new_string.size;
		delete[] this->string;
		this->string = new_string.string;
		new_string.string = nullptr;
	}
	void slice(const size_t& start, const size_t& end)
	{
		for (unsigned int i = start, j = 0; start != end; ++i, ++j)
		{
			this->string[j] = this->string[i];
		}
		this->size = end - start;
	}
	void clear()
	{
		this->size = 0;
	}
	bool empty() const
	{
		return this->size == 0;
	}
};