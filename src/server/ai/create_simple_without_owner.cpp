#include "create_simple_without_owner.hpp"
#include "create_simple.hpp"
#include "../entities/auto_weak_link.hpp"
#include <fcppt/function/object.hpp>

sanguis::server::ai::create_function const
sanguis::server::ai::create_simple_without_owner()
{
	return
		ai::create_simple(
			entities::auto_weak_link()
		);
}
