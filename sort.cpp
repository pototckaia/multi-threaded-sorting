#include <iterator>
#include <vector>
#include <iostream>

#include <thread>
#include <future>

int randomNum(int left, int end) 
{
	srand(time(0));
	return rand() % end + left;
}

template <class Iter>
int partition(Iter left, Iter right)
{
	auto size = right - left;

	int pivot_index = randomNum(0, size);
	typename std::iterator_traits<Iter>::value_type pivot = left[pivot_index];

	using std::swap;
	swap(left[pivot_index], *left);

	int i = 1; 
	for (int j = 1; j < size; ++j) 
	{
		if (left[j] < pivot)
		{
			swap(left[j], left[i]);
			++i;
		}
	}
	swap(*left, left[i - 1]);

	return i;
}

template <class Iter>
void quicksort(Iter left, Iter right, std::random_access_iterator_tag)
{
	typename std::iterator_traits<Iter>::difference_type size = right - left;
	if (size <= 0)
		return;
	
	int i = partition(left, right);
	quicksort(left, left + i - 1, std::random_access_iterator_tag());
	quicksort(left + i, right, std::random_access_iterator_tag());
}

template <typename Iter>
void quicksort(Iter left, Iter right)
{
	quicksort(left, right, 
		typename std::iterator_traits<Iter>::iterator_category());
}



template <typename Iter>
void multi_quicksort(Iter left, Iter right, int count_thread)
{
	int i = partition(left, right);
	if (count_thread > 0) 
	{
		--count_thread;
		auto handle = std::async(std::launch::async, 
								multi_quicksort<Iter>, 
								left, left + i - 1, count_thread
						);
		multi_quicksort(left + i, right, count_thread);
	}
	else 
	{
		quicksort(left, left + i - 1);
		quicksort(left + i, right);
	}

}


int main(){
    // This is C++11 syntax
    // Input must be unsigned
    std::vector<unsigned> input = {5,10,15,20,25,50,40,30,20,10,9524,878,17,1,99,18785,3649,164,94,
        123,432,654,3123,654,2123,543,131,653,123,533,1141,532,213,2241,824,1124,42,134,411,
        491,341,1234,527,388,245,1992,654,243,987};

    multi_quicksort(input.begin(), input.end(), 4);
    
    for (unsigned it : input){
        std::cout << it << " ";
    }

    return 0;
}
