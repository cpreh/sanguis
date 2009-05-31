#include "homedir.hpp"
#include "../../exception.hpp"
#include <sge/config/homedir.hpp>
#include <sge/filesystem/exists.hpp>
#include <sge/filesystem/is_regular.hpp>
#include <sge/filesystem/create_directory.hpp>
#include <sge/text.hpp>

sge::filesystem::path const sanguis::client::config::homedir()
{
	sge::filesystem::path const p = 
		sge::config::homedir()/SGE_TEXT(".sanguis");

	if (!sge::filesystem::exists(p))
		sge::filesystem::create_directory(p);
	
	if (sge::filesystem::is_regular(p))
		throw exception(SGE_TEXT("Home path ")+p.string()+SGE_TEXT(" exists but is not a directory"));
	
	return p;
}
