#include <sge/config/app_name.hpp>
#include <sanguis/app_name.hpp>
#include <sanguis/config_app_name.hpp>


sge::config::app_name
sanguis::config_app_name()
{
	return
		sge::config::app_name(
			sanguis::app_name()
		);
}
