
constexpr int f( int n )
{
	return n*2;
}

enum Status { OFF = f(0), ON };

int main()
{
	int n = f(21);

	return n;
}

