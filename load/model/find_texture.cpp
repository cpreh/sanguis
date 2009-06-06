#include "find_texture.hpp"
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/optional_impl.hpp>
#include <sge/exception.hpp>
#include <sge/string.hpp>
#include <sge/text.hpp>

sanguis::load::model::optional_texture_identifier const
sanguis::load::model::find_texture(
	sge::parse::json::member_vector const &members)
{
	try
	{
		return sge::parse::json::find_member<
			sge::string
		>(
			members,
			SGE_TEXT("texture")
		);
	}
	catch(sge::exception const &)
	{
		return optional_texture_identifier();
	}
}
