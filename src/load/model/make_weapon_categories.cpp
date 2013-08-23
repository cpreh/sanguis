#include <sanguis/exception.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sanguis/load/log.hpp>
#include <sanguis/load/model/find_texture.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/lookup_weapon_name.hpp>
#include <sanguis/load/model/make_weapon_categories.hpp>
#include <sanguis/load/model/optional_texture_identifier.hpp>
#include <sanguis/load/model/weapon_category_map.hpp>
#include <sanguis/load/model/weapon_category.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::load::model::weapon_category_map
sanguis::load::model::make_weapon_categories(
	sge::parse::json::object const &_object,
	sanguis::load::model::global_parameters const &_parameters
)
{
	sanguis::load::model::weapon_category_map result;

	sanguis::load::model::optional_texture_identifier const texture(
		sanguis::load::model::find_texture(
			_object
		)
	);

	sge::parse::json::array const &weapons_array(
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			_object.members,
			FCPPT_TEXT("weapon_categories")
		)
	);

	for(
		auto const &weapon : weapons_array.elements
	)
	{
		sge::parse::json::member_map const &inner_members(
			sge::parse::json::get<
				sge::parse::json::object
			>(
				weapon
			).members
		);

		if(
			inner_members.size() != 1
		)
			throw sanguis::exception(
				FCPPT_TEXT("inner members of the weapon category array have to contain exactly one element!")
			);

		sge::parse::json::member const &member(
			*inner_members.begin()
		);

		if(
			result.insert(
				std::make_pair(
					sanguis::load::model::lookup_weapon_name(
						member.first
					),
					fcppt::make_unique_ptr<
						sanguis::load::model::weapon_category
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
					<< FCPPT_TEXT("Double insert in part!")
			);
	}

	return
		std::move(
			result
		);
}
