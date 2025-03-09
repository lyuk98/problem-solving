#include <typeinfo>
#include <string_view>
#include <string>
#include <chrono>
#include <thread>
#include <iomanip>
#include <iostream>
using namespace std;

// Custom struct representing kilometers
struct kilometer
{
	long double value;
};

// Operator overloading to print kilometer
ostream& operator<<(ostream& s, const kilometer& km)
{
	s << km.value << "km";
	return s;
}

// Override literal operator
// (usage: 12.1_km)
//
// Operator must start with _
// because those that do not are reserved by the standard library
kilometer operator""_km(long double value)
{
	return kilometer{value};
}

int main()
{
	// Some types have literals that can be used to
	// initialize variables with specific types

	// Use namespace std::literals to use them all...
	using namespace std::literals;

	// ...or use specific namespaces for your specific needs
	// (using literals for string in this case)
	using namespace std::string_literals;

	// strings can be initialized with ""s literal
	auto string_var = "I am string"s;

	cout << "string_var = " << quoted(string_var) << '\n';
	cout << "type: " << typeid(string_var).name() << '\n';

	cout << endl;

	// string_views can be initialized with ""sv literal
	using namespace std::string_view_literals; // not needed if std::literals is used
	auto string_view_var = "I am string_view"sv;

	cout << "string_view_var = " << quoted(string_view_var) << '\n';
	cout << "type: " << typeid(string_view_var).name() << '\n';

	cout << endl;

	// Durations from std::chrono can be initialized with literals
	using namespace std::chrono_literals; // not needed if std::literals is used

	// You can sleep using the long way...
	cout << "Sleeping the long way...\n";
	this_thread::sleep_for(chrono::seconds(2));

	// ...or you can sleep the easy way
	cout << "Sleeping the easy way...\n";
	this_thread::sleep_for(2s);

	cout << endl;

	// Using custom literal operator
	auto kilometer_var = 12.1_km;

	cout << "kilometer_var = " << kilometer_var << '\n';
	cout << "type: " << typeid(kilometer_var).name() << '\n';

	return 0;
}
