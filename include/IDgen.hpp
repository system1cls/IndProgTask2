#include <random>

typedef unsigned long long int ulong;

class IDgen {
private:
	std::mt19937_64 generator;

public:
	IDgen();

	void set_seed(ulong seed);

	ulong gen();
};