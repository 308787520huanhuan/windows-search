#ifndef PRINTF_BOOK_H
#define PRINTF_BOOK_H

#include "json.h"
#include "windows.h"

struct print
{
	struct obj* p_obj;
	int len;
	CEdit* pEdit;
};

DWORD WINAPI print_book(void *);

#endif
