/*
MIT License
Copyright (c) 2019, 2020 Sven Lukas

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

#include <esl/system/process/ProducerFile.h>
#include <esl/object/ValueSettings.h>

namespace esl {
namespace system {
namespace process {

module::Implementation& ProducerFile::getDefault() {
	static module::Implementation implementation;
	return implementation;
}

ProducerFile::ProducerFile(std::string filename,
		std::initializer_list<std::pair<std::string, std::string>> settings,
		const std::string& implementation)
: producerFile(esl::getModule().getInterface<Interface>(implementation).createProducerFile(std::move(filename), object::ValueSettings(std::move(settings))))
{ }

ProducerFile::ProducerFile(std::string filename,
		const object::Values<std::string>& settings,
		const std::string& implementation)
: producerFile(esl::getModule().getInterface<Interface>(implementation).createProducerFile(std::move(filename), settings))
{ }

std::size_t ProducerFile::write(Interface::FileDescriptor& fileDescriptor) {
	return producerFile->write(fileDescriptor);
}

std::size_t ProducerFile::getFileSize() const {
	return producerFile->getFileSize();
}

} /* namespace process */
} /* namespace system */
} /* namespace esl */