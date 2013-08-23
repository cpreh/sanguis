#include <sanguis/client/console/activation.hpp>
#include <sanguis/client/console/object.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>


sanguis::client::console::activation::activation(
	sanguis::client::console::object &_console
)
:
	console_(
		_console
	)
{
	FCPPT_ASSERT_PRE(
		!console_.active()
	);

	console_.active(
		true
	);
}

sanguis::client::console::activation::~activation()
{
	FCPPT_ASSERT_ERROR(
		console_.active()
	);

	console_.active(
		false
	);
}
