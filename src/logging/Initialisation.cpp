#include "Initialisation.h"
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/filesystem.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>

namespace log = boost::log;
typedef log::sinks::synchronous_sink<log::sinks::text_ostream_backend> text_sink;

void Formatter(log::record_view const& rec, log::formatting_ostream& stream) {
    stream << log::extract<unsigned int>("LineID", rec) << " ";
    stream << "[" << log::extract<boost::posix_time::ptime>("TimeStamp", rec) << "] ";
    stream << "<" << rec[log::trivial::severity] << "> ";
    log::value_ref<std::string> fullpath = log::extract<std::string>("File", rec);
    stream << "(" << boost::filesystem::path(fullpath.get()).filename().string() << ":";
    stream << log::extract<int>("Line", rec) << ") ";
    stream << "|" << log::extract<std::string>("Function", rec) << "| ";
    stream << rec[log::expressions::smessage];
}

void Initialisation() {
    log::add_common_attributes();
    log::core::get()->add_global_attribute("Line", log::attributes::mutable_constant<int>(0));
    log::core::get()->add_global_attribute("File", log::attributes::mutable_constant<std::string>(""));
    log::core::get()->add_global_attribute("Function", log::attributes::mutable_constant<std::string>(""));
}

void InitialisationLoggingToConsole(const boost::log::trivial::severity_level& severity) {
    Initialisation();

    boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();
    sink->locked_backend()->auto_flush(true);
    sink->locked_backend()->add_stream(boost::shared_ptr<std::ostream>(&std::clog, boost::null_deleter()));

    sink->set_formatter(&Formatter);
    sink->set_filter(log::trivial::severity >= severity);

    log::core::get()->add_sink(sink);
}

void InitialisationLoggingToFile(const std::string& filename, const boost::log::trivial::severity_level& severity) {
    Initialisation();

    boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();
    sink->locked_backend()->auto_flush(true);
    sink->locked_backend()->add_stream(boost::make_shared<std::ofstream>(filename));

    sink->set_formatter(&Formatter);
    sink->set_filter(log::trivial::severity >= severity);

    log::core::get()->add_sink(sink);
}