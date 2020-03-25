-----------------------
-- Homework 3: Types --
-----------------------

-- Team Members: Nicholas Milford

import Data.Maybe

-----------------------------------------------------------
-- Exercise 1: Rank-based type system for Stack language --
-----------------------------------------------------------

data Cmd = LD Int
	 | ADD | MULT | DUP | INC | SWAP
	 | POP Int

type Prog = [Cmd]

type Rank = Int
type CmdRank = (Int, Int)

--	(a) Use Rank and CmdRank to define a function rankP

rankC :: Cmd -> CmdRank
rankC (LD _) = (0, 1)
rankC ADD = (2, 1)
rankC MULT = (2, 1)
rankC DUP = (1, 2)
rankC INC = (1, 1)
rankC SWAP = (1, 1)
rankC (POP i) = (i, 0)

rank :: [CmdRank] -> Rank -> Maybe Rank
rank [] rnk = Just rnk
rank ((cin, cout):cmds) rnk = if rnk < cin then Nothing else rank cmds (rnk - cin + cout)

rankP :: Prog -> Maybe Rank
rankP prg = rank (map rankC prg) 0

--	(b) define a function semStatTC for evaluating stack programs

type Stack = [Int]

mkBinary :: (Int -> Int -> Int) -> Stack -> Stack
mkBinary op st = ((head st) `op` ((head . tail) st) : ((tail . tail) st))

sem :: Prog -> Stack -> Stack
sem (LD i:cmds) st = (sem cmds) (i:st)
sem (ADD:cmds) st = (sem cmds) (mkBinary (+) st)
sem (MULT:cmds) st = (sem cmds) (mkBinary (*) st)
sem (DUP:cmds) st = (sem cmds) (head st : st)
sem (INC:cmds) st = (sem cmds) ((succ . head) st : (tail st))
sem (SWAP:cmds) st = (sem cmds) ((head . tail) st : (head st) : (tail . tail) st)
sem (POP 0:cmds) st = (sem cmds) st
sem (POP i:cmds) st = (sem (POP (i-1):cmds)) (tail st)
sem [] r = r

semStatTC :: Prog -> Stack -> Maybe Stack
semStatTC prg stk | isJust (rankP prg) = Just (sem prg stk)
	          | otherwise = Nothing

-- I built the simplified version of sem by mistake before writing semStatTc, but the
-- sem function that I was expected to write (Prog -> Maybe Stack -> Maybe Stack)
-- would have been simplified to the one written above, because the static type
-- checker would confirm that the program will run without errors before running it.

--------------------------------
-- Exercise 2: Shape Language --
--------------------------------

data Shape = X
	   | TD Shape Shape
	   | LR Shape Shape
	deriving Show

type BBox = (Int, Int)

--	(a): Define a type checker for the Shape language as a Haskell Function

bbox :: Shape -> BBox
bbox X = (1, 1)
bbox (TD sh1 sh2) = (max x1 x2, y1 + y2)
	where (x1, y1) = bbox sh1
	      (x2, y2) = bbox sh2
bbox (LR sh1 sh2) = (x1 + x2, max y1 y2)
	where (x1, y1) = bbox sh1
	      (x2, y2) = bbox sh2

--	(b): Define a type checker for the Shape language that only allows rectangular shapes

rect :: Shape -> Maybe BBox
rect X = Just (1, 1)
rect (TD sh1 sh2) = rect sh1 >>= (\(x1, y1) -> 
		    rect sh2 >>= (\(x2, y2) -> 
		    if x1 == x2 then Just (x1, y1 + y2) else Nothing)) 
rect (LR sh1 sh2) = rect sh1 >>= (\(x1, y1) -> 
		    rect sh2 >>= (\(x2, y2) ->
		    if y1 == y2 then Just (x1 + x2, y1) else Nothing))

-----------------------------------------
-- Exercise 3: Parametric Polymorphism --
-----------------------------------------

--	(a): Compare the types of two functions f and g

--	f :: [a] -> a -> [a]
--	g :: [a] -> b -> [b]

--	f has its type because in a statically typed language (haskell), the two branches
--	of an if statement must return the same type. The two possible branches are [y] 
--	and x, so the type of x must be equal to the type of [y].
--
--	g, on the other hand, does not use the variable x in its output, and therefore is
--	polymorphic in regards to its second argument and output type. 

--	(b): find a simple definition for a function h :: [b] -> [(a, b)] -> [b]

h bs abs = (map snd abs) ++ bs

--	(c): find a simple definition for a function k :: (a -> b) -> ((a -> b) -> a) -> b

k fn1 fn2 = fn1 (fn2 fn1)

--	(d) Can you define a function of type a -> b? Explain

--	No, because any function a -> b would need outside knowledge of type b to construct
--	a new value of type b, but having that knowledge would constrain what type b could
--	be, limiting its generality. The other solution would be to use type a to create a
--	type b, but that requires another generic function of type a -> b, which is where 
--	we started.
