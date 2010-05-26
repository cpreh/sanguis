#include "find_texture.hpp"
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/find_member.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>

sanguis::load::model::optional_texture_identifier const
sanguis::load::model::find_texture(
	sge::parse::json::member_vector const &members
)
{
	fcppt::string const *const ret(
		sge::parse::json::find_member<
			fcppt::string
		>(
			members,
			FCPPT_TEXT("texture")
		)
	);

	return
		ret
		?
			optional_texture_identifier(
				*ret
			)
		:
			optional_texture_identifier();
}
