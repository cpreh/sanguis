#include "find_texture.hpp"
#include "get_entry.hpp"
#include "../../exception.hpp"
#include <sge/optional_impl.hpp>
#include <sge/string.hpp>
#include <sge/text.hpp>

sanguis::load::model::optional_texture_identifier const
sanguis::load::model::find_texture(
	sge::parse::json::member_vector const &members)
{
	try
	{
		return get_entry<
			sge::string
		>(
			members,
			SGE_TEXT("texture")
		);
	}
	catch(exception const &)
	{
		return optional_texture_identifier();
	}
}
