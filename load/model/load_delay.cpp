#include "load_delay.hpp"
#include "../../exception.hpp"
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>

sanguis::load::model::optional_delay const
sanguis::load::model::load_delay(
	sge::parse::json::member_vector const &entries
)
{
	try
	{
		return sge::parse::json::find_member<
			int
		>(
			entries,
			FCPPT_TEXT("delay")
		);
	}
	catch(
		sanguis::exception const &e
	)
	{
		return sanguis::load::model::optional_delay();
	}
}
