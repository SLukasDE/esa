#include <esa/examples/Logger.h>
#include <esa/logging/appender/OStream.h>
#include <esa/logging/appender/MemBuffer.h>
#include <esa/logging/Location.h>

#include <vector>
#include <tuple>
#include <iostream>
#include <string>

namespace esa {
inline namespace v1_6 {
namespace examples {

namespace {
esl::monitoring::appender::OStream appenderOstream(std::cout, std::cout, std::cout, std::cout, std::cout);

/* MemBuffer appender just writes output to a buffer of a fixed number of lines.
 * If number of columns is specified as well the whole memory is allocated at initialization time.
 */
esl::monitoring::appender::MemBuffer appenderMemBuffer(100);//80);
//esl::monitoring::appender::MemBuffer appenderMemBuffer(100, 200);
}

esl::monitoring::Logger<> logger("esl::examples");

void loggerInitialize() {
	appenderOstream.setRecordLevel();
	appenderOstream.getLayout().setShowFile(true);
	appenderOstream.getLayout().setShowLineNo(true);
	esl::monitoring::addAppender(appenderOstream);

	/* Setting record level to ALL to an appender makes him catching all log messages, even if global logging level is set to SILENT */
	appenderMemBuffer.setRecordLevel(esl::monitoring::Appender::RecordLevel::ALL);
	appenderMemBuffer.getLayout().setShowFile(true);
	appenderMemBuffer.getLayout().setShowLineNo(true);
	esl::monitoring::addAppender(appenderMemBuffer);

	/* setting default */
	esl::monitoring::setLevel(esl::monitoring::Level::WARN, "*");

	//esl::monitoring::Logger<>::setLevel(esl::monitoring::Level::INFO, "AAA::BBB::*");
	//esl::monitoring::Logger<>::setLevel(esl::monitoring::Level::DEBUG, "AAA::BBB::CCC::*");
}

void loggerReplay() {
	appenderMemBuffer.getLayout().setShowTypeName(false);
	std::vector<std::tuple<esa::monitoring::Location, std::string>> buffer = appenderMemBuffer.getBuffer();
	std::cout << "Replay: " << buffer.size() << " elements\n";
	for(const auto& line : buffer) {
		std::cout << appenderMemBuffer.getLayout().makePrefix(std::get<0>(line)) << std::get<1>(line) << "\n";
	}
}


} /* namespace examples */
} /* inline namespace v1_6 */
} /* namespace esa */
