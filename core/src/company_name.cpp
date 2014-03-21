#include <sanguis/company_name.hpp>
#include <sge/config/company_name.hpp>
#include <fcppt/text.hpp>


sge::config::company_name
sanguis::company_name()
{
	return
		sge::config::company_name(
			FCPPT_TEXT("sanguis")
		);
}
