#include <sanguis/exception.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/load/log.hpp>
#include <sanguis/load/primary_weapon_name.hpp>
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
#include <fcppt/optional_comparison.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/string.hpp>
#include <fcppt/algorithm/array_fold.hpp>
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
			sanguis::primary_weapon_type
		>::value
	)
> weapon_type_array;

weapon_type_array const weapon_types(
	fcppt::algorithm::array_fold<
		weapon_type_array
	>(
		[](
			std::size_t const _index
		)
		{
			return
				sanguis::load::primary_weapon_name(
					static_cast<
						sanguis::primary_weapon_type
					>(
						_index
					)
				);
		}
	)
);

sanguis::optional_primary_weapon_type
find_weapon_type(
	fcppt::string const &_str
)
{
	return
		_str
		==
		FCPPT_TEXT("none")
		?
			sanguis::optional_primary_weapon_type()
		:
			sanguis::optional_primary_weapon_type(
				static_cast<
					sanguis::primary_weapon_type
				>(
					std::distance(
						weapon_types.begin(),
						fcppt::algorithm::find_exn(
							weapon_types.begin(),
							weapon_types.end(),
							_str
						)
					)
				)
			)
		;
}

}

sanguis::load::model::weapon_category const &
sanguis::load::model::part::operator[](
	sanguis::optional_primary_weapon_type const _type
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
		!_type
	)
		throw sanguis::exception(
			FCPPT_TEXT("Unarmed weapon model missing in TODO")
		);

	return
		(*this)[
			sanguis::optional_primary_weapon_type()
		];
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
