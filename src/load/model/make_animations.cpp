#include <sanguis/exception.hpp>
#include <sanguis/load/log.hpp>
#include <sanguis/load/model/animation.hpp>
#include <sanguis/load/model/animation_map.hpp>
#include <sanguis/load/model/find_texture.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/make_animations.hpp>
#include <sanguis/load/model/lookup_animation_name.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::load::model::animation_map
sanguis::load::model::make_animations(
	sge::parse::json::object const &_object,
	sanguis::load::model::global_parameters const &_parameters
)
{
	sanguis::load::model::animation_map result;

	optional_texture_identifier const texture(
		sanguis::load::model::find_texture(
			_object
		)
	);

	sge::parse::json::array const &animations_array(
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			_object.members,
			FCPPT_TEXT("animations")
		)
	);

	for(
		auto const &entry : animations_array.elements
	)
	{
		sge::parse::json::member_map const &inner_members(
			sge::parse::json::get<
				sge::parse::json::object
			>(
				entry
			).members
		);

		if(
			inner_members.size() != 1
		)
			throw sanguis::exception(
				FCPPT_TEXT("inner members of the animation array have to contain exactly one element!")
			);

		sge::parse::json::member const &member(
			*inner_members.begin()
		);

		if(
			result.insert(
				std::make_pair(
					sanguis::load::model::lookup_animation_name(
						member.first
					),
					fcppt::make_unique_ptr<
						sanguis::load::model::animation
					>(
						sge::parse::json::get<
							sge::parse::json::object
						>(
							member.second
						),
						_parameters.new_texture(
							texture
						)
					)
				)
			).second == false
		)
			FCPPT_LOG_WARNING(
				sanguis::load::log(),
				fcppt::log::_
					<< FCPPT_TEXT("Double insert in weapon_category!")
			);
	}

	return
		std::move(
			result
		);
}
