#include <sanguis/load/model/part.hpp>
#include <sanguis/load/model/find_texture.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/weapon_category.hpp>
#include <sanguis/load/log.hpp>
#include <sanguis/exception.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/get.hpp>
#include <fcppt/algorithm/find_exn.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>

namespace
{

typedef fcppt::container::array<
	fcppt::string,
	sanguis::weapon_type::size
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

sanguis::weapon_type::type
find_weapon_type(
	fcppt::string const &_str
)
{
	return
		static_cast<
			sanguis::weapon_type::type
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
	weapon_type::type const _type
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
	global_parameters const &_param
)
:
	categories_()
{
	sge::parse::json::member_vector const &members(
		_object.members
	);

	optional_texture_identifier const texture(
		model::find_texture(
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
		sge::parse::json::element_vector::const_iterator it(
			weapons_array.elements.begin()
		);
		it != weapons_array.elements.end();
		++it
	)
	{
		sge::parse::json::member_vector const &inner_members(
			sge::parse::json::get<
				sge::parse::json::object
			>(
				*it
			).members
		);

		if(
			inner_members.size() != 1
		)
			throw exception(
				FCPPT_TEXT("inner members of the weapon category array have to contain exactly one element!")
			);

		sge::parse::json::member const &member(
			inner_members[0]
		);

		if(
			fcppt::container::ptr::insert_unique_ptr_map(
				categories_,
				find_weapon_type(
					member.name
				),
				fcppt::make_unique_ptr<
					weapon_category
				>(
					sge::parse::json::get<
						sge::parse::json::object
					>(
						member.value
					),
					_param.new_texture(
						texture
					)
				)
			).second == false
		)
			FCPPT_LOG_WARNING(
				load::log(),
				fcppt::log::_
					<< FCPPT_TEXT("Double insert in part!")
			);
	}
}
