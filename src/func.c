/*-----------------------------------------------------/
 *  FUNC.C 
 *  Lisp組み込み関数
 *----------------------------------------------------*/ 

#include "lisp_mt.h"

L_obj append(L_obj x, L_obj y) /* append two lists */
{
    if (x == NIL) return y;
    return cons(Car[x],append(Cdr[x],y));
}
 
L_obj eq(L_obj x, L_obj y) /* equal predicate */
{
    if (x == y) return 1;
    if (is_numb(x) && is_numb(y)) return eq_wrd(Pname[x],Pname[y]);
    if (is_numb(x) || is_numb(y)) return 0;
    if (is_atom(x) || is_atom(y)) return 0;
    if (eq(Car[x],Car[y])) return eq(Cdr[x],Cdr[y]);
    return 0;
}
 
L_obj length(L_obj x) /* number of elements in list */
{
    if (is_atom(x)) return NIL; /* is zero */
    return add1(length(Cdr[x]));
}

/* compare two decimal numbers */
L_obj compare(L_obj x, L_obj y)
{
    L_obj already_decided, digit1, digit2;

    if(x == NIL || y == NIL)
    {   if(x != NIL) return '>';
        if(y != NIL) return '<';
        return '=';
    }
    already_decided = compare(Cdr[x],Cdr[y]);
    if(already_decided != '=') return already_decided;
    digit1 = Car[x];
    digit2 = Car[y];
    if (digit1  < digit2) return '<';
    if (digit1  > digit2) return '>';
    return '=';
}

/* Original: --->
L_obj add1(L_obj x)  //add 1 to decimal number 
{
    L_obj digit;
    if (x == NIL) return cons('1',NIL);
    digit = Car[x];
    if (digit != '9') return cons(digit+1,Cdr[x]);
    return cons('0',add1(Cdr[x]));
}
<---*/
/*
 * オブジェクト xの中身を変更するようにするように変更
 */
L_obj add1(L_obj x)  //add 1 to decimal number 
{
    L_obj digit;
    if (x == NIL) return cons('1',NIL);
    digit = Car[x];
    if (digit != '9'){
        Car[x]++;
    }else{
        Car[x] = '0'; Cdr[x] = add1(Cdr[x]);
    }
    return x;
}

/* sub1を上のadd1と同様に考えて
 * 次の様にオブジェクト xの中身を変更するようにすると
 * eval.c内でのsub1の使用に支障を来す。
 */
/*--->
L_obj sub1(L_obj x) // subtract 1 from decimal number
{
    L_obj digit;
    if (x == NIL) return x; // 0 - 1 = 0
    digit = Car[x];
    if (digit == '1' && Cdr[x] == NIL) return NIL; // 1 - 1 = 0
    if (digit != '0'){
        Car[x]--; 
    }else{
        Car[x] = '9'; Cdr[x] = sub1(Cdr[x]);
    }
    return x;
} 
<--*/

L_obj sub1(L_obj x) // subtract 1 from decimal number 
{
    L_obj digit;
    if (x == NIL) return x; // 0 - 1 = 0
    digit = Car[x];
    if (digit == '1' && Cdr[x] == NIL) return NIL; // 1 - 1 = 0
    if (digit != '0') return cons(digit-1,Cdr[x]);
    return cons('9',sub1(Cdr[x]));
} 

/* pick-up decimal number from atom & convert non-number to zero */
L_obj nmb(L_obj x)
{
    if (is_numb(x)) return Pname[x];
    return NIL;
}

/* from reversed list of digits of decimal number */ 
L_obj remove_leading_zeros(L_obj x)
{
    L_obj rest, digit;
    if (x == NIL) return NIL;
    digit = Car[x];
    rest = remove_leading_zeros(Cdr[x]);
    if (rest == NIL && digit == '0') return NIL;
    return cons(digit,rest);
}

L_obj addition(L_obj x, L_obj y, L_obj carry_in)
{
    L_obj sum, digit1, digit2, rest1, rest2;
    if (x == NIL && !carry_in) return y;
    if (y == NIL && !carry_in) return x;
    if (x != NIL) {digit1 = Car[x]; rest1 = Cdr[x];}
             else {digit1 = '0'; rest1 = NIL;}
    if (y != NIL) {digit2 = Car[y]; rest2 = Cdr[y];}
             else {digit2 = '0'; rest2 = NIL;}
    sum = digit1 + digit2 + carry_in - '0';
    if (sum <= '9') return cons(sum,addition(rest1,rest2,0));
    return cons(sum-10,addition(rest1,rest2,1));
}

/* x - y assumes x >= y */
/* removeing leading 0 */
static L_obj cons_but_rm_leading_0(L_obj t,L_obj x)
{
    return (x==NIL && t=='0')? NIL : cons(t,x);
}

static L_obj sbtr_sub(L_obj x, L_obj y, L_obj borrow_in)
{
    L_obj difference, digit1, digit2, rest1, rest2;

    if (x == NIL) return NIL;
    if (y == NIL)
    {   
        if(!borrow_in) return x;
        digit2 ='0'; rest2 = NIL;
    }
    else
    {  
        digit2 = Car[y]; rest2 = Cdr[y];
    }

    digit1 = Car[x]; rest1 = Cdr[x];
    difference = digit1 - digit2 - borrow_in + '0';

    if (difference >= '0')
        return cons_but_rm_leading_0(difference,sbtr_sub(rest1,rest2,0));
    return cons_but_rm_leading_0(difference+10,
                                 sbtr_sub(rest1,rest2,1));
}

/*  x < y ==> 0(NIL)   */
L_obj subtraction(L_obj x, L_obj y)
{
    if (compare(x,y) != '>') return NIL; 
    return sbtr_sub(x,y,0);
}

static L_obj mltp_sub(long d, L_obj y, long c)
{
    long p;
    if (y == NIL) return c == 0? NIL : cons(c+'0',NIL);
    p = d*(Car[y]-'0') + c;
    c = p/10;
    return cons(p%10 + '0',mltp_sub(d, Cdr[y], c));
}

L_obj multiplication(L_obj x, L_obj y) /* goes faster if x is small */
{
    long d;
    L_obj sum = NIL;
    if (y == NIL) return NIL; /* otherwise produces result 0000 */
    while (x != NIL) {
        d = Car[x]-'0';
        sum = addition(sum, mltp_sub(d,y,0), 0);
        y = cons('0',y); 
        x = Cdr[x];
    }
    return sum;
}  

static L_obj div_sub(L_obj x, L_obj y, long i)
{
    if(compare(x,y) == '<') return cons(i+'0',x);
    return div_sub(subtraction(x,y),y,++i);
}

static L_obj div_aux0(L_obj x, L_obj y, L_obj stk)
{
    if(compare(Cdr[x],y)=='<') return cons(x,stk);
    return div_aux0( Cdr[x],y,cons(Car[x],stk ));
}

static L_obj div_aux1(L_obj x, L_obj y, L_obj stk, L_obj q)
{
    L_obj v = div_sub(x,y,0);
    if(is_atom(stk)) return cons( cons_but_rm_leading_0(quot(v),q),rem(v) );
    return div_aux1(cons_but_rm_leading_0( Car[stk],rem(v)),y,
                    Cdr[stk],
                    cons(quot(v),q) );
}

L_obj division(L_obj x, L_obj y)
{
    L_obj z,x0,stk;
    if(x == NIL) return NIL;
    z = div_aux0(x,y,NIL); x0=Car[z]; stk=Cdr[z];
    return div_aux1( x0,y,stk,NIL ); 
}

L_obj power(L_obj base, L_obj exponent)
{
    L_obj product = cons('1',NIL);
    while (exponent != NIL) {
        /* multiply faster if smaller comes first */
        product = multiplication(base,product);
        exponent = sub1(exponent);
    }
    return product;
}

L_obj base2_to_10(L_obj x) /* convert bit string to decimal number */
{
    L_obj result = NIL;
    while (!is_atom(x)) {
        L_obj next_bit = Car[x];
        x = Cdr[x];
        if (!is_numb(next_bit) || Pname[next_bit] != NIL) next_bit = 1; 
        else next_bit = 0;
        result = addition(result,result,next_bit);
    }
    return result;
}
 
L_obj halve(L_obj x) /* used to convert decimal number to bit string */
{
    L_obj digit, next_digit, rest, halve_digit;
    if (x == NIL) return x; /* half of 0 is 0 */
    digit = Car[x] - '0';
    x = Cdr[x];
    rest = halve(x);
    if (x == NIL)
       next_digit = 0;
    else 
        next_digit = Car[x] - '0';
    next_digit = next_digit%2; /* remainder when divided by 2 */
    halve_digit = '0' + (digit/2) + (5*next_digit);
    if (halve_digit != '0' || rest != NIL) 
       return cons(halve_digit,rest);
    return NIL;
}
 
L_obj base10_to_2(L_obj x) /* convert decimal number to bit string */
{
    L_obj bits = NIL;
    while (x != NIL) {
        L_obj digit = Car[x] - '0';
        bits = cons((digit%2 ? wrd_one : wrd_zero),bits);
        x = halve(x);
    }
    return bits;
}
 
L_obj size(L_obj x) /* number of characters in print representation */
{
    L_obj sum = NIL;
    if (is_numb(x) && Pname[x] == NIL) return add1(NIL); /* number zero */
    if (is_atom(x)) return length(Pname[x]);
    while (!is_atom(x)) {
       sum = addition(sum,size(Car[x]),0);
       x = Cdr[x];
       if (!is_atom(x)) sum = add1(sum); /* blank separator */
    }
    return add1(add1(sum)); /* open & close paren */
}
 
/* read one square of Turing machine tape */
L_obj read_bit(void)
{
    L_obj x, tape = Car[turing_machine_tapes];
    if (is_atom(tape)) return - wrd_out_of_data; /* tape finished ! */
    x = Car[tape];
    Car[turing_machine_tapes] = Cdr[tape];
    if (!is_numb(x) || Pname[x] != NIL) return wrd_one;
    return wrd_zero;
}


/* read one character from Turing machine tape */
L_obj read_char(void)
{
    L_obj c, b, i = 8;
    c = 0;
    while (i-- > 0) {
        b = read_bit();
        if (b < 0) return b; /* error? */
        if (Pname[b] != NIL) b = 1; else b = 0;
        c = c + c + b;
    }
    return c;
}
 
L_obj read_record(void) /* read record from Turing machine tape */
{  /* fill Buffer2 with all the words in an input record */
    L_obj character, word, line, end_of_line, end_of_buffer;
    line = end_of_line = cons(NIL,NIL); /* stub */
    do { /* read characters until '\n' */
        character = read_char();
        if (character < 0) return character; /* error? */;
        /* add character to end of line */
        end_of_line = Cdr[end_of_line] = cons(character,NIL);
    }  /* end of read characters until '\n' */
    while (character != '\n');
    line = Cdr[line]; /* remove stub at beginning of line */
    /* break line into words at ( ) characters */
    Buffer2 = end_of_buffer = cons(NIL,NIL); /* stub */
    word = NIL;
    while ( line != NIL ) {
        character = Car[line];
        line = Cdr[line];
        /* look for characters that break words */
        if ( character == ' ' || character == '\n' ||
             character == '(' || character == ')' )
        { /* add nonempty word to end of buffer */
          if ( word != NIL )
          end_of_buffer = Cdr[end_of_buffer] = cons(word,NIL);
          word = NIL;
          /* add break character to end of buffer */
          if ( character != ' ' && character != '\n' )
          end_of_buffer = Cdr[end_of_buffer] = cons(cons(character,NIL),NIL);
        }
        else
        { /* add character to word (in reverse order) */
          /* keep only nonblank printable ASCII codes */
          if (32 < character && character < 127)
          word = cons(character,word);
         }
    } /* end while ( line != NIL ) */
    Buffer2 = Cdr[Buffer2]; /* remove stub at beginning of buffer */
    return 0; /* indicates no error */
}
 
L_obj read_word(void) { /* read word from Turing machine tape */
    /* Buffer2 has all the words in the input record */
    L_obj word;
    /* (if buffer empty, returns as many right parens as needed) */
    if (Buffer2 == NIL) return right_paren;
    /* if buffer nonempty, return first word in buffer */
    word = Car[Buffer2];
    Buffer2 = Cdr[Buffer2];
    /* first check if word consists only of digits */
    if (only_digits(word)) word = mk_numb(remove_leading_zeros(word));
    /* also makes 00099 into 99 and 0000 into null */
    else word = lookup_word(word); /* look up word in object list */
    /* also does mk_atom and adds it to object list if necessary */
    return word;
}

/* read s-exp from Turing machine tape */
L_obj read_expr(unsigned char rparenokay)
{
    L_obj w = read_word(), first, last, next;
    if (w < 0) return w; /* error? */
    if (w == right_paren){ if (rparenokay) return w; else return NIL; }
    if (w == left_paren) { /* explicit list */
       first = last = cons(NIL,NIL);
       while ((next = read_expr(1)) != right_paren) {
           if (next < 0) return next; /* error? */
           last = Cdr[last] = cons(next,NIL);
       }
       return Cdr[first];
    } /* end if (w == left_paren) */
    return w; /* normal atom */
}

/* convert a number to the list of digits in reverse order */ 
static L_obj num2Lobj(long num)
{
    if(num<=0) return NIL;
    return cons('0'+ num%10, num2Lobj(num/10));
}

L_obj mk_numb_from_long(long num)
{
    if(num<=0) mk_numb(cons('0',NIL));
    return mk_numb(num2Lobj(num));
}

/* find word in object list */
L_obj find_word_in_obj_lst(L_obj x)
{
    L_obj i,j;
    long k,n, n_curr;
    i= obj_lst_get(); n=-1; j=-1;
    for(k=0; !is_atom(i); i = Cdr[i],k++ ) 
    {   /* if word is found in object list */
       if (eq_wrd(Pname[get_atm_obj_lst(i)],Pname[x]))
       {   
           n=k; j=i;
       }
    }
    n_curr=k;  /* current object number */

    if(n>=0 && get_atm_obj_lst(j)==x) /* found object in obj_lst */
        return cons(cons(mk_numb_from_long(x),cons(Vlst[x],NIL)),
                    cons(mk_numb_from_long(n_curr-n),
               cons(mk_numb_from_long(n_curr),NIL)));
    return cons(mk_numb_from_long(x),
                cons(mk_atom(0,"not-found",0),
                     cons(mk_numb_from_long(n_curr),NIL)));
}
