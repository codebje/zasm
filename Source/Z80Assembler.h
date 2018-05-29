/*	Copyright  (c)	Günter Woigk 1994 - 2018
					mailto:kio@little-bat.de

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

	Permission to use, copy, modify, distribute, and sell this software and
	its documentation for any purpose is hereby granted without fee, provided
	that the above copyright notice appear in all copies and that both that
	copyright notice and this permission notice appear in supporting
	documentation, and that the name of the copyright holder not be used
	in advertising or publicity pertaining to distribution of the software
	without specific, written prior permission.  The copyright holder makes no
	representations about the suitability of this software for any purpose.
	It is provided "as is" without express or implied warranty.

	THE COPYRIGHT HOLDER DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
	INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
	EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY SPECIAL, INDIRECT OR
	CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
	DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
	TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
	PERFORMANCE OF THIS SOFTWARE.
*/


#ifndef ZASM_H
#define ZASM_H

#include "kio/kio.h"
#include "Templates/Array.h"
#include "Source.h"
#include "Label.h"
#include "Segment.h"
#include "Error.h"
#include "SyntaxError.h"
#include "Macro.h"



// hints may be set by caller:
//
extern cstr sdcc_compiler_path;
extern cstr sdcc_include_path;
extern cstr sdcc_library_path;
extern cstr vcc_compiler_path;
extern cstr vcc_include_path;
extern cstr vcc_library_path;


extern const char DEFAULT_CODE_SEGMENT[];

class CharMap;

enum Target
{
	TARGET_UNSET,
	ROM, BIN, Z80, SNA, TAP, ZX80, ZX81, ZX81P, ACE, TZX
};

class Z80Assembler
{
public:
	double		timestamp;			// of assembly

	cstr		source_directory;	// top-level source
	cstr		source_filename;
	cstr		temp_directory;
	Target		target;
	cstr		target_ext;
	cstr		target_filepath;

// source:
	Source		source;						// SourceLine[] accumulating total source
	uint		current_sourceline_index;
	SourceLine&	current_sourceline ()		{ return source[current_sourceline_index]; }

// code:
	Segments	segments;					// code and data segments
	Segment*	current_segment_ptr;
	Segment&	current_segment ()			{ return *current_segment_ptr; }

// Labels:
	Array<Labels> labels;
	uint		local_labels_index;
	Labels&		global_labels ()			{ return labels[0]; }
	Labels&		local_labels ()				{ return labels[local_labels_index]; }
	uint		local_blocks_count;
	cstr		reusable_label_basename;	// name of last normal label

// Macros:
	Macros		macros;

// cond. assembly:
	uint32		cond_off;		// effective final on/off state of conditions nested:
								// 0 = assemble; !0 => assembly off
	uint8		cond[32];		// cond. state for up to 32 nested conditional blocks
	enum 	{	no_cond=0, 		// no conditional assembly
				cond_if,		// #if or #elif pending and no path 'on' up to now
				cond_if_dis,	// #if or #elif pending and 'on' path currently or already processed
				cond_else	 	// #else pending
			};
	bool		if_pending;		// flag to modify label search in value()
	Array<bool>	if_values;
	uint		if_values_idx;

// values set and modified during assembly:
	CharMap*	charset;		// characterset conversion (if any)
	Value		cmd_dpos;		// start of current opcode in segment

// Errors:
	Errors		errors;
	uint		max_errors;
	uint		pass;
	bool		end;
	uint		verbose;
	Validity	validity;		// validity of generated code
	int			labels_changed;	// count value changes of (preliminary) labels
	int			labels_resolved;// count labels which became valid

// c compiler:
	cstr		c_compiler;		// -c: fqn to sdcc or vcc or NULL
	bool		is_sdcc;
	bool		is_vcc;
	cstr		c_includes;		// -I: fqn to custom include dir or NULL
	cstr		stdlib_dir;		// -L: fqn to custom library dir or NULL (not only c but any .globl)
	cstr		c_tempdir;		// fqn of sub directory in temp_directory acc. to c_flags for .s files
	Array<cstr>	c_flags;
	int			c_qi;			// index for source file in c_flags[] or -1
	int			c_zi;			// index for output file in c_flags[] or -1

// options:
	bool		ixcbr2_enabled;	// enable ixcb illegals: e.g. set b,(ix+d),r2
	bool		ixcbxh_enabled;	// enable ixcb illegals: e.g. bit b,xh
	bool		target_z180;	// enable Z180/hd64180 opcodes
	bool		target_8080;	// limit instruction set to 8080 opcodes
	bool		syntax_8080;	// use 8080 assembler syntax
	bool		target_z80;		// target_z80 == !target_8080  => at least a Zilog Z80
	bool		allow_dotnames;	// allow label names starting with a dot '.'
	bool		require_colon;	// program labels must be followed by a colon ':'
	bool		casefold;		// label names are not case sensitive
	bool		flat_operators;	// no operator precedence: evaluate strictly from left to right
	bool		compare_to_old;	// compare own output file to existing reference file
	bool		cgi_mode;		// disallow escaping from sourcefile's directory

private:
	Value	value			(SourceLine&, int prio=0)	throws;
	void	skip_expression	(SourceLine&, int prio)		throws;
	void	asmLabel		(SourceLine&)				throws;
	void	asmDirect		(SourceLine&)				throws;		// #directives
	void	asmIf			(SourceLine&)				throws;
	void	asmElif			(SourceLine&)				throws;
	void	asmElse			(SourceLine&)				throws;
	void	asmEndif		(SourceLine&)				throws;
	void	asmTarget		(SourceLine&)				throws;
	void	asmInclude		(SourceLine&)				throws;
	void	asmInsert		(SourceLine&)				throws;
	void	asmTzx			(SourceLine&)				throws;
	void	asmSegment		(SourceLine&,SegmentType)	throws;
	void	asmCFlags		(SourceLine&)				throws;
	void	asmCPath		(SourceLine&)				throws;
	void	asmLocal		(SourceLine&)				throws;
	void	asmEndLocal		(SourceLine&)				throws;
	void	asmEnd			(SourceLine&)				throws;
	void	asmAssert		(SourceLine&)				throws;
	void	asmDefine		(SourceLine&)				throws;
	void	asmCompress		(SourceLine&)				throws;
	void	asmCharset		(SourceLine&)				throws;
	void	asmFirstOrg		(SourceLine&)				throws;
	void	asmRept			(SourceLine&, cstr endm = "endm")	throws;
	void	asmMacro		(SourceLine&, cstr name, char tag)	throws;
	void	asmMacroCall	(SourceLine&, Macro&)		throws;
	void	asmShebang		(SourceLine&)				throws;
	cstr	compileFile		(cstr)						throws;
	void	compressSegments ()							throws;

	void	(Z80Assembler::*asmInstr) (SourceLine&,cstr)throws;
	void	asmPseudoInstr	(SourceLine&,cstr)			throws;
	void	asmZ80Instr		(SourceLine&,cstr)			throws;
	void	asm8080Instr	(SourceLine&,cstr)			throws;
	void	asmNoSegmentInstr (SourceLine&,cstr)   		throws;
	void	asmRawDataInstr (SourceLine&,cstr)			throws;
	void	asmTzxPulses	(SourceLine&,cstr)			throws;
	void	asmTzxHardwareInfo(SourceLine&,cstr)  		throws;
	void	asmTzxArchiveInfo(SourceLine&,cstr)			throws;

	void	store			(int n)						throws { current_segment().store(n); }
	void	store			(int n, int m)				throws { current_segment().store(n,m); }
	void	store			(int n, int m, int u)		throws { current_segment().store(n,m,u); }
	void	store			(int a, int b, int c, int d)throws { current_segment().store(a,b,c,d); }
	void	storeIXopcode	(int n)						throws;
	void	storeEDopcode	(int n)						throws;
	void	storeIYopcode	(int n)						throws;

	void 	storeWord		(int n)						throws	{ current_segment().storeWord(n); }
	void	storeBlock		(cstr blk, uint n)			throws	{ current_segment().storeBlock(blk,n); }
	void	storeHexbytes	(cstr hex, uint n)			throws	{ current_segment().storeHexBytes(hex,n); }

	void	storeByte 		(Value const& n)			throws { current_segment().storeByte(n); }
	void	storeOffset 	(Value const& n)			throws { current_segment().storeOffset(n); }

	Value const& currentPosition ()						{ return current_segment_ptr->dpos; }
	Value	dollar ()
			{
				if (DataSegment* seg = dynamic_cast<DataSegment*>(current_segment_ptr))
					return seg->lpos - seg->dpos + cmd_dpos;
					//return Value(seg->lpos.value - seg->dpos.value + cmd_dpos.value, seg->lpos.validity );
				else throw syntax_error("current segment does not provide a '$' address");
			}
	Value	dollarDollar	()
			{
				if (DataSegment* seg = dynamic_cast<DataSegment*>(current_segment_ptr))
					return seg->getAddress() + cmd_dpos;
				else throw syntax_error("current segment does not provide a '$$' address");
			}

	uint	getCondition	(SourceLine&, bool expect_comma) throws ;
	uint	getRegister		(SourceLine&, Value&)		throws;
	uint	get8080Register	(SourceLine& q)				throws;
	uint	get8080WordRegister	(SourceLine& q, uint)	throws;

	void	setLabelValue(Label*, int32, Validity) throws ;
	void	setLabelValue(Label*, Value const&) throws ;

	void	setError		(const any_error&);			// set error for current file, line & column
	void	addError		(cstr format, ...) __printflike(2,3); // add error without source line
	void	init_c_flags	();
	void	init_c_tempdir	()							THF;
	void	init_c_compiler	(cstr cc = NULL)			throws;

	bool	is_name			(cstr w)					{ return is_letter(*w)||*w=='_'||(allow_dotnames&&*w=='.'); }
	cstr	unquotedstr		(cstr);
	cstr	get_filename	(SourceLine&, bool dir=no)	throws;
	cstr	get_directory	(SourceLine& q)				throws		{ return get_filename(q,yes); }

public:
			Z80Assembler	();
			~Z80Assembler	();

	void	assembleFile	(cstr sourcepath,			// source file must exist
							 cstr destpath=NULL,		// dflt = source directory, may be dir or filename
							 cstr listpath=NULL,		// dflt = dest direcory, may be dir or filename
							 cstr temppath=NULL,		// dflt = dest dir, must be dir
							 int  liststyle=1,			// 0=none, 1=plain, 2=w/ocode, 4=w/labels, 8=w/clkcycles
							 int  deststyle='b',		// 0=none, 'b'=bin, 'x'=intel hex, 's'=motorola s19
							 bool clean=no)			noexcept;
	void	assemble		(StrArray& sourcelines)	noexcept;
	void	assembleOnePass	(uint pass) noexcept;
	void	assembleLine	(SourceLine&)			throws;
	uint	assembleSingleLine(uint address, cstr z80_instruction, char buffer[]);

	void	checkTargetfile	()		throws;
	void	writeListfile	(cstr filepath, int style) throws;
	void	writeTargetfile	(cstr &filepath, int style) throws;
	void	writeBinFile	(FD&)	throws;
	void	writeHexFile	(FD&)	throws;
	void	writeS19File	(FD&)	throws;
	void	writeTapFile	(FD&)	throws;
	void	writeTzxFile	(FD&)	throws;
	void	writeZ80File	(FD&)	throws;
	void	writeSnaFile	(FD&)	throws;
	void	writeAceFile	(FD&)	throws;
	void	writeZX80File	(FD&)	throws;
	void	writeZX81File	(FD&)	throws;
	void	checkBinFile	()		throws;
	void	checkTapFile	()		throws;
	void	checkTzxFile	()		throws;
	void	checkZ80File	()		throws;
	void	checkSnaFile	()		throws;
	void	checkAceFile	()		throws;
	void	checkZX80File	()		throws;
	void	checkZX81File	()		throws;

	uint	numErrors		()							{ return errors.count(); }
	cstr	targetFilepath	()							{ return target_filepath; }
};





#endif // ZASM_H

























