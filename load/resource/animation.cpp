#include "environment.hpp"
#include "map_get_or_create.hpp"
#include "../../exception.hpp"
#include <sge/time/millisecond.hpp>
#include <sge/fstream.hpp>
#include <sge/sstream.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/optional.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>


