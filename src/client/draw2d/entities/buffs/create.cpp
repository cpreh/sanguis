#include <sanguis/buff_type.hpp>
#include <sanguis/client/draw2d/entities/buffs/burn.hpp>
#include <sanguis/client/draw2d/entities/buffs/create.hpp>
#include <sanguis/client/draw2d/entities/buffs/slow.hpp>
#include <sanguis/client/draw2d/entities/buffs/unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::client::draw2d::entities::buffs::unique_ptr
sanguis::client::draw2d::entities::buffs::create(
	sanguis::buff_type const _type
)
{
	switch(
		_type
	)
	{
	case sanguis::buff_type::slow:
		return
			fcppt::make_unique_ptr<
				sanguis::client::draw2d::entities::buffs::slow
			>();
	case sanguis::buff_type::burn:
		return
			fcppt::make_unique_ptr<
				sanguis::client::draw2d::entities::buffs::burn
			>();
	}

	FCPPT_ASSERT_UNREACHABLE;
}
