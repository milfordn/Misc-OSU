data Type = BOOL
	  | INT
	  | NDET --Undetermined type, used for empty list
	  | LIST Type
	  deriving (Eq, Show)

data Expr = N Int
	  | B Bool
	  | SINGLETON Expr
	  | EMPTY
	  | CONS Expr Expr
	  | CAT Expr Expr
	  | HEAD Expr
	  | TAIL Expr

data Dom = Val (Either Int Bool) 
	 | Lst [Dom]
	 deriving Show

sem :: Expr -> Dom
sem (N i) = Val (Left i)
sem (B b) = Val (Right b)
sem EMPTY = Lst []
sem (SINGLETON xpr) = Lst [sem xpr]
sem (CONS xpr1 xpr2) = Lst ( (sem xpr1) : v2 ) where Lst v2 = sem xpr2
sem (CAT xpr1 xpr2) = Lst (v1 ++ v2) where Lst v1 = sem xpr1
					   Lst v2 = sem xpr2
sem (HEAD xpr) = head v where Lst v = sem xpr
sem (TAIL xpr) = Lst (tail v) where Lst v = sem xpr

-- returns true of t1 is of type LIST t2
listOf :: Type -> Type -> Bool
listOf (LIST t1) t2 = t1 == t2
listOf (NDET) _ = True
listOf _ _ = False

-- merge compatible types if possible
compatMerge :: Type -> Type -> Maybe Type
compatMerge NDET t2 = Just t2
compatMerge t1 NDET = Just t1
compatMerge t1 t2 | t1 == t2 = Just t1
compatMerge _ _ = Nothing

tc :: Expr -> Maybe Type
tc (N _) = Just INT
tc (B _) = Just BOOL
tc EMPTY = Just NDET
tc (SINGLETON xpr) = tc xpr >>= (Just . LIST)
tc (CONS xpr1 xpr2) = tc xpr1 >>= (\t1 ->
		      tc xpr2 >>= (\t2 ->
		      if listOf t2 t1 then Just (LIST t1) else Nothing))
tc (CAT xpr1 xpr2) = tc xpr1 >>= (\t1 ->
		     tc xpr2 >>= (\t2 ->
		     compatMerge t1 t2))
tc (HEAD xpr) = case tc xpr of
		Just (LIST t) -> Just t
		otherwise -> Nothing
tc (TAIL xpr) = case tc xpr of
		Just (LIST t) -> Just (LIST t)
		otherwise -> Nothing

statTc :: Expr -> Maybe Dom
statTc xpr = case tc xpr of
	     Just _ -> Just (sem xpr)
	     Nothing -> Nothing 
