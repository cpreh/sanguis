#ifndef SANGUIS_CLIENT_CONFIG_SETTINGS_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_CONFIG_SETTINGS_OBJECT_HPP_INCLUDED

#include <sanguis/client/config/settings/object_fwd.hpp>
#include <sge/parse/ini/section_vector.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/entry.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace client
{
namespace config
{
namespace settings
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit object(
		boost::filesystem::path const &
	);

	~object();

	sge::parse::ini::section_vector &
	sections();

	sge::parse::ini::section_vector const &
	sections() const;

	void
	save() const;
private:
	boost::filesystem::path const path_;

	sge::parse::ini::section_vector sections_;
};

}
}
}
}

#endif
