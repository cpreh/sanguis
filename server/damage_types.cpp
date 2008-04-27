#include "damage_types.hpp"
#include <algorithm>

const sanguis::server::damage::wrapper sanguis::server::damage::normal(sanguis::damage_type::normal),
                                       sanguis::server::damage::piercing(sanguis::damage_type::piercing),
                                       sanguis::server::damage::fire(sanguis::damage_type::fire),
                                       sanguis::server::damage::ice(sanguis::damage_type::ice),
                                       sanguis::server::damage::pure(sanguis::damage_type::pure);

const sanguis::server::damage::all_wrapper sanguis::server::damage::all = sanguis::server::damage::all_wrapper();

sanguis::server::damage::wrapper::wrapper(const damage_type::type e) : e(e) {}

sanguis::server::damage::all_meta sanguis::server::damage::all_wrapper::operator=(const damage_array::value_type c) const
{
	return all_meta(c);
}

sanguis::server::damage::all_meta::all_meta(const damage_array::value_type d)
	: d(d) {}

sanguis::server::damage::all_meta::operator damage_array() const
{
	damage_array a;
	std::fill(a.begin(),a.end(),d);
	return a;
}

sanguis::damage_array operator,(const sanguis::server::damage::all_meta &l,const sanguis::server::damage::meta &r)
{
	sanguis::damage_array a;
	std::fill(a.begin(),a.end(),l.d);
	a[r.e] = r.d;
	return a;
}

sanguis::server::damage::meta::meta(const damage_type::type e,const damage_array::value_type d) : e(e),d(d) {}

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
