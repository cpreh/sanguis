#ifndef SANGUIS_SERVER_DAMAGE_BASIC_META_LIST_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_BASIC_META_LIST_HPP_INCLUDED

#include <sanguis/server/damage/basic_meta_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <initializer_list>
#include <fcppt/config/external_end.hpp>


namespace sanguis::server::damage
{

template<
	typename Unit
>
using
basic_meta_list
=
std::initializer_list<
	sanguis::server::damage::basic_meta<
		Unit
	>
>;

}

#endif
