#ifndef SANGUIS_CREATOR_GENERATOR_TOP_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_TOP_PARAMETERS_HPP_INCLUDED

#include <sanguis/creator/symbol.hpp>
#include <sanguis/creator/generator/name.hpp>
#include <sanguis/creator/generator/top_parameters_fwd.hpp>
#include <sanguis/creator/generator/seed.hpp>
#include <sanguis/creator/generator/size.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace creator
{
namespace generator
{

class top_parameters
{
	FCPPT_NONASSIGNABLE(
		top_parameters
	);
public:
	SANGUIS_CREATOR_SYMBOL
	top_parameters(
		sanguis::creator::generator::name const &,
		sanguis::creator::generator::seed const &,
		sanguis::creator::generator::size const &
	);

	sanguis::creator::generator::name const &
	name() const;

	sanguis::creator::generator::seed const
	seed() const;

	sanguis::creator::generator::size const &
	size() const;
private:
	sanguis::creator::generator::name const name_;

	sanguis::creator::generator::seed const seed_;

	sanguis::creator::generator::size const size_;
};

}
}
}

#endif
