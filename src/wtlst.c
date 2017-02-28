/*-----------------------------------------------------/
 *  WTLST.C 
 *  S-Ž®‚ð bit—ñ‚É•ÏŠ·‚·‚éB
 *----------------------------------------------------*/

#include "lisp_mt.h"

static L_obj write_atm(L_obj x,L_obj firstpt);

/* convert character to list of 8 bits */
L_obj write_chr(L_obj x,L_obj firstpt)
{
    int byte=128;
    L_obj pt;

    for(pt=firstpt; byte>0; byte/=2)
    {   pt = Cdr[pt] = cons(( x & byte ? wrd_one : wrd_zero ), NIL);
    }
    return pt;
}

/* convert s-exp to list of bits */
L_obj write_lst(L_obj x, L_obj firstpt)
{
   L_obj pt=firstpt;
   /* null list of digits means zero */
   if (is_numb(x) && Pname[x] == NIL)return write_chr('0',pt);
   if (is_atom(x))                   return write_atm(Pname[x],pt);
   pt=write_chr('(',pt);
   while (!is_atom(x)) {
      pt=write_lst(Car[x],pt);
      x = Cdr[x];
      if (!is_atom(x)) pt=write_chr(' ',pt);
   }
   pt=write_chr(')',pt);
   return pt;
}

/* convert atom to 8 bits per character */
static L_obj write_atm(L_obj x,L_obj firstpt)
{
    L_obj pt=firstpt;
    if (x == NIL) return pt;
    pt=write_atm(Cdr[x],pt); /* output characters in reverse order */
    pt=write_chr(Car[x],pt);
    return pt;
}


