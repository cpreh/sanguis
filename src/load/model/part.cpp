#include <sanguis/exception.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/load/log.hpp>
#include <sanguis/load/model/find_texture.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/optional_texture_identifier.hpp>
#include <sanguis/load/model/part.hpp>
#include <sanguis/load/model/weapon_category.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <fcppt/enum_size.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/string.hpp>
#include <fcppt/algorithm/find_exn.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <cstddef>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef std::array<
	fcppt::string,
	static_cast<
		std::size_t
	>(
		fcppt::enum_size<
			sanguis::weapon_type
		>::value
	)
> weapon_type_array;

weapon_type_array const weapon_types = {
{
	FCPPT_TEXT("none"),
	FCPPT_TEXT("melee"),
	FCPPT_TEXT("pistol"),
	FCPPT_TEXT("dual_pistols"),
	FCPPT_TEXT("shotgun"),
	FCPPT_TEXT("rocket_launcher"),
	FCPPT_TEXT("grenade")
} };

sanguis::weapon_type
find_weapon_type(
	fcppt::string const &_str
)
{
	return
		static_cast<
			sanguis::weapon_type
		>(
			std::distance(
				weapon_types.begin(),
				fcppt::algorithm::find_exn(
					weapon_types.begin(),
					weapon_types.end(),
					_str
				)
			)
		);
}

}

sanguis::load::model::weapon_category const &
sanguis::load::model::part::operator[](
	sanguis::weapon_type const _type
) const
{
	category_map::const_iterator const it(
		categories_.find(
			_type
		)
	);

	if(
		it != categories_.end()
	)
		return *it->second;

	if(
		_type == weapon_type::none
	)
		throw sanguis::exception(
			FCPPT_TEXT("Unarmed weapon model missing in TODO")
		);

	return (*this)[weapon_type::none];
}

sanguis::load::model::part::~part()
{
}

sanguis::load::model::part::part(
	sge::parse::json::object const &_object,
	sanguis::load::model::global_parameters const &_param
)
:
	categories_()
{
	sge::parse::json::member_map const &members(
		_object.members
	);

	sanguis::load::model::optional_texture_identifier const texture(
		sanguis::load::model::find_texture(
			members
		)
	);

	sge::parse::json::array const &weapons_array(
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			members,
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
			fcppt::container::ptr::insert_unique_ptr_map(
				categories_,
				find_weapon_type(
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
					_param.new_texture(
						texture
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
}
