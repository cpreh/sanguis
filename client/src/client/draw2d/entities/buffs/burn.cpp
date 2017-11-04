#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/buffs/base.hpp>
#include <sanguis/client/draw2d/entities/buffs/burn.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/sprite/float_unit.hpp>
#include <sanguis/client/draw2d/sprite/size_or_texture_size.hpp>
#include <sanguis/client/draw2d/sprite/unit.hpp>
#include <sanguis/client/draw2d/sprite/animation/loop_method.hpp>
#include <sanguis/client/draw2d/sprite/normal/no_rotation.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_decl.hpp>
#include <sanguis/client/draw2d/sprite/normal/white.hpp>
#include <sanguis/client/load/animation_type.hpp>
#include <sanguis/client/load/model/animation.hpp>
#include <sanguis/client/load/model/collection.hpp>
#include <sanguis/client/load/model/object.hpp>
#include <sanguis/client/load/model/part.hpp>
#include <sanguis/client/load/model/weapon_category.hpp>
#include <sanguis/load/model/path.hpp>
#include <sge/sprite/intrusive/connection.hpp>
#include <sge/sprite/roles/center.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/connection.hpp>
#include <sge/sprite/roles/rotation.hpp>
#include <sge/sprite/roles/size_or_texture_size.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::entities::buffs::burn::burn(
	sanguis::diff_clock const &_diff_clock,
	sanguis::client::draw2d::sprite::normal::system &_normal_system,
	sanguis::client::load::model::collection const &_model_collection,
	sanguis::client::draw2d::entities::model::object const &_model
)
:
	sanguis::client::draw2d::entities::buffs::base(),
	animation_(
		_model_collection[
			sanguis::load::model::path{
				boost::filesystem::path{
					FCPPT_TEXT("fire")
				}
			}
		][
			FCPPT_TEXT("default")
		]
		[
			sanguis::optional_primary_weapon_type()
		][
			sanguis::client::load::animation_type::none
		]
		.series(),
		sanguis::client::draw2d::sprite::animation::loop_method::repeat,
		_diff_clock
	),
	sprite_(
		sge::sprite::roles::connection{} =
			_normal_system.connection(
				sanguis::client::draw2d::z_ordering::flare
			),
		sge::sprite::roles::center{} =
			_model.center().get(),
		sge::sprite::roles::rotation{} =
			sanguis::client::draw2d::sprite::normal::no_rotation().get(),
		sge::sprite::roles::size_or_texture_size{} =
			sanguis::client::draw2d::sprite::size_or_texture_size{
				(
					_model.master().size()
					/
					fcppt::literal<
						sanguis::client::draw2d::sprite::unit
					>(
						2
					)
				).get_unsafe()
			},
		sge::sprite::roles::texture0{} =
			animation_.current_texture(),
		sge::sprite::roles::color{} =
			sanguis::client::draw2d::sprite::normal::white()
	)
{
}

sanguis::client::draw2d::entities::buffs::burn::~burn()
{
}

void
sanguis::client::draw2d::entities::buffs::burn::update(
	sanguis::client::draw2d::entities::model::object const &_model
)
{
	sprite_.center(
		_model.center().get()
	);

	sprite_.texture(
		animation_.current_texture()
	);
}
