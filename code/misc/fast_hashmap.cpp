#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

unsigned hash_f(unsigned x) {
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = (x >> 16) ^ x;
	return x;
}
struct chash {
	int operator()(int x) const { return hash_f(x); }
};

gp_hash_table<int, int, chash> mp;

