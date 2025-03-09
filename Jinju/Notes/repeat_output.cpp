#include <iterator>
#include <algorithm>
#include <array>
#include <string>
#include <iostream>
using namespace std;

int main()
{
	// Our objective is to print the character '_' n times
	int n;
	cin >> n;

	// Simple solution
	// (May not be as efficient since it constructs new string objects
	// and allocates spaces for them upon each occurrence)
	cout << string(n, '_') << '\n';

	// Boring solution
	// (Does the job but what's cool in that?)
	for(int i = 0; i < n; ++i)
		cout << '_';
	cout << '\n';

	// Boring solution but involving a C-and-C++ trick
	// (Make your code harder to read!)
	for(int i = n; i; --i)
		cout << '_';
	cout << '\n';

	// Complicated solution using iterators
	// (Enables you to flex your C++ skills
	// but I cannot guarantee its performance)
	{
		ostream_iterator<char> out(cout);
		fill_n(out, n, '_');
		cout << '\n';

		// ostream_iterator can be used to print other stuff
		{
			const array<int, 3> numbers = {1, 2, 3};
			ostream_iterator<int> out2(cout, " ");
			
			// Output: 1 2 3
			copy(numbers.begin(), numbers.end(), out2);
			cout << '\n';
		}
	}

	// Same as above but applicable when printing chars only
	// (Maybe better than using ostream_iterator above)
	{
		ostreambuf_iterator<char> out(cout);
		fill_n(out, n, '_');
		cout << '\n';
	}

	return 0;
}
