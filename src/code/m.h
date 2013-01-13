#ifndef X64_SRC_CODE_M_H
#define X64_SRC_CODE_M_H

#include <cassert>

#include "src/code/r.h"
#include "src/code/imm.h"
#include "src/code/operand.h"
#include "src/code/scale.h"
#include "src/code/sreg.h"

namespace x64 {

enum class Scale {
	TIMES_1 = 0,
	TIMES_2,
	TIMES_4,
	TIMES_8
};

/** An operand in memory. */
class M : public Operand {
	public:
		inline M(const AddrR* b, bool addr_or = false)
				: seg_(0), base_(b), index_(0), scale_(Scale::TIMES_1), disp_(0),
				  addr_or_(addr_or) {
		}

		inline M(const Sreg* s, const AddrR* b, bool addr_or = false)
				: seg_(s), base_(b), index_(0), scale_(Scale::TIMES_1), disp_(0),
				  addr_or_(addr_or) {
		}

		inline M(const AddrR* b, const Imm32* d, bool addr_or = false)
				: seg_(0), base_(b), index_(0), scale_(Scale::TIMES_1), disp_(d),
				  addr_or_(addr_or) {
		}

		inline M(const Sreg* s, const AddrR* b, const Imm32* d, 
				     bool addr_or = false)
				: seg_(s), base_(b), index_(0), scale_(Scale::TIMES_1), disp_(d),
				  addr_or_(addr_or) {
		}

		inline M(const AddrR* i, Scale sc, bool addr_or = false)
				: seg_(0), base_(0), index_(i), scale_(sc), disp_(0), 
				  addr_or_(addr_or) {
		}

		inline M(const Sreg* s, const AddrR* i, Scale sc, bool addr_or = false)
				: seg_(s), base_(0), index_(i), scale_(sc), disp_(0), 
				  addr_or_(addr_or) {
		}

		inline M(const AddrR* i, Scale sc, const Imm32* d, bool addr_or = false) 
				: seg_(0), base_(0), index_(i), scale_(sc), disp_(d), 
				  addr_or_(addr_or) {
		}

		inline M(const Sreg* s, const AddrR* i, Scale sc, const Imm32* d, 
				     bool addr_or = false)
				: seg_(s), base_(0), index_(i), scale_(sc), disp_(d), 
				  addr_or_(addr_or) {
		}

		inline M(const AddrR* b, const AddrR* i, Scale sc, bool addr_or = false)
				: seg_(0), base_(b), index_(i), scale_(sc), disp_(0), 
				  addr_or_(addr_or) {
		}

		inline M(const Sreg* s, const AddrR* b, const AddrR* i, Scale sc, 
				     bool addr_or = false)
				: seg_(s), base_(b), index_(i), scale_(sc), disp_(0), 
				  addr_or_(addr_or) {
		}

		inline M(const AddrR* b, const AddrR* i, Scale sc, const Imm32* d, 
				     bool addr_or = false)
				: seg_(0), base_(b), index_(i), scale_(sc), disp_(d), 
				  addr_or_(addr_or) {
		}

		inline M(const Sreg* s, const AddrR* b, const AddrR* i, Scale sc, 
				     const Imm32* d, bool addr_or = false)
				: seg_(s), base_(b), index_(i), scale_(sc), disp_(d), 
				  addr_or_(addr_or) {
		}

		inline bool contains_seg() const {
			return seg_ != 0;
		}

		inline bool contains_base() const {
			return base_ != 0;
		}

		inline bool contains_index() const {
			return index_ != 0;
		}

		inline bool contains_disp() const {
			return disp_ != 0;
		}

		inline const Sreg* get_seg() const {
			assert(contains_seg());
			return seg_;
		}

		inline const AddrR* get_base() const {
			assert(constains_base());
			return base_;
		}

		inline const AddrR* get_index() const {
			assert(contains_index());
			return index_;
		}

		inline Scale get_scale() const {
			return scale_;
		}

		inline const Imm* get_disp() const {
			assert(contains_disp());
			return disp_;
		}

		inline bool get_addr_or() const {
			return addr_or_;
		}

		inline void set_set(const Sreg* seg) {
			seg_ = seg;
		}

		inline void set_base(const AddrR* base) {
			base_ = base;
		}

		inline void set_index(const AddrR* index) {
			index_ = index;
		}

		inline void set_scale(Scale scale) {
			scale_ = scale;
		}

		inline void set_disp(const Imm32* disp) {
			disp_ = disp;
		}

		inline void set_addr_or(bool addr_or) {
			addr_or_ = addr_or;
		}

		inline void clear_seg() {
			seg_ = 0;
		}

		inline void clear_base() {
			base_ = 0;
		}

		inline void clear_index() {
			index_ = 0;
		}

		inline void clear_disp() {
			disp_ = 0;
		}

		inline virtual bool check() const {
			// Both base and index can't both be null
			if ( !contains_base() && !contains_index() ) 
				return false;
			// Check non-null bases
			if ( contains_base() && !get_base()->check() )
				return false;
			// Check non-null indices
			if ( contains_index() && !get_index()->check() )
				return false;
			// Index cannot be rsp/esp
			if ( contains_index() && (R64)get_index() == rsp )
				return false;
			return true;
		}

	private:	
		const Sreg* seg_;
		const AddrR* base_;
		const AddrR* index_;
		const Scale scale_;
		const Imm32* disp_;
		bool addr_or_;
};

// NOTE: This ugliness can be replaced using inherited constructors come gcc 4.8
#define CONSTRUCTORS(T) \
	inline T(const AddrR* b, bool o = false) : M{b, o} { } \
	inline T(const Sreg* s, const Addr* b, bool o = false) : M{s, b, o} { } \
	inline T(const AddrR* b, const Imm32* d, bool o = false) : M{b, d, o} { } \
	inline T(const Sreg* s, const AddrR* b, const Imm32* d, bool o = false) : M{s, b, d, o} { } \
	inline T(const AddrR* i, Scale s, bool o = false) : M{i, s, o} { } \
	inline T(const Sreg* s, const AddrR* i, Scale sc, bool o = false) : M{s, i, sc, o} { } \
	inline T(const AddrR* i, Scale s, const Imm32* d, bool o = false) : M{i, s, d, o} { } \
	inline T(const Sreg* s, const AddrR* i, Scale sc, const Imm32* d, bool o = false) : M{s, i, sc, d, o} { } \
	inline T(const AddrR* b, const AddrR* i, Scale s, bool o = false) : M{b, i, s, o} { } \
	inline T(const Sreg* s, const AddrR* b, const AddrR* i, Scale sc, bool o = false) : M{s, b, i, sc, o} { } \
	inline T(const AddrR* b, const AddrR* i, Scale s, const Imm32* d, bool o = false) : M{b, i, s, d, o} { } \
	inline T(const Sreg* s, const AddrR* b, const AddrR* i, Scale sc, const Imm32* d, bool o = false) : M{s, b, i, sc, d, o} { } \

/** A byte operand in memory, usually expressed as a variable or array name, 
	  but pointed to by the DS:(E)SI or ES:(E)DI registers. 
		In 64-bit mode, it is pointed to by the RSI or RDI registers.
*/		
class M8 : public M {
	public:
		CONSTRUCTORS(M8)
};

/** A word operand in memory, usually expressed as a variable or array name, 
	  but pointed to by the DS:(E)SI or ES:(E)DI registers. This nomenclature is 
		used only with the string instructions.
*/
class M16 : public M {
	public:
		CONSTRUCTORS(M16)
};

/** A doubleword operand in memory, usually expressed as a variable or array 
		name, but pointed to by the DS:(E)SI or ES:(E)DI registers. This 
		nomenclature is used only with the string instructions.
*/
class M32 : public M {
	public:
		CONSTRUCTORS(M32)
};

/** A memory quadword operand in memory. */
class M64 : public M {
	public:
		CONSTRUCTORS(M64)
};

/** A memory double quadword operand in memory. */
class M128 : public M {
	public:
		CONSTRUCTORS(M128)
};

/** A 32-byte operand in memory. This nomenclature is used only with AVX 
	  instructions.
*/		
class M256 : public M {
	public:
		CONSTRUCTORS(M256)
};

/** A memory operand consisting of data item pairs whose sizes are indicated on 
	  the left and the right side of the ampersand. All memory addressing modes 
		are allowed. The m16&64 operand is used by LIDT and LGDT in 64-bit mode to 
		provide a word with which to load the limit field, and a quadword with 
		which to load the base field of the corresponding GDTR and IDTR registers.
*/
class MPair1664 : public M {
	public:
		CONSTRUCTORS(MPair1664)
};

/** A memory operand containing a far pointer composed of two numbers. The
		number to the left of the colon corresponds to the pointer's segment 
		selector. The number to the right corresponds to its offset.
*/
class MPtr1616 : public M {
	public:
		CONSTRUCTORS(MPtr1616)
};

/** A memory operand containing a far pointer composed of two numbers. The
		number to the left of the colon corresponds to the pointer's segment 
		selector. The number to the right corresponds to its offset.
*/
class MPtr1632 : public M {
	public:
		CONSTRUCTORS(MPtr1632)
};

/** A memory operand containing a far pointer composed of two numbers. The
		number to the left of the colon corresponds to the pointer's segment 
		selector. The number to the right corresponds to its offset.
*/
class MPtr1664 : public M {
	public:
		CONSTRUCTORS(MPtr1664)
};

/** A word integer operand in memory. This symbol designates integers that are 
	  used as operands for x87 FPU integer instructions.
*/
class M16Int : public M {
	public:
		CONSTRUCTORS(M16Int)
};

/** A doubleword integer operand in memory. This symbol designates integers 
	  that are used as operands for x87 FPU integer instructions.
*/
class M32Int : public M {
	public:
		CONSTRUCTORS(M32Int)
};

/** A quadword integer operand in memory. This symbol designates integers 
	  that are used as operands for x87 FPU integer instructions.
*/
class M64Int : public M {
	public:
		CONSTRUCTORS(M64Int)
};

/** A single-precision floating-point operand in memory. This symbol designates 
		floating-point values that are used as operands for x87 FPU floating-point 
		instructions.
*/
class M32Fp : public M {
	public:
		CONSTRUCTORS(M32Fp)
};

/** A double-precision floating-point operand in memory. This symbol designates 
		floating-point values that are used as operands for x87 FPU floating-point 
		instructions.
*/
class M64Fp : public M {
	public:
		CONSTRUCTORS(M64Fp)
};

/** A double extended-precision floating-point operand in memory. This symbol 
		designates floating-point values that are used as operands for x87 FPU 
		floating-point instructions.
*/
class M80Fp : public M {
	public:
		CONSTRUCTORS(M80Fp)
};

/** A double extended-precision binary-coded-decimaly operand in memory. */
class M80Bcd : public M {
	public:
		CONSTRUCTORS(M80Bcd)
};

/** A 2 byte operand in memory. */
class M2Byte : public M {
	public:
		CONSTRUCTORS(M2Byte)
};

/** A 14 byte operand in memory. */
class M14Byte : public M {
	public:
		CONSTRUCTORS(M14Byte)
};

/** A 28 byte operand in memory. */
class M28Byte : public M {
	public:
		CONSTRUCTORS(M28Byte)
};

/** A 94 byte operand in memory. */
class M94Byte : public M {
	public:
		CONSTRUCTORS(M94Byte)
};

/** A 108 byte operand in memory. */
class M108Byte : public M {
	public:
		CONSTRUCTORS(M108Byte)
};

/** A 5122 byte operand in memory. */
class M512Byte : public M {
	public:
		CONSTRUCTORS(M512Byte)
};

#undef CONSTRUCTORS

} // namespace x64

#endif
