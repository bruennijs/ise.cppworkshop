template <typename T>
struct isPointer
{
	//bool bvalue = true;
	enum : bool 
	{ 
		value = false 
	};
};


// template <typename T>
// struct isPointer<T>
// {
// 	//bool bvalue = true;
// 	enum : bool 
// 	{ 
// 		value = false 
// 	};
// };

template <typename T>
struct isPointer<T*>
{
	//bool bvalue = true;
	enum : bool 
	{ 
		value = true 
	};
};

int main() {
	static_assert(isPointer<int*>::value, "muss ein pointer sein");
	static_assert(isPointer<int>::value, "muss ein pointer sein");
}