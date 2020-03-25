type Vector a b = [a]

data S a = UnusedS
data Z = UnusedZ

empty :: Vector a Z
empty = []

cons :: a -> Vector a b -> Vector a (S b)
cons a v = a:v

vtail :: Vector a (S b) -> Vector a b
vtail (_:xs) = xs

vhead :: Vector a (S b) -> a
vhead (x:_) = x
