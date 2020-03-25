
type Name = String

data Type = Int | Bool | String 
	  | Err String
	  | Fn Type Type
	  deriving (Eq, Show)

isErr :: Type -> Bool
isErr (Err _) = True
isErr _ = False

type Decl = (Type, Name)

data Expr = Val Val 
	  | Var Name
	  | Let Decl Expr Expr
	  | Fun Decl Expr
	  | App Expr Expr
	  | Plus Expr Expr
	  | Less Expr Expr
	  | Not Expr
	  | And Expr Expr
	  | Print Expr
	  | Cat Expr Expr

data Val = I Int
	 | S String
	 | B Bool
	 | C Name Expr Stack

instance Show Val where
  show (S str) = str
  show _ = "error"

mergeT :: Type -> Type -> Type
mergeT (Err s1) (Err s2) = Err (s1++"\n"++s2)
mergeT (Err s) _ = Err s
mergeT _ (Err s) = Err s
mergeT x y | x == y = x
	      | otherwise = Err (show x++", "++show y++": Incompatible types")

assertT :: Type -> Type -> Type
assertT _ (Err s) = Err s
assertT x y | x == y = x
	    | otherwise = Err ("Expected type "++show x++", got type "++show y)

type Stack = [(Name, Val)]

eval :: Stack -> Expr -> Val
eval _ (Val v) = v
eval s (Var n) = case lookup n s of
		   Just v -> v
		   Nothing -> I 0 --this case never happens because TC also checks variables
eval s (Let (_, n) eb eu) = eval ((n, eval s eb):s) eu
eval s (Fun (_, n) e) = C n e s
eval s (App f e') = case eval s f of
		     C n e s' -> eval ((n, eval s e'):s') e
eval s (Plus e1 e2) = I (v1 + v2) where (I v1, I v2) = (eval s e1, eval s e2)
eval s (Less e1 e2) = B (v1 < v2) where (I v1, I v2) = (eval s e1, eval s e2)
eval s (Not e) = B (not v) where (B v) = (eval s e)
eval s (And e1 e2) = B (v1 && v2) where (B v1, B v2) = (eval s e1, eval s e2)
eval s (Print e) = case eval s e of
		     I i -> S(show i)
		     S s -> S(s)
		     B b -> S(show b)
eval s (Cat e1 e2) = S (v1 ++ v2) where (S v1, S v2) = (eval s e1, eval s e2)

type Tstack = [(Name, Type)]

tc :: Tstack -> Expr -> Type
tc _ (Val v) = case v of
		 I _ -> Int
		 S _ -> String
		 B _ -> Bool
tc s (Var n) = case lookup n s of
		 Just v -> v
		 Nothing -> Err (show n++": not declared")
tc s (Let (t, n) eb eu) = if t == (tc s eb) 
			  then tc ((n, t):s) eu 
			  else Err (show t++n++": does not match assigned type")
tc s (Fun (t, n) e) = Fn t (tc ((n, t):s) e)
tc s (App fn e) = if tc s e == ti then to else Err (show ti++"Does not match argument type")
		  where Fn ti to = tc s fn
tc s (Plus e1 e2) = assertT Int (mergeT (tc s e1) (tc s e2))
tc s (Less e1 e2) = assertT Int (mergeT (tc s e1) (tc s e2)) 
tc s (Not e) = if t == Bool then Bool else Err (show t++": cannot apply NOT") where t = tc s e
tc s (And e1 e2) = case (tc s e1, tc s e2) of
		   (Bool, Bool) -> Bool
		   (a, b) -> Err (show a++", "++show b++": cannot compute AND")
tc s (Print e) = if isErr t then Err (show t++": cannot be printed") else String where t = tc s e
tc s (Cat e1 e2) = case (tc s e1, tc s e2) of
		   (String, String) -> String
		   (a, b) -> Err (show a++", "++show b++": cannot concatenate")

sem :: Expr -> Maybe Val
sem e = case (tc [] e) of
	Err _ -> Nothing
	otherwise -> Just (eval [] e)
