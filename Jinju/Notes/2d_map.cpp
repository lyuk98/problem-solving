#include <cstdlib>
#include <utility>
#include <iterator>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int main() {
	int height, width;
	cin >> height >> width;

	// C-style malloc() and stuff
	// (Please don't do this; we are not using C, you know)
	{
		int** map = (int**)malloc(sizeof(int*) * height);

		for(int i = 0; i < height; ++i) {
			map[i] = (int*)malloc(sizeof(int) * width);

			for(int j = 0; j < width; ++j) {
				cin >> map[i][j];
			}
		}

		for(int i = 0; i < height; ++i) {
			free(map[i]);
		}
		free(map);
	}

	// C++-style memory allocation using new[] operator
	// (Maybe use this in case you need extreme efficiency on something,
	// but don't forget to delete the memory in production)
	{
		int** map = new int*[height];

		for(int i = 0; i < height; ++i) {
			map[i] = new int[width];

			for(int j = 0; j < width; ++j) {
				cin >> map[i][j];
			}
		}

		for(int i = 0; i < height; ++i) {
			delete[] map[i];
		}
		delete[] map;
	}

	// C++-style using std::vector
	// (Personally recommending this approach
	// as you don't need to remember freeing the memory and it's short)
	{
		vector<vector<int>> map(height, vector<int>(width));

		for(int i = 0; i < height; ++i) {
			for(int j = 0; j < width; ++j) {
				cin >> map[i][j];
			}
		}
	}

	// Same thing as before but now using enhanced for loops
	// (You can also do this but it may not be as intuitive)
	{
		vector<vector<int>> map(height, vector<int>(width));

		for(vector<int>& line : map) {
			for(int& spot : line) {
				cin >> spot;
			}
		}
	}

	// Using std::vector but filling up each line with istream_iterator
	// (I don't really know about the performance with this approach,
	// but if you want to flex your C++ skills, then why not)
	{
		vector<vector<int>> map;
		map.reserve(height);

		for(int i = 0; i < height; ++i) {
			vector<int> line;
			line.reserve(width);

			copy_n(
				istream_iterator<int>(cin),
				width,
				back_inserter(line)
			);

			map.push_back(std::move(line));
		}
	}

	// Just make the map in 1D vector lmao
	// (Shortest code among those presented here,
	// but may require a fair amount of knowledge in C++)
	{
		vector<int> map;
		map.reserve(height * width);
		copy_n(
			istream_iterator<int>(cin),
			height * width,
			back_inserter(map)
		);
	}

	return 0;
}
