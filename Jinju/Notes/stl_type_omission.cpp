#include <iterator>
#include <array>
#include <vector>
#include <string_view>
#include <iostream>
using namespace std;

template<typename container>
void print(string_view name, const container& c)
{
	cout << name << " = { ";
	for(auto i = cbegin(c); i != cend(c); ++i)
		cout << *i << ' ';
	cout << "}\n";
}

// Possible implementations for begin() and end()
template<typename type, size_t size>
auto my_begin(type (&c)[size]) -> type*
{
	return c;
}
template<typename type>
auto my_begin(type& c)
{
	return c.begin();
}
template<typename type, size_t size>
auto my_end(type (&c)[size]) -> type*
{
	return c + size;
}
template<typename type>
auto my_end(type& c)
{
	return c.end();
}

int main()
{
	using namespace std::string_view_literals;

	// You can omit size of arrays
	// if they are initialized at the time of declaration

	int numbers_1[5] = {1, 2, 3, 4, 5};
	print("int numbers_1[5]"sv, numbers_1);

	int numbers_2[] = {1, 2, 3, 4, 5};
	print("int numbers_2[]"sv, numbers_2);

	// You can omit template arguments in STL containers
	// if they are decided during initialization

	array<int, 5> numbers_3 = {1, 2, 3, 4, 5};
	print("array<int, 5> numbers_3"sv, numbers_3);

	array numbers_4 = {1, 2, 3, 4, 5};
	print("array numbers_4"sv, numbers_4);

	vector<int> numbers_5 = {1, 2, 3, 4, 5};
	print("vector<int> numbers_5"sv, numbers_5);

	vector numbers_6 = {1, 2, 3, 4, 5};
	print("vector numbers_6"sv, numbers_6);

	return 0;
}
