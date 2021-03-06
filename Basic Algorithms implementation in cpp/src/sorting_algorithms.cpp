#include "sorting_algorithms.hpp"

sorting_algorithms::sorting_algorithms(std::vector<int> arr, sorting_algorithm_method method)
	: _arr{ arr }, _method{ method } {}

sorting_algorithms::~sorting_algorithms() { _arr.clear(); }

/**
 * \brief
 * \param vec
 * \return
 */
std::vector<int> sorting_algorithms::merge_sort(std::vector<int> vec)
{
	//base case, the vector is sorted if its size is 1. 
	if (vec.size() == 1)
	{
		return vec;
	}

	//finding the iterator of the middle element. 
	std::vector<int>::iterator middle = vec.begin() + (vec.size() / 2);

	//splitting vector to left and right (divide step) 
	std::vector<int> left(vec.begin(), middle);
	std::vector<int> right(middle, vec.end());

	//perform merge sort on the splitted vectors. 
	left = merge_sort(left);
	right = merge_sort(right);

	return merge(left, right);
}

std::vector<int> sorting_algorithms::merge(std::vector<int> left, std::vector<int> right)
{
	unsigned int left_it = 0, right_it = 0;
	std::vector<int> result;

	//comparing between two vectors' elements and push_back the bigger to the result vector.
	while (left_it < left.size() && right_it < right.size())
	{
		if (left[left_it] < right[right_it])
		{
			result.push_back(left[left_it]);
			left_it++;
		}
		else
		{
			result.push_back(right[right_it]);
			right_it++;
		}
	}

	//push the remaining data from both vectors into the result. 
	while (left_it < left.size())
	{
		result.push_back(left[left_it]);
		left_it++;
	}
	while (right_it < right.size())
	{
		result.push_back(right[right_it]);
		right_it++;
	}

	return result;
}

void sorting_algorithms::quick_sort(std::vector<int>& vec, int first_index, int last_index)
{
	if (first_index < last_index)
	{
		int split_point = partition(vec, first_index, last_index);

		//splitting the vector to left half. 
		quick_sort(vec, first_index, split_point - 1);
		//splitting the vector to right half 
		quick_sort(vec, split_point + 1, last_index);
	}
}


int sorting_algorithms::partition(std::vector<int>& vec, int first_index, int last_index)
{
	int pivot = vec[first_index];
	int i = first_index, j = last_index;
	while (i != j)
	{
		if (vec[i] > vec[j])
			std::swap(vec[i], vec[j]);
		if (vec[i] != pivot)
			++i;
		else
			--j;
	}
	return i;
}


void sorting_algorithms::heapify(std::vector<int>& vec, int n, int root)
{
	int size = n;

	//largest is a pointer (index) of the largest element in sub-tree. 
	int largest = root;
	int left_child = 2 * root + 1;
	int right_child = 2 * root + 2;

	//if left child is larger than root, swap. 
	if (left_child < size && vec[left_child] > vec[largest])
		largest = left_child;

	//if right child is larger than root, swap. 
	if (right_child < size && vec[right_child] > vec[largest])
		largest = right_child;

	//if the root is not the largest
	if (root != largest)
	{
		std::swap(vec[root], vec[largest]);
		heapify(vec, n, largest);
	}
}
bool sorting_algorithms::check(const std::vector<int>& vec, const std::vector<int>& my_sorted) const
{
	auto stl_sorted = vec;
	bool success = true;
	unsigned int itr = 0;

	std::sort(stl_sorted.begin(), stl_sorted.end());
	for (const auto& ele : stl_sorted)
	{
		if (my_sorted[itr] != ele)
		{
			success = false;
			break;
		}
		++itr;
	}
	return success;
}

void sorting_algorithms::time_comparison(const std::vector<int>& vec)
{
	//initializing timing variables. 
	std::chrono::steady_clock::time_point start, end;

	//initializing heap sort. 
	auto heap_vec = vec;
	auto heap_sort = std::make_unique<sorting_algorithms>(heap_vec, heap);

	//heap sort time calculation. 
	start = std::chrono::steady_clock::now();
	heap_sort->sort();
	end = std::chrono::steady_clock::now();
	std::cout << "Heap sort time: " <<
		std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
		<< " ms." << '\n';

	//initializing quick sort. 
	auto quick_vec = vec;
	auto quick_sort = std::make_unique<sorting_algorithms>(quick_vec, quick);

	//quick sort time calculation. 
	start = std::chrono::steady_clock::now();
	quick_sort->sort();
	end = std::chrono::steady_clock::now();
	std::cout << "Quick sort time: " << std::chrono::duration_cast<std::chrono::milliseconds>
		(end - start).count() << " ms." << '\n';

	//initializing bubble sort. 
	auto bubble_vec = vec;
	auto bubble_sort = std::make_unique<sorting_algorithms>(bubble_vec, bubble);

	//bubble sort time calculation. 
	start = std::chrono::steady_clock::now();
	bubble_sort->sort();
	end = std::chrono::steady_clock::now();
	std::cout << "Bubble sort time: " << std::chrono::duration_cast<std::chrono::milliseconds>
		(end - start).count() << " ms." << '\n';

	//initializing selection sort. 
	auto selection_vec = vec;
	auto selection_sort = std::make_unique<sorting_algorithms>(selection_vec, selection);

	//selection sort time calculation. 
	start = std::chrono::steady_clock::now();
	selection_sort->sort();
	end = std::chrono::steady_clock::now();
	std::cout << "Selection sort time: " << std::chrono::duration_cast<std::chrono::milliseconds>
		(end - start).count() << " ms." << '\n';

	//initializing insertion sort. 
	auto insertion_vec = vec;
	auto insertion_sort = std::make_unique<sorting_algorithms>(insertion_vec, insertion);

	//insertion sort time calculation. 
	start = std::chrono::steady_clock::now();
	insertion_sort->sort();
	end = std::chrono::steady_clock::now();
	std::cout << "Insertion sort time: " << std::chrono::duration_cast<std::chrono::milliseconds>
		(end - start).count() << " ms." << '\n';

	//initializing merge sort. 
	auto merge_vec = vec;
	auto merge_sort = std::make_unique<sorting_algorithms>(merge_vec, mergeSort);

	//insertion sort time calculation. 
	start = std::chrono::steady_clock::now();
	merge_sort->sort();
	end = std::chrono::steady_clock::now();
	std::cout << "Merge sort time: " << std::chrono::duration_cast<std::chrono::milliseconds>
		(end - start).count() << " ms." << '\n';
}


std::vector<int> sorting_algorithms::sort()
{
	std::vector<int> vec;
	switch (_method)
	{
	case bubble:
	{
		std::cout << "performing bubble sort\n";
		vec = _arr;
		auto sorted = false;
		int pass_through = vec.size() - 1;
		while (!sorted)
		{
			sorted = true;
			//for loop for passes through.
			for (int i = 0; i < pass_through; ++i)
				//for loop to swap adjacent elements except the sorted ones (i). 
				for (int j = 0; j < pass_through - i; ++j)
					if (vec[j] > vec[j + 1])
					{
						sorted = false;
						std::swap(vec[j], vec[j + 1]);
					}
		}
		break;
	}
	case selection:
	{
		std::cout << "performing selection sort\n";
		vec = _arr;
		int n = vec.size();
		int i, j, min_index;
		//looping on all elements up to the last element/index. 
		for (i = 0; i < n - 1; ++i)
		{
			min_index = i;
			//looping on all elements 
			for (j = i + 1; j < n; ++j)
			{
				if (vec[min_index] > vec[j])
					min_index = j;
			}
			std::swap(vec[min_index], vec[i]);
		}
		break;
	}
	case insertion:
	{
		std::cout << "performing insertion sort\n";
		vec = _arr;
		int i, hole_index, temp, size = vec.size(); //hole_idex is (j) in my mind :D 

		// perform outer loop
		for (i = 0; i < size - 1; ++i)
		{
			hole_index = i + 1;
			temp = vec[hole_index];
			// perform shifting loop
			while (hole_index > 0 && temp < vec[hole_index - 1])
			{
				vec[hole_index] = vec[hole_index - 1];
				--hole_index;
			}
			// assigning temp value to the right position
			vec[hole_index] = temp;
		}
		break;
	}
	case mergeSort:
	{
		std::cout << "performing merge sort\n";
		vec = _arr;
		vec = merge_sort(vec);
		break;
	}
	case quick:
	{
		std::cout << "performing quick sort\n";
		vec = _arr;
		sorting_algorithms::quick_sort(vec, 0, vec.size() - 1);
		break;
	}
	case heap:
	{
		std::cout << "performing heap sort\n";
		vec = _arr;
		int size = vec.size();

		//building the tree. (step. 1) 
		for (int i = size / 2 - 1; i >= 0; --i)
			heapify(vec, size, i);

		//sorting.  (step. 2)
		for (int i = size - 1; i >= 0; --i)
		{
			//move current root to end. 
			std::swap(vec[i], vec[0]);

			//call max heapify on max-heap. 
			heapify(vec, i, 0);
		}

		break;
	}
	default:
	{
		std::cout << "no sorting algorithm selected\n";
		break;
	}
	}
	return vec;
}
