module ListLanguage where

type Name = String

data Syntax = Const Int
	    | Cons Syntax Syntax
	    | Empty
	    | Head Syntax
	    | Tail Syntax
	    | List [Syntax]
	    | Fun Name Syntax
	    | Let Name Syntax Syntax
