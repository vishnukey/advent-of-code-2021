module Main where

import Input

{-input = [
        199, 
        200, 
        208, 
        210, 
        200, 
        207, 
        240, 
        269, 
        260, 
        263 
        ]-}
rest = tail input

pairs = zip input rest

diffs = map (uncurry . flip $ (-)) pairs

incs = map sign diffs

solution = sum incs

-- part 1

solution' :: [Int] -> Int
solution' xs = sum . map (\x -> if x > 0 then 1 else 0) . map (uncurry . flip $ (-)) $ zip xs (tail xs) 

-- part 2
chunk :: Int -> [Int] -> [Int]
chunk n xs 
        | length xs < n = []
        | otherwise = (sum . take n $ xs) : (chunk n $ tail xs)

solution1 = solution' input

solution2 = solution' . chunk 3 $ input

sign :: Int -> Int
sign x
        | x > 0 = 1
        | x < 0 = 0
        | x == 0 = 0

main :: IO ()
main = undefined
