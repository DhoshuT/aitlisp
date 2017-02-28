<TeXmacs|1.0.7.19>

<style|<tuple|generic|my-utils|my-math>>

<\body>
  <\hide-preamble>
    <assign|par-sep|0.05fn><assign|par-par-sep|0.2fn><assign|par-mode|left>

    <assign|lcode|<macro|codes|<block|<tformat|<cwith|1|1|1|1|cell-background|#eeffee>|<cwith|1|1|1|1|cell-hyphen|t>|<cwith|1|1|1|1|cell-width|1par>|<cwith|1|1|1|1|cell-hmode|exact>|<table|<row|<\cell>
      <verbatim|<with|color|#001144|<arg|codes>>>
    </cell>>>>>>>
  </hide-preamble>

  <set-this-page-header|<small|Takama M., \ 2010. 9. 4<space|2em>Using
  GNU/<TeXmacs>>><subsection|Chaitin\<#5148\>\<#751F\>\<#306E\>Toy
  Lisp\<#3067\>\<#904A\>\<#3076\> >

  <subsubsection|<sikaku> Chaitin\<#5148\>\<#751F\>\<#306E\>Toy Lisp>

  Gregory J. Chaitin\<#306F\>\<#300C\>Kolmogorov-Chaitin
  Complexity\<#300D\>\<#306E\>\<#7406\>\<#8AD6\>
  <math|=>\<#300C\>\<#30A2\>\<#30EB\>\<#30B4\>\<#30EA\>\<#30BA\>\<#30E0\>\<#7684\>\<#60C5\>\<#5831\>\<#7406\>\<#8AD6\>\<#300D\>\<#306E\>\<#5275\>\<#59CB\>\<#8005\>\<#3068\>\<#3057\>\<#3066\>\<#77E5\>\<#3089\>\<#308C\>\<#3066\>\<#3044\>\<#308B\>\<#3002\>\ 

  Springer\<#304B\>\<#3089\>\<#51FA\>\<#7248\>\<#3055\>\<#308C\>\<#305F\>\<#4E09\>\<#90E8\>\<#4F5C\><\footnote>
    ``The Limit of mathematics (1998)'' , \ ``The Unkowable (1999)'',\ 

    \ \ \ ``Exploring Randomness (2001)''
  </footnote>\<#306F\>\<#3001\>\<#81EA\>\<#3089\>\<#304C\>\<#4F5C\>\<#3063\>\<#305F\>\<#7C21\>\<#6613\>
  Lisp\<#3092\>\<#4F7F\>\<#3063\>\<#3066\>\<#3001\>\<#7406\>\<#8AD6\>\<#3092\>\<#5B9F\>\<#969B\>\<#306B\>\<#30B3\>\<#30F3\>\<#30D4\>\<#30E5\>\<#30FC\>\<#30BF\>\<#3092\>\<#4F7F\>\<#3063\>\<#3066\>\<#78BA\>\<#3081\>\<#308B\>\<#5185\>\<#5BB9\>\<#3068\>\<#306A\>\<#3063\>\<#3066\>\<#3044\>\<#308B\>\<#3002\>\<#305D\>\<#306E\>\<#7C21\>\<#6613\>Lisp\<#30A4\>\<#30F3\>\<#30BF\>\<#30D7\>\<#30EA\>\<#30BF\>\<#306B\>\<#306F\>Mathematica,
  C, Java\<#3068\>\<#4E09\>\<#3064\>\<#306E\>\<#8A00\>\<#8A9E\>\<#306E\>\<#7248\>\<#304C\>\<#3042\>\<#308B\><\footnote>
    Chitin\<#6C0F\>\<#306E\>\<#30B5\>\<#30A4\>\<#30C8\>\<#304B\>\<#3089\>\<#5165\>\<#624B\>\<#53EF\>\<#80FD\>

    \ \ (\<#76F4\>\<#63A5\>\<#306B\>\<#306F\>
    http://www.cs.auckland.ac.nz/~chaitin/lisp.c )
  </footnote>\<#3002\>\<#4F8B\>\<#3048\>\<#3070\>\<#3001\>C\<#7248\>\<#306F\>1000\<#884C\>\<#7A0B\>\<#5EA6\>\<#306E\>\<#30D7\>\<#30ED\>\<#30B0\>\<#30E9\>\<#30E0\>\<#3067\>\<#3042\>\<#308B\>\<#3002\>\<#30B3\>\<#30FC\>\<#30C9\>\<#3092\>\<#5B8C\>\<#5168\>\<#306B\>\<#8FFD\>\<#3046\>\<#3053\>\<#3068\>\<#3082\>\<#3001\>\<#305D\>\<#306E\>\<#6C17\>\<#306B\>\<#306A\>\<#308C\>\<#3070\>\<#305D\>\<#308C\>\<#307B\>\<#3069\>\<#5927\>\<#5909\>\<#3067\>\<#306F\>\<#306A\>\<#3044\>\<#3002\>

  \<#4EE5\>\<#4E0B\>\<#3067\>\<#306F\>\<#3053\>\<#306E\>Chaitin\<#306E\>\<#7C21\>\<#6613\>Lisp\<#3092\>\<#7D39\>\<#4ECB\>\<#3059\>\<#308B\>\<#3002\>\<#305F\>\<#3060\>\<#3057\>\<#3001\>\<#4E09\>\<#90E8\>\<#4F5C\>\<#306E\>\<#4E2D\>\<#3067\>\<#3001\>\<#3053\>\<#306E\>Lisp\<#306F\>\<#4E8C\>\<#9032\>\<#30C6\>\<#30FC\>\<#30D7\>\<#3092\>\<#6301\>\<#3064\>\<#6C4E\>\<#7528\>\<#30C1\>\<#30E5\>\<#30FC\>\<#30EA\>\<#30F3\>\<#30B0\>\<#6A5F\>\<#68B0\>\<#30DE\>\<#30B7\>\<#30F3\>\<#306E\>\<#30A8\>\<#30DF\>\<#30E5\>\<#30EC\>\<#30FC\>\<#30BF\>\<#3068\>\<#3057\>\<#3066\>\<#4F7F\>\<#308F\>\<#308C\>\<#308B\>\<#306E\>\<#3067\>\<#3042\>\<#308B\>\<#304C\>\<#3001\>\<#305D\>\<#306E\>\<#305F\>\<#3081\>\<#306E\>\<#7279\>\<#6B8A\>\<#306A\>\<#6A5F\>\<#80FD\>\<#306B\>\<#3064\>\<#3044\>\<#3066\>\<#306F\>\<#3053\>\<#3053\>\<#3067\>\<#306F\>\<#5168\>\<#304F\>\<#89E6\>\<#308C\>\<#306A\>\<#3044\>\<#3002\>

  \<#3055\>\<#3066\>\<#3001\>\<#3053\>\<#306E\>Lisp\<#3001\>\<#81EA\>\<#7136\>\<#6570\>\<#3057\>\<#304B\>\<#6271\>\<#3048\>\<#306A\>\<#3044\>\<#7C21\>\<#6613\>
  Lisp\<#3067\>\<#3042\>\<#3063\>\<#3066\>\<#3001\>\<#975E\>\<#5E38\>\<#306B\>\<#7C21\>\<#5358\>\<#306B\>\<#4F5C\>\<#3089\>\<#308C\>\<#3066\>\<#3044\>\<#308B\>\<#3002\>\<#3057\>\<#304B\>\<#3057\>\<#3001\>\<#305D\>\<#3046\>\<#3067\>\<#3042\>\<#3063\>\<#3066\>\<#3082\>\<#4F8B\>\<#3048\>\<#3070\>C\<#8A00\>\<#8A9E\>\<#3067\>\<#306F\>\<#7C21\>\<#5358\>\<#306B\>\<#306F\>\<#3067\>\<#304D\>\<#306A\>\<#3044\>\<#3088\>\<#3046\>\<#306A\>\<#82B8\>\<#5F53\>\<#3082\>\<#898B\>\<#305B\>\<#3066\>\<#304F\>\<#308C\>\<#308B\>\<#3002\>\<#305F\>\<#3060\>\<#3057\>\<#3001\>\<#7C21\>\<#5358\>\<#306B\>\<#4F5C\>\<#3089\>\<#308C\>\<#3066\>\<#3044\>\<#308B\>\<#305F\>\<#3081\>\<#306B\>\<#3001\>
  \<#672C\>\<#683C\>\<#7684\>\<#306A\> \ Lisp\<#3067\>\<#3042\>\<#308B\>
  Scheme \<#3084\> Common Lisp\<#3068\>\<#306F\>\<#7570\>\<#306A\>\<#3063\>\<#305F\>\<#632F\>\<#308B\>\<#821E\>\<#3044\>\<#3092\>\<#3059\>\<#308B\>\<#5834\>\<#5408\>\<#304C\>\<#3042\>\<#308A\>\<#3001\>\<#6CE8\>\<#610F\>\<#3059\>\<#308B\>\<#5FC5\>\<#8981\>\<#304C\>\<#3042\>\<#308B\>\<#3002\>

  Chaitin Lisp \<#306E\>\<#7D44\>\<#307F\>\<#8FBC\>\<#307F\>\<#95A2\>\<#6570\>\<#306F\>\<#5F15\>\<#6570\>\<#306E\>\<#6570\>\<#304C\>\<#95A2\>\<#6570\>\<#6BCE\>\<#306B\>\<#5B9A\>\<#307E\>\<#3063\>\<#3066\>\<#3044\>\<#308B\>\<#306E\>\<#3067\><\footnote>
    \<#9006\>\<#306B\>\<#8A00\>\<#3048\>\<#3070\>\<#3001\>\<#5B9A\>\<#307E\>\<#3063\>\<#305F\>\<#5F15\>\<#6570\>\<#306E\>\<#95A2\>\<#6570\>\<#3057\>\<#304B\>\<#7D44\>\<#307F\>\<#8FBC\>\<#307F\>\<#95A2\>\<#6570\>\<#3068\>\<#3057\>\<#3066\>\<#8A31\>\<#3055\>\<#308C\>\<#3066\>\<#3044\>\<#306A\>\<#3044\>\<#3002\>
  </footnote>\<#3001\>Lisp \ \<#304C\>\<#6F14\>\<#7B97\>\<#306B\>\<#95A2\>\<#3057\>\<#3066\>\<#524D\>\<#7F6E\>\<#5F62\>\<#5F0F\>\<#3092\>\<#63A1\>\<#7528\>\<#3057\>\<#3066\>\<#3044\>\<#308B\>\<#306E\>\<#3068\>\<#76F8\>\<#307E\>\<#3063\>\<#3066\>\<#3001\>\<#7D44\>\<#307F\>\<#8FBC\>\<#307F\>\<#95A2\>\<#6570\>\<#306B\>\<#95A2\>\<#3057\>\<#3066\>\<#306F\>\<#62EC\>\<#5F27\>\<#304C\>\<#4E0D\>\<#8981\>\<#3068\>\<#306A\>\<#3063\>\<#3066\>\<#3044\>\<#308B\><footnote|\<#62EC\>\<#5F27\>\<#306E\>\<#958B\>\<#9589\>\<#30C1\>\<#30A7\>\<#30C3\>\<#30AF\>\<#6A5F\>\<#80FD\>\<#3092\>\<#6301\>\<#305F\>\<#306A\>\<#3044\>\<#30A8\>\<#30C7\>\<#30A3\>\<#30BF\>\<#3092\>\<#4F7F\>\<#3046\>\<#969B\>\<#306B\>\<#306F\>\<#975E\>\<#5E38\>\<#306B\>\<#3042\>\<#308A\>\<#304C\>\<#305F\>\<#3044\>\<#3002\>>\<#3002\>\<#305F\>\<#3060\>\<#3057\>\<#3001\>
  \<#81EA\>\<#5206\>\<#3067\>\<#5B9A\>\<#7FA9\>\<#3057\>\<#305F\>\<#95A2\>\<#6570\>\<#3092\>\<#4F7F\>\<#3046\>\<#969B\>\<#306B\>\<#306F\>\<#62EC\>\<#5F27\>\<#304C\>\<#5FC5\>\<#8981\>\<#3068\>\<#306A\>\<#308B\>\<#3002\>

  <subsubsection|<sikaku> \<#7C21\>\<#5358\>\<#306A\>\<#8A08\>\<#7B97\>>

  \<#30EA\>\<#30B9\>\<#30D7\>\<#306E\>\<#6F14\>\<#7B97\>\<#306F\>\<#524D\>\<#7F6E\>\<#5F62\>\<#5F0F\>

  <\lcode>
    + 2 * 7 - 12 5

    expression \ (+ 2 (* 7 (- 12 5)))

    value \ \ \ \ \ \ 51
  </lcode>

  \;

  <subsubsection|\<#30EA\>\<#30B9\>\<#30C8\>\<#FF1A\>\<#3000\>cons, \ cdr,
  \ car>

  \<#30EA\>\<#30B9\>\<#30D7\>\<#306E\>\<#57FA\>\<#672C\>\<#30C7\>\<#30FC\>\<#30BF\>\<#69CB\>\<#9020\>\<#306F\>\<#30EA\>\<#30B9\>\<#30C8\>

  <with|font-family|tt|nil> \<#FF1A\>\<#7A7A\>\<#30EA\>\<#30B9\>\<#30C8\>

  <\lcode>
    nil \ \ \ \ \ \ \ [\<less\>= \<#5165\>\<#529B\> ]

    expression \ nil

    value \ \ \ \ \ \ ()

    \;

    = nil '() \ [\<less\>= \<#5165\>\<#529B\> ]

    expression \ (= nil (' ()))

    value \ \ \ \ \ \ true
  </lcode>

  \;

  <with|font-family|tt|cons> \<#FF1A\>\<#8981\>\<#7D20\>\<#3092\>\<#30EA\>\<#30B9\>\<#30C8\>\<#5148\>\<#982D\>\<#306B\>\<#8FFD\>\<#52A0\>(<math|\<Rightarrow\>>\<#30EA\>\<#30B9\>\<#30C8\>\<#3092\>\<#69CB\>\<#6210\>)

  <\lcode>
    cons 3 cons 2 cons 1 nil

    expression \ (cons 3 (cons 2 (cons 1 nil)))

    value \ \ \ \ \ \ (3 2 1)
  </lcode>

  \;

  <with|font-family|tt|car> \<#FF1A\> \<#30EA\>\<#30B9\>\<#30C8\>\<#5148\>\<#982D\>\<#8981\>\<#7D20\>\<#3092\>\<#53D6\>\<#308A\>\<#51FA\>\<#3059\>

  <\lcode>
    car '(3 2 1)

    expression \ (car (' (3 2 1)))

    value \ \ \ \ \ \ 3
  </lcode>

  <with|font-family|tt|cdr> \<#FF1A\> \<#30EA\>\<#30B9\>\<#30C8\>\<#5148\>\<#982D\>\<#8981\>\<#7D20\>\<#3092\>\<#9664\>\<#3044\>\<#305F\>\<#6B8B\>\<#308A\>

  <\lcode>
    cdr '(3 2 1)

    expression \ (cdr (' (3 2 1)))

    value \ \ \ \ \ \ (2 1)
  </lcode>

  \;

  <\subsubsection>
    <sikaku> \<#30EA\>\<#30B9\>\<#30D7\>\<#5F0F\>\<#3001\>\<#30A2\>\<#30C8\>\<#30E0\>\<#3001\>\<#30EA\>\<#30B9\>\<#30C8\>
  </subsubsection>

  <strong|\<#30EA\>\<#30B9\>\<#30D7\>\<#5F0F\>>\<#306F\><strong|\<#30A2\>\<#30C8\>\<#30E0\>>\<#3068\><strong|\<#30EA\>\<#30B9\>\<#30C8\>>\<#304B\>\<#3089\>\<#306A\>\<#308B\>\<#3002\>\ 

  \<#5F0F\>\<#4E2D\>\<#306B\>\<#73FE\>\<#308C\>\<#308B\>\<#30B7\>\<#30F3\>\<#30DC\>\<#30EB\>\<#3084\>\<#6570\>\<#306F\>\<#30A2\>\<#30C8\>\<#30E0\>\<#3067\>\<#3042\>\<#308B\>\<#3002\>

  <with|font-family|tt|nil><math|=<mbox|\<#7A7A\>\<#30EA\>\<#30B9\>\<#30C8\>>>
  \<#306F\>\<#30A2\>\<#30C8\>\<#30E0\>\<#304B\>\<#3064\>\<#30EA\>\<#30B9\>\<#30C8\>\<#3068\>\<#306A\>\<#308B\>\<#552F\>\<#4E00\>\<#306E\>\<#4F8B\>\<#5916\>\<#3002\>

  <\lcode>
    atom? '(a b c)

    expression \ (atom? (' (a b c)))

    value \ \ \ \ \ \ false

    \;

    atom? '()

    expression \ (atom? (' ()))\ 

    value \ \ \ \ \ \ true
  </lcode>

  \<#30A2\>\<#30C8\>\<#30E0\>\<#306B\>\<#305D\>\<#306E\>\<#5024\>\<#3068\>\<#3057\>\<#3066\>\<#3001\>\<#4F55\>\<#3089\>\<#304B\>\<#306E\>\<#30EA\>\<#30B9\>\<#30D7\>\<#5F0F\>\<#3092\>\<#95A2\>\<#9023\>\<#4ED8\>\<#3051\>\<#308B\>\<#3053\>\<#3068\>\<#3092\>\<#300C\>\<#675F\>\<#7E1B\>\<#300D\>\<#3068\>\<#3044\>\<#3046\>\<#3002\>\<#30A2\>\<#30C8\>\<#30E0\>\<#306F\>\<#751F\>\<#6210\>\<#3055\>\<#308C\>\<#305F\>\<#6BB5\>\<#968E\>\<#3067\>\<#306F\>\<#81EA\>\<#5206\>\<#81EA\>\<#8EAB\>\<#306B\>\<#675F\>\<#7E1B\>\<#3055\>\<#308C\>\<#3066\>\<#3044\>\<#308B\>\<#3002\>\<#30A2\>\<#30C8\>\<#30E0\>\<#304C\>\<#8A55\>\<#4FA1\>\<#3055\>\<#308C\>\<#308B\>\<#3068\>\<#305D\>\<#306E\>\<#30A2\>\<#30C8\>\<#30E0\>\<#306B\>\<#675F\>\<#7E1B\>\<#3055\>\<#308C\>\<#3066\>\<#3044\>\<#308B\>\<#30EA\>\<#30B9\>\<#30D7\>\<#5F0F\>\<#304C\>\<#8FD4\>\<#3055\>\<#308C\>\<#308B\>\<#3002\>

  <\lcode>
    a \ \ \ \ \ \ \ \ \ [\<less\>= \<#5165\>\<#529B\> ]

    expression \ a

    value \ \ \ \ \ \ a
  </lcode>

  \;

  <with|font-family|tt|define> \<#3092\>\<#4F7F\>\<#3063\>\<#3066\>\<#73FE\>\<#5728\>\<#306E\>\<#8A08\>\<#7B97\>\<#74B0\>\<#5883\>\<#306B\>\<#304A\>\<#3044\>\<#3066\>\<#6709\>\<#52B9\>\<#306A\>\<#5927\>\<#57DF\>\<#7684\>\<#306A\>\<#675F\>\<#7E1B\>\<#3092\>\<#4F5C\>\<#308B\>\<#3053\>\<#3068\>\<#304C\>\<#3067\>\<#304D\>\<#308B\>\<#3002\>

  <with|font-family|tt|lambda> \<#3092\>\<#4F7F\>\<#3063\>\<#3066\>\<#4E00\>\<#3064\>\<#306E\>\<#30EA\>\<#30B9\>\<#30D7\>\<#5F0F\>\<#306E\>\<#4E2D\>\<#3060\>\<#3051\>\<#3067\>\<#6709\>\<#52B9\>\<#306A\>\<#5C40\>\<#6240\>\<#7684\>\<#306A\>\<#675F\>\<#7E1B\>\<#3092\>\<#4F5C\>\<#308B\>\<#3053\>\<#3068\>\<#304C\>\<#3067\>\<#304D\>\<#308B\>\<#3002\>

  <\lcode>
    define a 7 [\<less\>= \<#5165\>\<#529B\> ]

    define \ \ \ \ \ a

    value \ \ \ \ \ \ 7

    * a a \ \ \ \ \ [\<less\>= \<#5165\>\<#529B\> ]

    expression \ (* a a)\ 

    value \ \ \ \ \ \ 49

    ('lambda (a) * a a \ 5) \ \ [\<less\>= \<#5165\>\<#529B\> ]

    expression \ ((' (lambda (a) (* a a))) 5)

    value \ \ \ \ \ \ 25

    * a a \ \ \ \ \ [\<less\>= \<#5165\>\<#529B\> ]

    expression \ (* a a)

    value \ \ \ \ \ \ 49
  </lcode>

  \;

  \<#4E0A\>\<#306E\><with|font-family|tt|('lambda (a) * a a
  5)>\<#306F\>\<#3001\>\<#6B21\>\<#306E\>\<#3088\>\<#3046\>\<#306B\><with|font-family|tt|let>\<#3092\>\<#4F7F\>\<#3063\>\<#3066\>\<#66F8\>\<#304F\>\<#3053\>\<#3068\>\<#3082\>\<#3067\>\<#304D\>\<#308B\>\<#3002\><with|font-family|tt|let>\<#3092\>\<#4F7F\>\<#3063\>\<#305F\>\<#5F0F\>\<#306F\><strong|\<#7CD6\>\<#8863\>\<#69CB\>\<#6587\>>\<#3067\>\<#4E21\>\<#8005\>\<#306F\>\<#5168\>\<#304F\>\<#540C\>\<#7B49\>\<#3067\>\<#3042\>\<#308B\>\<#3002\>(
  expression\<#3092\>\<#898B\>\<#3088\>\<#3002\>)

  <\lcode>
    let a 5 * a a

    expression \ ((' (lambda (a) (* a a))) 5)

    value 25
  </lcode>

  \;

  \;

  <subsubsection|<sikaku> \<#95A2\>\<#6570\>\<#3068\>\<#95A2\>\<#6570\>\<#9069\>\<#7528\>\<#3001\>\<#5F0F\>\<#306E\>\<#8A55\>\<#4FA1\>>

  \<#7E70\>\<#308A\>\<#8FD4\>\<#3059\>\<#3068\>\<#3001\>\<#30A2\>\<#30C8\>\<#30E0\>\<#304C\>\<#8A55\>\<#4FA1\>\<#3055\>\<#308C\>\<#308B\>\<#3068\>\<#305D\>\<#306E\>\<#30A2\>\<#30C8\>\<#30E0\>\<#306B\>\<#675F\>\<#7E1B\>\<#3055\>\<#308C\>\<#3066\>\<#3044\>\<#308B\>\<#30EA\>\<#30B9\>\<#30D7\>\<#5F0F\>\<#304C\>\<#8FD4\>\<#3055\>\<#308C\>\<#308B\>\<#3002\>\<#30EA\>\<#30B9\>\<#30C8\>\<#306F\><strong|\<#57FA\>\<#672C\>\<#7684\>\<#306B\>>\<#6B21\>\<#306E\>\<#3088\>\<#3046\>\<#306B\>\<#8A55\>\<#4FA1\>\<#3055\>\<#308C\>\<#308B\>\<#3002\>

  <parag-box|<space|2em><verbatim|( \<less\>func\<gtr\> \<less\>arg_1\<gtr\>
  \<less\>arg_2\<gtr\> ... \<less\>arg_n\<gtr\> )>>

  \<#30EA\>\<#30B9\>\<#30C8\>\<#306E\>\<#5148\>\<#982D\>\<#8981\>\<#7D20\>\<#304C\>\<#8A55\>\<#4FA1\>\<#3055\>\<#308C\>\<#95A2\>\<#6570\>\<#3068\>\<#89E3\>\<#91C8\>\<#3055\>\<#308C\>\<#308B\>\<#3002\>\<#30EA\>\<#30B9\>\<#30C8\>\<#306E\>\<#4E8C\>\<#756A\>\<#76EE\>\<#4EE5\>\<#964D\>\<#306E\>\<#8981\>\<#7D20\>(=\<#5F15\>\<#6570\>)\<#304C\>\<#305D\>\<#308C\>\<#305E\>\<#308C\>\<#8A55\>\<#4FA1\>\<#3055\>\<#308C\>\<#3001\>\<#30EA\>\<#30B9\>\<#30C8\>\<#7B2C\>\<#4E00\>\<#8981\>\<#7D20\>\<#306E\>\<#8A55\>\<#4FA1\>\<#7D50\>\<#679C\>\<#3068\>\<#3057\>\<#3066\>\<#5F97\>\<#3089\>\<#308C\>\<#305F\>\<#95A2\>\<#6570\>\<#306B\>\<#9069\>\<#7528\>\<#3055\>\<#308C\>\<#308B\>\<#3002\>

  \<#95A2\>\<#6570\>\<#306F\><with|font-family|tt|lambda>\<#5F0F\>\<#306B\>\<#3088\>\<#3063\>\<#3066\>\<#4F5C\>\<#3089\>\<#308C\>\<#308B\>\<#3002\>\<#6B21\>\<#306B\>\<#793A\>\<#3059\>\<#306E\>\<#306F\>\<#3001\>\<#4E00\>\<#5909\>\<#6570\><math|x>\<#3092\>\<#5F15\>\<#6570\>\<#3068\>\<#3057\>\<#3001\><math|x<rsup|2>>\<#3092\>\<#305D\>\<#306E\>\<#5024\>\<#3068\>\<#3059\>\<#308B\>\<#95A2\>\<#6570\>\<#3067\>\<#3042\>\<#308B\>\<#3002\>

  <\parag-box>
    <\equation>
      <text|<verbatim|lambda (x) * x x>><label|sq>
    </equation>
  </parag-box>

  \<#5148\>\<#306E\>\<#8AAC\>\<#660E\>\<#3067\>\<#306F\>

  <\lcode>
    ('lambda (x) * x x \ 5)

    expression \ ((' (lambda (x) (* x x))) 5)

    value \ \ \ \ \ \ 25
  </lcode>

  \<#306E\>\<#8A08\>\<#7B97\>\<#3092\>\<#3001\>\<#5C40\>\<#6240\>\<#7684\>\<#306B\>
  <math|x>\<#306B\> 5\<#3092\>\<#675F\>\<#7E1B\>\<#3055\>\<#305B\>\<#3001\>\<#305D\>\<#306E\>\<#675F\>\<#7E1B\>\<#4E0B\>\<#3067\><math|x\<times\>x>\<#3092\>\<#8A08\>\<#7B97\>\<#3055\>\<#305B\>\<#308B\>\<#3001\>\<#3068\>\<#3057\>\<#305F\>\<#3002\>\<#3053\>\<#308C\>\<#3092\>\<#3001\>\<#300C\>\<#95A2\>\<#6570\>(<reference|sq>)\<#306B\>\<#6570\><math|5>\<#3092\><strong|\<#9069\>\<#7528\>>\<#3059\>\<#308B\>\<#300D\>\<#3068\>\<#8A00\>\<#3046\>\<#3002\>

  \<#3055\>\<#3066\>\<#3001\>\<#95A2\>\<#6570\>(<reference|sq>)\<#306F\>\<#540D\>\<#524D\>\<#304C\>\<#306A\>\<#3044\><strong|\<#7121\>\<#540D\>\<#306E\>\<#95A2\>\<#6570\>>\<#3067\>\<#3042\>\<#308B\>\<#3002\>\<#95A2\>\<#6570\>\<#3092\>\<#540D\>\<#524D\>\<#3067\>\<#53C2\>\<#7167\>\<#3059\>\<#308B\>\<#306B\>\<#306F\>\<#3001\>\<#95A2\>\<#6570\>(<reference|sq>)\<#3092\>\<#5024\>\<#3068\>\<#3059\>\<#308B\>\<#30A2\>\<#30C8\>\<#30E0\>\<#3092\>\<#7528\>\<#610F\>\<#3059\>\<#308C\>\<#3070\>\<#3088\>\<#3044\>\<#3002\>
  \<#3064\>\<#307E\>\<#308A\>\<#3001\><with|font-family|tt|define>\<#3092\>\<#4F7F\>\<#3063\>\<#3066\>

  <\lcode>
    define square 'lambda (x) * x x

    define \ \ \ \ \ square

    value \ \ \ \ \ \ (lambda (x) (* x x))
  </lcode>

  \<#3068\>\<#3059\>\<#308B\>\<#3002\>

  <\lcode>
    (square 7)

    expression \ (square 7)

    value \ \ \ \ \ \ 49
  </lcode>

  \;

  \<#3053\>\<#306E\>\<#8A08\>\<#7B97\>\<#4F8B\>\<#3067\>\<#306F\>\<#30EA\>\<#30B9\>\<#30C8\>\<#306E\>\<#8A55\>\<#4FA1\>\<#5247\>\<#306B\>\<#5F93\>\<#3044\>\<#3001\><with|font-family|tt|square>\<#304C\>\<#8A55\>\<#4FA1\>\<#3055\>\<#308C\>\<#3066\>\<#95A2\>\<#6570\>(<reference|sq>)\<#304C\>\<#8FD4\>\<#3055\>\<#308C\>\<#3001\>\<#305D\>\<#308C\>\<#306B\><math|7>\<#304C\>\<#9069\>\<#7528\>\<#3055\>\<#308C\>\<#3066\><math|49>
  \<#304C\>\<#5F97\>\<#3089\>\<#308C\>\<#3066\>\<#3044\>\<#308B\>\<#3002\>

  <with|font-family|tt|define>\<#306B\>\<#306F\>\<#95A2\>\<#6570\>\<#5B9A\>\<#7FA9\>\<#306E\>\<#305F\>\<#3081\>\<#306E\>\<#6B21\>\<#306E\>\<#5F62\>\<#5F0F\>\<#306E\>\<#7CD6\>\<#8863\>\<#69CB\>\<#6587\>\<#3082\>\<#7528\>\<#610F\>\<#3055\>\<#308C\>\<#3066\>\<#3044\>\<#308B\>\<#3002\>

  <\lcode>
    define (square x) * x x

    define \ \ \ \ \ square

    value \ \ \ \ \ \ (lambda (x) (* x x))
  </lcode>

  \<#3053\>\<#308C\>\<#3089\>\<#4E8C\>\<#3064\>

  <\parag-box>
    <space|2em><with|font-family|tt|define (square x) * x x>

    <space|2em><with|font-family|tt|define square 'lambda (x) * x x>
  </parag-box>

  \;

  \<#306F\>\<#5168\>\<#304F\>\<#540C\>\<#7B49\>\<#306E\>\<#5F0F\>\<#3067\>\<#3042\>\<#308B\>\<#3002\>

  <strong|\<#30EA\>\<#30B9\>\<#30C8\>\<#8A55\>\<#4FA1\>\<#306E\>\<#4F8B\>\<#5916\>>\<#306F\>\<#30EA\>\<#30B9\>\<#30C8\>\<#5148\>\<#982D\>\<#8981\>\<#7D20\>\<#304C\>
  <with|font-family|tt|define>, <with|font-family|tt|lambda>,
  <with|font-family|tt|'>, <with|font-family|tt|``>, <with|font-family|tt|if>
  \<#306E\>\<#5834\>\<#5408\>\<#306B\>\<#9650\>\<#308B\>\<#3002\><with|font-family|tt|'>\<#306F\>quote\<#3068\>\<#547C\>\<#3070\>\<#308C\>\<#3001\>\<#4E00\>\<#3064\>\<#306E\>\<#5F15\>\<#6570\>\<#3092\>\<#53D6\>\<#308B\>\<#3002\><with|font-family|tt|'>\<#306E\>\<#52B9\>\<#679C\>\<#306F\>\<#3001\>\<#5F15\>\<#6570\>\<#3092\>\<#8A55\>\<#4FA1\>\<#305B\>\<#305A\>\<#306B\>\<#305D\>\<#306E\>\<#307E\>\<#307E\>\<#8FD4\>\<#3059\>\<#3053\>\<#3068\>\<#3067\>\<#3042\>\<#308B\>\<#3002\>

  <\lcode>
    '+ 2 3

    expression \ (' (+ 2 3))

    value \ \ \ \ \ \ (+ 2 3)
  </lcode>

  <subsubsection|<sikaku> \<#53CD\>\<#5FA9\>(\<#518D\>\<#5E30\>)\<#8A08\>\<#7B97\>>

  \<#53CD\>\<#5FA9\>\<#8A08\>\<#7B97\>\<#306E\>\<#5178\>\<#578B\>\<#4F8B\>\<#3068\>\<#3057\>\<#3066\><math|1+2+3+\<cdots\>+n>
  \<#3092\>\<#8A08\>\<#7B97\>\<#3057\>\<#3066\>\<#307F\>\<#3088\>\<#3046\>\<#3002\>Lisp\<#3067\>\<#306F\>\<#3001\>\<#6B21\>\<#306E\>\<#4E8C\>\<#901A\>\<#308A\>\<#306E\>\<#65B9\>\<#6CD5\>\<#304C\>\<#5178\>\<#578B\>\<#7684\>\<#3067\>\<#3042\>\<#308B\>\<#3002\>

  <\lcode>
    [1. ]

    define (sum1 n) if = n 0 0 + n (sum1 - n 1)

    define \ \ \ \ \ sum1\ 

    value \ \ \ \ \ \ (lambda (n) (if (= n 0) 0 (+ n (sum (-

    \ \ \ \ \ \ \ \ \ \ \ \ n 1)))))

    (sum 100)

    expression \ (sum1 100)

    value \ \ \ \ \ \ 5050

    \;

    [2. ]

    define (sum2 n s) if = n 0 s (sum2 - n 1 + s n)

    define \ \ \ \ \ sum2\ 

    value \ \ \ \ \ \ (lambda (n s) (if (= n 0) s (sum2 (- n

    \ \ \ \ \ \ \ \ \ \ \ \ 1) (+ s n))))

    (sum2 100 0)

    expression \ (sum2 100 0)

    value \ \ \ \ \ \ 5050
  </lcode>

  \;

  \<#30EA\>\<#30B9\>\<#30C8\>\<#3092\>\<#751F\>\<#6210\>\<#3059\>\<#308B\>\<#4F8B\>\<#3068\>\<#3057\>\<#3066\>fibonacci\<#6570\>\<#5217\>\<#3092\>\<#8A08\>\<#7B97\>\<#3057\>\<#3066\>\<#307F\>\<#3088\>\<#3046\>\<#3002\>

  <\lcode>
    define (fibos n p1 p2)\ 

    \ \ if = n 0\ 

    \ \ \ \ \ nil\ 

    \ \ \ \ \ cons p1 (fibos - n 1 p2 + p1 p2)

    define \ \ \ \ \ fibos

    value \ \ \ \ \ \ (lambda (n p1 p2) (if (= n 0) nil (cons

    \ \ \ \ \ \ \ \ \ \ \ \ p1 (fibos (- n 1) p2 (+ p1 p2)))))

    (fibos 10 0 1)

    expression \ (fibos 10 0 1)

    value \ \ \ \ \ \ (0 1 1 2 3 5 8 13 21 34)
  </lcode>

  \;

  <\problem>
    \ <with|font-family|tt|(intgen 1 100)>\<#306B\>\<#3088\>\<#3063\>\<#3066\>\<#81EA\>\<#7136\>\<#6570\>\<#306E\>\<#30EA\>\<#30B9\>\<#30C8\><math|
    <around|(|1 <space|0.6spc>2<space|0.6spc> 3<space|0.6spc>
    ...<space|0.6spc> 100|)>>\<#3092\>\<#4F5C\>\<#308B\>\<#95A2\>\<#6570\>
    <with|font-family|tt|(intgen m n)>\<#3092\>\<#5B9A\>\<#7FA9\>\<#305B\>\<#3088\>\<#3002\>
  </problem>

  <\problem>
    \ <with|font-family|tt|(revers lst1 nil)>\<#306B\>\<#3088\>\<#308A\>\<#3001\>\<#4E0E\>\<#3048\>\<#3089\>\<#308C\>\<#305F\>\<#30EA\>\<#30B9\>\<#30C8\><with|font-family|tt|lst1>\<#306E\>\<#8981\>\<#7D20\>\<#3092\>\<#3001\>\<#9006\>\<#9806\>\<#306B\>\<#4E26\>\<#3079\>\<#3066\>\<#8FD4\>\<#3059\>\<#95A2\>\<#6570\>
    <with|font-family|tt|(revers lst1 lst2)>\<#3092\>\<#5B9A\>\<#7FA9\>\<#305B\>\<#3088\>\<#3002\>
  </problem>

  \<#6B21\>\<#306E\>\<#4F8B\>\<#306F\>\<#7D20\>\<#56E0\>\<#6570\>\<#5206\>\<#89E3\>\<#3092\>\<#884C\>\<#3046\>\<#95A2\>\<#6570\>\<#3067\>\<#3042\>\<#308B\>\<#3002\>

  <\lcode>
    define (prmf p n)\ 

    \ \ if = n 1\ 

    \ \ \ \ \ nil\ 

    \ \ \ \ \ let q / n p let r remainder n p\ 

    \ \ \ \ \ \ \ if = r 0

    \ \ \ \ \ \ \ \ \ \ cons p (prmf p q)\ 

    \ \ \ \ \ \ \ \ \ \ (prmf + p 1 n)

    define \ \ \ \ \ prmf\ 

    value \ \ \ \ \ \ (lambda (p n) (if (= n 1) nil ((' (lambd

    \ \ \ \ \ \ \ \ \ \ \ \ a (q) ((' (lambda (r) (if (= r 0) (cons\ 

    \ \ \ \ \ \ \ \ \ \ \ \ p (prmf p q)) (prmf (+ p 1) n)))) (remai

    \ \ \ \ \ \ \ \ \ \ \ \ nder n p)))) (/ n p))))

    [ \<#5B9F\>\<#884C\>\<#4F8B\> ]

    (prmf 2 876543212)

    expression \ (prmf 2 876543212)

    value \ \ \ \ \ \ (2 2 29 2389 3163)
  </lcode>

  \;

  <subsubsection|<sikaku> \<#5F15\>\<#6570\>\<#306B\>\<#95A2\>\<#6570\>\<#3092\>\<#53D6\>\<#308B\>\<#4F8B\>\<#FF1A\>\<#30EA\>\<#30B9\>\<#30C8\>\<#64CD\>\<#4F5C\>>

  \<#95A2\>\<#6570\>\<#3092\>\<#5F15\>\<#6570\>\<#306B\>\<#53D6\>\<#308B\>\<#3053\>\<#3068\>\<#306B\>\<#3088\>\<#308A\>\<#3001\>\<#67D4\>\<#8EDF\>\<#6027\>\<#306E\>\<#9AD8\>\<#3044\>(\<#62BD\>\<#8C61\>\<#5EA6\>\<#306E\>\<#9AD8\>\<#3044\>)\<#30D7\>\<#30ED\>\<#30B0\>\<#30E9\>\<#30E0\>\<#3092\>\<#66F8\>\<#304F\>\<#3053\>\<#3068\>\<#304C\>\<#3067\>\<#304D\>\<#308B\>\<#3002\>\<#305D\>\<#306E\>\<#3088\>\<#3046\>\<#306A\>\<#4F8B\>\<#3068\>\<#3057\>\<#3066\>\<#30EA\>\<#30B9\>\<#30C8\>\<#3092\>\<#64CD\>\<#4F5C\>\<#3059\>\<#308B\>\<#4E00\>\<#822C\>\<#7684\>\<#306A\>\<#95A2\>\<#6570\>\<#3092\>\<#53D6\>\<#308A\>\<#4E0A\>\<#3052\>\<#3066\>\<#307F\>\<#3088\>\<#3046\>\<#3002\>

  <\lcode>
    define (mapapp f proc init lst)

    \ \ if = lst nil

    \ \ \ \ \ init\ 

    \ \ \ \ \ (proc (f car lst)\ 

    \ \ \ \ \ \ \ \ \ \ \ (mapapp f proc init cdr lst))
  </lcode>

  \;

  \<#4F8B\>\<#3048\>\<#3070\>\<#300C\>\<#4E0E\>\<#3048\>\<#3089\>\<#308C\>\<#305F\>\<#6570\>\<#306E\>\<#30EA\>\<#30B9\>\<#30C8\>\<#306E\>\<#4E8C\>\<#4E57\>\<#548C\>\<#3092\>\<#53D6\>\<#308B\>\<#95A2\>\<#6570\>\<#300D\>\<#306F\>\<#4E0A\>\<#306E\>\<#95A2\>\<#6570\>\<#3092\>\<#4F7F\>\<#3063\>\<#3066\>\<#6B21\>\<#306E\>\<#3088\>\<#3046\>\<#306B\>\<#66F8\>\<#3051\>\<#308B\>\<#3002\><with|font-family|tt|mapapp>
  \<#306E\>\<#5F15\>\<#6570\>\<#306B\> <with|font-family|tt|f>\<#3068\>\<#3057\>\<#3066\>\<#4E8C\>\<#4E57\>\<#3092\>\<#8A08\>\<#7B97\>\<#3059\>\<#308B\>\<#7121\>\<#540D\>\<#95A2\>\<#6570\>\<#3001\><with|font-family|tt|proc>\<#3068\>\<#3057\>\<#3066\>\<#548C\>\<#3092\>\<#53D6\>\<#308B\>\<#57FA\>\<#672C\>\<#95A2\>\<#6570\>
  <with|font-family|tt|+> \<#3001\><with|font-family|tt|init>(\<#521D\>\<#671F\>\<#5024\>)\<#3068\>\<#3057\>\<#3066\>0\<#3092\>\<#4E0E\>\<#3048\>\<#308C\>\<#3070\>\<#3088\>\<#3044\>\<#3002\>

  <\lcode>
    define (sqsum lst)\ 

    \ \ (mapapp 'lambda (x) * x x "+ 0 lst)

    [\<#5B9F\>\<#884C\>\<#4F8B\>]

    (sqsum (intgen 1 1000))

    expression \ (sqsum (intgen 1 10000))

    value \ \ \ \ \ \ 333383335000
  </lcode>

  \;

  <subsubsection|<sikaku> \<#95A2\>\<#6570\>\<#3092\>\<#8FD4\>\<#3059\>\<#95A2\>\<#6570\>>

  \<#95A2\>\<#6570\>\<#3092\>\<#8FD4\>\<#3059\>\<#95A2\>\<#6570\>\<#3082\>\<#5B9A\>\<#7FA9\>\<#3059\>\<#308B\>\<#3053\>\<#3068\>\<#304C\>\<#3067\>\<#304D\>\<#308B\>\<#3002\>\<#3057\>\<#304B\>\<#3057\>\<#3001\>Scheme\<#3084\>Common
  Lisp\<#306E\>\<#3088\>\<#3046\>\<#306B\>\<#683C\>\<#597D\>\<#826F\>\<#304F\>\<#306F\>\<#3067\>\<#304D\>\<#306A\>\<#3044\>\<#3002\>

  \<#4F8B\>\<#3048\>\<#3070\>\<#4E00\>\<#5909\>\<#6570\>\<#95A2\>\<#6570\><math|f<around|(|x|)>>\<#3068\><math|g<around|(|x|)>>\<#306E\>\<#5408\>\<#6210\>\<#95A2\>\<#6570\><math|g<around|(|f<around|(|x|)>|)>=<around|(|g\<circ\>f|)><around|(|x|)>>\<#3092\>\<#8FD4\>\<#3059\>\<#95A2\>\<#6570\>
  <with|font-family|tt|(comp f g)> \<#306F\>\<#6B21\>\<#306E\>\<#3088\>\<#3046\>\<#306B\>\<#306A\>\<#308B\>\<#3002\>

  <\lcode>
    define (comp f g)\ 

    \ \ cons "lambda\ 

    \ \ cons '(x)\ 

    \ \ cons cons cons "' cons g nil\ 

    \ \ \ \ \ \ \ cons cons cons "' cons f nil\ 

    \ \ \ \ \ \ \ \ \ \ \ \ cons 'x

    \ \ \ \ \ \ \ \ \ \ \ \ nil\ 

    \ \ \ \ \ \ \ nil\ 

    \ \ nil

    [\<#5B9F\>\<#884C\>\<#4F8B\>]

    (comp f g)

    expression \ (comp (' f) (' g))

    value \ \ \ \ \ \ (lambda (x) ((' g) ((' f) x)))

    \;

    ((comp `lambda (x) ^ x 3\ 

    \ \ \ \ \ \ \ `lambda (x) + * 2 x 1) 3)

    expression \ ((comp (' (lambda (x) (^ x 3))) (' (lamb

    \ \ \ \ \ \ \ \ \ \ \ \ da (x) (+ (* 2 x) 1)))) 3)

    value \ \ \ \ \ \ 55
  </lcode>

  \;

  \<#6700\>\<#5F8C\>\<#306E\>\<#4F8B\>\<#3067\>\<#306F\>
  <math|2*x<rsup|3>+1\|<rsub|x=3>> \<#3092\>\<#8A08\>\<#7B97\>\<#3057\>\<#3066\>\<#308B\>\<#3002\>

  \<#4E0E\>\<#3048\>\<#3089\>\<#308C\>\<#305F\>\<#95A2\>\<#6570\><math|f>\<#3092\><math|n>\<#56DE\>\<#5408\>\<#6210\>\<#3057\>\<#305F\>\<#95A2\>\<#6570\><math|<wide*|f\<circ\>f\<circ\>\<cdots\>\<circ\>f|\<wide-underbrace\>><rsub|n>>\<#3092\>\<#8FD4\>\<#3059\>Lisp\<#95A2\>\<#6570\>

  <with|font-family|tt|(fpow n f)>\<#3092\>\<#4F5C\>\<#3063\>\<#3066\>\<#307F\>\<#3088\>\<#3046\>\<#3002\>\<#5B9F\>\<#884C\>\<#4F8B\>\<#3067\>\<#306F\><math|f<around|(|x|)>=x<rsup|2>>\<#3092\>5\<#56DE\>\<#5408\>\<#6210\>\<#3057\>\<#305F\>\<#95A2\>\<#6570\>\<#3092\>\<#4F5C\>\<#308A\><math|x=2>\<#3067\>\<#306E\>\<#5024\>\<#3092\>\<#8A08\>\<#7B97\>\<#3057\>\<#3066\>\<#3044\>\<#308B\>\<#3002\>

  <\lcode>
    define (fpow n f)\ 

    \ \ if = n 0\ 

    \ \ \ \ \ 'lambda (x) x\ 

    \ \ \ \ \ (comp f (fpow - n 1 f))

    [\<#5B9F\>\<#884C\>\<#4F8B\>]

    ((fpow 5 'lambda (x) * x x) 2)

    expression \ ((fpow 5 (' (lambda (x) (* x x)))) 2)

    value \ \ \ \ \ \ 4294967296
  </lcode>

  \;

  <subsubsection|<sikaku> \<#95A2\>\<#6570\>\<#306E\>\<#81EA\>\<#5DF1\>\<#9069\>\<#7528\>>

  \<#6700\>\<#5F8C\>\<#306B\>Lisp\<#306A\>\<#3089\>\<#3067\>\<#306F\>\<#306E\>\<#8A08\>\<#7B97\>\<#3092\>\<#793A\>\<#3057\>\<#3066\>\<#304A\>\<#3053\>\<#3046\>\<#3002\>\<#6B21\>\<#306E\>\<#8A08\>\<#7B97\>\<#306F\><math|100>!\<#3092\>\<#6C42\>\<#3081\>\<#308B\>\<#3082\>\<#306E\>\<#3067\>\<#3042\>\<#308B\>\<#3002\>\<#306A\>\<#305C\>\<#8A08\>\<#7B97\>\<#3067\>\<#304D\>\<#308B\>\<#306E\>\<#304B\>\<#5206\>\<#304B\>\<#308A\>\<#307E\>\<#3059\>\<#304B\>?\<#3002\>

  <\lcode>
    define F\ 

    \ \ 'lambda (f n) if = n 0 1 * n (f f - n 1)

    expression \ F\ 

    value \ \ \ \ \ \ (lambda (f n) (if (= n 0) 1 (* n (f f (-

    \ \ \ \ \ \ \ \ \ \ \ \ \ n 1)))))

    (F F 100)

    expression \ (F F 100)

    value \ \ \ \ \ \ 9332621544394415268169923885626670049071

    \ \ \ \ \ \ \ \ \ \ \ \ 5968264381621468592963895217599993229915

    \ \ \ \ \ \ \ \ \ \ \ \ 6089414639761565182862536979208272237582

    \ \ \ \ \ \ \ \ \ \ \ \ 51185210916864000000000000000000000000
  </lcode>

  \;
</body>

<\initial>
  <\collection>
    <associate|font|modern>
    <associate|language|japanese>
    <associate|magnification|0.9>
    <associate|page-bot|20mm>
    <associate|page-even|10mm>
    <associate|page-medium|paper>
    <associate|page-odd|10mm>
    <associate|page-right|10mm>
    <associate|page-top|20mm>
    <associate|par-columns|2>
    <associate|preamble|false>
  </collection>
</initial>

<\references>
  <\collection>
    <associate|auto-1|<tuple|1|1>>
    <associate|auto-10|<tuple|1.5|1>>
    <associate|auto-11|<tuple|1.6|2>>
    <associate|auto-12|<tuple|1.7|2>>
    <associate|auto-13|<tuple|1.8|2>>
    <associate|auto-14|<tuple|1.9|3>>
    <associate|auto-2|<tuple|1.1|1>>
    <associate|auto-3|<tuple|1.2|1>>
    <associate|auto-4|<tuple|1.3|1>>
    <associate|auto-5|<tuple|1|1>>
    <associate|auto-6|<tuple|1.1|1>>
    <associate|auto-7|<tuple|1.2|1>>
    <associate|auto-8|<tuple|1.3|1>>
    <associate|auto-9|<tuple|1.4|1>>
    <associate|footnote-1|<tuple|1|1>>
    <associate|footnote-2|<tuple|2|1>>
    <associate|footnote-3|<tuple|3|1>>
    <associate|footnote-4|<tuple|4|1>>
    <associate|footnr-1|<tuple|1|1>>
    <associate|footnr-2|<tuple|2|1>>
    <associate|footnr-3|<tuple|3|1>>
    <associate|footnr-4|<tuple|4|1>>
    <associate|sq|<tuple|1|1>>
  </collection>
</references>

<\auxiliary>
  <\collection>
    <\associate|toc>
      <with|par-left|<quote|1.5fn>|Chaitin\<#5148\>\<#751F\>\<#306E\>Toy
      Lisp\<#3067\>\<#904A\>\<#3076\> \ <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-5>>

      <with|par-left|<quote|3fn>|\<blacksquare\>
      Chaitin\<#5148\>\<#751F\>\<#306E\>Toy Lisp
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-6>>

      <with|par-left|<quote|3fn>|\<blacksquare\>
      \<#7C21\>\<#5358\>\<#306A\>\<#8A08\>\<#7B97\>
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-7>>

      <with|par-left|<quote|3fn>|\<#30EA\>\<#30B9\>\<#30C8\>\<#FF1A\>\<#3000\>cons,
      \ cdr, \ car <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-8>>

      <with|par-left|<quote|3fn>|\<blacksquare\>
      \<#30EA\>\<#30B9\>\<#30D7\>\<#5F0F\>\<#3001\>\<#30A2\>\<#30C8\>\<#30E0\>\<#3001\>\<#30EA\>\<#30B9\>\<#30C8\>
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-9>>

      <with|par-left|<quote|3fn>|\<blacksquare\>
      \<#95A2\>\<#6570\>\<#3068\>\<#95A2\>\<#6570\>\<#9069\>\<#7528\>\<#3001\>\<#5F0F\>\<#306E\>\<#8A55\>\<#4FA1\>
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-10>>

      <with|par-left|<quote|3fn>|\<blacksquare\>
      \<#53CD\>\<#5FA9\>(\<#518D\>\<#5E30\>)\<#8A08\>\<#7B97\>
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-11>>

      <with|par-left|<quote|3fn>|\<blacksquare\>
      \<#5F15\>\<#6570\>\<#306B\>\<#95A2\>\<#6570\>\<#3092\>\<#53D6\>\<#308B\>\<#4F8B\>\<#FF1A\>\<#30EA\>\<#30B9\>\<#30C8\>\<#64CD\>\<#4F5C\>
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-12>>

      <with|par-left|<quote|3fn>|\<blacksquare\>
      \<#95A2\>\<#6570\>\<#3092\>\<#8FD4\>\<#3059\>\<#95A2\>\<#6570\>
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-13>>

      <with|par-left|<quote|3fn>|\<blacksquare\>
      \<#95A2\>\<#6570\>\<#306E\>\<#81EA\>\<#5DF1\>\<#9069\>\<#7528\>
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-14>>
    </associate>
  </collection>
</auxiliary>