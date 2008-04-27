#include "damage_types.hpp"
#include <algorithm>

const sanguis::server::damage::wrapper sanguis::server::damage::normal(sanguis::damage_type::normal),
                                       sanguis::server::damage::piercing(sanguis::damage_type::piercing),
                                       sanguis::server::damage::fire(sanguis::damage_type::fire),
                                       sanguis::server::damage::ice(sanguis::damage_type::ice),
                                       sanguis::server::damage::pure(sanguis::damage_type::pure);

sanguis::server::damage::meta sanguis::server::damage::wrapper::operator=(const damage_array::value_type c) const
{
	return damage::meta(e,c);
}

sanguis::damage_array operator,(sanguis::damage_array l,const sanguis::server::damage::meta &r)
{
	l[r.e] = r.d;
	return l;
}

sanguis::damage_array operator,(const sanguis::server::damage::meta &l,const sanguis::server::damage::meta &r)
{
	sanguis::damage_array a;
	std::fill(a.begin(),a.end(),sanguis::damage_array::value_type());
	a[l.e] = l.d;
	a[r.e] = r.d;
	return a;
}

sanguis::server::damage::meta::operator damage_array() const
{
	damage_array a;
	std::fill(a.begin(),a.end(),damage_array::value_type());
	a[e] = d;
	return a;
}
