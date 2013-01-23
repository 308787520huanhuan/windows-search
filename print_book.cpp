#include "StdAfx.h"
#include <stdio.h>
#include "json.h"
#include "print_book.h"

#define FORMAT_NUM 4
extern CButton *g_Search;
void print_arr(struct arr* arr, int num, CEdit* pEdit, struct print* P)
{
	
	int i;
	CString str_tmp = _T("");
	struct value* p_v = arr->p_v;

	for (i = 0; i < FORMAT_NUM * num; i++)
	{
		pEdit->SetSel(-1);
		pEdit->ReplaceSel(_T(" "));
	}

	while(p_v)
	{
		switch (p_v->type)
		{
			case INT:
				i = *(int*)p_v->p_data;
				str_tmp.Format("%d, ", i);
				pEdit->SetSel(-1);
				pEdit->ReplaceSel(str_tmp);
				
				break;
			case STR:
				str_tmp.Format("%s, ", (CString)((char*)p_v->p_data));
				pEdit->SetSel(-1);
				pEdit->ReplaceSel(str_tmp);
				break;
			case ARR:
				print_arr(arr, num + 1, pEdit, P);
				break;
			case OBJ:
				pEdit->SetSel(-1);
				pEdit->ReplaceSel("\n");
				struct print p_t;
				p_t.p_obj = (struct obj*)p_v->p_data;
				p_t.len = num + 1;
				p_t.pEdit = pEdit;
				print_book(&p_t);
				break;
			default:
				pEdit->SetSel(-1);
				pEdit->ReplaceSel("\n");
				break;
		}
		p_v = p_v->p_next;
	}
}

DWORD WINAPI print_book(void *P)
{
	struct obj* obj = ((struct print*)P)->p_obj;
	int num = ((struct print*)P)->len;
	CEdit * pEdit = ((struct print*)P)->pEdit;
	struct print* print_q = (struct print*)P;

	int i;
	struct key* key = obj->p_k;
	CString str_tmp = _T("");

	while(key)
	{
		for (i = 0; i < FORMAT_NUM * num; i++)
		{
			pEdit->SetSel(-1);
			pEdit->ReplaceSel(" ");
		}

		str_tmp.Format("%s:", (CString)(key->p_key));
		pEdit->SetSel(-1);
		pEdit->ReplaceSel(str_tmp);

		switch (key->p_v->type)
		{
			case INT:
				i = *(int*)(key->p_v->p_data);
				str_tmp.Format("%d\n", i);
				pEdit->SetSel(-1);
				pEdit->ReplaceSel(str_tmp);
				break;
			case STR:
				((char*)key->p_v->p_data)[STRSIZE - 1] = 0;
				str_tmp.Format("%s\n", (CString)((char*)key->p_v->p_data));
				pEdit->SetSel(-1);
				pEdit->ReplaceSel(str_tmp);
				break;
			case ARR:
				pEdit->SetSel(-1);
				pEdit->ReplaceSel("\n");
				print_arr((struct arr*)key->p_v->p_data, num + 1, pEdit, (struct print*)P);
				pEdit->SetSel(-1);
				pEdit->ReplaceSel("\n");
				break;
			case OBJ:
				pEdit->SetSel(-1);
				pEdit->ReplaceSel("\n");
				struct print p_t1;
				p_t1.p_obj = (struct obj*)key->p_v->p_data;
				p_t1.len = num + 1;
				p_t1.pEdit = pEdit;
				print_book(&p_t1);
				break;
			default:
				break;
		}
		key = key->p_next;
	}	

	return 1;
}	

