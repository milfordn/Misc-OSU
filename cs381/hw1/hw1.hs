-- HW1
-- Team Members: Nicholas Milford

-------------------
-- 	Exercise 1: Mini Logo
-------------------

-- 		A: Define the abstract syntax for Mini Logo as a Haskell data type
-- mode ::= up | down
data Mode = Up | Down
	deriving Show

-- pos ::= num::int | name::string
data Pos = Num Int | Name String
	deriving Show

-- pars ::= name::string, pars | name::string
type Pars = [String]

-- vals ::= num::int, vals | num::int
type Vals = [Int]

-- cmd ::= pen::mode
-- 	 | moveto::(pos, pos)
-- 	 | def::(string, pars, cmd)
-- 	 | call::(string, vals)
-- 	 | then::(cmd, cmd)
data Cmd = Pen Mode
	 | Moveto Pos Pos
	 | Def String Pars Cmd
	 | Call String Vals
	 | Then Cmd Cmd
	deriving Show

--		B: Write a Mini Logo macro vector that draws a line from a given position (x1, y1) to (x2, y2)
--		def vector (x1, y1, x2, y2) 
--			pen up;
--			moveto (x1, y1);
--			pen down;
--			moveto (x2, y2);
vector = Def "vector" ["x1", "y1", "x2", "y2"] (
		(Pen Up) `Then` 
		(Moveto (Name "x1") (Name "y1")) `Then` 
		(Pen Down) `Then`
		(Moveto (Name "x2") (Name "y2"))
	)

--		C: Define a Haskell function steps that constructs a Mini Logo program which draws a stair of n steps
steps :: Int -> Cmd
steps n = (Pen Up) `Then` (Moveto (Num n) (Num n)) `Then` (Pen Down) `Then` (isteps n)
	where isteps :: Int -> Cmd
	      isteps 0 = Pen Up
	      isteps n = (Moveto (Num (n-1)) (Num n)) `Then` (Moveto (Num (n-1)) (Num (n-1))) `Then` (isteps (n-1))

-------------------
--	Exercise 2: Digital Circuit Design Language
-------------------

--		A: Define the abstract syntax for the above language as a Haskell data type
-- gateFn ::= and | or | xor | not
data GateFn = And | Or | Xor | Not

-- gates ::= gates(num, gateFn, gates) | empty
type Gates = [(Int, GateFn)]

-- links ::= link(num, num, num, num, links) | empty
type Links = [(Int, Int, Int, Int)]

-- curcuit ::= circuit(gates, links)
type Circuit = (Gates, Links)

--		B: Represent the half adder circuit as a haskell data type value
halfadder :: Circuit
halfadder = ([(1, Xor), (2, And)], [(1, 1, 2, 1), (1, 2, 2, 2)])

--		C: Define a Haskell function that implements a pretty printer for the abstract syntax
diCiDL_PP :: Circuit -> String
diCiDL_PP (gs, ls) = (foldr (++) "" . map gatesPP) gs ++ (foldr (++) "" . map linksPP) ls
	where   gatesPP (i, And) = show i ++ ":and;\n"
		gatesPP (i, Or) = show i ++ ":or;\n"
		gatesPP (i, Xor) = show i ++ ":xor;\n"
		gatesPP (i, Not) = show i ++ ":not;\n"
		linksPP (g1, l1, g2, l2) = "from " ++ show g1 ++ "." ++ show l1 ++ " to " ++ show g2 ++ "." ++ show l2 ++ ";\n"
-------------------
--	Exercise 3: Designing Abstract Suntax
-------------------

-- first abstract syntax
data Expr = N Int
	  | Plus Expr Expr
	  | Times Expr Expr
	  | Neg Expr
	deriving Show

-- second abstract syntax
data Op = Add | Multiply | Negate
	deriving Show
data Exp = Number Int | Apply Op [Exp]
	deriving Show

--		A: Represent the expression -(3+4)*7 in the alternative abstract syntax


expr_a = Multiply `Apply` [ (Negate `Apply` [ (Add `Apply` [(Number 3), (Number 4)])]), (Number 7)]

--		B: What are the advantages or disadvantages of either representation?
--	The main advantage of the second representation is that only one rule application is needed to represent 
--	combining many numbers with one operation, whereas with the first, combining n numbers in the same way
--	requires n-1 rule applications.
--
--	The disadvantage of the second representation is that it can be more difficult to interpret. The behavior
--	of Apply changes depending on the operation. For example, Applying Negate to an expression list maps
--	multiplication of -1 to each member, resulting in a new list of numbers, while Add or Multiply fold over
--	the expression list with an operation, leaving just one number.

-- 		C: Define a function translate that translates expressions from the first syntax to the second
translate :: Expr -> Exp
translate (N n) = Number n
translate (Neg xpr) = Apply Negate [translate xpr]
translate (Plus xpr1 xpr2) = Apply Add [(translate xpr1), (translate xpr2)]
translate (Times xpr1 xpr2) = Apply Multiply [(translate xpr1), (translate xpr2)]
