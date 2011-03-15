#include "activation.hpp"
#include "chooser.hpp"
#include <fcppt/assert.hpp>

sanguis::client::gui::perk::activation::activation(
	perk::chooser &_instance
)
:
	instance_(_instance)
{
	FCPPT_ASSERT(
		!instance_.activated()
	);

	instance_.activated(
		true
	);
}

sanguis::client::gui::perk::activation::~activation()
{
	FCPPT_ASSERT(
		instance_.activated()
	);

	instance_.activated(
		false
	);
}
