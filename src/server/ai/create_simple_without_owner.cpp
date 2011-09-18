#include <sanguis/server/ai/create_simple_without_owner.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <fcppt/function/object.hpp>

sanguis::server::ai::create_function const
sanguis::server::ai::create_simple_without_owner(
	sanguis::diff_clock const &_diff_clock
)
{
	return
		ai::create_simple(
			_diff_clock,
			entities::auto_weak_link()
		);
}
