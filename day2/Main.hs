module Main where

import Input

data Info = Info { dist :: Int, depth :: Int, aim :: Int}

update :: Info -> Command -> Info
update (Info x y aim) cmd = case cmd of
        Forward dx -> Info (x + dx) (y + dx * aim) aim
        Up daim      -> Info x y (aim - daim)
        Down daim    -> Info x y (aim + daim)

solution :: Info -> [Command] -> Int
solution start = (\(Info x y _) -> x * y) . foldl update start
                

main :: IO ()
main = undefined
