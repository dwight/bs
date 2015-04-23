/*    Copyright 2015 MongoDB Inc.
*
*    Licensed under the Apache License, Version 2.0 (the "License");
*    you may not use this file except in compliance with the License.
*    You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
*    Unless required by applicable law or agreed to in writing, software
*    distributed under the License is distributed on an "AS IS" BASIS,
*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*    See the License for the specific language governing permissions and
*    limitations under the License.
*/

// http://www.ecma-international.org/ecma-262/5.1/#sec-A.1

#include "reader.h"

namespace bs_impl { 

	class simple_reader : public reader {
		const char *_p;
	public:
		simple_reader(const char *p) : _p(p) { }

		char pop() {
			if( *p == 0 ) 
				throw eof();
			return *p++;
		}
		char peek() const { 
			return *p;
		}
		
	};
	
	class parser { 
		const set<string> reservedWords { 
			"true", "false", "null", 
			// reserved:
			"break","do","instanceof","typeof",
			"case","else","new","var","catch","finally","return","void","continue","for","switch","while","debugger",
			"function","this","with","default","if","throw","delete","in","try",
			// future:
			"fdcx","enum","extends","super","const","export","import",
			"implements","let","private","public","interface","package","protected","static","yield"		
		};	
		simple_reader& r;
		AST& a;
	public:
		parser(simple_reader& reader, AST& out) : r(reader), a(out) { }
	private:
		string identifier() { 
			
		}
		void function() { 
			Function f;
			f.name = identifier();
		}
		void sourceElement() { 
			if( got("function") ) function(); else statement(); 
		}
	public:
		void parse() {
			while( 1 ) { 
				sourceElement();
			}			
		}
	};	

}


