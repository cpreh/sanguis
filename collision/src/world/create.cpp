#include <sanguis/collision/impl/world/simple/object.hpp>
#include <sanguis/collision/world/create.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/collision/world/object_unique_ptr.hpp>
#include <sanguis/collision/world/parameters_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>

sanguis::collision::world::object_unique_ptr
sanguis::collision::world::create(sanguis::collision::world::parameters const &_parameters)
{
  return fcppt::unique_ptr_to_base<sanguis::collision::world::object>(
      fcppt::make_unique_ptr<sanguis::collision::impl::world::simple::object>(_parameters));
}
