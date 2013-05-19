#ifndef SANGUIS_CREATOR_RESULT_HPP_INCLUDED
#define SANGUIS_CREATOR_RESULT_HPP_INCLUDED

#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/result_fwd.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/symbol.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace creator
{

class result
{
	FCPPT_NONASSIGNABLE(
		result
	);
public:
	result(
		sanguis::creator::grid const &,
		sanguis::creator::seed const &,
		sanguis::creator::name const &
	);

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::grid const &
	grid() const;

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::seed const
	seed() const;

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::name const &
	name() const;
private:
	sanguis::creator::grid const grid_;

	sanguis::creator::seed const seed_;

	sanguis::creator::name const name_;
};

}
}

#endif
