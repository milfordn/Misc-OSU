import Data.Set (Set, singleton, union)
import qualified Data.Set as Set

vals = [(3, "Fizz"), (5, "Buzz"), (4, "Spaz"), (11, "Wux")]

main :: IO()
--main = putStrLn $ foldr (++) "" $ map ((++) "\n" . fbSimple) $ [1, 2..100]
--main = putStrLn $ unlines $ map (fbComplex vals) $ [1, 2..100]
main = (putStrLn . show) (pown ['a', 'b', 'c'] 3)

fbSimple :: Int -> String
fbSimple i =
	if i `rem` 15 == 0 then "FIZZBUZZ"
	else if i `rem` 3 == 0 then "FIZZ"
	else if i `rem` 5 == 0 then "BUZZ"
	else show i

ifEmpty :: [a] -> [a] -> [a]
ifEmpty def [] = def
ifEmpty _ v = v

fbComplex :: [(Int, String)] -> Int -> String
fbComplex mapping i = 
	foldr (++) "" $ ifEmpty [show i] $ map snd $ filter ((\x -> i `mod` x == 0) . fst) $ mapping

--data ntree a = Val a | Sub [a]

{-
subdivide :: (a, a) -> [a] -> (ntree a, [a])
subdivide _ [] = [], []
subdivide (o, c) (x:xs)
	| x == o = 
		let (c, r) = subdivide xs in
		let (c2, r2) = subdivide r in
		(Sub c : c2, r2)
	| x == c = (Sub [], xs)
	| _ = 
		let (c, r) = subdivide xs in
		(Val x : c, r)
-}

expand :: [a] -> [[a]] -> [[a]]
expand [] _ = []
expand (x:xs) l = (map (x:) l) ++ (expand xs l)

pown :: [a] -> Int -> [[a]]
pown _ 0 = [[]];
pown l n = []:expand l (pown l (n-1))
