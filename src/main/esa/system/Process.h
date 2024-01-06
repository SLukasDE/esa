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

#ifndef ESA_SYSTEM_PROCESS_H_
#define ESA_SYSTEM_PROCESS_H_

#include <esa/system/Transceiver.h>
#include <esa/system/Arguments.h>
#include <esa/system/Environment.h>
#include <esa/system/FileDescriptor.h>
#include <esa/object/Object.h>
#include <esa/utility/Signal.h>

#include <memory>
#include <string>


namespace esa {
inline namespace v1_6 {
namespace system {

class Process : public object::Object {
public:
	Process() = default;

	virtual Transceiver& operator[](const FileDescriptor& fd) = 0;

	virtual void setWorkingDir(std::string workingDir) = 0;
	virtual void setEnvironment(std::unique_ptr<Environment> environment) = 0;
	virtual const Environment* getEnvironment() const = 0;

	virtual void addFeature(object::Object& feature) = 0;

	virtual int execute(Arguments arguments) const = 0;

	virtual void sendSignal(const utility::Signal& signal) const = 0;
	virtual const void* getNativeHandle() const = 0;
};

} /* namespace system */
} /* inline namespace v1_6 */
} /* namespace esa */

#endif /* ESA_SYSTEM_PROCESS_H_ */