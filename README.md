# README

## 目的
G.J.Chaitin氏の三部作

* The Limits of Mathematics
* Unkownable
* Exploring Randomness

に使用されている lisp (C言語版) は1000行ほどのプログラムである。  
このソースを解きほぐすために、ソースが長くなることは気にせず、ファイル分割してより可読性を高めようとしてみた。

# オリジナルからの変更点

* Chaitin のオリジナル版では 

  `define <name> <body>`

  において、body は評価されずに name に束縛されるが、この lisp では評価
  した後、束縛する。