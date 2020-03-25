{-# LANGUAGE MultiParamTypeClasses #-}

class Lang a b where
	sem :: a -> b

data Bin = One | Zero
	   | Cat Bin Bin
	   | Not Bin

instance Lang Shape [Bool] where
	sem :: Shape -> [Bool]
	sem One = [True]
	sem Zero = [False]
	sem (Cat b1 b2) = (sem b1) ++ (sem b2)
	sem (Not b) = map not (sem b)

data Lang a _ => WithVars a = Expr a
			    | Let String a a
			    | Ref String

instance Lang (WithVars a, [(String, b)]) b where
	sem :: (WithVars a, [(String, b)]) -> b
	sem ((Expr xpr), s) = sem xpr
	sem ((Let n b u), s) = sem (u, (n, sem b):s)
	sem ((Ref n), s) = --this isn't going to work
