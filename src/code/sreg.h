#ifndef X64_SRC_CODE_SREG_H
#define X64_SRC_CODE_SREG_H

#include "src/code/operand.h"

namespace x64 {

/** A segment register. The segment register bit assignments are ES = 0, 
	  CS = 1, SS = 2, DS = 3, FS = 4, and GS = 5.
*/
class Sreg : public Operand {
	public:
		inline Sreg(uint64_t val) : Operand{val} { }

		inline virtual bool check() const {
			return val_ < 6;
		}
};

/** The segment register FS. */
class Fs : public Sreg {
	public:
		inline Fs() : Sreg{4} { }
		inline Fs(uint64_t ignore) : Sreg{4} { }

		inline virtual bool check() const {
			return val_ == 4;
		}
};

/** The segment register GS. */
class Gs : public Sreg {
	public:
		inline Gs() : Sreg{5} { }
		inline Gs(uint64_t ignore) : Sreg{5} { }

		inline virtual bool check() const {
			return val_ == 5;
		}
};

} // namespace x64

#endif
