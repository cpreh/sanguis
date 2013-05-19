#ifndef SANGUIS_CREATOR_TOP_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CREATOR_TOP_PARAMETERS_HPP_INCLUDED

#include <sanguis/creator/name.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/size.hpp>
#include <sanguis/creator/symbol.hpp>
#include <sanguis/creator/top_parameters_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace creator
{

class top_parameters
{
	FCPPT_NONASSIGNABLE(
		top_parameters
	);
public:
	SANGUIS_CREATOR_SYMBOL
	top_parameters(
		sanguis::creator::name const &,
		sanguis::creator::seed const &,
		sanguis::creator::size const &
	);

	sanguis::creator::name const &
	name() const;

	sanguis::creator::seed const
	seed() const;

	sanguis::creator::size const &
	size() const;
private:
	sanguis::creator::name const name_;

	sanguis::creator::seed const seed_;

	sanguis::creator::size const size_;
};

}
}

#endif
