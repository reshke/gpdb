//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2010 Greenplum, Inc.
//
//	@filename:
//		CWStringBase.h
//
//	@doc:
//		Abstract wide character string class
//---------------------------------------------------------------------------
#ifndef GPOS_CWStringBase_H
#define GPOS_CWStringBase_H

#include "gpos/types.h"
#include "gpos/common/clibwrapper.h"

#define GPOS_WSZ_LENGTH(x) gpos::clib::UlWcsLen(x)
#define GPOS_WSZ_STR_LENGTH(x) GPOS_WSZ_LIT(x), GPOS_WSZ_LENGTH(GPOS_WSZ_LIT(x))

#define WCHAR_EOS GPOS_WSZ_LIT('\0')


namespace gpos
{
	class CWStringConst;
	class IMemoryPool;
	
	//---------------------------------------------------------------------------
	//	@class:
	//		CWStringBase
	//
	//	@doc:
	//		Abstract wide character string class.
	//		Currently, the class has two derived classes: CWStringConst and CWString.
	//		CWString is used to represent constant strings that once initialized are never
	//		modified. This class is not responsible for any memory management, rather
	//		its users are in charge for allocating and releasing the necessary memory.
	//		In contrast, CWString can be used to store strings that are modified after
	//		they are created. CWString is in charge of dynamically allocating and deallocating
	//		memory for storing the characters of the string.
	//
	//---------------------------------------------------------------------------
	class CWStringBase
	{
		private:
			// private copy ctor
			CWStringBase(const CWStringBase&);
			
		protected:
			// represents end-of-wide-string character
			static const WCHAR m_wcEmpty;
			
			// size of the string in number of WCHAR units (not counting the terminating '\0')
			ULONG m_ulLength;
			
			// whether string owns its memory and should take care of deallocating it at destruction time
			BOOL m_fOwnsMemory;
			
			// checks whether the string is byte-wise equal to a given string literal
			virtual BOOL FEquals(const WCHAR *wszBuf) const;
			
		public:
			
			// ctor
			CWStringBase(ULONG ulLength, BOOL fOwnsMemory)
				:
				m_ulLength(ulLength),
				m_fOwnsMemory(fOwnsMemory)
			{}
			
			// dtor
			virtual ~CWStringBase(){}
			
			// deep copy of the string
			virtual CWStringConst *PStrCopy(IMemoryPool *pmp) const;

			// accessors
			virtual ULONG UlLength() const;
			
			// checks whether the string is byte-wise equal to another string
			virtual BOOL FEquals(const CWStringBase *pStr) const;			
			
			// checks whether the string contains any characters
			virtual BOOL FEmpty() const;
			
			// checks whether a string is properly null-terminated
			bool FValid() const;
			
			// equality operator 
			BOOL operator == (const CWStringBase &str) const;

			// returns the wide character buffer storing the string
			virtual const WCHAR* Wsz() const = 0;

			// returns the index of the first occurrence of a character, -1 if not found
			INT IFind(WCHAR wc) const;

			// checks if a character is escaped
			BOOL FEscaped(ULONG ulOfst) const;

			// count how many times the character appears in string
			ULONG UlOccurences(const WCHAR wc) const;
	};
	
}

#endif // !GPOS_CWStringBase_H

// EOF

