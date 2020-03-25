---------------------------
-- Homework Assignment 2 --
---------------------------

-- Team Members: Nicholas Milford

----------------------------------
-- Exercise 1: A Stack Language --
----------------------------------

data Cmd = LD Int
	 | ADD
	 | MULT
	 | DUP

type Prog = [Cmd]

type Stack = [Int]

mkBinary :: (Int -> Int -> Int) -> Stack -> Stack
mkBinary op st = ((head st) `op` ((head . tail) st) : ((tail . tail) st))

sem :: Prog -> Stack -> Stack
sem (LD i:cmds) st = (sem cmds) (i:st)
sem (ADD:cmds) st = (sem cmds) (mkBinary (+) st)
sem (MULT:cmds) st = (sem cmds) (mkBinary (*) st)
sem (DUP:cmds) st = (sem cmds) ((head st) : st)
sem [] x = x 

------------------------------
-- Exercise 2: Stack Macros --
------------------------------

-- (a): extend the abstract syntax ro represent macro definitions and calls

data Cmd2 = LD2 Int
	  | ADD2
	  | MULT2
	  | DUP2
	  | DEF String [Cmd2]
	  | CALL String
	deriving Show

-- (b): define a new type State to represent state for the new language

type Macros = [(String, [Cmd2])]

type State = (Macros, Stack)

-- (c): define the semantics for the extended language as a function sem2

getMacro :: String -> Macros -> [Cmd2]
getMacro call ((nam, prg):ms)
			| call == nam = prg
			| otherwise = getMacro call ms
getMacro call [] = error ("Undefined Macro: " ++ call)

mapsnd :: (Stack -> Stack) -> State -> State
mapsnd f (mac, stac) = (mac, f stac)

mapfst :: (Macros -> Macros) -> State -> State
mapfst f (mac, stac) = (f mac, stac)

sem2 :: [Cmd2] -> State -> State
sem2 (LD2 i:cmds) st = (sem2 cmds) (mapsnd (i:) st)
sem2 (ADD2:cmds) st = (sem2 cmds) (mapsnd (mkBinary (+)) st)
sem2 (MULT2:cmds) st = (sem2 cmds) (mapsnd (mkBinary (*)) st)
sem2 (DUP2:cmds) st = (sem2 cmds) (mapsnd (\stk -> (head stk):stk) st)
sem2 (DEF nam prog:cmds) st = (sem2 cmds) (mapfst ((nam, prog):) st)
sem2 (CALL nam:cmds) st = (sem2 cmds) (sem2 (getMacro nam (fst st)) st)
sem2 [] st = st

---------------------------
-- Exercise 3: Mini Logo --
---------------------------

data LogoCmd = Pen Mode
	     | MoveTo Int Int
	     | Seq LogoCmd LogoCmd

data Mode = Up | Down

type LogoState = (Mode, Int, Int)
type Line = (Int, Int, Int, Int)
type Lines = [Line]

semS :: LogoCmd -> LogoState -> (LogoState, Lines)
semS (Pen mod) (_, x, y) = ( (mod, x, y), [] )
semS (MoveTo xn yn) (Up, x, y) = ( (Up, xn, yn), [] )
semS (MoveTo xn yn) (Down, x, y) = ( (Down, xn, yn), [(x, y, xn, yn)] )
semS (Seq cmd1 cmd2) st = (s2, ls1 ++ ls2)
			where (s1, ls1) = semS cmd1 st
			      (s2, ls2) = semS cmd2 s1

sem' :: LogoCmd -> Lines
sem' cmd = snd (semS cmd (Up, 0, 0))
