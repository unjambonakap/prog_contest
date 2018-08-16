import Control.Applicative
import Control.Monad
import Data.List
import qualified Data.Set as S
import Debug.Trace

data Clause = Clause (Maybe Int) (S.Set Int) deriving Show

chunks :: Int -> [a] -> [[a]]
chunks n = map (take n) . (takeWhile (not . null)) . iterate (drop n)

clausify :: [[Int]] -> Clause
clausify = foldr addTerm (Clause Nothing S.empty)
  where addTerm [flavor, 0] (Clause yes nos) = Clause yes (S.insert flavor nos)
        addTerm [flavor, 1] (Clause yes nos) = Clause (Just flavor) nos

solve :: Int -> [Clause] -> String
solve n clauses = solveWithAssignments [] clauses
  where solveWithAssignments s c = case [ yes | clause@(Clause yes nos) <- c, S.null nos ] of
          Nothing:ys -> "IMPOSSIBLE"
          (Just y):ys -> solveWithAssignments (y:s) [ Clause yes (S.filter (/= y) nos) | Clause yes nos <- c, yes /= Just y ]
          [] -> intercalate " " $ map (\x -> if x `elem` s then "1" else "0") [1..n]

main = (enumFromTo 1 <$> readLn) >>= mapM_ do1
  where do1 caseno = do
              n <- readLn
              m <- readLn
              clauses <- replicateM m $ clausify . chunks 2 . map read . tail . words <$> getLine
              putStrLn $ "Case #" ++ show caseno ++ ": " ++ solve n clauses
