#ifndef SANGUIS_CLIENT_CONFIG_SETTINGS_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_CONFIG_SETTINGS_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include <sge/parse/ini/section_vector.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/entry.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/noncopyable.hpp>

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
		fcppt::filesystem::path const &
	);

	~object();

	sge::parse::ini::section_vector &
	sections();

	sge::parse::ini::section_vector const &
	sections() const;

	void
	save() const;
private:
	fcppt::filesystem::path const path_;

	sge::parse::ini::section_vector sections_;
};

}
}
}
}

#endif
