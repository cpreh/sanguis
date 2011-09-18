#ifndef SANGUIS_SERVER_PERKS_TREE_EQUAL_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_EQUAL_HPP_INCLUDED

#include <sanguis/server/perks/tree/object.hpp>
#include <sanguis/perk_type.hpp>
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace server
{
namespace perks
{
namespace tree
{

class equal
{
	FCPPT_NONASSIGNABLE(
		equal
	);
public:
	explicit equal(
		sanguis::perk_type::type
	);

	bool
	operator()(
		tree::object const &
	) const;
private:
	sanguis::perk_type::type const type_;
};

}
}
}
}

#endif
