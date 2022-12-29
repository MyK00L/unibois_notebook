#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace __gnu_cxx;
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> k;
k.insert(x);
k.find_by_order(x);  // iteretor to k-th element
k.order_of_key(x);   // number of items < x
rope<int> v;
v.push_back(x);
rope<int> a = v.substr(l, dim);
v.erase(l, dim);