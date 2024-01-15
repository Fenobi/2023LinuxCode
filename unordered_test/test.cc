#include <iostream>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#include <string>
#include <ctime>
#include <vector>

int main()
{
    const long long N = 1000000;
    std::unordered_set<int> us;
    std::set<int> s;

    std::vector<int> v;
    v.reserve(N);
    srand(time(0));
    for (size_t i = 0; i < N; ++i)
    {
        v.push_back(rand()+i);
    }

    size_t begin1 = clock();
    for (auto e : v)
    {
        us.insert(e);
    }
    size_t end1 = clock();
    std::cout << "unordered_set insert : " << end1 - begin1 << std::endl;

    size_t begin2 = clock();
    for (auto e : v)
    {
        s.insert(e);
    }
    size_t end2 = clock();
    std::cout << "set insert : " << end2 - begin2 << std::endl;

    std::cout << us.size() << std::endl;

    return 0;
}
