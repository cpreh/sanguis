#include "activation.hpp"
#include "object.hpp"
#include <fcppt/assert.hpp>

sanguis::client::console::activation::activation(
	console::object &_console
)
:
	console_(_console)
{
	FCPPT_ASSERT(
		!console_.active()
	);

	console_.active(
		true
	);
}

sanguis::client::console::activation::~activation()
{
	FCPPT_ASSERT(
		console_.active()
	);

	console_.active(
		false
	);
}
