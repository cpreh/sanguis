#include <sanguis/model/animation_map.hpp>
#include <sanguis/model/impl/deserialize/animation.hpp>
#include <sanguis/model/impl/deserialize/animation_map.hpp>
#include <sanguis/model/impl/deserialize/map.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/object_fwd.hpp>


sanguis::model::animation_map
sanguis::model::impl::deserialize::animation_map(
	sge::parse::json::object const &_object
)
{
	return
		sanguis::model::impl::deserialize::map<
			sanguis::model::animation_map
		>(
			_object,
			sge::charconv::utf8_string{
				"animations"
			},
			&sanguis::model::impl::deserialize::animation
		);
}
