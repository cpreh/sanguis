#ifndef SANGUIS_SERVER_DAMAGE_BASIC_LIST_DECL_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_BASIC_LIST_DECL_HPP_INCLUDED

#include <sanguis/server/damage/basic_array.hpp>
#include <sanguis/server/damage/basic_list_fwd.hpp>
#include <sanguis/server/damage/basic_meta_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace damage
{

template<
	typename Unit
>
class basic_list
{
public:
	typedef
	sanguis::server::damage::basic_meta<
		Unit
	>
	meta_type;

	typedef
	std::initializer_list<
		meta_type
	>
	meta_initializer_list;

	typedef
	sanguis::server::damage::basic_array<
		Unit
	>
	array_type;

	explicit
	basic_list(
		Unit
	);

	explicit
	basic_list(
		meta_initializer_list const &
	);

	operator array_type() const;
private:
	array_type array_;
};

}
}
}

#endif
