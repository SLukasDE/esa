/*
MIT License
Copyright (c) 2019-2023 Sven Lukas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef ESA_MONITORING_LOGGER_H_
#define ESA_MONITORING_LOGGER_H_

#include <esa/monitoring/Streams.h>

namespace esa {
inline namespace v1_6 {
namespace monitoring {

template<Streams::Level level>
struct Logger;

template<>
struct Logger<Streams::Level::TRACE> : Streams {
	Logger(const char* aTypeName)
	: Streams(aTypeName),
	  trace(aTypeName, Level::TRACE),
	  debug(aTypeName, Level::DEBUG),
	  info(aTypeName, Level::INFO),
	  warn(aTypeName, Level::WARN),
	  error(aTypeName, Level::ERROR)
	{ }

	Real trace;
	Real debug;
	Real info;
	Real warn;
	Real error;
};

template<>
struct Logger<Streams::Level::DEBUG> : Streams {
	Logger(const char* aTypeName)
	: Streams(aTypeName),
	  debug(aTypeName, Level::DEBUG),
	  info(aTypeName, Level::INFO),
	  warn(aTypeName, Level::WARN),
	  error(aTypeName, Level::ERROR)
	{ }

	Empty trace;
	Real debug;
	Real info;
	Real warn;
	Real error;
};

template<>
struct Logger<Streams::Level::INFO> : Streams {
	Logger(const char* aTypeName)
	: Streams(aTypeName),
	  info(aTypeName, Level::INFO),
	  warn(aTypeName, Level::WARN),
	  error(aTypeName, Level::ERROR)
	{ }

	Empty trace;
	Empty debug;
	Real info;
	Real warn;
	Real error;
};

template<>
struct Logger<Streams::Level::WARN> : Streams {
	Logger(const char* aTypeName)
	: Streams(aTypeName),
	  warn(aTypeName, Level::WARN),
	  error(aTypeName, Level::ERROR)
	{ }

	Empty trace;
	Empty debug;
	Empty info;
	Real warn;
	Real error;
};

template<>
struct Logger<Streams::Level::ERROR> : Streams {
	Logger(const char* aTypeName)
	: Streams(aTypeName),
	  error(aTypeName, Level::ERROR)
	{ }

	Empty trace;
	Empty debug;
	Empty info;
	Empty warn;
	Real error;
};

template<>
struct Logger<Streams::Level::SILENT> : Streams {
	Logger(const char* aTypeName)
	: Streams(aTypeName)
	{ }

	Empty trace;
	Empty debug;
	Empty info;
	Empty warn;
	Empty error;
};

} /* namespace monitoring */
} /* inline namespace v1_6 */
} /* namespace esa */

#endif /* ESA_MONITORING_LOGGER_H_ */
