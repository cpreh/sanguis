#include <sanguis/buff_type.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/client/draw2d/entities/buffs/burn.hpp>
#include <sanguis/client/draw2d/entities/buffs/create.hpp>
#include <sanguis/client/draw2d/entities/buffs/slow.hpp>
#include <sanguis/client/draw2d/entities/buffs/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/object_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>
#include <sanguis/client/load/model/collection_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::client::draw2d::entities::buffs::unique_ptr
sanguis::client::draw2d::entities::buffs::create(
	sanguis::diff_clock const &_diff_clock,
	sanguis::client::draw2d::sprite::normal::system &_normal_system,
	sanguis::client::load::model::collection const &_model_collection,
	sanguis::client::draw2d::entities::model::object const &_model,
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
			>(
				_diff_clock,
				_normal_system,
				_model_collection,
				_model
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
