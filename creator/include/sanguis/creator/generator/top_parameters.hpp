#ifndef SANGUIS_CREATOR_GENERATOR_TOP_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_TOP_PARAMETERS_HPP_INCLUDED

#include <sanguis/creator/generator/top_parameters_fwd.hpp>
#include <sanguis/creator/generator/seed.hpp>
#include <sanguis/creator/generator/name.hpp>
#include <sanguis/creator/generator/size.hpp>
#include <sanguis/creator/symbol.hpp>
#include <fcppt/math/dim/object_impl.hpp>
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
		generator::name const &,
		generator::seed const &,
		generator::size const &
	);

	generator::name const &
	name() const;

	generator::seed const
	seed() const;

	generator::size const &
	size() const;
private:
	generator::name const name_;

	generator::seed const seed_;

	generator::size const size_;
};

}
}
}

#endif
