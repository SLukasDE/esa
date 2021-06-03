/*
MIT License
Copyright (c) 2019-2021 Sven Lukas

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

#ifndef ESL_COM_HTTP_CLIENT_INTERFACE_H_
#define ESL_COM_HTTP_CLIENT_INTERFACE_H_

#include <esl/com/http/client/Response.h>
#include <esl/io/Input.h>
#include <esl/io/Output.h>
#include <esl/object/Values.h>
#include <esl/utility/URL.h>
#include <esl/module/Interface.h>
#include <esl/Module.h>

#include <string>
#include <memory>
#include <functional>

namespace esl {
namespace com {
namespace http {
namespace client {

class Connection;
class Request;
//class Response;

struct Interface : esl::module::Interface {
	/* *************************************** *
	 * definitions required for this interface *
	 * *************************************** */
	using CreateInput = std::function<esl::io::Input (const Response&)>;

	class Connection {
	public:
		Connection() = default;
		virtual ~Connection() = default;

		virtual Response send(Request request, esl::io::Output output, CreateInput createInput) = 0;
		virtual Response send(Request request, esl::io::Output output, esl::io::Input input) = 0;
	};

	using CreateConnection = std::unique_ptr<Connection> (*)(const utility::URL& hostUrl, const object::Values<std::string>& settings);

	/* ************************************ *
	 * standard API definition of interface *
	 * ************************************ */

	static inline const char* getType() {
		return "esl-com-http-client";
	}

	static inline const std::string& getApiVersion() {
		return esl::getModule().getApiVersion();
	}


	/* ************************************ *
	 * extended API definition of interface *
	 * ************************************ */

	Interface(std::string module, std::string implementation,
			CreateConnection aCreateConnection)
	: esl::module::Interface(std::move(module), getType(), std::move(implementation), getApiVersion()),
	  createConnection(aCreateConnection)
	{ }

	static inline void initialize(Interface& interface, CreateConnection createConnection) {
		interface.createConnection = createConnection;
	}

	/* **************************** *
	 * start extension of interface *
	 * **************************** */
	CreateConnection createConnection;
};

} /* namespace client */
} /* namespace http */
} /* namespace com */
} /* namespace esl */

#endif /* ESL_COM_HTTP_CLIENT_INTERFACE_H_ */