#include <iterator>
#include <vector>
#include <bits/shared_ptr.h>
#include <vector>

int randomNum(int left, int end) 
{
	srand(time(0));
	return rand() % end + left;
}

std::shared_ptr<std::vector<int>> rand_vector(std::size_t size)
{
    std::shared_ptr<std::vector<int>> v(new std::vector<int>);
    for (std::size_t i = 0; i < size; ++i) {
        v->push_back(randomNum(-size, size));
    }
    return v;
}