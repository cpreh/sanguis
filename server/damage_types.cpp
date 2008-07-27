#include "damage_types.hpp"
#include <boost/foreach.hpp>
#include <algorithm>

const sanguis::server::damage::wrapper sanguis::server::damage::normal(sanguis::damage_type::normal),
                                       sanguis::server::damage::piercing(sanguis::damage_type::piercing),
                                       sanguis::server::damage::fire(sanguis::damage_type::fire),
                                       sanguis::server::damage::ice(sanguis::damage_type::ice),
                                       sanguis::server::damage::pure(sanguis::damage_type::pure);

sanguis::server::damage::wrapper::wrapper(const damage_type::type e) : e(e) {}

sanguis::server::damage::meta::meta(const damage_type::type e,const damage_array::value_type d) : e(e),d(d) {}

sanguis::server::damage::meta sanguis::server::damage::wrapper::operator=(const damage_array::value_type c) const
{
	return damage::meta(e,c);
}

sanguis::server::damage::list::list(const damage_array::value_type t)
{
	BOOST_FOREACH(damage_array::value_type &i,array)
		i = t;
}

sanguis::server::damage::list::list(meta const &m)
{
	array[m.e] = m.d;
}

sanguis::server::damage::list &sanguis::server::damage::list::operator()(meta const &m)
{
	array[m.e] = m.d;
	return *this;
}

sanguis::server::damage::list::operator damage_array() const
{
	return array;
}

sanguis::server::damage::list const
sanguis::server::damage::all(
	damage_array::value_type const v)
{
	return list(v);
}
