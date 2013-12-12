#include <sanguis/gui/default_aspect.hpp>
#include <sge/rucksack/aspect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <fcppt/literal.hpp>


sge::rucksack::aspect const
sanguis::gui::default_aspect()
{
	sge::rucksack::scalar const one(
		fcppt::literal<
			sge::rucksack::scalar
		>(
			1
		)
	);

	return
		sge::rucksack::aspect(
			one,
			one
		);
}
