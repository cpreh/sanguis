#ifndef SANGUIS_CLIENT_PERK_COMPARE_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_COMPARE_HPP_INCLUDED

#include <sanguis/client/perk/tree.hpp>
#include <sanguis/perk_type.hpp>
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace client
{
namespace perk
{

class compare
{
	FCPPT_NONASSIGNABLE(
		compare
	);
public:
	explicit compare(
		sanguis::perk_type::type
	);

	bool
	operator()(
		sanguis::client::perk::tree const &
	) const;
private:
	sanguis::perk_type::type const type_;
};

}
}
}

#endif
