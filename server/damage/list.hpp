#ifndef SANGUIS_SERVER_DAMAGE_LIST_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_LIST_HPP_INCLUDED

#include "list_fwd.hpp"
#include "value_type.hpp"
#include "array.hpp"
#include "meta_fwd.hpp"

namespace sanguis
{
namespace server
{
namespace damage
{

struct list
{
	explicit list(
		meta const &);
	
	explicit list(
		value_type);
	
	list &
	operator()(
		meta const &);

	operator array() const;
private:
	array array_;
};

}
}
}

#endif
