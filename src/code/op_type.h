#ifndef X64_SRC_CODE_OP_TYPE_H
#define X64_SRC_CODE_OP_TYPE_H

namespace x64 {

/** Any of the types which appear in the Intel Manual. */
enum class OpType {
	// Condition Registers (cr.h)
	CR_0234 = 0,
	CR_8,

	// Debug Registers (dr.h)
	DR,

	// Immediates (imm.h)
	IMM_8,
	IMM_16,
	IMM_32,
	IMM_64,
	ZERO,
	ONE,
	THREE,

	// Labels (label.h)
	LABEL,

	// Memory (m.h)
	M_8,
	M_16,
	M_32,
	M_64,
	M_128,
	M_256,
	M_PAIR_16_64,
	M_PTR_16_16,
	M_PTR_16_32,
	M_PTR_16_64,
	M_16_INT,
	M_32_INT,
	M_64_INT,
	M_32_FP,
	M_64_FP,
	M_80_FP,
	M_80_BCD,
	M_2_BYTE,
	M_14_BYTE,
	M_28_BYTE,
	M_94_BYTE,
	M_108_BYTE,
	M_512_BYTE,

	// MMX Registers (mm.h)
	MM,

	// Modifiers (modifier.h)
	PREF_66,
	PREF_REX_W,
	FAR,

	// Memory Offsets (moffs.h)
	MOFFS_8,
	MOFFS_16,
	MOFFS_32,
	MOFFS_64,

	// General Purpose Registers (r.h)
	RL,
	RH,
	RB,
	AL,
	CL,
	R_16,
	AX,
	DX,
	R_32,
	EAX,
	R_64,
	RAX,

	// Relatives Addresses (rel.h)
	REL_8,
	REL_32,

	// Segment Registers (sreg.h)
	SREG,
	FS,
	GS,

	// XMM Registers (xmm.h)
	XMM,
	XMM_0,

	// YMM Registers (ymm.h)
	YMM
};

} // namespace x64

#endif
