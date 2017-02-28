/*-----------------------------------------------------/
 *  IN.C 
 *  入力されたM-式を読み込み、コメントを取り除いた後に、
 *  そのM-式に対応するリスト構造に変換する。
 *----------------------------------------------------*/

#include "lisp_mt.h"

static L_obj wrd2atm(L_obj word);
static L_obj in_word2();
static L_obj in_word(unsigned char cmtflag);
static L_obj macro_expand();

/* are two lists of characters equal ? */
L_obj eq_wrd(L_obj x, L_obj y)
{
   if (x == NIL) return y == NIL;
   if (y == NIL) return 0;
   if (Car[x] != Car[y]) return 0;
   return eq_wrd(Cdr[x],Cdr[y]);
}

/* is word in object list ? */
L_obj lookup_word(L_obj x)
{
   L_obj i = obj_lst_get();
   while (!is_atom(i)) {
       /* if word is already in object list, don't make a new atom */
       if (eq_wrd(Pname[get_atm_obj_lst(i)],x))
          return get_atm2_obj_lst(i);
       i = obj_lst_next(i);
   }
   /* if word isn't in object list, make new atom & add it to object list */
   i = mk_atom(0,"",0); /* adds word to object list */
   Pname[i] = x;
   return i;
}

/* check if list of characters are exclusively digits */
L_obj only_digits(L_obj x)
{
   while (x != NIL) {
      L_obj digit = Car[x];
      if (digit < '0' || digit > '9') return 0;
      x = Cdr[x];
   }
   return 1;
}

/*--------------------------------------------------------------------------*/
static L_obj in_word2() { /* read word */
   /* buffer with all the words in a line of input */
   static L_obj buffer = NIL;
   L_obj character, word, line, end_of_line, end_of_buffer;

   while ( buffer == NIL ) { /* read in a line */
      line = end_of_line = cons(NIL,NIL); /* stub */
      do 
      {    /* read characters until '\n' */
           character = getc(get_InputStream());
           if (character == EOF) return wrd_find_EOF;
           putchar(character);
           /* add character to end of line */
           end_of_line = Cdr[end_of_line] = cons(character,NIL);
      }  /* end of read characters until '\n' */
      while (character != '\n');

      line = Cdr[line]; /* remove stub at beginning of line */
      /* break line into words at  ( ) [ ] ' " characters */
      buffer = end_of_buffer = cons(NIL,NIL); /* stub */
      word = NIL;
      while ( line != NIL ) {
         character = Car[line];
         line = Cdr[line];
         /* look for characters that break words */
         if ( character == ' '  || character == '\n' ||
              character == '('  || character == ')'  ||
              character == '['  || character == ']'  ||
              character == '\'' || character == '\"' )
         { /* add nonempty word to end of buffer */
           if ( word != NIL )
           end_of_buffer = Cdr[end_of_buffer] = cons(word,NIL);
           word = NIL;
           /* add break character to end of buffer */
           if ( character != ' ' && character != '\n' )
           {   end_of_buffer = Cdr[end_of_buffer] = cons(cons(character,NIL),NIL);
           }
         }
         else
         { /* add character to word (in reverse order) */
           /* keep only nonblank printable ASCII codes */
           if (32 < character && character < 127)
           word = cons(character,word);
         }
      } /* end while ( line != NIL ) */
      buffer = Cdr[buffer]; /* remove stub at beginning of buffer */

   } /* end of do while ( buffer == NIL ) */

   /* if buffer nonempty, return first word in buffer */
   word = Car[buffer];
   buffer = Cdr[buffer];

   return word;
}

static L_obj wrd2atm(L_obj word)
{
   if (word == wrd_find_EOF) return word; 
   /* check if word consists only of digits */
   if (only_digits(word)) 
      word = mk_numb(remove_leading_zeros(word));
   /* also makes 00099 into 99 and 0000 into null */
   else
      word = lookup_word(word);  /* look up word in object list */
   /* also does mk_atom and adds it to object list if necessary */
   return word;
}

/* read word - skip comments */
static L_obj in_word(unsigned char cmtflag)
{
     L_obj word;
     while(1)
     {
        word = in_word2();
        if ( eq_wrd(word,begin_comment) )
           while ( !eq_wrd(in_word(1),end_comment) ); /* comments may be nested */
        else 
        {
           if(cmtflag) return word;
           else        return wrd2atm(word);
        }
     }
}

/* input m-exp */ 
L_obj in(unsigned char mexp, unsigned char rparenokay)
{
   L_obj w, first, last, next;
   short i;
   L_obj mcr;

   w=in_word(0);
   if (w == right_paren)
   {   if (rparenokay) return w; 
       else            return NIL; 
   }
   if (w == left_paren) 
   {   /* explicit list */
       first = last = cons(NIL,NIL);
       while((next = in(mexp,1)) != right_paren)
          last = Cdr[last] = cons(next,NIL);
       return Cdr[first];
   }

   if (!mexp) return w; /* atom */
   if (w == double_quote) return in(0,0); /* s-exp */

   /*--- Macro-expansion --------*/
   if((mcr=macro_expand(w)) != NIL) 
       return mcr;
   /*----------------------------*/

   i = Pf_args[w];
   if (i == 0) return w; /* normal atom (i.e. not function)*/
   /* atom is a primitive function with i-1 arguments */
   first = last = cons(w,NIL);
   while (--i > 0)
      last = Cdr[last] = cons(in(1,0),NIL);
   return first;
}

/*--- Macro-expansion --------------------------*/
static L_obj macro_expand(L_obj w)
{
    if(w == wrd_caar) /* expand caar */
        return 
            cons(wrd_car,
                 cons(cons(wrd_car,cons(in(1,0),NIL)),
                      NIL));
    if(w == wrd_cadr) /* expand cadr */
        return
            cons(wrd_car,
                 cons(cons(wrd_cdr,cons(in(1,0),NIL)),
                      NIL));
    if(w == wrd_caddr) /* expand caddr */
        return
            cons(wrd_car,
                 cons(cons(wrd_cdr,
                           cons(cons(wrd_cdr,cons(in(1,0),NIL)),
                                NIL)),
                      NIL));
    if(w == wrd_let) 
    {   /* expand let name def body  */
        L_obj name, def, body, var_lst;
        name = in(1,0);
        def  = in(1,0);
        body = in(1,0);
        if (!is_atom(name)) 
        { /* let (name var_lst) def body */
            var_lst = Cdr[name];
            name = Car[name];
            def = cons(wrd_quote,
                       cons(cons(wrd_lambda,
                                 cons(var_lst,
                                      cons(def,NIL))),
                            NIL));
        }
        /* let name def body */
        return
            cons(cons(wrd_quote,
                      cons(cons(wrd_lambda,
                                cons(cons(name,NIL),
                                     cons(body,NIL))),
                           NIL)),
                 cons(def,NIL));
    }
    if(w == wrd_not)
    {   return
            cons(wrd_if,
                 cons(in(1,0),
                      cons(wrd_false,cons(wrd_true, NIL))));
    }
    if(w == wrd_and)
    {   L_obj arg1=in(1,0), 
              arg2=in(1,0);
        return
            cons(wrd_if, 
                 cons(arg1,
                      cons(arg2, 
                           cons(wrd_false,NIL))));
    }
    if(w == wrd_or)
    {   L_obj arg1=in(1,0), 
              arg2=in(1,0);
        return
            cons(wrd_if, 
                 cons(arg1,
                      cons(wrd_true, 
                           cons(arg2,NIL))));
    }
    if(w == wrd_run_utm_on)
    {   L_obj re_try;
        re_try=
            cons(wrd_try,
                 cons(wrd_no_time_limit,
                      cons(cons(wrd_quote,
                                cons(cons(wrd_eval,
                                          cons(cons(wrd_read_exp,NIL),
                                               NIL)),
                                     NIL)),
                           cons(in(1,0),NIL))));
        return
            cons(wrd_car,
                 cons(cons(wrd_cdr,cons(re_try,NIL)),
                      NIL));
    }

    return NIL;
}
