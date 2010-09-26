#include "perk_chooser_activation.hpp"
#include "perk_chooser.hpp"
#include <fcppt/assert.hpp>

sanguis::client::perk_chooser_activation::perk_chooser_activation(
	perk_chooser &_instance
)
:
	instance_(_instance)
{
	FCPPT_ASSERT(
		!instance_.activated()
	);

	instance_.activated(true);
}

sanguis::client::perk_chooser_activation::~perk_chooser_activation()
{
	FCPPT_ASSERT(
		instance_.activated()
	);

	instance_.activated(false);
}
