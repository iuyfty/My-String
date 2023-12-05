#pragma once

#pragma  warning(disable : 6386)



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
		:
		size(_size),
		capacity(_size + 20),
		string(new char[capacity]) {}

	MyString(const MyString& other)
	{
		this->size = other.size;
		this->capacity = other.capacity;
		delete[] this->string;
		this->string = new char[this->capacity];
		for (unsigned int i = 0; i < this->size; ++i)
		{
			this->string[i] = other.string[i];
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
		new_string = size_len;
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
};
