#include "weak_link_pair.hpp"
#include <algorithm>

sanguis::server::entities::weak_link_pair::weak_link_pair(
	entity *const me,
	entity *const ref)
:
	me(me),
	ref(ref)
{}

void sanguis::server::entities::weak_link_pair::swap(
	weak_link_pair &r)
{
	std::swap(me, r.me);
	std::swap(ref, r.ref);
}
