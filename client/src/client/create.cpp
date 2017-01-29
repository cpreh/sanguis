#include <sanguis/client/create.hpp>
#include <sanguis/client/object.hpp>
#include <sanguis/client/object_base.hpp>
#include <sanguis/client/object_base_unique_ptr.hpp>
#include <sanguis/client/args/result_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_fwd.hpp>


sanguis::client::object_base_unique_ptr
sanguis::client::create(
	fcppt::log::context &_log_context,
	sanguis::client::args::result const &_args
)
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::client::object_base
		>(
			fcppt::make_unique_ptr<
				sanguis::client::object
			>(
				_log_context,
				_args
			)
		);
}
