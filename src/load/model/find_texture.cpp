#include <sanguis/load/model/find_texture.hpp>
#include <sanguis/load/model/optional_texture_identifier.hpp>
#include <sanguis/load/resource/texture_identifier.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>


sanguis::load::model::optional_texture_identifier const
sanguis::load::model::find_texture(
	sge::parse::json::object const &_object
)
{
	typedef fcppt::optional<
		fcppt::string const &
	> optional_string;

	optional_string const ret(
		sge::parse::json::find_member<
			fcppt::string
		>(
			_object.members,
			FCPPT_TEXT("texture")
		)
	);

	return
		ret
		?
			sanguis::load::model::optional_texture_identifier(
				sanguis::load::resource::texture_identifier(
					*ret
				)
			)
		:
			sanguis::load::model::optional_texture_identifier()
		;
}
