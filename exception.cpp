#include "exception.hpp"
#include <fcppt/text.hpp>

sanguis::exception::exception(sge::string const &w)
	: sge::exception(FCPPT_TEXT("sanguis: ")+w)
{
}
